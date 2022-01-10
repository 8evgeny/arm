/*!
  ******************************************************************************
  * \file			led.c
  * \brief			led.c file.
  * \details		Led control module (Source file).
  * \author			Arthur Markaryan
  * \date			26.03.2021
  * \copyright
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "led.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

// LED control module initialization.
void LED_init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW};

	/* Configure GPIO pin for Alarm LED*/
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = LED1_Pin;
	HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

	/* Configure GPIO pin for Write LED */
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = LED2_Pin;
	HAL_GPIO_Init(LED2_GPIO_Port, &GPIO_InitStruct);
}

// Turn on LED Alarm. 
void LED_setLED1(void){
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
}

// Turn off LED Alarm.
void LED_resetLED1(void){
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
}

// Turn on LED "Write".
void LED_setLED2(void){
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
}

// Turn off LED "Write".
void LED_resetLED2(void){
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
}

