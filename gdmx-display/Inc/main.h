/*!
 * \file		main.h
 * \brief		Header for main.c file.
 * \details		Main module (header file).
 * \author		Donskih Dmitry, Arthur Markaryan
 * \date		02.03.2019, 23.03.2021
 * \attention
 *
 * <h2><center>&copy; Copyright (c) 2019 - 2021 Donskih Dmitriy.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by Donskih Dmitriy under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MAIN_H_
#define _MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/

#include "led.h"
#include "buzzer.h"
#include "display.h"

/* Private defines -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/*!
 * \brief		FreeRTOS error handler function
 * \details		This function is executed in case of error occurrence.
 * 				User can add his own implementation to report the HAL error return state.
 * \param		None
 * \retval		None
 */	void Error_Handler(void);

/*!
 * \brief		System Clock Configuration
 * \details		Initializes the CPU, AHB and APB busses clocks.
 * \param		None
 * \retval		None
 */	void SystemClock_Config(void);
#if 0
/*!
 * \brief		TIM1 Initialization Function
 * \details		This timer used for FreeRTOS functionality.
 * \param		None
 * \retval		None
 */	/*static*/ void MX_TIM1_Init(void);
#endif
/*!
 * \brief		FreeRTOS start default task function
 * \details		Function implementing the defaultTask thread.
 * \param		argument: Not used
 * \retval		None
 */	void StartDefaultTask(void const * argument);

/*!
 * \brief		USB stack procedure function
 * \details		Function implementing the usbProcTask thread.
 * \param		argument: Not used
 * \retval		None
 */	void usbProceed(void const * argument);

#ifdef __cplusplus
}
#endif

#endif /* _MAIN_H_ */
