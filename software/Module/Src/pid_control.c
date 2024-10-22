#include "module_index.h"

float TIRE_RADIUS = 13 / 2;  // タイヤの半径[mm]
float Kp_straight = 3, Ki_straight = 0, Kd_straight = 0;
float Kp_rotate = 0, Ki_rotate = 0, Kd_rotate = 0;

int main() {
    float target_straight_velocity = 0;  // 目標速度[ms^-1]
    float target_rotate_velocity = 0;
    float current_straight_velocity;
    float current_rotate_velocity;

    float pid_straight_proportional_diff = 0;
    float pid_straight_integral_diff = 0;
    float pid_straight_differential_diff = 0;
    float pid_straight_differential_diff_before = 0;

    float pid_rotate_proportional_diff = 0;
    float pid_rotate_integral_diff = 0;
    float pid_rotate_differential_diff = 0;
    float pid_rotate_differential_diff_before = 0;

    float duty_l = 0, duty_r = 0;  // dutyは0~1000 "Module\src\motor.c"

    while (1) {
        // 1. 現在速を計算する

        current_straight_velocity = TIRE_RADIUS * (Encoder_GetAngle_Left() + Encoder_GetAngle_Right()) / 2;  // mm/ms
        current_rotate_velocity = IMU_GetGyro_Z();                                                           // rad/s

        // 2. 目標との差分を計算する
        pid_straight_proportional_diff = target_straight_velocity - current_straight_velocity;
        pid_straight_integral_diff += pid_straight_proportional_diff;
        pid_straight_differential_diff = pid_straight_differential_diff_before - pid_straight_proportional_diff;
        pid_straight_differential_diff_before = pid_straight_differential_diff;

        pid_rotate_proportional_diff = target_rotate_velocity - current_rotate_velocity;
        pid_rotate_integral_diff += pid_rotate_proportional_diff;
        pid_rotate_differential_diff = pid_rotate_differential_diff_before - pid_rotate_proportional_diff;
        pid_rotate_differential_diff_before = pid_rotate_differential_diff;

        // 3. PID制御 右が正
        duty_r = Kp_straight * pid_straight_proportional_diff + Ki_straight * pid_straight_integral_diff +
                 Kd_straight * pid_straight_differential_diff +
                 (Kp_rotate * pid_rotate_proportional_diff + Ki_rotate * pid_rotate_integral_diff + Kd_rotate * pid_rotate_differential_diff);
        duty_l = Kp_straight * pid_straight_proportional_diff + Ki_straight * pid_straight_integral_diff +
                 Kd_straight * pid_straight_differential_diff -
                 (Kp_rotate * pid_rotate_proportional_diff + Ki_rotate * pid_rotate_integral_diff + Kd_rotate * pid_rotate_differential_diff);

        duty_r = SIGN(duty_r) * MIN(950, ABS(duty_r));
        duty_l = SIGN(duty_l) * MIN(950, ABS(duty_l));
    }
}