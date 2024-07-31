################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/ntshell-v0.3.1/lib/util/ntopt.c \
../Library/ntshell-v0.3.1/lib/util/ntstdio.c 

OBJS += \
./Library/ntshell-v0.3.1/lib/util/ntopt.o \
./Library/ntshell-v0.3.1/lib/util/ntstdio.o 

C_DEPS += \
./Library/ntshell-v0.3.1/lib/util/ntopt.d \
./Library/ntshell-v0.3.1/lib/util/ntstdio.d 


# Each subdirectory must supply rules for building sources it contributes
Library/ntshell-v0.3.1/lib/util/%.o Library/ntshell-v0.3.1/lib/util/%.su Library/ntshell-v0.3.1/lib/util/%.cyclo: ../Library/ntshell-v0.3.1/lib/util/%.c Library/ntshell-v0.3.1/lib/util/subdir.mk
<<<<<<< HEAD
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nakagawa/Bitbucket/zirconia_sample/software/Module/Inc" -I"C:/Users/nakagawa/Bitbucket/zirconia_sample/software/Library/ntshell-v0.3.1/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
=======
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nakagawa/bitbucket/zirconia_sample/software/Module/Inc" -I"C:/Users/nakagawa/bitbucket/zirconia_sample/software/Library/ntshell-v0.3.1/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
>>>>>>> e968368332e594be0bbbd6a99198443cc3b01749

clean: clean-Library-2f-ntshell-2d-v0-2e-3-2e-1-2f-lib-2f-util

clean-Library-2f-ntshell-2d-v0-2e-3-2e-1-2f-lib-2f-util:
	-$(RM) ./Library/ntshell-v0.3.1/lib/util/ntopt.cyclo ./Library/ntshell-v0.3.1/lib/util/ntopt.d ./Library/ntshell-v0.3.1/lib/util/ntopt.o ./Library/ntshell-v0.3.1/lib/util/ntopt.su ./Library/ntshell-v0.3.1/lib/util/ntstdio.cyclo ./Library/ntshell-v0.3.1/lib/util/ntstdio.d ./Library/ntshell-v0.3.1/lib/util/ntstdio.o ./Library/ntshell-v0.3.1/lib/util/ntstdio.su

.PHONY: clean-Library-2f-ntshell-2d-v0-2e-3-2e-1-2f-lib-2f-util

