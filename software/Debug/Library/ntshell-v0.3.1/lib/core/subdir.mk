################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Library/ntshell-v0.3.1/lib/core/ntlibc.c \
../Library/ntshell-v0.3.1/lib/core/ntshell.c \
../Library/ntshell-v0.3.1/lib/core/text_editor.c \
../Library/ntshell-v0.3.1/lib/core/text_history.c \
../Library/ntshell-v0.3.1/lib/core/vtrecv.c \
../Library/ntshell-v0.3.1/lib/core/vtsend.c 

OBJS += \
./Library/ntshell-v0.3.1/lib/core/ntlibc.o \
./Library/ntshell-v0.3.1/lib/core/ntshell.o \
./Library/ntshell-v0.3.1/lib/core/text_editor.o \
./Library/ntshell-v0.3.1/lib/core/text_history.o \
./Library/ntshell-v0.3.1/lib/core/vtrecv.o \
./Library/ntshell-v0.3.1/lib/core/vtsend.o 

C_DEPS += \
./Library/ntshell-v0.3.1/lib/core/ntlibc.d \
./Library/ntshell-v0.3.1/lib/core/ntshell.d \
./Library/ntshell-v0.3.1/lib/core/text_editor.d \
./Library/ntshell-v0.3.1/lib/core/text_history.d \
./Library/ntshell-v0.3.1/lib/core/vtrecv.d \
./Library/ntshell-v0.3.1/lib/core/vtsend.d 


# Each subdirectory must supply rules for building sources it contributes
Library/ntshell-v0.3.1/lib/core/%.o Library/ntshell-v0.3.1/lib/core/%.su Library/ntshell-v0.3.1/lib/core/%.cyclo: ../Library/ntshell-v0.3.1/lib/core/%.c Library/ntshell-v0.3.1/lib/core/subdir.mk
<<<<<<< HEAD
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nakagawa/Bitbucket/zirconia_sample/software/Module/Inc" -I"C:/Users/nakagawa/Bitbucket/zirconia_sample/software/Library/ntshell-v0.3.1/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
=======
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nakagawa/bitbucket/zirconia_sample/software/Module/Inc" -I"C:/Users/nakagawa/bitbucket/zirconia_sample/software/Library/ntshell-v0.3.1/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
>>>>>>> e968368332e594be0bbbd6a99198443cc3b01749

clean: clean-Library-2f-ntshell-2d-v0-2e-3-2e-1-2f-lib-2f-core

clean-Library-2f-ntshell-2d-v0-2e-3-2e-1-2f-lib-2f-core:
	-$(RM) ./Library/ntshell-v0.3.1/lib/core/ntlibc.cyclo ./Library/ntshell-v0.3.1/lib/core/ntlibc.d ./Library/ntshell-v0.3.1/lib/core/ntlibc.o ./Library/ntshell-v0.3.1/lib/core/ntlibc.su ./Library/ntshell-v0.3.1/lib/core/ntshell.cyclo ./Library/ntshell-v0.3.1/lib/core/ntshell.d ./Library/ntshell-v0.3.1/lib/core/ntshell.o ./Library/ntshell-v0.3.1/lib/core/ntshell.su ./Library/ntshell-v0.3.1/lib/core/text_editor.cyclo ./Library/ntshell-v0.3.1/lib/core/text_editor.d ./Library/ntshell-v0.3.1/lib/core/text_editor.o ./Library/ntshell-v0.3.1/lib/core/text_editor.su ./Library/ntshell-v0.3.1/lib/core/text_history.cyclo ./Library/ntshell-v0.3.1/lib/core/text_history.d ./Library/ntshell-v0.3.1/lib/core/text_history.o ./Library/ntshell-v0.3.1/lib/core/text_history.su ./Library/ntshell-v0.3.1/lib/core/vtrecv.cyclo ./Library/ntshell-v0.3.1/lib/core/vtrecv.d ./Library/ntshell-v0.3.1/lib/core/vtrecv.o ./Library/ntshell-v0.3.1/lib/core/vtrecv.su ./Library/ntshell-v0.3.1/lib/core/vtsend.cyclo ./Library/ntshell-v0.3.1/lib/core/vtsend.d ./Library/ntshell-v0.3.1/lib/core/vtsend.o ./Library/ntshell-v0.3.1/lib/core/vtsend.su

.PHONY: clean-Library-2f-ntshell-2d-v0-2e-3-2e-1-2f-lib-2f-core

