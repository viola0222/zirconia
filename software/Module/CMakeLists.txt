cmake_minimum_required(VERSION 3.10)

add_library(Module STATIC
    Src/battery.c
    Src/communicate.c
    Src/encoder.c
    Src/flash.c
    Src/imu.c
    Src/interrupt.c
    Src/ir_sensor.c
    Src/module_test.c
    Src/motor.c
    Src/myshell.c
)
