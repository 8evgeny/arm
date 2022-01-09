/*!
  ******************************************************************************
  * \file			main.c
  * \brief			Main program body
  * \details		Main module (source file).
  * \author			Donskih Dmitry, Arthur Markaryan
  * \date			02.03.2019
  ******************************************************************************
  * \attention
  *
  * <h2><center>&copy; Copyright (c) 2018 - 2021 Donskih Dmitry.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Donskih Dmitry under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

/* Private includes ----------------------------------------------------------*/

#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

/*
const char test[]=					"                    " \
									"                    " \
									"    System Loaded   " \
									"                    ";
*/
osThreadId defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;

static osThreadId usbProcTaskHandle;
uint32_t myTask04Buffer[ 128 ];
osStaticThreadDef_t myTask04ControlBlock;

osMutexId usbRxMutexHandle;
osStaticMutexDef_t usbRxMutexControlBlock;

/* Private user code ---------------------------------------------------------*/

/*!
 * \brief		TIM1 Initialization Function
 * \details		This timer used for FreeRTOS functionality.
 * \param		None
 * \retval		None
 */	static void MX_TIM1_Init(void);

/*!
 * \brief		The application entry point
 * \param		None
 * \retval		int
 */	int main(void)
{
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClock_Config();

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/* System timer for FreeRTOS initialization */
	MX_TIM1_Init();

	/*
	 * Initialize all configured peripherals
	 */

	/* Configure GPIO pin for Leds */
	LED_init();

	/* Configure GPIO pin for Buzzer */
	BUZZER_init();

	/* Configure GPIO pins and startup sequence for LCD */
	DISPLAY_init();

	/* Create the mutex(es) */
	/* definition and creation of usbRxMutex */
	osMutexStaticDef(usbRxMutex, &usbRxMutexControlBlock);
	usbRxMutexHandle = osMutexCreate(osMutex(usbRxMutex));

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128, defaultTaskBuffer, &defaultTaskControlBlock);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* definition and creation of usbProcTask */
	osThreadStaticDef(usbProcTask, usbProceed, osPriorityNormal, 0, 128, myTask04Buffer, &myTask04ControlBlock);
	usbProcTaskHandle = osThreadCreate(osThread(usbProcTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* Start scheduler */
	osKernelStart();
  
	/* We should never get here as control is now taken by the scheduler */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{

	}
}

/* System Clock Configuration */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Error_Handler();
	}

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
	PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
		Error_Handler();
	}
}

/* TIM1 Initialization Function */
static void MX_TIM1_Init(void)
{
	//
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	//
	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 72;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 0xffff;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}

	//
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}

	//
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	//
	HAL_TIM_Base_Start(&htim1);
}

/* Function implementing the defaultTask thread */
void StartDefaultTask(void const * argument)
{
	/* Init code for USB_DEVICE */
	MX_USB_DEVICE_Init();

	/* Init code for LCD */
	DISPLAY_init();

	/* Init code for LEDs and Buzzer */
	LED_resetLED1();
	LED_resetLED2();
	BUZZER_reset();
	osDelay(50);

	osThreadSetPriority(usbProcTaskHandle,osPriorityNormal);

	osThreadTerminate(defaultTaskHandle);
}

/* USB stack procedure function */
void usbProceed(void const * argument)
{
	while(1)
	{
		osDelay(1000);
	}
}

/* FreeRTOS error handler function */
void Error_Handler(void)
{
	osThreadTerminate(usbProcTaskHandle);
}

#ifdef  USE_FULL_ASSERT
/*!
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
