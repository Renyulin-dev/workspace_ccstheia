#include "ti_msp_dl_config.h"
#include "interrupt.h"
#include "clock.h"
#include "mpu6050.h"

int nextway=0;

static ENCODER_RES motor_encoder;

//获取编码器的值
int get_encoder_count(void)
{
	return motor_encoder.count;
}
//获取编码器的方向
ENCODER_DIR get_encoder_dir(void)
{
	return motor_encoder.dir;
}
volatile long long get_encoder_temp_count(void)
{
	return motor_encoder.temp_count;
}


void SysTick_Handler(void)
{
    tick_ms++;
}

void TIMER_TICK_INST_IRQHandler(void)
{
	//20ms归零中断触发
	if( DL_TimerG_getPendingInterrupt(TIMER_TICK_INST) == DL_TIMER_IIDX_ZERO )
	{
		motor_encoder.count = motor_encoder.temp_count;
        //确定方向
        motor_encoder.dir = ( motor_encoder.count >= 0 ) ? FORWARD : REVERSAL;
        motor_encoder.temp_count = 0;//编码器计数值清零
	}
}

void GROUP1_IRQHandler(void)
{
    // pins affected: ["KEY2","KEY3","PIN_INT"]
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, 
        GPIO_KEYS_KEY2_PIN | GPIO_KEYS_KEY3_PIN | GPIO_MPU6050_PIN_INT_PIN |
        GPIO_ENCODER_E1A_PIN | GPIO_ENCODER_E1B_PIN);

    if ((gpioA & GPIO_KEYS_KEY2_PIN) == GPIO_KEYS_KEY2_PIN){
        nextway = 1;
        DL_GPIO_clearInterruptStatus(GPIO_KEYS_KEY2_PORT, GPIO_KEYS_KEY2_PIN);
    }

    if ((gpioA & GPIO_KEYS_KEY3_PIN) == GPIO_KEYS_KEY3_PIN){
        nextway = 2;
        DL_GPIO_clearInterruptStatus(GPIO_KEYS_KEY3_PORT, GPIO_KEYS_KEY3_PIN);
    }

    if ((gpioA & GPIO_MPU6050_PIN_INT_PIN) == GPIO_MPU6050_PIN_INT_PIN){
        Read_Quad();
        DL_GPIO_clearInterruptStatus(GPIOB, GPIO_MPU6050_PIN_INT_PIN);
    }

    if((gpioA & GPIO_ENCODER_E1A_PIN) == GPIO_ENCODER_E1A_PIN)
	{
		//如果在A相上升沿下，B相为低电平
		if(!DL_GPIO_readPins(GPIO_ENCODER_E1B_PORT,GPIO_ENCODER_E1B_PIN))
		{
			motor_encoder.temp_count--;
		}
		else
		{
			motor_encoder.temp_count++;
		}
        DL_GPIO_clearInterruptStatus(GPIOA,GPIO_ENCODER_E1A_PIN|GPIO_ENCODER_E1B_PIN);
	}//编码器B相上升沿触发
	else if((gpioA & GPIO_ENCODER_E1B_PIN)==GPIO_ENCODER_E1B_PIN)
	{
		//如果在B相上升沿下，A相为低电平
		if(!DL_GPIO_readPins(GPIO_ENCODER_E1A_PORT,GPIO_ENCODER_E1A_PIN))
		{
			motor_encoder.temp_count++;
		}
		else
		{
			motor_encoder.temp_count--;
		}
        DL_GPIO_clearInterruptStatus(GPIOA,GPIO_ENCODER_E1A_PIN|GPIO_ENCODER_E1B_PIN);
	}

    // pins affected by this interrupt request:["KEY1","KEY4"]
    uint32_t gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB,
        GPIO_KEYS_KEY1_PIN | GPIO_KEYS_KEY4_PIN);

    if ((gpioB & GPIO_KEYS_KEY1_PIN) == GPIO_KEYS_KEY1_PIN){
        nextway = -1;
        DL_GPIO_clearInterruptStatus(GPIO_KEYS_KEY1_PORT, GPIO_KEYS_KEY1_PIN);
    }

    if ((gpioB & GPIO_KEYS_KEY4_PIN) == GPIO_KEYS_KEY4_PIN){
        nextway = 3;
        DL_GPIO_clearInterruptStatus(GPIO_KEYS_KEY4_PORT, GPIO_KEYS_KEY4_PIN);
    }
}