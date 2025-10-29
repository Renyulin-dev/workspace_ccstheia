#include "ti_msp_dl_config.h"
#include "string.h"
#include "stdio.h"
#include "hw_encoder.h"
#include "hw_timer.h"
#include "uart.h"

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
int main(void)
{
    SYSCFG_DL_init();
	//编码器初始化
	encoder_init();
	UART_Init();
	//定时器初始化
	timer_init();

    while (1)
	{
		delay_ms(1000);
		printf("count :%d,dir :%d,temp_count :%lld\n",get_encoder_count(),get_encoder_dir(),get_encoder_temp_count());
    }
}
