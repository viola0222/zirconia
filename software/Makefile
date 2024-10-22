######################################
# target
######################################
TARGET = Zirconia2

######################################
# building variables
######################################
# debug build
DEBUG = 1
# optimization
OPT = -Og

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/adc.c \
Core/Src/dma.c \
Core/Src/gpio.c \
Core/Src/spi.c \
Core/Src/stm32f4xx_hal_msp.c \
Core/Src/stm32f4xx_it.c \
Core/Src/syscalls.c \
Core/Src/sysmem.c \
Core/Src/system_stm32f4xx.c \
Core/Src/tim.c \
Core/Src/usart.c \
Core/Src/main.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c \
Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c \
Library/ntshell-v0.3.1/lib/core/ntlibc.c \
Library/ntshell-v0.3.1/lib/core/ntshell.c \
Library/ntshell-v0.3.1/lib/core/text_editor.c \
Library/ntshell-v0.3.1/lib/core/text_history.c \
Library/ntshell-v0.3.1/lib/core/vtrecv.c \
Library/ntshell-v0.3.1/lib/core/vtsend.c \
Library/ntshell-v0.3.1/lib/util/ntopt.c \
Library/ntshell-v0.3.1/lib/util/ntstdio.c \
Module/Src/battery.c \
Module/Src/communicate.c \
Module/Src/encoder.c \
Module/Src/flash.c \
Module/Src/imu.c \
Module/Src/interrupt.c \
Module/Src/ir_sensor.c \
Module/Src/module_test.c \
Module/Src/motor.c \
Module/Src/myshell.c

# ASM sources
ASM_SOURCES =  \
Core/Startup/startup_stm32f411ceux.s

#######################################
# binaries
#######################################
COMPILER = arm-none-eabi
# COMPILER = clang
GCC_COMPILER_PATH = ./arm-gnu-toolchain-13.2.Rel1-mingw-w64-i686-arm-none-eabi/bin
CLANG_COMPILER_PATH = ./clang-llvm-18.1.8-x86_64-linux-gnu-ubuntu-18.04/bin

ifeq ($(COMPILER), arm-none-eabi)
CC = $(GCC_COMPILER_PATH)/$(PREFIX)arm-none-eabi-gcc
AS = $(GCC_COMPILER_PATH)/$(PREFIX)arm-none-eabi-gcc -x assembler-with-cpp
LD = $(GCC_COMPILER_PATH)/$(PREFIX)arm-none-eabi-gcc
CP = $(GCC_COMPILER_PATH)/$(PREFIX)arm-none-eabi-objcopy
SZ = $(GCC_COMPILER_PATH)/$(PREFIX)arm-none-eabi-size
else
CC = $(CLANG_COMPILER_PATH)/$(PREFIX)clang
AS = $(CLANG_COMPILER_PATH)/$(PREFIX)clang -x assembler-with-cpp
LD = $(GCC_COMPILER_PATH)/$(PREFIX)arm-none-eabi-gcc
CP = $(CLANG_COMPILER_PATH)/$(PREFIX)llvm-objcopy
SZ = $(CLANG_COMPILER_PATH)/$(PREFIX)llvm-size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DSTM32 \
-DSTM32F411xE \
-DARM_MATH_CM4 \
-DUSE_FULL_LL_DRIVER \
-DUSE_HAL_DRIVER \
-DHSE_VALUE=25000000 \
-DHSE_STARTUP_TIMEOUT=100 \
-DLSE_STARTUP_TIMEOUT=5000 \
-DLSE_VALUE=32768 \
-DEXTERNAL_CLOCK_VALUE=12288000 \
-DHSI_VALUE=16000000 \
-DLSI_VALUE=32000 \
-D_USE_MATH_DEFINES

# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-I. \
-IModule/Inc \
-ILibrary/ntshell-v0.3.1/lib \
-ILibrary/ntshell-v0.3.1/lib/core \
-ILibrary/ntshell-v0.3.1/lib/util \
-IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
-IDrivers/CMSIS/Include \
-IDrivers/STM32F4xx_HAL_Driver/Inc \
-ICore/Inc \
-Iarm-gnu-toolchain-13.2.Rel1-mingw-w64-i686-arm-none-eabi/arm-none-eabi/include

# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

ifeq ($(COMPILER), clang)
CFLAGS += --target=arm-none-eabi -Oz -fshort-enums
endif

#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32F411CEUX_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
#    $(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
