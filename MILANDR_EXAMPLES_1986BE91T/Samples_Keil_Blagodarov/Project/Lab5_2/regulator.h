// ***********************************************************************************
// Проект:      Lab5_2 
// Программа:   Работа с ШИМ. Регулирование ширины импульса с помощью потенциометра и АЦП. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Модуль: regulator.h 
// Назначение: Регулятор ширины импульсов     
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#ifndef __U_REGULATOR
 #define __U_REGULATOR

#include "common.h"
#include "mlt_lcd.h"
#include "adc.h"
#include "pwm.h"
#include "math.h"

// Задача по реализации регулятора
__task void U_Regulator_Task_Function (void);

// Переменная для хранения идентификатора задачи
extern OS_TID U_Regulator_Task_ID;



#endif 
