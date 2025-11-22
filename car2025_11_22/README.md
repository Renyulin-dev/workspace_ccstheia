## 智能小车项目概述

本项目是一个基于 MSPM0G3507 微控制器的智能小车系统，集成了多种功能模块，包括循迹控制、MPU6050陀螺仪姿态检测、OLED显示界面以及电机驱动控制。项目采用PID算法实现精确的运动控制，支持多种控制模式。

## 主要功能模块

- **循迹控制**：使用8路红外传感器进行线路跟踪，通过PID算法实现精确转弯控制
- **姿态检测**：通过MPU6050陀螺仪获取小车的俯仰角、横滚角和偏航角
- **OLED显示**：提供友好的用户界面，显示小车状态信息
- **电机驱动**：控制直流电机实现前进、后退、转向等动作
- **UART通信**：支持与外部设备进行数据交互

## 外设与引脚分配

| 外设 | 引脚 | 功能 |
| --- | --- | --- |
| SYSCTL |  | 系统时钟控制 |
| DEBUGSS | PA20 | 调试时钟 |
| DEBUGSS | PA19 | 调试数据输入输出 |
| GPIO_OLED | 多个 | OLED显示屏控制（RES、SCL、SDA、DC、CS） |
| GPIO_MPU6050 | PIN_INT | MPU6050中断引脚 |
| I2C_MPU6050 |  | 与MPU6050通信的I2C总线 |
| I2C |  | 与循迹传感器通信的I2C总线 |

## BoosterPacks, 板资源与跳线设置

请访问 [LP_MSPM0G3507](https://www.ti.com/tool/LP-MSPM0G3507) 获取LaunchPad相关信息，包括用户指南和硬件文件。

| 引脚 | 外设 | 功能 | LaunchPad引脚 | LaunchPad设置 |
| --- | --- | --- | --- | --- |
| PA20 | DEBUGSS | SWCLK | N/A | <ul><li>PA20用于SWD调试<br><ul><li>`J101 15:16 ON` 调试时连接到XDS-110 SWCLK<br><li>`J101 15:16 OFF` 如在应用中使用该引脚则断开连接</ul></ul> |
| PA19 | DEBUGSS | SWDIO | N/A | <ul><li>PA19用于SWD调试<br><ul><li>`J101 13:14 ON` 调试时连接到XDS-110 SWDIO<br><li>`J101 13:14 OFF` 如在应用中使用该引脚则断开连接</ul></ul> |

### 设备迁移建议
本项目是为LP_MSPM0G3507 LaunchPad中包含的超集设备开发的。请访问[CCS用户指南](https://software-dl.ti.com/msp430/esd/MSPM0-SDK/latest/docs/english/tools/ccs_ide_guide/doc_guide/doc_guide-srcs/ccs_ide_guide.html#sysconfig-project-migration)了解迁移到其他MSPM0设备的信息。

### 低功耗建议
TI建议通过将相应功能设置为GPIO并将引脚配置为输出低电平或具有内部上拉/下拉电阻的输入来终止未使用的引脚。

SysConfig允许开发人员通过选择**Board**→**Configure Unused Pins**轻松配置未使用的引脚。

有关使用MSPM0 LaunchPad实现低功耗的跳线配置的更多信息，请访问[LP-MSPM0G3507用户指南](https://www.ti.com/lit/slau873)。

## 系统配置步骤

### MPU6050配置
1. 增加一个I2C模块，命名为"I2C_MPU6050"
2. 选中"Enable Controller Mode"复选框
3. 将"Standard Bus Speed"设置为"Fast Mode (400kHz)"
4. 添加GPIO模块，命名为"GPIO_MPU6050"
5. 将pin命名为"PIN_INT"，方向设置为"Input"
6. 将"Internal Resistor"设置为"Pull-Up Resistor"
7. 选中"Enable Interrupts"复选框
8. 将"Interrupt Priority"设置为"Level 1 - High"或更低
9. 将"Trigger Polarity"设置为"Trigger on Falling Edge"

### OLED配置
1. 添加GPIO模块，命名为"GPIO_OLED"
2. 设置5个pin分别命名为"PIN_RES", "PIN_SCL", "PIN_SDA", "PIN_DC", "PIN_CS"

## 项目使用

1. 编译并加载程序到MSPM0G3507微控制器
2. 上电后，系统会先进行陀螺仪校准（在OLED屏幕上显示校准界面）
3. 校准完成后，小车进入正常工作模式
4. 可以通过OLED界面进行功能选择和参数调整
5. 循迹功能会自动检测并跟踪黑色线条

## 主要控制参数

- **PID参数**：默认设置为P=40.0, I=3.0, D=40
- **传感器数量**：8路红外传感器
- **最大转弯修正值**：150
- **积分项最大值**：80.0f

## 注意事项

- 确保在使用前进行正确的陀螺仪校准
- 循迹传感器需要在适当的环境光条件下工作
- 电机驱动电路需要正确连接，避免短路
- 建议在测试阶段使用较低的电机速度