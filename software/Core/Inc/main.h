/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define SWITCH_Pin GPIO_PIN_13
#define SWITCH_GPIO_Port GPIOC
#define LED_YELLOW_Pin GPIO_PIN_14
#define LED_YELLOW_GPIO_Port GPIOC
#define LED_RED_Pin GPIO_PIN_15
#define LED_RED_GPIO_Port GPIOC
#define LED_GREEN_Pin GPIO_PIN_0
#define LED_GREEN_GPIO_Port GPIOH
#define LED_BLUE_Pin GPIO_PIN_1
#define LED_BLUE_GPIO_Port GPIOH
#define LED_FR_Pin GPIO_PIN_0
#define LED_FR_GPIO_Port GPIOA
#define LED_SR_Pin GPIO_PIN_1
#define LED_SR_GPIO_Port GPIOA
#define LED_SL_Pin GPIO_PIN_2
#define LED_SL_GPIO_Port GPIOA
#define LED_FL_Pin GPIO_PIN_3
#define LED_FL_GPIO_Port GPIOA
#define SEN_FR_Pin GPIO_PIN_4
#define SEN_FR_GPIO_Port GPIOA
#define SEN_SR_Pin GPIO_PIN_5
#define SEN_SR_GPIO_Port GPIOA
#define SEN_SL_Pin GPIO_PIN_6
#define SEN_SL_GPIO_Port GPIOA
#define SEN_FL_Pin GPIO_PIN_7
#define SEN_FL_GPIO_Port GPIOA
#define V_BAT_Pin GPIO_PIN_0
#define V_BAT_GPIO_Port GPIOB
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define MOT_RF_Pin GPIO_PIN_6
#define MOT_RF_GPIO_Port GPIOB
#define MOT_RR_Pin GPIO_PIN_7
#define MOT_RR_GPIO_Port GPIOB
#define MOT_LF_Pin GPIO_PIN_8
#define MOT_LF_GPIO_Port GPIOB
#define MOT_LR_Pin GPIO_PIN_9
#define MOT_LR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
