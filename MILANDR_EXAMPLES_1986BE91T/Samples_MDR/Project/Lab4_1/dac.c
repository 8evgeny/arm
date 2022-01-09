// ***********************************************************************************
// Проект:      Lab4_1 
// Программа:   Работа с ЦАП. Режим одиночного преобразования
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: adc.с 
// Назначение: Управление АЦП      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "dac.h"

// Инициализировать ЦАП
void U_DAC_Init (void)
{
	// Структруа для инициализации портов
	PORT_InitTypeDef PortInitStructure;	
	
  // Разрешить тактирование ЦАП и порта E
  RST_CLK_PCLKcmd (RST_CLK_PCLK_DAC | RST_CLK_PCLK_PORTE, ENABLE);  

  // Линию PE0, с которой связан выход  DAC2, сделать аналоговым выходом
  PORT_StructInit (&PortInitStructure);	
  PortInitStructure.PORT_Pin   = PORT_Pin_0;
  PortInitStructure.PORT_OE    = PORT_OE_OUT;
  PortInitStructure.PORT_MODE =  PORT_MODE_ANALOG;
  PORT_Init (MDR_PORTE, &PortInitStructure);		

	// Сбросить все настройки ЦАП
  DAC_DeInit ();

	// Инициализировать ЦАП2, задав в качестве опоры напряжение питания аналоговой части МК
  DAC2_Init (DAC2_AVCC);

  // Разрешить работу канала ЦАП2 
  DAC2_Cmd (ENABLE);

	// Запустить цифро-аналоговое преобразование, задав на вход ЦАП2 значение U_DAC_VALUE.
  DAC2_SetData (U_DAC_VALUE);	
	
}







