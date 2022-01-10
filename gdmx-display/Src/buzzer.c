/*!
  ******************************************************************************
  * \file			buzzer.c
  * \brief			buzzer.c file.
  * \details		Buzzer control module (Source file).
  * \author			Arthur Markaryan
  * \date			26.03.2021
  * \copyright
  */

/* Includes ------------------------------------------------------------------*/
#include "buzzer.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void BUZZER_init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW};

	/* Configure GPIO pin for Buzzer*/
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = BUZZER_Pin;
	HAL_GPIO_Init(BUZZER_GPIO_Port, &GPIO_InitStruct);
}

//
void BUZZER_set(void){
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_SET);
}

//
void BUZZER_reset(void){
	HAL_GPIO_WritePin(BUZZER_GPIO_Port, BUZZER_Pin, GPIO_PIN_RESET);
}
