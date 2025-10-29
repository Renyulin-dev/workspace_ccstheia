################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
OLED/csrc/%.o: ../OLED/csrc/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/car2025_10_29/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_29/Tracking" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_29/MPU6050" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_29/UART" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_29/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_29/OLED" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_29/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_29/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"OLED/csrc/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


