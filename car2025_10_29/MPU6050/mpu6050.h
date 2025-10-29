/*
 *sysconfig配置步骤:
 *I2C:
 *      1.增加一个I2C模块。
 *      2.命名为“ I2C_MPU6050 ”。    
 *      3.选中“Enable Controller Mode”复选框。   
 *      4.将" Standard Bus Speed "设置为“Fast Mode (400kHz)”。(可选)  
 *      5.根据您的需要设置引脚。   
 
 *      GPIO: 
 *      1.添加GPIO模块。   
 *      2.将该组命名为“ GPIO_MPU6050 ”。  
 *      3.将pin命名为“ PIN_INT ”。
 *      4.将"方向"设置为"Input"。  
 *      5.将"Internal Resistor"设置为"Pull-Up Resistor"。
 *      6.选中“Enable Interrupts”复选框。
 *      7.将"Interrupt Priority"设置为"Level 1 - High"或更低。
 *      8.将"Trigger Polarity"设置为"Trigger on Falling Edge"。
 *      9.根据您的需要设置引脚。
 */

#ifndef _MPU6050_H_
#define _MPU6050_H_


void MPU6050_Init(void);
int Read_Quad(void);

extern short gyro[3], accel[3];
extern float pitch, roll, yaw;

#endif  /* #ifndef _MPU6050_H_ */