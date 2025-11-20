#include "electrical_machinery.h"
#include "ti_msp_dl_config.h"
#include "uart.h"
#include "draw.h"
#include "interrupt.h"

int MAX=0;
int MIN=0;

float Velcity_Kp=2,  Velcity_Ki=1,  Velcity_Kd;

int Velocity_A(int TargetVelocity, int CurrentVelocity)
{  
    int Bias;  //定义相关变量
		static int ControlVelocity, Last_bias; //静态变量，函数调用结束后其值依然存在
		
		Bias=TargetVelocity-CurrentVelocity; //求速度偏差
		
		ControlVelocity+=Velcity_Kp*(Bias-Last_bias)+Velcity_Ki*Bias;  //增量式PI控制器
                                                                   //Velcity_Kp*(Bias-Last_bias) 作用为限制加速度
	                                                                 //Velcity_Ki*Bias             速度控制值由Bias不断积分得到 偏差越大加速度越大
		if(ControlVelocity>999)ControlVelocity=999;
		if(ControlVelocity<-999)ControlVelocity=-999;
        printf("count :%d,dir :%d,temp_count :%lld\n",
            get_encoder_count(),get_encoder_dir(),get_encoder_temp_count());
		Last_bias=Bias;	
		return ControlVelocity; //返回速度控制值
}

void MOTOR_CONTROL(int TargetVelocity_A, int TargetVelocity_B, int TargetVelocity_C, int TargetVelocity_D)
{
    int ControlVelocity_A = Velocity_A(TargetVelocity_A, get_encoder_count());
    if(ControlVelocity_A > 0){
        DL_GPIO_clearPins(GPIO_MOTOR_AIN1_PORT, GPIO_MOTOR_AIN1_PIN);
        DL_GPIO_setPins(GPIO_MOTOR_AIN2_PORT, GPIO_MOTOR_AIN2_PIN);
    }
    else if (ControlVelocity_A == 0) {
        DL_GPIO_clearPins(GPIO_MOTOR_AIN1_PORT, GPIO_MOTOR_AIN1_PIN);
        DL_GPIO_clearPins(GPIO_MOTOR_AIN2_PORT, GPIO_MOTOR_AIN2_PIN);
    }
    else if (ControlVelocity_A < 0) {
        DL_GPIO_setPins(GPIO_MOTOR_AIN1_PORT, GPIO_MOTOR_AIN1_PIN);
        DL_GPIO_clearPins(GPIO_MOTOR_AIN2_PORT, GPIO_MOTOR_AIN2_PIN);
        ControlVelocity_A = -ControlVelocity_A;
    }
    DL_TimerG_setCaptureCompareValue(PWMA_INST, 999-ControlVelocity_A, GPIO_PWMA_C0_IDX);

}

void car_run(int speed, int difference)
{
    

}
void car_stop()
{

}