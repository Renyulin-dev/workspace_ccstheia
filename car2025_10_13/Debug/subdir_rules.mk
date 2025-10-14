################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1698674975: ../car2025_10_13.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.23.1/sysconfig_cli.bat" --script "C:/Users/renyu/workspace_ccstheia/car2025_10_13/car2025_10_13.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_04_00_06/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1698674975 ../car2025_10_13.syscfg
device.opt: build-1698674975
device.cmd.genlibs: build-1698674975
ti_msp_dl_config.c: build-1698674975
ti_msp_dl_config.h: build-1698674975
Event.dot: build-1698674975

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/Tracking" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/MPU6050" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/UART" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/OLED" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_04_00_06/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/Tracking" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/MPU6050" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/UART" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/OLED" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/Tracking" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/MPU6050" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/UART" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/OLED" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/car2025_10_13/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


