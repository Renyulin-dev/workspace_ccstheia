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
    switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1))
    {
        case DL_INTERRUPT_GROUP1_IIDX_GPIOA:
            switch (DL_GPIO_getPendingInterrupt(GPIOA)) {
                case GPIO_KEYS_KEY2_IIDX:
                    nextway = 1;
                    break;
                case GPIO_KEYS_KEY3_IIDX:
                    nextway = 2;
                    break;
                case GPIO_MPU6050_PIN_INT_IIDX:
                    Read_Quad();
                    break;
                case GPIO_ENCODER_E1A_IIDX:
                    if(!DL_GPIO_readPins(GPIOA, GPIO_ENCODER_E1B_PIN))
                    {
                        motor_encoder.temp_count--;
                    }
                    else
                    {
                        motor_encoder.temp_count++;
                    }
                    break;
                case GPIO_ENCODER_E1B_IIDX:
                	if(!DL_GPIO_readPins(GPIOA, GPIO_ENCODER_E1A_PIN))
                    {
                        motor_encoder.temp_count++;
                    }
                    else
                    {
                        motor_encoder.temp_count--;
                    }
                    break;
                default:
                    break;
            }
        case DL_INTERRUPT_GROUP1_IIDX_GPIOB:
            switch (DL_GPIO_getPendingInterrupt(GPIOB))
            {
                case GPIO_KEYS_KEY1_IIDX:
                    nextway = -1;
                    break;
                case GPIO_KEYS_KEY4_IIDX:
                    nextway = 3;
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}