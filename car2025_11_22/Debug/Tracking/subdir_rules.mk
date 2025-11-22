################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Tracking/%.o: ../Tracking/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/Tracking" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/MPU6050" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/UART" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/OLED" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"Tracking/$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


