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
    switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) {
        
        case GPIO_MULTIPLE_GPIOA_INT_IIDX:
            if(DL_GPIO_readPins(GPIO_KEYS_PORT, GPIO_KEYS_PIN_26_PIN) > 0)
            {
                nextway = -1;
                while(DL_GPIO_readPins(GPIO_KEYS_PORT, GPIO_KEYS_PIN_26_PIN)>0);
            }
            else if(DL_GPIO_readPins(GPIO_KEYS_PORT, GPIO_KEYS_PIN_25_PIN) > 0)
            {
                nextway =  1;
                while(DL_GPIO_readPins(GPIO_KEYS_PORT, GPIO_KEYS_PIN_25_PIN)>0);
            }
            else if(DL_GPIO_readPins(GPIO_KEYS_PORT, GPIO_KEYS_PIN_24_PIN) > 0)
            {
                nextway =  2;
                while(DL_GPIO_readPins(GPIO_KEYS_PORT, GPIO_KEYS_PIN_24_PIN)>0);
            }
            else if(DL_GPIO_readPins(GPIO_KEYS_PORT, GPIO_KEYS_PIN_22_PIN) > 0)
            {
                nextway =  3;
                while(DL_GPIO_readPins(GPIO_KEYS_PORT, GPIO_KEYS_PIN_22_PIN)>0);
            }
            
            if(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1) == GPIO_MPU6050_PIN_INT_IIDX)Read_Quad();
            break;
            
        default:
            break;    
    }
}