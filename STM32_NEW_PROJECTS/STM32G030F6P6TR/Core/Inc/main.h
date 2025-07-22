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
#define GPIO2_IN_Pin GPIO_PIN_7
#define GPIO2_IN_GPIO_Port GPIOB
#define IRQ_IN_Pin GPIO_PIN_0
#define IRQ_IN_GPIO_Port GPIOA
#define CE_OUT_Pin GPIO_PIN_1
#define CE_OUT_GPIO_Port GPIOA
#define UART_SEL_OUT_Pin GPIO_PIN_4
#define UART_SEL_OUT_GPIO_Port GPIOA
#define NSHDN_IN_Pin GPIO_PIN_5
#define NSHDN_IN_GPIO_Port GPIOA
#define One_Wire_Pin GPIO_PIN_6
#define One_Wire_GPIO_Port GPIOA
#define WDT_IN_Pin GPIO_PIN_7
#define WDT_IN_GPIO_Port GPIOA
#define XALERT_IN_Pin GPIO_PIN_8
#define XALERT_IN_GPIO_Port GPIOA
#define GPIO1_IN_Pin GPIO_PIN_3
#define GPIO1_IN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
