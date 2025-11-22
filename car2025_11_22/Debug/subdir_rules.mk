################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1337133535: ../car2025_11_22.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.23.1/sysconfig_cli.bat" --script "C:/Users/renyu/workspace_ccstheia/car2025_11_22/car2025_11_22.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_04_00_06/.metadata/product.json" -d "MSPM0G350X" -p "LQFP-64(PM)" -r "Default" --context "system" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1337133535 ../car2025_11_22.syscfg
device.opt: build-1337133535
device.cmd.genlibs: build-1337133535
ti_msp_dl_config.c: build-1337133535
ti_msp_dl_config.h: build-1337133535
Event.dot: build-1337133535

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/Tracking" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/MPU6050" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/UART" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/OLED" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: C:/ti/mspm0_sdk_2_04_00_06/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/Tracking" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/MPU6050" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/UART" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/OLED" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/Tracking" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/MPU6050" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/UART" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/OLED" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/car2025_11_22/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


