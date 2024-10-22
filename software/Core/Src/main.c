/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "module_index.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick.
     */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
    MX_ADC1_Init();
    MX_TIM1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_SPI2_Init();
    /* USER CODE BEGIN 2 */
    LED_ALL_ON();              // LED全点灯
    Communicate_Initialize();  // ターミナルとの通信初期設�?
    Motor_Initialize();        // モータ用タイマ�?�期設�?
    Encoder_Initialize();      // エンコー�?ー用タイマ�?�期設�?
    IMU_Initialize();          // IMU用通信およびICM42688Pの初期設�?
    Sensor_Initialize();       // 壁センサ用AD変換およびタイマ�?�期設�?
    Interrupt_Initialize();    // メイン割り込み処�?の初期設�?
    Myshell_Initialize();      // シェルの初期設�?

    Battery_LimiterVoltage();  // バッ�?リの電圧管�?
    module_test();             // �?機�?�の動作確認（動作確認が完�?したらコメントアウトして下さ�?�?
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    float target_straight_velocity = 0;  // 目標速度[ms^-1]
    float target_rotate_velocity = 0;
    float current_straight_velocity;
    float current_rotate_velocity;
    float TIRE_RADIUS = 13 / 2;  // タイヤの半径[mm]

    float pid_straight_proportional_diff = 0;
    float pid_straight_integral_diff = 0;
    float pid_straight_differential_diff = 0;
    float pid_straight_differential_diff_before = 0;

    float pid_rotate_proportional_diff = 0;
    float pid_rotate_integral_diff = 0;
    float pid_rotate_differential_diff = 0;
    float pid_rotate_differential_diff_before = 0;

    float Kp_straight = 3, Ki_straight = 0, Kd_straight = 0;
    float Kp_rotate = 0, Ki_rotate = 0, Kd_rotate = 0;

    float duty_l = 0, duty_r = 0;  // dutyは0~1000 "Module\src\motor.c"

    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        // ここにメインループ�?�処�?を記述する
        // Myshell_Execute();

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

        // 4. Dutyをつっこむ
        Motor_SetDuty_Left(duty_l);
        Motor_SetDuty_Right(duty_r);

        // 5. 制御周期は1msだから1msまつ
        HAL_Delay(1);
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 192;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK) {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {}
    /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line) {
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line
       number, ex: printf("Wrong parameters value: file %s on line %d\r\n", file,
       line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
