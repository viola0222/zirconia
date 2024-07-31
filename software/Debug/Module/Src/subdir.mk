################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Module/Src/battery.c \
../Module/Src/communicate.c \
../Module/Src/encoder.c \
../Module/Src/flash.c \
../Module/Src/imu.c \
../Module/Src/interrupt.c \
../Module/Src/ir_sensor.c \
../Module/Src/module_test.c \
../Module/Src/motor.c \
../Module/Src/myshell.c 

OBJS += \
./Module/Src/battery.o \
./Module/Src/communicate.o \
./Module/Src/encoder.o \
./Module/Src/flash.o \
./Module/Src/imu.o \
./Module/Src/interrupt.o \
./Module/Src/ir_sensor.o \
./Module/Src/module_test.o \
./Module/Src/motor.o \
./Module/Src/myshell.o 

C_DEPS += \
./Module/Src/battery.d \
./Module/Src/communicate.d \
./Module/Src/encoder.d \
./Module/Src/flash.d \
./Module/Src/imu.d \
./Module/Src/interrupt.d \
./Module/Src/ir_sensor.d \
./Module/Src/module_test.d \
./Module/Src/motor.d \
./Module/Src/myshell.d 


# Each subdirectory must supply rules for building sources it contributes
Module/Src/%.o Module/Src/%.su Module/Src/%.cyclo: ../Module/Src/%.c Module/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/nakagawa/Bitbucket/zirconia_sample/software/Module/Inc" -I"C:/Users/nakagawa/Bitbucket/zirconia_sample/software/Library/ntshell-v0.3.1/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Module-2f-Src

clean-Module-2f-Src:
	-$(RM) ./Module/Src/battery.cyclo ./Module/Src/battery.d ./Module/Src/battery.o ./Module/Src/battery.su ./Module/Src/communicate.cyclo ./Module/Src/communicate.d ./Module/Src/communicate.o ./Module/Src/communicate.su ./Module/Src/encoder.cyclo ./Module/Src/encoder.d ./Module/Src/encoder.o ./Module/Src/encoder.su ./Module/Src/flash.cyclo ./Module/Src/flash.d ./Module/Src/flash.o ./Module/Src/flash.su ./Module/Src/imu.cyclo ./Module/Src/imu.d ./Module/Src/imu.o ./Module/Src/imu.su ./Module/Src/interrupt.cyclo ./Module/Src/interrupt.d ./Module/Src/interrupt.o ./Module/Src/interrupt.su ./Module/Src/ir_sensor.cyclo ./Module/Src/ir_sensor.d ./Module/Src/ir_sensor.o ./Module/Src/ir_sensor.su ./Module/Src/module_test.cyclo ./Module/Src/module_test.d ./Module/Src/module_test.o ./Module/Src/module_test.su ./Module/Src/motor.cyclo ./Module/Src/motor.d ./Module/Src/motor.o ./Module/Src/motor.su ./Module/Src/myshell.cyclo ./Module/Src/myshell.d ./Module/Src/myshell.o ./Module/Src/myshell.su

.PHONY: clean-Module-2f-Src

