#include "ti_msp_dl_config.h"
#include "interrupt.h"
#include "clock.h"
#include "mpu6050.h"

int nextway=0;

void SysTick_Handler(void)
{
    tick_ms++;
}


void GROUP1_IRQHandler(void)
{
    // pins affected: ["KEY2","KEY3","PIN_INT"]
    uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, 
        GPIO_KEYS_KEY2_PIN | GPIO_KEYS_KEY3_PIN | GPIO_MPU6050_PIN_INT_PIN);

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