// ***********************************************************************************
// Проект:      Lab4_1 
// Программа:   Работа с ЦАП. Режим одиночного преобразования
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: adc.h 
// Назначение: Управление АЦП      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************
#ifndef __U_DAC
 #define __U_DAC

#include "common.h"

// Значение, подаваемое на вход ЦАП
#define U_DAC_VALUE 1300

// Инициализировать ЦАП
void U_DAC_Init (void);

#endif 

