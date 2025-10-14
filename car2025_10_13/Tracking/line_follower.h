/*
 *此为循迹逻辑
*/
#ifndef _LINE_FOLLOWER_H_
#define _LINE_FOLLOWER_H_

#include <stdbool.h>

// I2C相关常量定义
#define IIC_ADDRESS               0x20        // I2C设备地址
#define REGISTER_WRITE_ADDRESS    0x40        // 寄存器写地址
#define REGISTER_READ_ADDRESS     0x41        // 寄存器读地址

// 控制相关常量
#define MAX_CORRECTION            150         // 最大转弯修正值
#define SENSOR_COUNT              8           // 传感器数量
#define HISTORY_LENGTH            6           // 历史状态长度
#define MAX_INTEGRAL              80.0f       // 积分项最大值
#define ALL_ONE_THRESHOLD         3           // 连续全1状态阈值
#define BEEP_DURATION_MS          1000        // 蜂鸣器持续时间
#define TIMER_RESET_MS            3000        // 定时器重置时间(防止同一角重复计数)

// 外部变量声明
extern int l_num, r_num;                    // 左右转计数
extern int lr;                              // 修正值参考
extern float correction_factor1, correction_factor2, correction_factor3, correction_factor4; // 转弯修正系数
extern float car_begin_yaw;

/**
 * @brief 计算PID控制输出
 * @param kp 比例系数
 * @param ki 积分系数
 * @param kd 微分系数
 * @return PID控制输出值
 */
float line_follower(float kp, float ki, float kd);

/**
 * @brief 车辆控制主函数
 * 调用line_follower获取差速值，并控制车辆运行
 */
void c_control(void);

#endif /* _LINE_FOLLOWER_H_ */