// ***********************************************************************************
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: led.c 
// Назначение: Управление светодиодами      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************
#include "led.h"

// Инициализировать светодиоды
void U_LED_Init (void)
{
	// Структура для инициализации портов
	PORT_InitTypeDef PortInitStructure;	

  // Разрешить тактирование требуемых периферийных устройств
  RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTB, ENABLE);	
	
  // Сделать выходами порты, к которым подключены светодиоды
  PORT_StructInit (&PortInitStructure);	
  PortInitStructure.PORT_Pin   = U_LED_RED_PIN | U_LED_YELLOW_PIN | U_LED_GREEN_PIN | U_LED_BLUE_PIN;
  PortInitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
  PortInitStructure.PORT_FUNC  = PORT_FUNC_PORT;
  PortInitStructure.PORT_OE    = PORT_OE_OUT;
	PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;
  PORT_Init (U_LED_PORT, &PortInitStructure);	

	// Потушить все светодиоды
	U_LED_Off (U_LED_RED_PIN | U_LED_YELLOW_PIN | U_LED_GREEN_PIN | U_LED_BLUE_PIN);
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
	uint32_t data;
	
	data	= PORT_ReadInputData (U_LED_PORT);
	PORT_Write (U_LED_PORT, data ^= Pins);
}

// Задача по миганию синим светодиодом 
__task void U_LED_Task_Function (void)
{
	while(1)
	{
		// Сменить состояние синего светодиода на противоположное 
		U_LED_Toggle (U_LED_BLUE_PIN);  
		
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (500);  
	}
}


