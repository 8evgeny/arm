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
#include "stm32g0xx_hal.h"

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
#define GPIO_2_Pin GPIO_PIN_7
#define GPIO_2_GPIO_Port GPIOB
#define IRQ_FROM_42790_Pin GPIO_PIN_0
#define IRQ_FROM_42790_GPIO_Port GPIOA
#define IRQ_FROM_42790_EXTI_IRQn EXTI0_1_IRQn
#define Enable_42790_Pin GPIO_PIN_1
#define Enable_42790_GPIO_Port GPIOA
#define Enable_RS485_Pin GPIO_PIN_4
#define Enable_RS485_GPIO_Port GPIOA
#define Enable_2790_Pin GPIO_PIN_5
#define Enable_2790_GPIO_Port GPIOA
#define One_Wire_Pin GPIO_PIN_6
#define One_Wire_GPIO_Port GPIOA
#define WDT_OUT_Pin GPIO_PIN_7
#define WDT_OUT_GPIO_Port GPIOA
#define IRQ_FROM_7920_Pin GPIO_PIN_8
#define IRQ_FROM_7920_GPIO_Port GPIOA
#define IRQ_FROM_7920_EXTI_IRQn EXTI4_15_IRQn
#define GPIO_1_Pin GPIO_PIN_3
#define GPIO_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
