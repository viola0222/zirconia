cmake_minimum_required(VERSION 3.10)

add_library(Core STATIC
    Src/adc.c
    Src/dma.c
    Src/gpio.c
    Src/spi.c
    Src/stm32f4xx_hal_msp.c
    Src/stm32f4xx_it.c
    Src/syscalls.c
    Src/sysmem.c
    Src/system_stm32f4xx.c
    Src/tim.c
    Src/usart.c
)
