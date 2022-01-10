/*! \file		display.h
 *  \brief		Display module (header file). 
 *  \details	Display control module. 
 *  \author		Arthur Markaryan
 *  \date		31.03.2021
 *  \copyright	
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#ifdef __cplusplus
extern "C" {
#endif

// Standart libraries
#include <stdint.h>
#include <stdio.h>

// Device specific libraries
#include "stm32f1xx_hal.h"

// Custom modules include
//#include "debug.h"
#include "hd44780.h"

//-------------------Defines of hardware parameters---------------------------//

//! Display video page render interval, ms 
#define DISPLAY_REFRESH_INTERVAL			60

/* \{ */
/*!
 * \name	Framebuffer parameters 
 */
//! Number of characters per line 
#define DISPLAY_ROW_SIZE					HD44780_ROW_SIZE
//! Number of lines 
#define DISPLAY_ROW_NUM						HD44780_ROW_NUM
/*! \} */

//-----------------------Structures definitions-------------------------------//



//--------------------Define functions and macroses---------------------------//



//-----------------------Function declarationes-------------------------------//

/*! \brief		Display initialization. 
 *  \details	Display control module initialization function. 
 */	void DISPLAY_init(void);

/*! \brief		Display clear.
 *  \details	Display cleaning function. 
 */	void DISPLAY_clear(void);

/*! \brief		Setting the display buffer. 
 *  \details	Display buffer setting function. 
 *  \param		buffer - Pointer to a two-dimensional buffer of displayed information. 
 */	void DISPLAY_setRenderBuffer(uint8_t **buffer);

/*! \brief		Cursor mode control. 
 *  \details	A function that controls the mode of the cursor. 
 *  \param		mode - cursor operation mode. Bit0 - On / Off, Bit1 - BlankOn / BlankOff. 
 */	void DISPLAY_setCursorMode(uint8_t mode);

/*! \brief		Moves the cursor to the specified position. 
 *  \details	The function of moving the cursor to the X, Y position. 
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N). 
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N). 
 *  \note		The origin is in the upper left corner of the display. 
 */	uint8_t DISPLAY_moveCursorXY(uint8_t X, uint8_t Y);

/*! \brief		Print the character at the current position.
 *  \details	The function of printing a character at the current cursor position on the display. 
 *  \param		Symbol - the displayed symbol. 
 */	void DISPLAY_printSymbol(uint8_t Symbol);

/*! \brief		Printing a character at the current position from FLASH memory. 
 *  \details	The function of printing a character at the current cursor position on the display. 
 *  \param		ptrSymbol - pointer to the displayed symbol in FLASH memory.
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
	void DISPLAY_printSymbolFromFlash(__flash uint8_t *ptrSymbol);
#elif defined(__GNUC__)
	void DISPLAY_printSymbolFromFlash(volatile uint8_t * const ptrSymbol);
#else
#error Compiler not supported!
#endif

/*! \brief		Prints a character at the specified position.
 *  \details	The function of printing a character in the X, Y position.
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N). 
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N). 
 *  \param		Symbol - the displayed symbol. 
 *  \note		The origin is in the upper left corner of the display. 
 */	void DISPLAY_printSymbolXY(uint8_t X, uint8_t Y, uint8_t Symbol);

/*! \brief		Print a character at a specified position from FLASH memory. 
 *  \details	The function of printing a character from FLASH memory to position X, Y. 
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N). 
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N). 
 *  \param		ptrSymbol - pointer to the displayed symbol in FLASH memory. 
 *  \note		The origin is in the upper left corner of the display. 
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
	void DISPLAY_printSymbolXYFromFlash(uint8_t X, uint8_t Y, __flash uint8_t *ptrSymbol);
#elif defined(__GNUC__)
	void DISPLAY_printSymbolXYFromFlash(uint8_t X, uint8_t Y, volatile uint8_t * const ptrSymbol);
#else
#error Compiler not supported!
#endif

/*! \brief		Print a string. 
 *  \details	Function of printing the string at the current cursor position on the display. 
 *  \param		String - the string to be printed.
 *  \note		The origin is in the upper left corner of the display. 
 */	void DISPLAY_printString(uint8_t *String);

 // Function of printing the Screen from the (0, 0) position on the display.
 void DISPLAY_printScreen(uint8_t *Screen);

/*! \brief		Print a string from FLASH memory at the current position. 
 *  \details	Function of printing a string from FLASH memory at the current cursor position on the display. 
 *  \param		String - the string to be printed.
 *  \note		The origin is in the upper left corner of the display. 
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
	void DISPLAY_printStringFromFlash(__flash uint8_t *String);
#elif defined(__GNUC__)
	void DISPLAY_printStringFromFlash(volatile uint8_t * const String);
#else
#error Compiler not supported!
#endif

/*! \brief		Print the string at the specified position.
 *  \details	The function of printing a line to position X, Y. 
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N).
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N).
 *  \param		String - the string to be printed.
 *  \note		The origin is in the upper left corner of the display. 
 */	void DISPLAY_printStringXY(uint8_t X, uint8_t Y, uint8_t *String);

/*! \brief		Printing a line from FLASH memory to position X, Y. 
 *  \details	Function of printing a line from FLASH memory to position X, Y on the display. 
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N). 
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N). 
 *  \param		String - string to be printed. 
 *  \note		The origin is in the upper left corner of the display. 
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
	void DISPLAY_printStringXYFromFlash(uint8_t X, uint8_t Y, __flash uint8_t *String);
#elif defined(__GNUC__)
	void DISPLAY_printStringXYFromFlash(uint8_t X, uint8_t Y, volatile uint8_t * const String);
#else
#error Compiler not supported!
#endif

/*! \brief		The function of printing a character in RenderBuffer.
 *  \details	The function to print a character in RenderBuffer at X, Y position. 
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N).
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N).
 *  \param		Symbol - the symbol to be printed into the buffer. 
 *  \note		The origin is in the upper left corner of the display. 
 */	void DISPLAY_putSymbolXYToRenderBuffer(uint8_t X, uint8_t Y, uint8_t Symbol);

/*! \brief		Function for printing a string in RenderBuffer. 
 *  \details	The function of printing a string in RenderBuffer at position X, Y. 
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N).
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N).
 *  \param		String - the string to be printed to the buffer. 
 *  \note		The origin is in the upper left corner of the display. 
 */	void DISPLAY_putStringXYToRenderBuffer(uint8_t X, uint8_t Y, uint8_t *String);

/*! \brief		Function of printing an unsigned integer number on the display. 
 *  \details	Function of printing an "uint8_t" number on the display from current position. 
 *  \param		Value - the unsigned integer number to be printed on the display.  
 */	void DISPLAY_printuint8_t(uint8_t Value);

/*! \brief		Function of printing an unsigned integer number on the display. 
 *  \details	Function of printing an "uint8_t" number on the display from position from the of X, Y. 
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N).
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N).
 *  \param		Value - the unsigned integer number to be printed on the display. 
 *  \note		The origin is in the upper left corner of the display. 
 */	void DISPLAY_printXYuint8_t(uint8_t X, uint8_t Y, uint8_t Value);

/*! \brief		Function of printing an unsigned integer number on the display. 
 *  \details	Function of printing an "uint16_t" number on the display from current position. 
 *  \param		Value - the unsigned integer number to be printed on the display.  
 */	void DISPLAY_printuint16_t(uint16_t Value);

/*! \brief		Function of printing an unsigned integer number on the display. 
 *  \details	Function of printing an "uint16_t" number on the display from position from the of X, Y. 
 *  \param		X - coordinate of familiarity along the X axis (from 0 to N).
 *  \param		Y - coordinate of familiarity along the Y axis (from 0 to N).
 *  \param		Value - the unsigned integer number to be printed on the display. 
 *  \note		The origin is in the upper left corner of the display.
 */	void DISPLAY_printXYuint16_t(uint8_t X, uint8_t Y, uint16_t Value);

/*! \brief		Display render function. 
 *  \details	A function that renders the framebuffer to the display. 
 *  \param		none.
 *	\return		none. 
 */	void DISPLAY_run(void);

#ifdef __cplusplus
}
#endif

#endif //_DISPLAY_H_
