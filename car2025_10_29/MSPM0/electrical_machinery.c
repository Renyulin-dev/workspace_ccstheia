#include "electrical_machinery.h"
#include "ti_msp_dl_config.h"
#include "uart.h"
#include "draw.h"

int MIN = 150;
int MAX = 350;

int L, R;

int limit_max(int input, int MAX_OUTPUT){
    input = (input > +MAX_OUTPUT) ? +MAX_OUTPUT : input;
    input = (input < -MAX_OUTPUT) ? -MAX_OUTPUT : input;
    return input;
}

int limit_min(int input, int MIN_OUTPUT){
    if(input < +MIN_OUTPUT && input > -MIN_OUTPUT)input = (input >0) ? +MIN_OUTPUT : -MIN_OUTPUT;
    return input;
}

void car_run(int speed, int difference){

    // if(speed != 0 || difference != 0)printf("L : %d  R : %d\r\n",(speed != 0 || difference != 0) ? limit_min(limit_max(speed - difference,MAX),MIN) : 0, (speed != 0 || difference != 0) ? limit_min(limit_max(speed + difference, MAX),MIN) : 0);
    if(speed + difference >= 0){
        DL_TimerG_setCaptureCompareValue(PWM_R1_INST, (speed != 0 || difference != 0) ? limit_min(limit_max(speed + difference, MAX),MIN) : 0, GPIO_PWM_R1_C1_IDX);
        DL_TimerA_setCaptureCompareValue(PWM_R2_INST, 0, GPIO_PWM_R2_C1_IDX);
        R=(speed != 0 || difference != 0) ? limit_min(limit_max(speed + difference, MAX),MIN) : 0;
    }
    else{
        DL_TimerG_setCaptureCompareValue(PWM_R1_INST, 0, GPIO_PWM_R1_C1_IDX);
        DL_TimerA_setCaptureCompareValue(PWM_R2_INST, (speed != 0 || difference != 0) ? limit_min(limit_max(-speed - difference,MAX),MIN) : 0, GPIO_PWM_R2_C1_IDX);
        R=-(speed != 0 || difference != 0) ? limit_min(limit_max(-speed - difference,MAX),MIN) : 0;
    } 
    if(speed - difference >= 0){ 
        DL_TimerG_setCaptureCompareValue(PWM_L1_INST, (speed != 0 || difference != 0) ? limit_min(limit_max(speed - difference,MAX),MIN) : 0,GPIO_PWM_L1_C1_IDX);
        DL_TimerA_setCaptureCompareValue(PWM_L2_INST, 0, GPIO_PWM_L2_C1_IDX);
        L=-(speed != 0 || difference != 0) ? limit_min(limit_max(speed - difference,MAX),MIN) : 0;
    } 
    else{ 
        DL_TimerG_setCaptureCompareValue(PWM_L1_INST, 0, GPIO_PWM_L1_C1_IDX);
        DL_TimerA_setCaptureCompareValue(PWM_L2_INST, (speed != 0 || difference != 0) ? limit_min(limit_max(difference - speed,MAX),MIN) : 0, GPIO_PWM_L2_C1_IDX);
        L=(speed != 0 || difference != 0) ? limit_min(limit_max(difference - speed,MAX),MIN) : 0;
    } 
}

void car_stop(){
    DL_TimerG_setCaptureCompareValue(PWM_R1_INST, 999, GPIO_PWM_R1_C1_IDX);
    DL_TimerA_setCaptureCompareValue(PWM_R2_INST, 999, GPIO_PWM_R2_C1_IDX);
    DL_TimerG_setCaptureCompareValue(PWM_L1_INST, 999, GPIO_PWM_L1_C1_IDX);
    DL_TimerA_setCaptureCompareValue(PWM_L2_INST, 999, GPIO_PWM_L2_C1_IDX);
}