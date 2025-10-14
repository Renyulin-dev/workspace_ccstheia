################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MSPM0\ copy/clock.o: ../MSPM0\ copy/clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/GGGG/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED/XBM" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED" -I"C:/Users/renyu/workspace_ccstheia/GGGG/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/GGGG/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"MSPM0 copy/clock.d_raw" -MT"MSPM0\ copy/clock.o"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

MSPM0\ copy/electrical_machinery.o: ../MSPM0\ copy/electrical_machinery.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/GGGG/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED/XBM" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED" -I"C:/Users/renyu/workspace_ccstheia/GGGG/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/GGGG/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"MSPM0 copy/electrical_machinery.d_raw" -MT"MSPM0\ copy/electrical_machinery.o"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

MSPM0\ copy/interrupt.o: ../MSPM0\ copy/interrupt.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/GGGG/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED/XBM" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED" -I"C:/Users/renyu/workspace_ccstheia/GGGG/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/GGGG/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"MSPM0 copy/interrupt.d_raw" -MT"MSPM0\ copy/interrupt.o"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

MSPM0\ copy/mspm0_i2c.o: ../MSPM0\ copy/mspm0_i2c.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-armllvm_4.0.3.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/Users/renyu/workspace_ccstheia/GGGG/MSPM0" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED/XBM" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED/csrc" -I"C:/Users/renyu/workspace_ccstheia/GGGG/OLED" -I"C:/Users/renyu/workspace_ccstheia/GGGG/targetConfigs" -I"C:/Users/renyu/workspace_ccstheia/GGGG/Debug" -I"C:/ti/mspm0_sdk_2_04_00_06/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_04_00_06/source" -gdwarf-3 -MMD -MP -MF"MSPM0 copy/mspm0_i2c.d_raw" -MT"MSPM0\ copy/mspm0_i2c.o"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


