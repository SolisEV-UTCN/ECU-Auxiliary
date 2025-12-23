/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "aux.h"

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
#define HORN_Pin GPIO_PIN_14
#define HORN_GPIO_Port GPIOC
#define HEARTHBEAT_Pin GPIO_PIN_0
#define HEARTHBEAT_GPIO_Port GPIOA
#define FAN_Pin GPIO_PIN_7
#define FAN_GPIO_Port GPIOA
#define SIGNAL_LEFT_Pin GPIO_PIN_0
#define SIGNAL_LEFT_GPIO_Port GPIOB
#define SIGNAL_RIGHT_Pin GPIO_PIN_1
#define SIGNAL_RIGHT_GPIO_Port GPIOB
#define BRAKE_Pin GPIO_PIN_2
#define BRAKE_GPIO_Port GPIOB
#define BACK_LIGHT_Pin GPIO_PIN_10
#define BACK_LIGHT_GPIO_Port GPIOB
#define FRONT_LIGHT_Pin GPIO_PIN_11
#define FRONT_LIGHT_GPIO_Port GPIOB
#define CAMERA_Pin GPIO_PIN_12
#define CAMERA_GPIO_Port GPIOB
#define ENABLE_POWER_Pin GPIO_PIN_13
#define ENABLE_POWER_GPIO_Port GPIOB
#define OFFLINE_FRONT_LIGHT_Pin GPIO_PIN_15
#define OFFLINE_FRONT_LIGHT_GPIO_Port GPIOB
#define OFFLINE_BACK_LIGHT_Pin GPIO_PIN_8
#define OFFLINE_BACK_LIGHT_GPIO_Port GPIOA
#define OFFLINE_MODE_Pin GPIO_PIN_9
#define OFFLINE_MODE_GPIO_Port GPIOA
#define OFFLINE_BRAKE_Pin GPIO_PIN_10
#define OFFLINE_BRAKE_GPIO_Port GPIOA
#define OFFLINE_REVERSE_Pin GPIO_PIN_4
#define OFFLINE_REVERSE_GPIO_Port GPIOB
#define OFFLINE_CAMERA_Pin GPIO_PIN_5
#define OFFLINE_CAMERA_GPIO_Port GPIOB
#define OFFLINE_HORN_Pin GPIO_PIN_6
#define OFFLINE_HORN_GPIO_Port GPIOB
#define OFFLINE_SIGNAL_RIGHT_Pin GPIO_PIN_7
#define OFFLINE_SIGNAL_RIGHT_GPIO_Port GPIOB
#define OFFLINE_FAN_Pin GPIO_PIN_8
#define OFFLINE_FAN_GPIO_Port GPIOB
#define OFFLINE_SIGNAL_LEFT_Pin GPIO_PIN_9
#define OFFLINE_SIGNAL_LEFT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
