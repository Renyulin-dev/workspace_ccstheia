#include "electrical_machinery.h"

void car_speed(int speed)
{
    if(speed>99)speed = 99;
    if(speed<0)speed=0;
    DL_TimerG_setCaptureCompareValue(PWMA_INST, 99-speed, GPIO_PWMA_C0_IDX);
}
