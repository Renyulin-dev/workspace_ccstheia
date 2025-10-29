/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_R1 */
#define PWM_R1_INST                                                       TIMG12
#define PWM_R1_INST_IRQHandler                                 TIMG12_IRQHandler
#define PWM_R1_INST_INT_IRQN                                   (TIMG12_INT_IRQn)
#define PWM_R1_INST_CLK_FREQ                                            80000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_R1_C1_PORT                                                GPIOB
#define GPIO_PWM_R1_C1_PIN                                        DL_GPIO_PIN_24
#define GPIO_PWM_R1_C1_IOMUX                                     (IOMUX_PINCM52)
#define GPIO_PWM_R1_C1_IOMUX_FUNC                   IOMUX_PINCM52_PF_TIMG12_CCP1
#define GPIO_PWM_R1_C1_IDX                                   DL_TIMER_CC_1_INDEX

/* Defines for PWM_R2 */
#define PWM_R2_INST                                                        TIMA0
#define PWM_R2_INST_IRQHandler                                  TIMA0_IRQHandler
#define PWM_R2_INST_INT_IRQN                                    (TIMA0_INT_IRQn)
#define PWM_R2_INST_CLK_FREQ                                            80000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_R2_C1_PORT                                                GPIOB
#define GPIO_PWM_R2_C1_PIN                                        DL_GPIO_PIN_20
#define GPIO_PWM_R2_C1_IOMUX                                     (IOMUX_PINCM48)
#define GPIO_PWM_R2_C1_IOMUX_FUNC                    IOMUX_PINCM48_PF_TIMA0_CCP1
#define GPIO_PWM_R2_C1_IDX                                   DL_TIMER_CC_1_INDEX

/* Defines for PWM_L1 */
#define PWM_L1_INST                                                        TIMG8
#define PWM_L1_INST_IRQHandler                                  TIMG8_IRQHandler
#define PWM_L1_INST_INT_IRQN                                    (TIMG8_INT_IRQn)
#define PWM_L1_INST_CLK_FREQ                                            40000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_L1_C1_PORT                                                GPIOB
#define GPIO_PWM_L1_C1_PIN                                        DL_GPIO_PIN_19
#define GPIO_PWM_L1_C1_IOMUX                                     (IOMUX_PINCM45)
#define GPIO_PWM_L1_C1_IOMUX_FUNC                    IOMUX_PINCM45_PF_TIMG8_CCP1
#define GPIO_PWM_L1_C1_IDX                                   DL_TIMER_CC_1_INDEX

/* Defines for PWM_L2 */
#define PWM_L2_INST                                                        TIMA1
#define PWM_L2_INST_IRQHandler                                  TIMA1_IRQHandler
#define PWM_L2_INST_INT_IRQN                                    (TIMA1_INT_IRQn)
#define PWM_L2_INST_CLK_FREQ                                            80000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_L2_C1_PORT                                                GPIOB
#define GPIO_PWM_L2_C1_PIN                                        DL_GPIO_PIN_18
#define GPIO_PWM_L2_C1_IOMUX                                     (IOMUX_PINCM44)
#define GPIO_PWM_L2_C1_IOMUX_FUNC                    IOMUX_PINCM44_PF_TIMA1_CCP1
#define GPIO_PWM_L2_C1_IDX                                   DL_TIMER_CC_1_INDEX




/* Defines for I2C_BUS */
#define I2C_BUS_INST                                                        I2C1
#define I2C_BUS_INST_IRQHandler                                  I2C1_IRQHandler
#define I2C_BUS_INST_INT_IRQN                                      I2C1_INT_IRQn
#define I2C_BUS_BUS_SPEED_HZ                                              400000
#define GPIO_I2C_BUS_SDA_PORT                                              GPIOB
#define GPIO_I2C_BUS_SDA_PIN                                       DL_GPIO_PIN_3
#define GPIO_I2C_BUS_IOMUX_SDA                                   (IOMUX_PINCM16)
#define GPIO_I2C_BUS_IOMUX_SDA_FUNC                    IOMUX_PINCM16_PF_I2C1_SDA
#define GPIO_I2C_BUS_SCL_PORT                                              GPIOB
#define GPIO_I2C_BUS_SCL_PIN                                       DL_GPIO_PIN_2
#define GPIO_I2C_BUS_IOMUX_SCL                                   (IOMUX_PINCM15)
#define GPIO_I2C_BUS_IOMUX_SCL_FUNC                    IOMUX_PINCM15_PF_I2C1_SCL

/* Defines for I2C_MPU6050 */
#define I2C_MPU6050_INST                                                    I2C0
#define I2C_MPU6050_INST_IRQHandler                              I2C0_IRQHandler
#define I2C_MPU6050_INST_INT_IRQN                                  I2C0_INT_IRQn
#define I2C_MPU6050_BUS_SPEED_HZ                                          400000
#define GPIO_I2C_MPU6050_SDA_PORT                                          GPIOA
#define GPIO_I2C_MPU6050_SDA_PIN                                   DL_GPIO_PIN_0
#define GPIO_I2C_MPU6050_IOMUX_SDA                                (IOMUX_PINCM1)
#define GPIO_I2C_MPU6050_IOMUX_SDA_FUNC                 IOMUX_PINCM1_PF_I2C0_SDA
#define GPIO_I2C_MPU6050_SCL_PORT                                          GPIOA
#define GPIO_I2C_MPU6050_SCL_PIN                                   DL_GPIO_PIN_1
#define GPIO_I2C_MPU6050_IOMUX_SCL                                (IOMUX_PINCM2)
#define GPIO_I2C_MPU6050_IOMUX_SCL_FUNC                 IOMUX_PINCM2_PF_I2C0_SCL


/* Defines for UART_0 */
#define UART_0_INST                                                        UART1
#define UART_0_INST_FREQUENCY                                            4000000
#define UART_0_INST_IRQHandler                                  UART1_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                         DL_GPIO_PIN_9
#define GPIO_UART_0_TX_PIN                                         DL_GPIO_PIN_8
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM20)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM19)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM20_PF_UART1_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM19_PF_UART1_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_0_FBRD_4_MHZ_9600_BAUD                                          (3)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART0
#define UART_1_INST_FREQUENCY                                            4000000
#define UART_1_INST_IRQHandler                                  UART0_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOA
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_1_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_1_BAUD_RATE                                                  (9600)
#define UART_1_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_1_FBRD_4_MHZ_9600_BAUD                                          (3)





/* Port definition for Pin Group BEEP */
#define BEEP_PORT                                                        (GPIOA)

/* Defines for PIN_21: GPIOA.21 with pinCMx 46 on package pin 39 */
#define BEEP_PIN_21_PIN                                         (DL_GPIO_PIN_21)
#define BEEP_PIN_21_IOMUX                                        (IOMUX_PINCM46)
/* Port definition for Pin Group GPIO_MPU6050 */
#define GPIO_MPU6050_PORT                                                (GPIOA)

/* Defines for PIN_INT: GPIOA.28 with pinCMx 3 on package pin 3 */
// groups represented: ["GPIO_ENCODER","GPIO_KEYS","GPIO_MPU6050"]
// pins affected: ["E1A","PIN_26","PIN_25","PIN_24","PIN_22","PIN_INT"]
#define GPIO_MULTIPLE_GPIOA_INT_IRQN                            (GPIOA_INT_IRQn)
#define GPIO_MULTIPLE_GPIOA_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_MPU6050_PIN_INT_IIDX                           (DL_GPIO_IIDX_DIO28)
#define GPIO_MPU6050_PIN_INT_PIN                                (DL_GPIO_PIN_28)
#define GPIO_MPU6050_PIN_INT_IOMUX                                (IOMUX_PINCM3)
/* Defines for PIN_RES: GPIOB.8 with pinCMx 25 on package pin 22 */
#define GPIO_OLED_PIN_RES_PORT                                           (GPIOB)
#define GPIO_OLED_PIN_RES_PIN                                    (DL_GPIO_PIN_8)
#define GPIO_OLED_PIN_RES_IOMUX                                  (IOMUX_PINCM25)
/* Defines for PIN_SCL: GPIOA.17 with pinCMx 39 on package pin 32 */
#define GPIO_OLED_PIN_SCL_PORT                                           (GPIOA)
#define GPIO_OLED_PIN_SCL_PIN                                   (DL_GPIO_PIN_17)
#define GPIO_OLED_PIN_SCL_IOMUX                                  (IOMUX_PINCM39)
/* Defines for PIN_SDA: GPIOA.16 with pinCMx 38 on package pin 31 */
#define GPIO_OLED_PIN_SDA_PORT                                           (GPIOA)
#define GPIO_OLED_PIN_SDA_PIN                                   (DL_GPIO_PIN_16)
#define GPIO_OLED_PIN_SDA_IOMUX                                  (IOMUX_PINCM38)
/* Defines for PIN_DC: GPIOB.9 with pinCMx 26 on package pin 23 */
#define GPIO_OLED_PIN_DC_PORT                                            (GPIOB)
#define GPIO_OLED_PIN_DC_PIN                                     (DL_GPIO_PIN_9)
#define GPIO_OLED_PIN_DC_IOMUX                                   (IOMUX_PINCM26)
/* Defines for PIN_CS: GPIOA.27 with pinCMx 60 on package pin 47 */
#define GPIO_OLED_PIN_CS_PORT                                            (GPIOA)
#define GPIO_OLED_PIN_CS_PIN                                    (DL_GPIO_PIN_27)
#define GPIO_OLED_PIN_CS_IOMUX                                   (IOMUX_PINCM60)
/* Defines for E1A: GPIOA.31 with pinCMx 6 on package pin 5 */
#define GPIO_ENCODER_E1A_PORT                                            (GPIOA)
#define GPIO_ENCODER_E1A_IIDX                               (DL_GPIO_IIDX_DIO31)
#define GPIO_ENCODER_E1A_PIN                                    (DL_GPIO_PIN_31)
#define GPIO_ENCODER_E1A_IOMUX                                    (IOMUX_PINCM6)
/* Defines for E1B: GPIOA.2 with pinCMx 7 on package pin 8 */
#define GPIO_ENCODER_E1B_PORT                                            (GPIOA)
#define GPIO_ENCODER_E1B_PIN                                     (DL_GPIO_PIN_2)
#define GPIO_ENCODER_E1B_IOMUX                                    (IOMUX_PINCM7)
/* Defines for E2A: GPIOA.3 with pinCMx 8 on package pin 9 */
#define GPIO_ENCODER_E2A_PORT                                            (GPIOA)
#define GPIO_ENCODER_E2A_PIN                                     (DL_GPIO_PIN_3)
#define GPIO_ENCODER_E2A_IOMUX                                    (IOMUX_PINCM8)
/* Defines for E2B: GPIOA.4 with pinCMx 9 on package pin 10 */
#define GPIO_ENCODER_E2B_PORT                                            (GPIOA)
#define GPIO_ENCODER_E2B_PIN                                     (DL_GPIO_PIN_4)
#define GPIO_ENCODER_E2B_IOMUX                                    (IOMUX_PINCM9)
/* Defines for E3A: GPIOA.5 with pinCMx 10 on package pin 11 */
#define GPIO_ENCODER_E3A_PORT                                            (GPIOA)
#define GPIO_ENCODER_E3A_PIN                                     (DL_GPIO_PIN_5)
#define GPIO_ENCODER_E3A_IOMUX                                   (IOMUX_PINCM10)
/* Defines for E3B: GPIOA.6 with pinCMx 11 on package pin 12 */
#define GPIO_ENCODER_E3B_PORT                                            (GPIOA)
#define GPIO_ENCODER_E3B_PIN                                     (DL_GPIO_PIN_6)
#define GPIO_ENCODER_E3B_IOMUX                                   (IOMUX_PINCM11)
/* Defines for E4A: GPIOA.7 with pinCMx 14 on package pin 13 */
#define GPIO_ENCODER_E4A_PORT                                            (GPIOA)
#define GPIO_ENCODER_E4A_PIN                                     (DL_GPIO_PIN_7)
#define GPIO_ENCODER_E4A_IOMUX                                   (IOMUX_PINCM14)
/* Defines for E4B: GPIOB.6 with pinCMx 23 on package pin 20 */
#define GPIO_ENCODER_E4B_PORT                                            (GPIOB)
#define GPIO_ENCODER_E4B_PIN                                     (DL_GPIO_PIN_6)
#define GPIO_ENCODER_E4B_IOMUX                                   (IOMUX_PINCM23)
/* Port definition for Pin Group GPIO_KEYS */
#define GPIO_KEYS_PORT                                                   (GPIOA)

/* Defines for PIN_26: GPIOA.26 with pinCMx 59 on package pin 46 */
#define GPIO_KEYS_PIN_26_IIDX                               (DL_GPIO_IIDX_DIO26)
#define GPIO_KEYS_PIN_26_PIN                                    (DL_GPIO_PIN_26)
#define GPIO_KEYS_PIN_26_IOMUX                                   (IOMUX_PINCM59)
/* Defines for PIN_25: GPIOA.25 with pinCMx 55 on package pin 45 */
#define GPIO_KEYS_PIN_25_IIDX                               (DL_GPIO_IIDX_DIO25)
#define GPIO_KEYS_PIN_25_PIN                                    (DL_GPIO_PIN_25)
#define GPIO_KEYS_PIN_25_IOMUX                                   (IOMUX_PINCM55)
/* Defines for PIN_24: GPIOA.24 with pinCMx 54 on package pin 44 */
#define GPIO_KEYS_PIN_24_IIDX                               (DL_GPIO_IIDX_DIO24)
#define GPIO_KEYS_PIN_24_PIN                                    (DL_GPIO_PIN_24)
#define GPIO_KEYS_PIN_24_IOMUX                                   (IOMUX_PINCM54)
/* Defines for PIN_22: GPIOA.22 with pinCMx 47 on package pin 40 */
#define GPIO_KEYS_PIN_22_IIDX                               (DL_GPIO_IIDX_DIO22)
#define GPIO_KEYS_PIN_22_PIN                                    (DL_GPIO_PIN_22)
#define GPIO_KEYS_PIN_22_IOMUX                                   (IOMUX_PINCM47)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_R1_init(void);
void SYSCFG_DL_PWM_R2_init(void);
void SYSCFG_DL_PWM_L1_init(void);
void SYSCFG_DL_PWM_L2_init(void);
void SYSCFG_DL_I2C_BUS_init(void);
void SYSCFG_DL_I2C_MPU6050_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
