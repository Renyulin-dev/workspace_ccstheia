#include "uart.h"
#include "ti_msp_dl_config.h"
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 128
static char uart_buffer[BUFFER_SIZE] = {0};
static int buffer_index = 0;
float P, I, D;
//串口发送单个字符
volatile unsigned char uart_data = 0;

//重定向fputc函数
int fputc(int ch, FILE *stream)
{
    while( DL_UART_isBusy(UART_0_INST) == true );
    DL_UART_Main_transmitData(UART_0_INST, ch);
    return ch;
}

//重定向fputs函数
int fputs(const char* restrict s, FILE* restrict stream) {

    uint16_t char_len=0;
    while(*s!=0)
    {
        while( DL_UART_isBusy(UART_0_INST) == true );
        DL_UART_Main_transmitData(UART_0_INST, *s++);
        char_len++;
    }
    return char_len;
}
int puts(const char* _ptr)
{
 return 0;
}

void uart0_send_char(char ch)
{
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(UART_0_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(UART_0_INST, ch);
}

void uart1_send_char(char ch)
{
    //当串口0忙的时候等待，不忙的时候再发送传进来的字符
    while( DL_UART_isBusy(UART_1_INST) == true );
    //发送单个字符
    DL_UART_Main_transmitData(UART_1_INST, ch);
}

//串口发送字符串
void uart0_send_string(char* str)
{
    //当前字符串地址不在结尾 并且 字符串首地址不为空
    while(*str!=0&&str!=0)
    {
        //发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart0_send_char(*str++);
    }
}

void uart1_send_string(char* str)
{
    //当前字符串地址不在结尾 并且 字符串首地址不为空
    while(*str!=0&&str!=0)
    {
        //发送字符串首地址中的字符，并且在发送完成之后首地址自增
        uart1_send_char(*str++);
    }
}

void UART_Init(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_1_INST_INT_IRQN);
    printf("UART Init is OK!!!");
}

static void parse_uart_command(char *command)
{
    char *start = command;
    while ((start = strchr(start, '@')) != NULL)
    {
        start++;//跳过@
        if (*start == '\0') break;
        
        char var_name = *start++;
        if (*start != '$') continue;//格式错误
        
        start++;//跳过$
        char *value_start = start;
        start = strchr(start, '$');
        if (start == NULL) break;
        
        *start = '\0';//截断值字符串
        float value = atof(value_start);
        start++;//移动到end$
        
        if (strncmp(start, "end$", 4) != 0) continue;
        
        //根据变量名赋值
        switch(var_name){
            case 'P': P = value; printf("P : %f",P); break;
            case 'I': I = value; printf("I : %f",I); break;
            case 'D': D = value; printf("D : %f",D); break;
            //可添加更多变量
        }
        
        start += 4;//移动到下一个命令
    }
}


//串口的中断服务函数
void UART_0_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(UART_0_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
            //将发送过来的数据保存在变量中
            uart_data = DL_UART_Main_receiveData(UART_0_INST);
            // 接收数据存入缓冲区
            if (buffer_index < BUFFER_SIZE - 1) {
                uart_buffer[buffer_index++] = uart_data;
                uart_buffer[buffer_index] = '\0';
            }
            
            // 检查是否接收到结束标记$end$
            if (strstr(uart_buffer, "$end$") != NULL) {
                parse_uart_command(uart_buffer);
                buffer_index = 0;
                memset(uart_buffer, 0, BUFFER_SIZE);
            }
            //将保存的数据再发送出去
            uart1_send_char(uart_data);
            break;

        default://其他的串口中断
            break;
    }
}

//串口的中断服务函数
void UART_1_INST_IRQHandler(void)
{
    //如果产生了串口中断
    switch( DL_UART_getPendingInterrupt(UART_1_INST) )
    {
        case DL_UART_IIDX_RX://如果是接收中断
            //将发送过来的数据保存在变量中
            uart_data = DL_UART_Main_receiveData(UART_1_INST);
            
            // 接收数据存入缓冲区
            if (buffer_index < BUFFER_SIZE - 1) {
                uart_buffer[buffer_index++] = uart_data;
                uart_buffer[buffer_index] = '\0';
            }
            
            // 检查是否接收到结束标记$end$
            if (strstr(uart_buffer, "$end$") != NULL) {
                parse_uart_command(uart_buffer);
                buffer_index = 0;
                memset(uart_buffer, 0, BUFFER_SIZE);
            }
            uart0_send_char(uart_data);
            break;

        default://其他的串口中断
            break;
    }
}



