/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SENSOR_FR_Pin GPIO_PIN_0
#define SENSOR_FR_GPIO_Port GPIOA
#define SENSOR_SR_Pin GPIO_PIN_1
#define SENSOR_SR_GPIO_Port GPIOA
#define SENSOR_SL_Pin GPIO_PIN_2
#define SENSOR_SL_GPIO_Port GPIOA
#define SENSOR_FL_Pin GPIO_PIN_3
#define SENSOR_FL_GPIO_Port GPIOA
#define LED_FR_Pin GPIO_PIN_4
#define LED_FR_GPIO_Port GPIOA
#define LED_SR_Pin GPIO_PIN_5
#define LED_SR_GPIO_Port GPIOA
#define LED_SL_Pin GPIO_PIN_6
#define LED_SL_GPIO_Port GPIOA
#define LED_FL_Pin GPIO_PIN_7
#define LED_FL_GPIO_Port GPIOA
#define V_BATTERY_Pin GPIO_PIN_0
#define V_BATTERY_GPIO_Port GPIOB
#define SWITCH_Pin GPIO_PIN_1
#define SWITCH_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define LED_BLUE_Pin GPIO_PIN_8
#define LED_BLUE_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_11
#define LED_GREEN_GPIO_Port GPIOA
#define LED_RED_Pin GPIO_PIN_12
#define LED_RED_GPIO_Port GPIOA
#define LED_YELLOW_Pin GPIO_PIN_13
#define LED_YELLOW_GPIO_Port GPIOA
#define MOTOR_RF_Pin GPIO_PIN_6
#define MOTOR_RF_GPIO_Port GPIOB
#define MOTOR_RR_Pin GPIO_PIN_7
#define MOTOR_RR_GPIO_Port GPIOB
#define MOTOR_LF_Pin GPIO_PIN_8
#define MOTOR_LF_GPIO_Port GPIOB
#define MOTOR_LR_Pin GPIO_PIN_9
#define MOTOR_LR_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
