/*
 *功能:将串口0重定向printf上,并串口0和串口1能相互发送信息;
 *sysconfig配置步骤:
 *      UART: 
 *      1.添加UART模块。   
 *      2.将组命名为“ UART_0 ”,“ UART_1 ”。
 *      3.将" Clock Source "设置为" MFCLK "。
 *      4.将" Target Baud Rate "设置为对应波特率。
 *      5.将" Enable Interrupts "设置为" Receive "
 *      6.根据您的需要设置引脚。
 */

#ifndef UART_H
#define UART_H

void UART_Init(void);
void uart0_send_char(char ch); //串口0发送单个字符
void uart0_send_string(char* str); //串口0发送字符串
#endif