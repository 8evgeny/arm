/*!
 * \file		hd44780.h
 * \brief		Модуль hd44780.h (заголовочный файл).
 * \details		Модуль драйвера ЖК дисплеем HD44780.
 * \author		Donskih Dmitry, Артур Маркарян
 * \date		02.03.2019
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

#ifndef _HD44780_H_
#define _HD44780_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

//-------------------Defines of hardware parameters---------------------------//

#ifdef GV_INFOBOARD_V1
#	define HD44780_4BIT_BUS_REQURED		//!< 4-bit mode of the LCD bus. 
#endif /* GV_INFOBOARD_V1 */
#ifdef GV_INFOBOARD_V2
#	define HD44780_8BIT_BUS_REQURED		//!< 8-bit mode of the LCD bus. 
#endif /* GV_INFOBOARD_V2 */

// LCD mode
#define HD44780_TIMEOUT_CONTROL_ENABLE		//!< Uncomment if necessary to enable BF LCD timeout control.
#define HD44780_4BIT_BUS_REQURED			//!< Uncomment if a 4-bit data bus is required.

// Driver flags
#define HD44780_BUSY_TIMEOUT_FLAG	0x01	//!< BF flag timeout for HD44780.

// LCD parameters
#define HD44780_ROW_SIZE	20				//!< Number of symbols per row.
#define HD44780_ROW_NUM		4	  			//!< Number of rows.
#define HD44780_SCREEN_SIZE	HD44780_ROW_SIZE*HD44780_ROW_NUM

#define HD44780_LINE1_START	0x00			//!< The starting address of the first line of segments.
#define HD44780_LINE2_START	0x40			//!< The starting address of the second line of segments.

#if (4 == HD44780_ROW_NUM)
// Starting addresses of lines for a 4-line LCD.
#define HD44780_ROW1_START	HD44780_LINE1_START
#define HD44780_ROW2_START	HD44780_LINE2_START
#define HD44780_ROW3_START	HD44780_ROW1_START + HD44780_ROW_SIZE
#define HD44780_ROW4_START	HD44780_ROW2_START + HD44780_ROW_SIZE
#elif(2 == HD44780_ROW_NUM)
// Starting addresses of lines for a 2-line LCD.
#define HD44780_ROW1_START	HD44780_LINE1_START
#define HD44780_ROW2_START	HD44780_LINE2_START
#elif(1 == HD44780_ROW_NUM)
// Starting addresses of lines for a 1-line LCD.
#define HD44780_ROW1_START	HD44780_LINE1_START
#else
// Undefined LCD.
#error Unknown HD44780 format
#endif//#if (4 == HD44780_ROW_NUM)

//---------------------------Define I/O PORTS---------------------------------//

// Description of control and data buses between MCU and LCD. 

/* \{ */
/*!
 * \name	Data bus.
 */
#ifdef GV_INFOBOARD_V1		
#	define HD44780_D4_Pin 			GPIO_PIN_4	//!< D4-pin for LCD CTRL in 4-bit bus mode
#	define HD44780_D4_GPIO_Port 	GPIOA		//!< D4-port for LCD CTRL in 4-bit bus mode
#	define HD44780_D5_Pin 			GPIO_PIN_5
#	define HD44780_D5_GPIO_Port 	GPIOA
#	define HD44780_D6_Pin 			GPIO_PIN_6
#	define HD44780_D6_GPIO_Port 	GPIOA
#	define HD44780_D7_Pin 			GPIO_PIN_7
#	define HD44780_D7_GPIO_Port 	GPIOA
#endif /* GV_INFOBOARD_V1 */
#ifdef GV_INFOBOARD_V2
#	define HD44780_D0_Pin 			GPIO_PIN_0
#	define HD44780_D0_GPIO_Port 	GPIOA
#	define HD44780_D1_Pin 			GPIO_PIN_1
#	define HD44780_D1_GPIO_Port 	GPIOA
#	define HD44780_D2_Pin 			GPIO_PIN_2
#	define HD44780_D2_GPIO_Port 	GPIOA
#	define HD44780_D3_Pin 			GPIO_PIN_3
#	define HD44780_D3_GPIO_Port 	GPIOA
#	define HD44780_D4_Pin 			GPIO_PIN_4	//!< D4-pin for LCD CTRL in 8-bit bus mode
#	define HD44780_D4_GPIO_Port 	GPIOA		//!< D4-port for LCD CTRL in 8-bit bus mode
#	define HD44780_D5_Pin 			GPIO_PIN_5
#	define HD44780_D5_GPIO_Port 	GPIOA
#	define HD44780_D6_Pin 			GPIO_PIN_6
#	define HD44780_D6_GPIO_Port 	GPIOA
#	define HD44780_D7_Pin 			GPIO_PIN_7
#	define HD44780_D7_GPIO_Port 	GPIOA
#endif /* GV_INFOBOARD_V2 */
/*! \} */

// Control lines of HD44780. 

// The backlight is controlled differently.

/* \{ */
/*!
 * \name	RS control output for LCD module. 
 */
#ifdef GV_INFOBOARD_V1
#	define HD44780_RS_Pin 			GPIO_PIN_1	//!< RS-pin for LCD CTRL in 4-bit bus mode
#	define HD44780_RS_GPIO_Port 	GPIOA		//!< RS-port for LCD CTRL in 4-bit bus mode
#endif /* GV_INFOBOARD_V1 */
#ifdef GV_INFOBOARD_V2
#	define HD44780_RS_Pin 			GPIO_PIN_0	//!< RS-pin for LCD CTRL in 8-bit bus mode
#	define HD44780_RS_GPIO_Port 	GPIOB		//!< RS-port for LCD CTRL in 8-bit bus mode
#endif /* GV_INFOBOARD_V2 */
/*! \} */

/* \{ */
/*!
 * \name	RW control output for LCD module.
 */
#ifdef GV_INFOBOARD_V1
#	define HD44780_RW_Pin 			GPIO_PIN_2	//!< RW-pin for LCD CTRL in 4-bit bus mode
#	define HD44780_RW_GPIO_Port 	GPIOA		//!< RW-port for LCD CTRL in 4-bit bus mode
#endif /* GV_INFOBOARD_V1 */
#ifdef GV_INFOBOARD_V2
#	define HD44780_RW_Pin 			GPIO_PIN_1	//!< RW-pin for LCD CTRL in 8-bit bus mode
#	define HD44780_RW_GPIO_Port 	GPIOB		//!< RW-port for LCD CTRL in 8-bit bus mode
#endif /* GV_INFOBOARD_V2 */
/*! \} */

/* \{ */
/*!
 * \name	EN control output for LCD module.
 */
#ifdef GV_INFOBOARD_V1
#	define HD44780_EN_Pin 			GPIO_PIN_3	//!< EN-pin for LCD CTRL in 4-bit bus mode
#	define HD44780_EN_GPIO_Port 	GPIOA		//!< EN-port for LCD CTRL in 4-bit bus mode
#endif /* GV_INFOBOARD_V1 */
#ifdef GV_INFOBOARD_V2
#	define HD44780_EN_Pin 			GPIO_PIN_2	//!< EN-pin for LCD CTRL in 8-bit bus mode
#	define HD44780_EN_GPIO_Port 	GPIOB		//!< EN-port for LCD CTRL in 8-bit bus mode
#endif /* GV_INFOBOARD_V2 */
/*! \} */

//-----------------------Structures definitions-------------------------------//



//--------------------Define functions and macroses---------------------------//

// Lowlevel LCD command.

// RS-line state: data / command

// Select LCD data mode
#define HD44780_RQDATA()			do{HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin, GPIO_PIN_SET);}while(0)

// Select LCD command mode.
#define HD44780_RQCMD()				do{HAL_GPIO_WritePin(HD44780_RS_GPIO_Port, HD44780_RS_Pin, GPIO_PIN_RESET);}while(0)

// Setting the direction of exchange on the data bus.
// Read data from LCD.
#define HD44780_RQRD()	 			do{HAL_GPIO_WritePin(HD44780_RW_GPIO_Port, HD44780_RW_Pin, GPIO_PIN_SET);}while(0)

// Write data to LCD
#define HD44780_RQWR()	 			do{HAL_GPIO_WritePin(HD44780_RW_GPIO_Port, HD44780_RW_Pin, GPIO_PIN_RESET);}while(0)

// Setting the exchange cycle on the data bus.
// Start of data exchange strobe.
#define HD44780_STARTSTB() 			do{HAL_GPIO_WritePin(HD44780_EN_GPIO_Port, HD44780_EN_Pin, GPIO_PIN_SET);}while(0)

// End of data exchange strobe.
#define HD44780_ENDSTB()			do{HAL_GPIO_WritePin(HD44780_EN_GPIO_Port, HD44780_EN_Pin, GPIO_PIN_RESET);}while(0)

// Backlight control

#define HD44780_BACKLIGHT_ON()		do{__asm__("NOP");}while(0)	// Temporary stub! Then you need to do this through another microcontroller.
#define HD44780_BACKLIGHT_OFF()		do{__asm__("NOP");}while(0)	// Temporary stub! Then you need to do this through another microcontroller.

// Defines of LCD commands.

#define HD44780_CLEAR()					HD44780_writeCommand(0x01)
#define HD44780_RESET()					HD44780_writeCommand(0x02)
#define HD44780_AC_DEC_MODE()			HD44780_writeCommand(0x04)
#define HD44780_AC_INC_MODE()			HD44780_writeCommand(0x06)
#define HD44780_SHIFT_LEFT_MODE()		HD44780_writeCommand(0x05)
#define HD44780_SHIFT_RIGHT_MODE()		HD44780_writeCommand(0x07)
#define HD44780_DISPLAY_ON()			HD44780_writeCommand(0x0C)
#define HD44780_DISPLAY_OFF()			HD44780_writeCommand(0x08)
#define HD44780_CURSOR_ON()				HD44780_writeCommand(0x0E)
#define HD44780_CURSOR_OFF()			HD44780_writeCommand(0x08)
#define HD44780_BLANK_ON()				HD44780_writeCommand(0x0D)
#define HD44780_BLANK_OFF()				HD44780_writeCommand(0x08)
#define HD44780_SET_CURSOR_LEFT()		HD44780_writeCommand(0x10)
#define HD44780_SET_CURSOR_RIGHT()		HD44780_writeCommand(0x14)
#define HD44780_SET_DISPLAY_LEFT()		HD44780_writeCommand(0x18)
#define HD44780_SET_DISPLAY_RIGHT()		HD44780_writeCommand(0x1C)
#define HD44780_SET_CGR_ADDR(a)			HD44780_writeCommand(0x40 | a)
#define HD44780_SET_DDR_ADDR(a)			HD44780_writeCommand(0x80 | a)

// LCD main parameters.
#define HD44780_SETUP(param)			HD44780_writeCommand(0x20 | param)
#define HD44780_BUS4					0
#define HD44780_BUS8					(1 << 4)
#define HD44780_1ROW					0
#define HD44780_2ROW					(1 << 3)
#define HD44780_5x8CHAR					0
#define HD44780_5x10CHAR				(1 << 2)
#define HD44780_PAGE0					(0x08)
#define HD44780_PAGE1					(0x0A)

// Define LCD bus width.
#ifdef  HD44780_4BIT_BUS_REQURED
#define HD44780_BUS_MODE				HD44780_BUS4
#else
#define HD44780_BUS_MODE				HD44780_BUS8
#endif//HD44780_4BIT_BUS_REQURED

// LCD busy flag BF
#define HD44780_BUSY_FLAG				(1 << 7)

// LCD busy timeout, us
#define HD44780_BUSY_TIMEOUT_us			1600	// User defined parameter
#define HD44780_BUSY_TIMEOUT_STEP_us	100
#define HD44780_BUSY_TIMEOUT			(HD44780_BUSY_TIMEOUT_us / HD44780_BUSY_TIMEOUT_STEP_us)

//-----------------------Function declarationes-------------------------------//

/*! \brief		Initial LCD initialization based on HD44780 controller. initial GPIO for control LCD.
 *  \details	The controller manufacturer recommends the following initialization sequence: 
 *				1. Maintain a pause of at least 15 ms between the establishment
 *				of the operating supply voltage (> 4.5 V) and the performance of any operations with the controller.
 *				2. The first operation is to execute the command that selects the bus width
 *				(it must be the 0x30 command regardless of which interface you are going to use in the future),
 *				and do not check the value of the BF flag before performing this operation.
 *				3. Hold a pause of at least 4.1 ms.
 *				4. Repeat the command to select the bus width, also without checking the state of the BF flag before.
 *				5. Hold a pause of at least 100 µs.
 *				6. Repeat the command to select the bus width, also without checking the state of the BF flag before.
 *				These operations are initializing, and are designed to bring the controller to the initial operating mode
 *				(i.e. to switch to the operating mode with an 8-bit data bus) following this normal order (without pauses,
 *				but checking the BF flag), the operating modes are initialized , including the command for setting the bus width.
 *  \param		none.
 *  \return		none.
 */	void HD44780_init(void);

/*! \brief		The RS line of the LCD is set to LOW / HIGH.
 *  \details	Function of setting the level on the RS line for LCD.
 *  \param		state (0 - requred CMD, 1 - requred DATA)
 *  \retval		None.
 */ void HD44780_setRS(uint8_t state);

/*! \brief		The RW line of the LCD is set to LOW / HIGH.
 *  \details	Function of setting the level on the RW line for LCD.
 *  \param		state (0 - write mode, 1 - read mode).
 *  \retval		None.
 */	void HD44780_setRW(uint8_t state);

/*! \brief		The EN line of the LCD is set to LOW / HIGH.
 *  \details	Function of setting the level on the EN line for LCD.
 *  \param		state (0 - start of strobe, 1 - end of strobe).
 *  \retval		None.
 */	void HD44780_setEN(uint8_t state);

/*
 * Lowlevel LCD interface control functions
*/

/*! \brief		Write cycle for LCD.
 *  \details	Write byte to the LCD data bus (command or data).
 *  \param		data - byte to be written.
 *  \param		state - 0 if command byte, 1 - if data.
 *  \retval		None.
 */	void HD44780_writeByte(uint8_t data, uint8_t state);

/*! \brief		Цикл чтения из ЖКИ.
 *  \details	Перед циклом должны быть произведены установки линий:
 *  			HD44780_wire_RS(команда/данные)
 *  			HD44780_wire_RW(запись/чение) = 1
 *	\note		ПРЕДУПРЕЖДЕНИЕ!!! Во избежание порчи данных в неиспользуемых линиях порта данных
 *				ЖКИ в 4-х битном режиме, желательно запрещать прерывания, код которых
 *				взаимодействует со свободными линиями порта, либо в прерывании запоминать
 *				состояние регистров порта, перед внесением изменений, и восстанавливать данные
 *				по завершению прерывания.
 */	//uint8_t HD44780_readByte(void);

/*! \brief		Waiting cycle for LCD readiness.
 *	\param		None.
 *  \return		Returns 1 if the LCD is ready and there is no timeout, otherwise 0.
 */	//uint8_t HD44780_wait(void);

	void HD44780_setDataLow(uint8_t data);
	void HD44780_setDataHigh(uint8_t data);
	void HD44780_setDataBus(uint8_t data);
	void HD44780_writeCommand(uint8_t data);
	void HD44780_writeData(uint8_t data);

void usDelay(uint16_t us);

#ifdef __cplusplus
}
#endif

#endif /* _HD44780_H_ */
