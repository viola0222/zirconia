cmake_minimum_required(VERSION 3.10)

project("zirconia")

if(UNIX)
    set(CMAKE_C_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc")
    set(CMAKE_CXX_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-g++")
    set(CMAKE_ASM_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc")
    set(CMAKE_EXE_LINKER "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-g++")
    set(OBJCOPY "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-objcopy")
    set(SIZE "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-size")
elseif(WIN32)
    set(CMAKE_C_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc")
    set(CMAKE_CXX_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-g++")
    set(CMAKE_ASM_COMPILER "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc")
    set(CMAKE_EXE_LINKER "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-g++")
    set(OBJCOPY "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-objcopy")
    set(SIZE "${CMAKE_CURRENT_SOURCE_DIR}/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-size")
else()
    message(FATAL_ERROR "Invalid Operating System. Currently only UNIX and WIN32 are supported.")
endif()

add_definitions(
    -DSTM32
    -DSTM32F411xE
    -DARM_MATH_CM4
    -DUSE_FULL_LL_DRIVER
    -DUSE_HAL_DRIVER
    -DHSE_VALUE=25000000
    -DHSE_STARTUP_TIMEOUT=100
    -DLSE_STARTUP_TIMEOUT=5000
    -DLSE_VALUE=32768
    -DEXTERNAL_CLOCK_VALUE=12288000
    -DHSI_VALUE=16000000
    -DLSI_VALUE=32000
    -D_USE_MATH_DEFINES
)
add_compile_options(
    -ffunction-sections
    -fdata-sections
    -fstack-usage
    --specs=nano.specs
    -Wall
    -fmessage-length=0
    -fno-exceptions
    -funsigned-char
    -Wno-narrowing
    -g3
    -gdwarf-2
)

set(CMAKE_C_FLAGS "-mcpu=cortex-m4 -std=gnu11 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb")
set(CMAKE_CXX_FLAGS "-mcpu=cortex-m4 -std=c++17 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb")
set(CMAKE_AS_FLAGS "-mcpu=cortex-m4 -x assembler-with-cpp -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb")
set(CMAKE_EXE_LINKER_FLAGS "-mcpu=cortex-m4 -T${CMAKE_CURRENT_SOURCE_DIR}/STM32F411CEUX_FLASH.ld -Wl,-Map=${CMAKE_CURRENT_SOURCE_DIR}/build/${TARGET}.map,--cref -mcpu=cortex-m4 --specs=nosys.specs -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group")

enable_language(ASM)
set(STARTUP_ASM_FILE Core/Startup/startup_stm32f411ceux.s)

include_directories(
    .
    Module/Inc
    Library/ntshell-v0.3.1/lib
    Library/ntshell-v0.3.1/lib/core
    Library/ntshell-v0.3.1/lib/util
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
    Drivers/STM32F4xx_HAL_Driver/Inc
    Core/Inc
    arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi/arm-none-eabi/include
)

add_subdirectory(Module)
add_subdirectory(Drivers)
add_subdirectory(Library)
add_subdirectory(Core)

add_custom_target(zirconia)

set(ELF_FILE zirconia.elf)
set(HEX_FILE zirconia.hex)
set(BIN_FILE zirconia.bin)
set(MAP_FILE zirconia.map)

add_executable(${ELF_FILE}
    ${STARTUP_ASM_FILE}
    Core/Src/main.c
)
add_dependencies(zirconia ${ELF_FILE})
target_link_libraries(${ELF_FILE}
    Module
    Drivers
    Library
    Core
)

add_custom_command(TARGET ${ELF_FILE} POST_BUILD
    COMMAND ${OBJCOPY} -Obinary ${ELF_FILE} ${BIN_FILE}
    COMMAND ${OBJCOPY} -Oihex   ${ELF_FILE} ${HEX_FILE}
    COMMAND ${SIZE} --format=berkeley ${ELF_FILE} ${HEX_FILE}
)
