/*!
  ******************************************************************************
  * \file           HD44780.c
  * \brief          C library app for 4-, 8-bit parallel LCD interface
  * \details		Driver of HD44780 display.
  * \author			Donskih Dmitry, Arthur Markaryan
  * \date			02.03.2019, 25.03.2021
  * \copyright
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

#include "hd44780.h"

//#define GDMXPROJ
#define GET_GPIO_BIT(dat, weight) (GPIO_PinState)((dat>>weight)&1u)	// why?
#define HD44780_STROBE_TIME		5	//!< LCD time of strobe signal. Must be > 230 ns.
#define HD44780_DATA_LATCH		20	//!< The settling time of signals on the data bus. Must be > 230 ns.
#define TCMD_EXEC 				200	//!<

//
void HD44780_init(void){
	GPIO_InitTypeDef GPIO_InitStruct = {0, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW};

	/* Configure GPIO pins for LCD */

	HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_RS_Pin;
	HAL_GPIO_Init(HD44780_RS_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(HD44780_RW_GPIO_Port, HD44780_RW_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_RW_Pin;
	HAL_GPIO_Init(HD44780_RW_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(HD44780_EN_GPIO_Port, HD44780_EN_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_EN_Pin;
	HAL_GPIO_Init(HD44780_EN_GPIO_Port, &GPIO_InitStruct);

#ifdef HD44780_8BIT_BUS_REQURED
	HAL_GPIO_WritePin(HD44780_D0_GPIO_Port, HD44780_D0_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_D0_Pin;
	HAL_GPIO_Init(HD44780_D0_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(HD44780_D1_GPIO_Port, HD44780_D1_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_D1_Pin;
	HAL_GPIO_Init(HD44780_D1_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(HD44780_D2_GPIO_Port, HD44780_D2_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_D2_Pin;
	HAL_GPIO_Init(HD44780_D2_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(HD44780_D3_GPIO_Port, HD44780_D3_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_D3_Pin;
	HAL_GPIO_Init(HD44780_D3_GPIO_Port, &GPIO_InitStruct);
#endif // HD44780_8BIT_BUS_REQURED

	HAL_GPIO_WritePin(HD44780_D4_GPIO_Port, HD44780_D4_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_D4_Pin;
	HAL_GPIO_Init(HD44780_D4_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(HD44780_D5_GPIO_Port, HD44780_D5_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_D5_Pin;
	HAL_GPIO_Init(HD44780_D5_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(HD44780_D6_GPIO_Port, HD44780_D6_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_D6_Pin;
	HAL_GPIO_Init(HD44780_D6_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(HD44780_D7_GPIO_Port, HD44780_D7_Pin, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = HD44780_D7_Pin;
	HAL_GPIO_Init(HD44780_D7_GPIO_Port, &GPIO_InitStruct);

#ifdef HD44780_8BIT_BUS_REQURED
	//TO DO...
#endif // HD44780_8BIT_BUS_REQURED
#ifdef HD44780_4BIT_BUS_REQURED

	HD44780_setEN(0);				// Set EN to "0"
	usDelay(30000);					// Delay > 20 ms after power on.

	// Set on all pins of the control lines to the "0" (command write)
	HD44780_setRS(0);				// Set CMD mode
	HD44780_setRW(0);				// Write
	HD44780_setDataHigh(0x30);		// Setting the interface type (8 bits) (0x03 - high nibble of the command 0x30)
									// at the beginning ALWAYS switch the indicator to the 8-bit mode of operation.
	usDelay(1);						// Delay > 40 ns. This is the address preset time (tAS).

	HD44780_setEN(1);				// Start of strobe.
	HD44780_setEN(0);				// End of strobe.

	HD44780_setEN(1);				// Start of strobe.
	HD44780_setEN(0);				// End of strobe.

	HD44780_setEN(1);				// Start of strobe.
	HD44780_setEN(0);				// End of strobe.

	HD44780_setDataHigh(0x20);		// Setting the interface type (4 bits) (0x02 - high nibble of the command 0x20).
									// In this case, the RW and RS bits should not change!
	HD44780_setEN(1);				// Start of strobe.
	HD44780_setEN(0);				// End of strobe.
#endif // HD44780_4BIT_BUS_REQURED*/
}

//
void HD44780_writeCommand(uint8_t data){
	HD44780_writeByte(data, 0);
	usDelay(TCMD_EXEC);
}

//
void HD44780_writeData(uint8_t data){
	HD44780_writeByte(data, 1);
}

//
void HD44780_setDataLow(uint8_t data){
	HD44780_setDataBus((data << 4));
}

//
void HD44780_setDataHigh(uint8_t data){
	HD44780_setDataBus(data);
}

//
void HD44780_setDataBus(uint8_t data){
#ifdef HD44780_8BIT_BUS_REQURED
	HAL_GPIO_WritePin(HD44780_D0_GPIO_Port, HD44780_D0_Pin, GET_GPIO_BIT(data, 0));
	HAL_GPIO_WritePin(HD44780_D1_GPIO_Port, HD44780_D1_Pin, GET_GPIO_BIT(data, 1));
	HAL_GPIO_WritePin(HD44780_D2_GPIO_Port, HD44780_D2_Pin, GET_GPIO_BIT(data, 2));
	HAL_GPIO_WritePin(HD44780_D3_GPIO_Port, HD44780_D3_Pin, GET_GPIO_BIT(data, 3));
#endif // HD44780_8BIT_BUS_REQURED
#ifdef HD44780_4BIT_BUS_REQURED
	HAL_GPIO_WritePin(HD44780_D4_GPIO_Port, HD44780_D4_Pin, GET_GPIO_BIT(data, 4));
	HAL_GPIO_WritePin(HD44780_D5_GPIO_Port, HD44780_D5_Pin, GET_GPIO_BIT(data, 5));
	HAL_GPIO_WritePin(HD44780_D6_GPIO_Port, HD44780_D6_Pin, GET_GPIO_BIT(data, 6));
	HAL_GPIO_WritePin(HD44780_D7_GPIO_Port, HD44780_D7_Pin, GET_GPIO_BIT(data, 7));
#endif // HD44780_4BIT_BUS_REQURED
	usDelay(HD44780_DATA_LATCH);
}

// The RS line of the LCD is set to LOW / HIGH.
// state (0 - requred CMD, 1 - requred DATA)
void HD44780_setRS(uint8_t state){
	if (state){
		HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin, GPIO_PIN_RESET);
	}
}

// The RW line of the LCD is set to LOW / HIGH.
// state (0 - write mode, 1 - read mode).
void HD44780_setRW(uint8_t state){
	if (state){
		HAL_GPIO_WritePin(HD44780_RW_GPIO_Port, HD44780_RW_Pin, GPIO_PIN_SET);
	}else{
		HAL_GPIO_WritePin(HD44780_RW_GPIO_Port, HD44780_RW_Pin, GPIO_PIN_RESET);
	}
}

// The EN line of the LCD is set to LOW / HIGH.
// state (0 - start of strobe, 1 - end of strobe).
void HD44780_setEN(uint8_t state){
	if (state){
		HAL_GPIO_WritePin(HD44780_EN_GPIO_Port, HD44780_EN_Pin, GPIO_PIN_SET);
		usDelay(HD44780_STROBE_TIME); 	// Stobe delay must be > 230 ns
	}else{
		HAL_GPIO_WritePin(HD44780_EN_GPIO_Port, HD44780_EN_Pin, GPIO_PIN_RESET);
		usDelay(100);					// Delay > 270 ns. Minimum allowable interval between signals EN = 1
	}

}

//
void usDelay(uint16_t us){

	TIM1->CNT = 0;
	while(TIM1->CNT < us){};	// Почему так?

}

// LCD write cycle
void HD44780_writeByte(uint8_t data, uint8_t state){
  	// Preparing the LCD for data recording.
	HD44780_setRS(state);	// Set CMD mode
	HD44780_setRW(0);		// Write.
	HD44780_setEN(0);		// Start of strobe.

#ifdef HD44780_8BIT_BUS_REQURED
	// Preparing data for sending.
	HD44780_setDataBus(data);
	// We send the junior data tetrad to the port.
	HD44780_setEN(1);		// Start of strobe
	HD44780_setEN(0);		// Start of strobe.
#endif	//HD44780_8BIT_BUS_REQURED

#ifdef HD44780_4BIT_BUS_REQURED
  	// Preparing the data of the senior notebook for sending.
	HD44780_setDataHigh(data);

	// First, we send the senior data tetrad to the port.
  	HD44780_setEN(1);		// Start of strobe
  	HD44780_setEN(0);		// Start of strobe

	// Preparing the data of the junior tetrad for sending.
  	HD44780_setDataLow(data);

    // We send the junior data tetrad to the port.
  	HD44780_setEN(1);		// Start of strobe
  	HD44780_setEN(0);		// Start of strobe.
#endif	//HD44780_4BIT_BUS_REQURED
}
/*
// Цикл чтения из ЖКИ
uint8_t HD44780_readByte(void){
	uint8_t data = 0;

	// Принимаем данные из порта (Все 8 бит)
	HD44780_STARTSTB();				// Начало строба
	usDelay(1);			// Необходимо для установки состояния на линии HD44780_wire_EN
    //data = HD44780_PINDATA; 		// читаем данные (AVR)
	//data = HD44780_DATA_PxIN;		// Читаем данные
	//data |=
    HD44780_ENDSTB(); 				// Конец строба

#ifdef HD44780_4BIT_BUS_REQURED

    // Запоминаем старшую тетраду
	uint8_t temp = ((data & 0x0F)<<4);

	// Принимаем данные из порта (Все 8 бит)
  	HD44780_STARTSTB(); 			// Начало строба
  	__asm__("NOP");					// Необходимо для установки состояния на линии HD44780_wire_EN
    //data = HD44780_PINDATA; 		// читаем младшую тетраду	(AVR)
  	//data = HD44780_DATA_PxIN;		// Читаем данные
    HD44780_ENDSTB(); 				// Конец строба

    // Оставляем в data только младшую тетраду
    //SWAP(data);				// младшую тетраду на свое место (AVR)
    data &= 0x0F;				// Очищаем старшую тетраду в data
    //temp &= 0xf0;				// Очищаем младшую тетраду в temp (AVR)
    data |= temp;				// Совмещаем тетрады

#else
  	// TO DO...
#endif//HD44780_4BIT_BUS_REQURED

    return data;
}

// Цикл ожидания готовности
uint8_t HD44780_wait(void){
	// Результат работы функции
	uint8_t result = 0;

	// Чтение команды
  	HD44780_RQCMD();
	HD44780_RQRD();

	// Инициализируем переменную для контроля таймаута
	#ifdef HD44780_TIMEOUT_CONTROL_ENABLE
	uint32_t timeout = HD44780_BUSY_TIMEOUT;
	#else
	uint32_t timeout = 1;
	#endif //HD44780_TIMEOUT_CONTROL_ENABLE

	// Ждем, пока не вышел таймаут
	while(timeout-- > 0 ){
		// Если флаг BF установлен, то ждем
		if(HD44780_BUSY_FLAG & HD44780_readByte()){
			usDelay(HD44780_BUSY_TIMEOUT_STEP_us);
		}else{
			result = 1;
			break;
		}
	}

	return(result);
}
*/
