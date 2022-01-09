// ***********************************************************************************
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: led.h 
// Назначение: Управление светодиодами      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#ifndef __U_LED
 //#define __U_LED

#include "common.h"

// Порт светодиодов
#define U_LED_PORT MDR_PORTC
//#define U_LED_PORT MDR_PORTF
// Линия для светодиода 0
#define U_LED_0_PIN PORT_Pin_0
// Линия для светодиода 1
#define U_LED_1_PIN PORT_Pin_1

// Инициализировать светодиоды
void U_LED_Init (void);

// Потушить указанные светодиоды
void U_LED_Off (uint32_t Pins);

// Зажечь указанные светодиоды
void U_LED_On (uint32_t Pins);

// Переключить указанные светодиоды
void U_LED_Toggle (uint32_t Pins);

// Задача по миганию светодиодом 0
__task void U_LED_Task0_Function (void);

// Задача по миганию светодиодом 1
__task void U_LED_Task1_Function (void);

#endif 

