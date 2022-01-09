// ***********************************************************************************
// Проект:      Lab2_2 
// Программа:   Работа с кнопкой 
// Микроконтроллер: 1986ВЕ92У
// Файл: button.с 
// Назначение: Управление кнопкой      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "button.h"

// Инициализировать кнопки
void U_BTN_Init (void)
{
	// Структура для инициализации портов	
	PORT_InitTypeDef PortInitStructure;

	// Разрешить тактирование порта B
	RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTB, ENABLE);

  // Сделать входом линию, к которой подключены кнопки
	PORT_StructInit (&PortInitStructure);
	PortInitStructure.PORT_Pin   = U_BTN_PIN;
	PortInitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	PortInitStructure.PORT_FUNC  = PORT_FUNC_PORT;
	PortInitStructure.PORT_OE    = PORT_OE_IN;
	PortInitStructure. PORT_PULL_UP = PORT_PULL_UP_OFF;
	PortInitStructure. PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
	PORT_Init (U_BTN_PORT, &PortInitStructure);
}

// Получить состояние кнопки (0 - отпущена, 1 - нажата)
uint8_t U_BTN_Read_Button (void)
{
	// Прочитать состояние входа, к которому подключена кнопка
	if(PORT_ReadInputDataBit (U_BTN_PORT, U_BTN_PIN))
	  // Кнопка отпущена
	  return 0;
	else
	  // Кнопка нажата
		return 1;
}


