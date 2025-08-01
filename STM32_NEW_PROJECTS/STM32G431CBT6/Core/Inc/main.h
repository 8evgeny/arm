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
#include "stm32g4xx_hal.h"

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ACOK_1_Pin GPIO_PIN_0
#define ACOK_1_GPIO_Port GPIOA
#define ADC_IAM_1_Pin GPIO_PIN_4
#define ADC_IAM_1_GPIO_Port GPIOA
#define ADC_IBM_1_Pin GPIO_PIN_5
#define ADC_IBM_1_GPIO_Port GPIOA
#define ADC_IAM_2_Pin GPIO_PIN_6
#define ADC_IAM_2_GPIO_Port GPIOA
#define ADC_IBM_2_Pin GPIO_PIN_7
#define ADC_IBM_2_GPIO_Port GPIOA
#define INT_1_Pin GPIO_PIN_0
#define INT_1_GPIO_Port GPIOB
#define PROCHOT_1_Pin GPIO_PIN_1
#define PROCHOT_1_GPIO_Port GPIOB
#define ADC_PSYS_1_Pin GPIO_PIN_2
#define ADC_PSYS_1_GPIO_Port GPIOB
#define ACOK_2_Pin GPIO_PIN_12
#define ACOK_2_GPIO_Port GPIOB
#define INT_2_Pin GPIO_PIN_13
#define INT_2_GPIO_Port GPIOB
#define PROCHOT_2_Pin GPIO_PIN_10
#define PROCHOT_2_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
