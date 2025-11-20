#include "ti_msp_dl_config.h"
#include "string.h"
#include "stdio.h"
#include "hw_encoder.h"
#include "hw_timer.h"
#include "uart.h"
#include "electrical_machinery.h"

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    // 下面的嵌套循环的次数是根据主控频率和编译器生成的指令周期大致计算出来的，
    // 需要通过实际测试调整来达到所需的延时。
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 8000; j++)
        {
            // 仅执行一个足够简单以致于可以预测其执行时间的操作
            __asm__("nop"); // "nop" 代表“无操作”，在大多数架构中，这会消耗一个或几个时钟周期
        }
    }
}

float Velcity_Kp=1,  Velcity_Ki=1,  Velcity_Kd;

int Velocity_A(int TargetVelocity, int CurrentVelocity)
{  
    int Bias;  //定义相关变量
		static int ControlVelocity, Last_bias; //静态变量，函数调用结束后其值依然存在
		
		Bias=TargetVelocity-CurrentVelocity; //求速度偏差
		
		ControlVelocity+=Velcity_Kp*(Bias-Last_bias)+Velcity_Ki*Bias;  //增量式PI控制器
                                                                   //Velcity_Kp*(Bias-Last_bias) 作用为限制加速度
	                                                                 //Velcity_Ki*Bias             速度控制值由Bias不断积分得到 偏差越大加速度越大
		if(ControlVelocity>99)ControlVelocity=99;
		if(ControlVelocity<-99)ControlVelocity=-99;
		Last_bias=Bias;	
        printf("ControlVelocity = %d ",ControlVelocity);
		return ControlVelocity; //返回速度控制值
}

int main(void)
{
    SYSCFG_DL_init();
    DL_TimerG_startCounter(PWMA_INST);
	//编码器初始化
	encoder_init();
	UART_Init();
	//定时器初始化
	timer_init();
    DL_GPIO_setPins(GPIO_TB6612_STBY_PORT, GPIO_TB6612_STBY_PIN);
    DL_GPIO_clearPins(GPIO_TB6612_AIN1_PORT, GPIO_TB6612_AIN1_PIN);
    DL_GPIO_setPins(GPIO_TB6612_AIN2_PORT, GPIO_TB6612_AIN2_PIN);
    while (1)
	{   
        car_speed(Velocity_A(70,get_encoder_count()));
		printf("count :%d,dir :%d,temp_count :%lld\n",get_encoder_count(),get_encoder_dir(),get_encoder_temp_count());
        delay_ms(99);
    }
}
