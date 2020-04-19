################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
zilconia_sample.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
zilconia_sample.list \

OBJCOPY_HEX += \
zilconia_sample.hex \


# All Target
all: zilconia_sample.elf secondary-outputs

# Tool invocations
zilconia_sample.elf: $(OBJS) $(USER_OBJS) G:\Dropbox\CubeIDE\zilconia_sample\STM32F413CHUX_FLASH.ld
	arm-none-eabi-gcc -o "zilconia_sample.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"G:\Dropbox\CubeIDE\zilconia_sample\STM32F413CHUX_FLASH.ld" --specs=nosys.specs -Wl,-Map="zilconia_sample.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

zilconia_sample.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "zilconia_sample.list"
	@echo 'Finished building: $@'
	@echo ' '

zilconia_sample.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "zilconia_sample.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
