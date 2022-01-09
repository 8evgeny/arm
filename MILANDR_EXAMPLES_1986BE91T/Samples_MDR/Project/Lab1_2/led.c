// ***********************************************************************************
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: led.c 
// Назначение: Управление светодиодами      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************
#include "led.h"

#include "mlt_lcd.h"

// Инициализировать светодиоды
void U_LED_Init (void)
{
	// Структруа для инициализации портов
	PORT_InitTypeDef PortInitStructure;	
	
  // Сделать выходами порты, к которым подключены светодиоды
  PORT_StructInit (&PortInitStructure);	
  PortInitStructure.PORT_Pin   = U_LED_0_PIN | U_LED_1_PIN;
  PortInitStructure.PORT_MODE =  PORT_MODE_DIGITAL;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PortInitStructure.PORT_OE    = PORT_OE_OUT;
	PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;
  PORT_Init (U_LED_PORT, &PortInitStructure);	
}

// Потушить указанные светодиоды
void U_LED_Off (uint32_t Pins)
{
	PORT_ResetBits (U_LED_PORT, Pins);
}

// Зажечь указанные светодиоды
void U_LED_On (uint32_t Pins)
{
	PORT_SetBits (U_LED_PORT, Pins);
}

// Переключить указанные светодиоды
void U_LED_Toggle (uint32_t Pins)
{
	uint32_t data	= PORT_ReadInputData (U_LED_PORT);
	PORT_Write (U_LED_PORT, data ^= Pins);
}

// Задача по миганию синим светодиодом
__task void U_LED_Task_Function (void)
{
	uint32_t i = 0;
	uint32_t k = 0;
	
	// Строка, выводимая на индикатор 
	const char s[] =  "\xD0\xC3\xD0\xD2\xD3";          // РГРТУ - строка короче индикатора
	//const char s[] =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; // строка длиннее индикатора
	
	while(1)
	{
		
		// Сменить состояние светодиода 0 на противоположное 
		if (i > 0)
		{
		  U_LED_On (U_LED_0_PIN);  
			i = 0;
		}
		else
		{
		  U_LED_Off (U_LED_0_PIN);  
      i = 1;
    }			

		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (1000);  
		
		// Вывести строку c прокруткой
		U_MLT_Scroll_String (s, 4, k++);
		
	}
}
