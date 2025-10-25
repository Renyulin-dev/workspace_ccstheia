#include "line_follower.h"
#include "ti_msp_dl_config.h"
#include "mspm0_xj_i2c.h"
#include "uart.h"
#include "draw.h"
#include "clock.h"
#include "electrical_machinery.h"
#include "mpu6050.h"

// 传感器数据缓冲区
static unsigned char IRbuf[1];

float out;
float out1;
float out2;

// 全局变量
int l_num = 0;                     // 左转次数计数
int r_num = 0;                     // 右转次数计数
int gyro_l_num = 0;                // 陀螺仪检测到的左转次数
int gyro_r_num = 0;                // 陀螺仪检测到的右转次数
static float error = 0.0f;         // 当前误差
static float last_error = 0.0f;    // 上一次误差
static float integral = 0.0f;      // 积分值
static int turn_flag = 0;          // 转向标志：-1左转 1右转 0无转向
static unsigned long now_time = 0; // 当前时间戳
float car_straight_yaw;            // 直线行驶时的初始yaw角
float car_begin_yaw;               // 行驶开始时的初始yaw角
float angle_diff = 0;              // 角度变化值
int MAX_CORRECTION = 150;          // 最大转弯修正值


// 转弯修正系数
float correction_factor1 = 1.0f;   // 轻微修正
float correction_factor2 = 2.0f;   // 中度修正
float correction_factor3 = 4.0f;   // 较强修正
float correction_factor4 = 6.0f;   // 强修正

// 状态标志
static bool right_flag = false;    // 右转标志
static bool left_flag = false;     // 左转标志
static bool timer_flag = false;    // 定时器标志

bool mode_flag = false;            // 回转标志
bool angle_correction_flag = true; // 允许回转标志

// 传感器状态历史，用于滤波
static uint8_t sensor_state_history[HISTORY_LENGTH];
static int all_one_count = 0;           // 连续全1状态计数
static float last_valid_error = 0.0f;   // 上次有效的error值
static bool use_last_valid = false;     // 是否使用上次有效的error值

/**
 * @brief 更新转弯计数并触发蜂鸣器
 * @param is_left_turn 是否为左转
 */
static void update_turn_count(bool is_left_turn)
{
    if (is_left_turn) {
        l_num++;
    } else {
        r_num++;
    }
    
    mspm0_get_clock_ms(&now_time);
    DL_GPIO_setPins(BEEP_PORT, BEEP_PIN_21_PIN);
    timer_flag = false; // 重置定时器标志
}

/**
 * @brief 处理转向逻辑
 * 当检测到需要转向时，更新转向标志、计数并触发蜂鸣器
 */
static void handle_turn_event(void)
{
    if (turn_flag == 0) {
        if (right_flag && timer_flag) {
            turn_flag = -1; // 设置为左转标志（补偿右转）
            update_turn_count(false); // 增加右转计数
        } else if (left_flag && timer_flag) {
            turn_flag = 1; // 设置为右转标志（补偿左转）
            update_turn_count(true); // 增加左转计数
        }
    }
}

/**
 * @brief 获取经过滤波的传感器状态
 * @param current_state 当前传感器状态
 * @return 滤波后的传感器状态
 */
static uint8_t filter_sensor_state(uint8_t current_state)
{
    // 更新状态历史（从后往前移动）
    for (int i = HISTORY_LENGTH - 1; i > 0; i--) {
        sensor_state_history[i] = sensor_state_history[i-1];
    }
    sensor_state_history[0] = current_state;
    
    // 默认不使用上次有效状态
    use_last_valid = false;
    
    // 检测当前是否为全1状态（可能是传感器故障或出界）
    if (current_state == 0xFF) {
        all_one_count++;
        // 如果连续全1次数不足阈值，使用上次有效状态
        if (all_one_count < ALL_ONE_THRESHOLD) {
            use_last_valid = true;
        }
    } else {
        // 非全1状态，重置计数
        all_one_count = 0;
        // 更新上次有效error值
        last_valid_error = error;
    }
    
    return current_state;
}

/**
 * @brief 解析传感器状态
 * @param sensor_data 原始传感器数据字节
 * @param s 传感器状态数组（大小至少为8）
 */
static void parse_sensor_data(uint8_t sensor_data, uint8_t s[]) {
    for (int i = 0; i < SENSOR_COUNT; i++) {
        s[i] = (sensor_data >> (7 - i)) & 0x01;
    }
}

/**
 * @brief yaw角换算
 * @param car_straight_yaw 直线时角度
 * @return 与直线时差值
 */
float angle_calculation(float car_straight_yaw) {
    float Angle_difference = car_straight_yaw - yaw;
    // 调整角度差到[-180, 180]范围
    if (Angle_difference <= -180) Angle_difference += 360;
    if (Angle_difference >= 180) Angle_difference -= 360;
    return Angle_difference;
}

/**
 * @brief 判断并执行回转以修正角度
 */
void angle_correction(){
    if((l_num % 5 == 0 && l_num != 0)){
        // 初始化角度计算变量
        float start_yaw = yaw;        // 记录起始角度
        float current_yaw = yaw;      // 当前角度
        float previous_yaw = yaw;     // 上一次角度
        float total_rotation = 0;     // 累计旋转角度
        float angle_diff;             // 相邻两次采样的角度差
        angle_correction_flag = false;
        
        // 旋转控制循环
        while(1){
            // 控制小车旋转
            car_run(0, -MAX_CORRECTION);
            
            // 获取当前角度
            current_yaw = yaw;
            
            // 计算相邻两次采样的角度差，处理闭环圆特性
            angle_diff = current_yaw - previous_yaw;
            
            // 处理角度跳变问题（如179°到-179°的过渡）
            if (angle_diff > 180.0f) {
                angle_diff -= 360.0f;  // 处理逆时针跳变
            } else if (angle_diff < -180.0f) {
                angle_diff += 360.0f;  // 处理顺时针跳变
            }
            
            // 累计旋转角度
            total_rotation += angle_diff;
            
            // 更新上一次角度
            previous_yaw = current_yaw;
            
            // 输出当前累计旋转角度（调试用）
            out = -total_rotation;
            
            // 判断是否完成280度旋转（考虑顺时针旋转）
            if (total_rotation <= -280.0f) {
                break;
            }
        }
    }
    if((r_num % 5 == 0 && r_num != 0)){
        // 初始化角度计算变量
        float start_yaw = yaw;        // 记录起始角度
        float current_yaw = yaw;      // 当前角度
        float previous_yaw = yaw;     // 上一次角度
        float total_rotation = 0;     // 累计旋转角度
        float angle_diff;             // 相邻两次采样的角度差
        angle_correction_flag = false;
        
        // 旋转控制循环
        while(1){
            // 控制小车旋转
            car_run(0, MAX_CORRECTION);
            
            // 获取当前角度
            current_yaw = yaw;
            
            // 计算相邻两次采样的角度差，处理闭环圆特性
            angle_diff = current_yaw - previous_yaw;
            
            // 处理角度跳变问题（如179°到-179°的过渡）
            if (angle_diff > 180.0f) {
                angle_diff -= 360.0f;  // 处理逆时针跳变
            } else if (angle_diff < -180.0f) {
                angle_diff += 360.0f;  // 处理顺时针跳变
            }
            
            // 累计旋转角度
            total_rotation += angle_diff;
            
            // 更新上一次角度
            previous_yaw = current_yaw;
            
            // 输出当前累计旋转角度（调试用）
            out = total_rotation;
            
            // 判断是否完成280度旋转（考虑逆时针旋转）
            if (total_rotation >= 280.0f) {
                break;
            }
        }
    }
}

/**
 * @brief 计算PID控制输出
 * @param kp 比例系数
 * @param ki 积分系数
 * @param kd 微分系数
 * @return PID控制输出值
 */
float line_follower(float kp, float ki, float kd){
    // 验证参数有效性
    if (kp < 0 || ki < 0 || kd < 0) {
        return 0.0f; // 参数无效，返回默认值
    }
    
    uint8_t s[8]; // 传感器状态数组
    uint8_t current_state;
    
    angle_diff = angle_calculation(car_straight_yaw);

    // 读取传感器数据（添加错误处理）
    if (mspm0_xj_i2c_read(IIC_ADDRESS, REGISTER_READ_ADDRESS, 1, IRbuf) != 0) {
        // I2C读取失败，使用上次有效状态
        if (use_last_valid) {
            return kp * last_valid_error + ki * integral + kd * (last_valid_error - last_error);
        }
        return 0.0f; // 无有效状态，返回零输出
    }
    
    // 解析传感器状态
    parse_sensor_data(IRbuf[0], s);
    
    // 更新当前速度
    now_speed = car_speed;

    // 处理蜂鸣器和定时器逻辑
    if (tick_ms - now_time > BEEP_DURATION_MS) {
        DL_GPIO_clearPins(BEEP_PORT, BEEP_PIN_21_PIN);
    }
    if (tick_ms - now_time > TIMER_RESET_MS) {
        timer_flag = true;
    }
    
    // 构建当前传感器状态字节
    current_state = 0;
    for (int i = 0; i < SENSOR_COUNT; i++) {
        current_state |= (s[i] << (7 - i));
    }
    
    // 应用传感器状态滤波
    filter_sensor_state(current_state);
    
    // 如果需要使用上次有效状态
    if (use_last_valid) {
        float output = kp * last_valid_error + ki * integral + kd * (last_valid_error - last_error);
        last_error = last_valid_error; // 更新last_error以保持连续性
        return output;
    }
    
    // 检测是否出界或连续全1
    if (current_state == 0xFF && (left_flag || right_flag)) {
        now_speed = 0;         // 停止电机
        handle_turn_event();   // 处理转向事件
        
        if (left_flag) {
            return MAX_CORRECTION;    // 左出界，大幅右转
        }
        if (right_flag) {
            return -MAX_CORRECTION;   // 右出界，大幅左转
        }
    }
    
    // 当陀螺仪检测到的旋转角度大于85度时，判断旋转方向并更新计数
    if (fabs(angle_diff) >= 80.0f) {
        car_straight_yaw = yaw;
        if (angle_diff > 0) {
            // 角度差为正，判定为右转
            gyro_r_num++;
            // 如果陀螺仪右转计数大于传感器右转计数，则更新传感器计数
            if (gyro_r_num > r_num) {
                update_turn_count(false); // 增加右转计数
            }
        } else {
            // 角度差为负，判定为左转
            gyro_l_num++;
            // 如果陀螺仪左转计数大于传感器左转计数，则更新传感器计数
            if (gyro_l_num > l_num) {
                update_turn_count(true); // 增加左转计数
            }
        }
    }

    // 直线行驶逻辑 - 计算误差值
    if (s[0] && s[1] && s[2] && !s[3] && s[4] && s[5] && s[6] && s[7]) {
        /* 1 1 1 0 1 1 1 1 */
        error = correction_factor1;
    } else if (s[0] && s[1] && s[2] && s[3] && !s[4] && s[5] && s[6] && s[7]) {
        /* 1 1 1 1 0 1 1 1 */
        error = -correction_factor1;
    } else if (s[0] && s[1] && !s[2] && !s[3] && s[4] && s[5] && s[6] && s[7]) {
        /* 1 1 0 0 1 1 1 1 */
        error = correction_factor1 + 0.2f;
    } else if (s[0] && s[1] && s[2] && s[3] && !s[4] && !s[5] && s[6] && s[7]) {
        /* 1 1 1 1 0 0 1 1 */
        error = -correction_factor1 - 0.2f;
    } else if (s[0] && s[1] && !s[2] && s[3] && s[4] && s[5] && s[6] && s[7]) {
        /* 1 1 0 1 1 1 1 1 */
        error = correction_factor2;
    } else if (s[0] && s[1] && s[2] && s[3] && s[4] && !s[5] && s[6] && s[7]) {
        /* 1 1 1 1 1 0 1 1 */
        error = -correction_factor2;
    } else if (s[0] && !s[1] && !s[2] && s[3] && s[4] && s[5] && s[6] && s[7]) {
        /* 1 0 0 1 1 1 1 1 */
        error = correction_factor2 + 0.2f;
    } else if (s[0] && s[1] && s[2] && s[3] && s[4] && !s[5] && !s[6] && s[7]) {
        /* 1 1 1 1 1 0 0 1 */
        error = -correction_factor2 - 0.2f;
    } else if (s[0] && !s[1] && s[2] && s[3] && s[4] && s[5] && s[6] && s[7]) {
        /* 1 0 1 1 1 1 1 1 */
        error = correction_factor3;
    } else if (s[0] && s[1] && s[2] && s[3] && s[4] && s[5] && !s[6] && s[7]) {
        /* 1 1 1 1 1 1 0 1 */
        error = -correction_factor3;
    } else if (!s[0] && !s[1] && s[2] && s[3] && s[4] && s[5] && s[6] && s[7]) {
        /* 0 0 1 1 1 1 1 1 */
        error = correction_factor3 + 0.2f;
    } else if (s[0] && s[1] && s[2] && s[3] && s[4] && s[5] && !s[6] && !s[7]) {
        /* 1 1 1 1 1 1 0 0 */
        error = -correction_factor3 - 0.2f;
    } else if (!s[0] && s[1] && s[2] && s[3] && s[4] && s[5] && s[6] && s[7]) {
        /* 0 1 1 1 1 1 1 1 */
        error = correction_factor4;
    } else if (s[0] && s[1] && s[2] && s[3] && s[4] && s[5] && s[6] && !s[7]) {
        /* 1 1 1 1 1 1 1 0 */
        error = -correction_factor4;
    } else if (s[0] && s[1] && s[2] && !s[3] && !s[4] && s[5] && s[6] && s[7]) {
        /* 1 1 1 0 0 1 1 1 */
        error = 0.0f;
        car_straight_yaw = yaw;
    }
    
    // 左转逻辑
    else if ((s[5] && s[6] && s[7])                                     /* - - - - - 1 1 1 */
           || (!s[1] && !s[3] && !s[5] && s[6] && s[7])                 /* - 0 - 0 - 0 1 1 */
           || (!s[2] && !s[4] && !s[6] && s[7]))                        /* - - 0 - 0 - 0 1 */
    {
        if (!left_flag && !right_flag) {
            left_flag = true;
        }
        turn_flag = 0;
        
        // 当检测到左转时，如果timer_flag为true，直接更新计数
        if (timer_flag) {
            update_turn_count(true);
        }
        
        return MAX_CORRECTION; // 执行左转
    }
    
    // 右转逻辑
    else if ((s[0] && s[1] && s[2])                                     /* 1 1 1 - - - - - */
           || (s[0] && s[1] && !s[2] && !s[4] && !s[6])                 /* 1 1 0 - 0 - 0 - */
           || (s[0] && !s[1] && !s[3] && !s[5]))                        /* 1 0 - 0 - 0 - - */
    {
        if (!left_flag && !right_flag) {
            right_flag = true;
        }
        turn_flag = 0;
        
        // 当检测到右转时，如果timer_flag为true，直接更新计数
        if (timer_flag) {
            update_turn_count(false);
        }
        
        return -MAX_CORRECTION; // 执行右转
    }
    
    // 其他情况，默认无误差
    else {
        error = 0.0f;
    }
    
    // 处理边界情况
    if (!s[0] && !s[1] && s[7]) {  /* 0 - - - - - - 1 */
        if (!left_flag && !right_flag) {
            left_flag = true;
        }
        turn_flag = 0;
    } else if (s[0] && !s[6] && !s[7]) { /* 1 - - - - - - 0 */
        if (!left_flag && !right_flag) {
            right_flag = true;
        }
        turn_flag = 0;
    }

    
    // PID控制器计算
    integral += error;
    // 积分限幅，防止积分饱和
    if (integral > MAX_INTEGRAL) {
        integral = MAX_INTEGRAL;
    } else if (integral < -MAX_INTEGRAL) {
        integral = -MAX_INTEGRAL;
    }
    
    // 计算PID输出
    float output = kp * error + ki * integral + kd * (error - last_error);
    last_error = error; // 更新上一次误差
    
    return output;
}

/**
 * @brief 车辆控制主函数
 * 调用line_follower获取差速值，并控制车辆运行
 */
void c_control(void)
{
    // 调用line_follower函数获取差速值，仅在car_speed不为零时计算
    car_run(now_speed, car_speed ? line_follower(P, I, D) : 0);
    if(mode_flag && angle_correction_flag)angle_correction();
    if((l_num % 6 == 0 && l_num != 0) || (r_num % 6 == 0 && r_num != 0))angle_correction_flag = true;
    // 检查是否完成指定圈数
    out1 = car_begin_yaw - yaw <= 0 ? car_begin_yaw - yaw :car_begin_yaw - yaw - 360;
    out2 = car_begin_yaw - yaw >= 0 ? car_begin_yaw - yaw :car_begin_yaw - yaw + 360;
    if (((l_num > 0 && (l_num - 1) / 4 == quanshu)) || 
        ((r_num > 0 && (r_num - 1) / 4 == quanshu))) {
        // 停止车辆
        car_speed = 0;
        stop_flag = true;
        car_stop();
        
        // 重置标志和计数
        right_flag = false;
        left_flag = false;
        l_num = 0;
        r_num = 0;
        gyro_l_num = 0;
        gyro_r_num = 0;
        
        mspm0_delay_ms(100);
        DL_GPIO_clearPins(BEEP_PORT, BEEP_PIN_21_PIN); // 关闭蜂鸣器
    }
}