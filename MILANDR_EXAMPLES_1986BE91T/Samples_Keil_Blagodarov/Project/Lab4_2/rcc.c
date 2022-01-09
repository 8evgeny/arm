// ***********************************************************************************
// Проект:      Lab3 
// Программа:   Работа с АЦП 
// Микроконтроллер: STM32L152RB
// Устройство: Отладочная плата STM32L-Discovery
// Модуль: rcc.c 
// Назначение: Настройка тактирования микроконтроллера
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "rcc.h"

// Инициализация RCC
void U_RCC_Init(void)
{  
  // Основные настройки тактирования заданы в функции SystemInit() модуля system_stm32l1xx.c.
	// Эта функция автоматически вызывается из модуля startup_stm32l1xx_xx.s перед запуском main
	// Файл system_stm32l1xx.c создается автоматически с помощью утилиты 
	// STM32L1xx_Clock_Configuration_V1.2.0.xls, которую можно скачать с сайта www.st.com (пакет AN3309)
	// Утилита открывается в MS Excel 2003/2007 и позволяет визуально настраивать подсистему тактирования микроконтроллера
  // Но работают эти настройки не всегда надежно. Поэтому вручную зададим некоторые настройки RSS.
	
  // Разрешить работу HSI (врутреннего RC-генератора)
  RCC_HSICmd(ENABLE);
  
  // Дождаться, пока HSI запустится
  while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  // Выбрать HSI в качестве системного источника тактирования
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
  
  // Для MSI установить частоту ~4.194МГц
  RCC_MSIRangeConfig(RCC_MSIRange_6);
  
  // Разрешить тактирование портов ввода-вывода
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC| RCC_AHBPeriph_GPIOD | RCC_AHBPeriph_GPIOH, ENABLE);     

  // Разрешить тактирование аналогового компаратора, ЖКИ и управления 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP | RCC_APB1Periph_LCD | RCC_APB1Periph_PWR,ENABLE);
    
  // Разрешить тактирование АЦП и SYSCFG 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_SYSCFG , ENABLE);

  // Разрешить доступ к RTC (часы реального времени)
  PWR_RTCAccessCmd(ENABLE);

  // Сбросить батарейный домен для питания RTC 
  RCC_RTCResetCmd(ENABLE);
  RCC_RTCResetCmd(DISABLE);

  // Разрешить работу LSE (генератор низкой частоты на внешнем кварце)
  RCC_LSEConfig(RCC_LSE_ON);

  // Дождаться, пока LSE будет готово
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
  
  // Для тактирования RTC выбрать LSE
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); 
  
  // Разрешить работу RTC
  RCC_RTCCLKCmd(ENABLE);   
	
  // Запретить работу HSE (высокочастотного генератора на внешнем кварце)
  RCC_HSEConfig(RCC_HSE_OFF);
	// Дождаться выключения HSE
  if(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET )
  {
    while(1); 
  }
}

