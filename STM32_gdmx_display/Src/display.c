/*! \file		display.h
 *  \brief		Display module (source file). 
 *  \details	Display control module. 
 *  \author		Arthur Markaryan
 *  \date		31.03.2021
 *  \copyright	
 */

#include "display.h"

//------------------------Constant definitions--------------------------------//



//------------------------Variable definitions--------------------------------//

//! Tick counter before display refresh.
volatile uint16_t DISPLAY_Counter;

//! Render permission flag with DISPLAY_REFRESH_INTERVAL interval.
volatile uint8_t DISPLAY_RenderEnable;

//! Display process flag.
volatile uint8_t DISPLAY_RenderFlag;

//! Variable that stores the current step of displaying a character from the display buffer.
volatile uint8_t DISPLAY_RenderStep;

//! Display Buffer.
volatile uint8_t DISPLAY_RenderBuffer[DISPLAY_ROW_NUM][DISPLAY_ROW_SIZE];

// Variables for the needs of the LCD emulator. 
#ifdef DEBUG_DISPLAY_IN_TERMINAL
//!
static volatile uint8_t DISPLAY_X = 0;
//!
static volatile uint8_t DISPLAY_Y = 0;
#endif
//-----------------------Function implementations-----------------------------//

// Initialize the display.
void DISPLAY_init(void){

	//
#ifdef DEBUG_DISPLAY_IN_TERMINAL
	DEBUG_printf(	"\r\n"
					" DISPLAY EMULATOR \r\n"
					"+----------------+\r\n"
					"|                |\r\n"
					"|                |\r\n"
					"+----------------+\r\n");
	// Place the cursor in the upper left corner.
#if (4 == HD44780_ROW_NUM)
	DEBUG_printf("\x1B[5A");	// Cursor Up for 5 position
#elif(2 == HD44780_ROW_NUM)
	DEBUG_printf("\x1B[3A");	// Cursor Up for 3 position
#elif(1 == HD44780_ROW_NUM)
	DEBUG_printf("\x1B[1A");	// Cursor Up for 1 position
#else
// Undefined LCD.
#error Unknown HD44780 format
#endif//#if (4 == HD44780_ROW_NUM)
	
	DEBUG_printf("\x1B[1C");	// Cursor Right for 1 position
	DISPLAY_X = 0;
	DISPLAY_Y = 0;
	
#else

	/* LCD Driver Initialization */
	HD44780_init();

	// Here the indicator enters the operating mode with the set interface type and you can send commands as usual.
	HD44780_SETUP(HD44780_BUS4 | HD44780_PAGE1);
	HD44780_DISPLAY_ON();
	HD44780_CLEAR();
	HD44780_AC_INC_MODE();

	/* Turn on the screen backlight */
	HD44780_BACKLIGHT_ON();

	/* Set cursor on */
	HD44780_CURSOR_ON();
#endif

	// Tick counter initialization before display refresh. 
	DISPLAY_Counter = DISPLAY_REFRESH_INTERVAL;

	// Initialization of the display process flag.
	DISPLAY_RenderFlag = 0;

	// Initialization of a variable that stores the current display step of the character from the display buffer.
	DISPLAY_RenderStep = 0;

	// Initialization of framebuffer.
	for(uint8_t i=0; i<DISPLAY_ROW_NUM; i++){
		for(uint8_t j=0; j<DISPLAY_ROW_SIZE; j++){
			DISPLAY_RenderBuffer[i][j] = 0x20;
		}
	}

	// Disable rendering with the DISPLAY_REFRESH_INTERVAL interval. 
	DISPLAY_RenderEnable = 0;
}

// Clearing the didplay.
void DISPLAY_clear(void){
	//
#ifdef DEBUG_DISPLAY_IN_TERMINAL
	// Place the cursor in the upper left corner. 
	if(DISPLAY_X > 0)
		DEBUG_printf("\x1B[%dD", DISPLAY_X);// Left
	DISPLAY_X = 0;
	if(DISPLAY_Y)
		DEBUG_printf("\x1B[%dA", DISPLAY_Y);// Up
	DISPLAY_Y = 0;
	DEBUG_printf("                ");
	DEBUG_printf("\x1B[%dD", 16);			// Left
	DEBUG_printf("\x1B[%dB", 1);			// Down
	DEBUG_printf("                ");
	DEBUG_printf("\x1B[%dD", 16);			// Left
	DEBUG_printf("\x1B[%dA", 1);			// Up
#else
	HD44780_CLEAR();
#endif
}

// Display buffer setting function.
void DISPLAY_setRenderBuffer(uint8_t **buffer){
	// TO DO...
}

// A function that controls the mode of the cursor. Bit0 - On / Off, Bit1 - BlankOn / BlankOff.
void DISPLAY_setCursorMode(uint8_t mode){
	//
#ifdef DEBUG_DISPLAY_IN_TERMINAL
	// TO DO...
#else
	// Turn the cursor on or off.
	if(mode & 0x01){
		HD44780_CURSOR_ON();
	}else{
		HD44780_CURSOR_OFF();
	}
	// Delay 100 us.
	usDelay(100);
	// Turn cursor blinking on or off.
	if(mode & 0x02){
		HD44780_BLANK_ON();
	}else{
		HD44780_BLANK_OFF();
	}
	// Delay 100 us.
	usDelay(100);
#endif
}

// The function of moving the cursor to the X, Y position. 
uint8_t DISPLAY_moveCursorXY(uint8_t X, uint8_t Y){
	//
	uint8_t result = 0;

	//
#ifdef DEBUG_DISPLAY_IN_TERMINAL
	//
	if((X >=0) && (X < DISPLAY_ROW_SIZE)){
		//
		if(X > DISPLAY_X){
			DEBUG_printf("\x1B[%dC", X - DISPLAY_X);	// Right
		}
		if(X < DISPLAY_X){
			DEBUG_printf("\x1B[%dD", DISPLAY_X - X);	// Left
		}
		DISPLAY_X = X;
	}else{
		result |= 0x01;
	}
	//
	if((Y >=0) && (Y < DISPLAY_ROW_NUM)){
		//
		if(Y > DISPLAY_Y){
			DEBUG_printf("\x1B[%dB", Y - DISPLAY_Y);	// Down
		}if(Y < DISPLAY_Y){
			DEBUG_printf("\x1B[%dA", DISPLAY_Y - Y);	// Up
		}
		DISPLAY_Y = Y;
	}else{
		result |= 0x02;
	}
#else
	switch(Y){
#if(DISPLAY_ROW_NUM > 0)
		case 0:
			HD44780_SET_DDR_ADDR((uint8_t)(HD44780_ROW1_START+X));
		break;
#endif
#if(DISPLAY_ROW_NUM > 1)
		case 1:
			HD44780_SET_DDR_ADDR((uint8_t)(HD44780_ROW2_START+X));
		break;
#endif
#if(DISPLAY_ROW_NUM > 2)
		case 2:
			HD44780_SET_DDR_ADDR((uint8_t)(HD44780_ROW3_START+X));
		break;
		case 3:
			HD44780_SET_DDR_ADDR((uint8_t)(HD44780_ROW4_START+X));
		break;
#endif
		default:
		break;
	}
	// Delay 100 us.
	usDelay(100);
#endif

	return result;
}

// The function of printing a character at the current cursor position on the display. 
void DISPLAY_printSymbol(uint8_t Symbol){
	//
#ifdef DEBUG_DISPLAY_IN_TERMINAL
	if(DISPLAY_X < DISPLAY_ROW_SIZE){
		DEBUG_printf("%c", Symbol);
		DISPLAY_X++;
	}
#else
	// Display the symbol at the current position.
	HD44780_writeData(Symbol);
	// Delay 100 us.
	usDelay(100);
#endif
}

#if 0
// The function of printing a character at the current cursor position on the display from Flash memory. 
void DISPLAY_printSymbolFromFlash(__FLASH_STRING ptrSymbol){
	// Display the symbol at the current position.
	HD44780_writeData(Symbol);
	// Delay 100 us.
	usDelay(100);
}
#endif

// The function of printing a character on the display in position X, Y. 
void DISPLAY_printSymbolXY(uint8_t X, uint8_t Y, uint8_t Symbol){
	DISPLAY_moveCursorXY(X, Y);
	DISPLAY_printSymbol(Symbol);
}

// The function of printing a character from FLASH memory on the display to position X, Y. 
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
void DISPLAY_printSymbolXYFromFlash(uint8_t X, uint8_t Y, __flash uint8_t *ptrSymbol){
#elif defined(__GNUC__)
void DISPLAY_printSymbolXYFromFlash(uint8_t X, uint8_t Y, volatile uint8_t * const ptrSymbol){
#else
#error Compiler not supported!
#endif
	DISPLAY_moveCursorXY(X, Y);
	DISPLAY_printSymbol(*ptrSymbol);
}

// Function of printing the String at the current cursor position on the display. 
void DISPLAY_printString(uint8_t *String){
	while(0 != *String){
		DISPLAY_printSymbol(*String++);
	}
}

// Function of printing the Screen from the (0, 0) position on the display.
void DISPLAY_printScreen(uint8_t *Screen){
	uint8_t x = 0, y = 0;
	DISPLAY_moveCursorXY(x, y);
	while(0 != *Screen){
		DISPLAY_printSymbol(*Screen++);
		if(x<HD44780_ROW_SIZE-1){
			x++;
		}else{
			x=0;
			if(y<HD44780_ROW_NUM-1){
				y++;
				DISPLAY_moveCursorXY(x, y);
			}else{
				y=0;
			}
		}
	}
}

// Function of printing the String from FLASH memory at the current cursor position on the display. 
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
void DISPLAY_printStringFromFlash(__flash uint8_t *String){
#elif defined(__GNUC__)
void DISPLAY_printStringFromFlash(volatile uint8_t * const String){
#else
#error Compiler not supported!
#endif
	uint8_t SringEndFlag = 0;
	for(uint8_t i=0; i<DISPLAY_ROW_SIZE; i++){
		//
		if(String[i] == 0)SringEndFlag = 1;
		//
		//if(!SringEndFlag)HD44780_put(String[i]); else HD44780_put(0x20);
		if(!SringEndFlag)HD44780_writeByte(String[i], 1); else HD44780_writeData(0x20);
		// Delay 100 us.
		usDelay(100);
	}
}

// Function of printing the String on the display at the X, Y position. 
void DISPLAY_printStringXY(uint8_t X, uint8_t Y, uint8_t *String){
	DISPLAY_moveCursorXY(X, Y);
	DISPLAY_printString(String);
}

// Function of printing the String from FLASH memory on the display at the X, Y position.
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
void DISPLAY_printStringXYFromFlash(uint8_t X, uint8_t Y, __flash uint8_t *String){
#elif defined(__GNUC__)
void DISPLAY_printStringXYFromFlash(uint8_t X, uint8_t Y, volatile uint8_t * const String){
#else
#error Compiler not supported!
#endif
	DISPLAY_moveCursorXY(X, Y);
	DISPLAY_printStringFromFlash(String);
}

// The function of printing a character in RenderBuffer.
void DISPLAY_putSymbolXYToRenderBuffer(uint8_t X, uint8_t Y, uint8_t Symbol){
	DISPLAY_RenderBuffer[Y][X] = Symbol;
}

// Function for printing a string in RenderBuffer. 
void DISPLAY_putStringXYToRenderBuffer(uint8_t X, uint8_t Y, uint8_t *String){
	// TO DO...
}

// A function to print an unsigned integer uint8_t to the display. 
void DISPLAY_printuint8_t(uint8_t Value){
	char Str[4] = {0, 0, 0, 0};
	sprintf(Str, "%u", Value);
	DISPLAY_printString((uint8_t*)Str);
}

// Function of printing an unsigned integer number uint8_t on the display from FLASH memory at the X, Y position. 
void DISPLAY_printXYuint8_t(uint8_t X, uint8_t Y, uint8_t Value){
	DISPLAY_moveCursorXY(X, Y);
	DISPLAY_printuint8_t(Value);
}

// A function to print an unsigned integer uint16_t to the display. 
void DISPLAY_printuint16_t(uint16_t Value){
	char Str[6] = {0, 0, 0, 0, 0, 0};
	sprintf(Str, "%u", Value);
	DISPLAY_printString((uint8_t*)Str);
}

// Function of printing an unsigned integer number uint16_t on the display from FLASH memory at the X, Y position. 
void DISPLAY_printXYuint16_t(uint8_t X, uint8_t Y, uint16_t Value){
	DISPLAY_moveCursorXY(X, Y);
	DISPLAY_printuint16_t(Value);
}

// Display display function. 
// TO DO: SHOULD BE REDUCED taking into account the runtime!
void DISPLAY_run(void){
/*
	//if(DisplayRenderStep < 32){
	if(DISPLAY_RenderStep < 32){
		UCHAR PY = (DisplayRenderStep & 0x10);
		SWAP(PY);
	  	//if(DisplayRenderStep == 0x00) DisplayRefreshCounter = 0;
		if(DisplayRenderStep == 0x00) DISPLAY_Counter = DISPLAY_REFRESH_INTERVAL;
		for(UCHAR i=0; i<4; i++){
			moveDisplayCursorXY((DisplayRenderStep & 0x0F), PY);
			printSymbol(DisplayRenderBuffer[PY][(DisplayRenderStep & 0x0F)]);
			DisplayRenderStep++;
		}
		moveDisplayCursorXY(17,0);
	}else{
		DisplayRenderStep = 0;
		DisplayRenderFlag = 0;
	}
*/
}
