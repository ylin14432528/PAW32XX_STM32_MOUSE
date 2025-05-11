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
#include "stm32f1xx_hal.h"

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
#define DEFINE_Pin GPIO_PIN_1
#define DEFINE_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOA
#define NCS_Pin GPIO_PIN_3
#define NCS_GPIO_Port GPIOA
#define CV_Pin GPIO_PIN_12
#define CV_GPIO_Port GPIOB
#define CC_Pin GPIO_PIN_13
#define CC_GPIO_Port GPIOB
#define RIGHT_Pin GPIO_PIN_14
#define RIGHT_GPIO_Port GPIOB
#define RIGHT_EXTI_IRQn EXTI15_10_IRQn
#define MIDDLE_Pin GPIO_PIN_15
#define MIDDLE_GPIO_Port GPIOB
#define DPI_Pin GPIO_PIN_8
#define DPI_GPIO_Port GPIOA
#define LEFT_Pin GPIO_PIN_15
#define LEFT_GPIO_Port GPIOA
#define LEFT_EXTI_IRQn EXTI15_10_IRQn
#define LB_Pin GPIO_PIN_3
#define LB_GPIO_Port GPIOB
#define LB_EXTI_IRQn EXTI3_IRQn
#define RB_Pin GPIO_PIN_4
#define RB_GPIO_Port GPIOB
#define RB_EXTI_IRQn EXTI4_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
