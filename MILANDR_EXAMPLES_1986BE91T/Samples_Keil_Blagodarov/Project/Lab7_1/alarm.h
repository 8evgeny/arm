// ***********************************************************************************
// Проект:      Lab7_1 
// Программа:   Использование батарейного домена. Таймер на основе RTC. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл:  alarm.h 
// Модуль:  Таймер 
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#ifndef __U_ALARM
 #define __U_ALARM

#include "common.h"
#include "mlt_lcd.h"

#include <time.h>


// Время в секундах, через которое сработает таймер часов реального времени
#define U_ALARM_WAIT_TIME 12


// Событие (Event) срабатывании таймера
#define EVENT_ALARM 0x0001

// Инициализация таймера
void U_Alarm_Init(void);


// Задача по управлению таймером
extern OS_TID U_Alarm_Task_ID;						// Переменная для хранения идентификатора задачи
__task void U_Alarm_Task_Function (void);

// Задача по выводу текущего отсчета времени
extern OS_TID U_Alarm_Task_CountDown_ID;  // Переменная для хранения идентификатора задачи
__task void U_Alarm_Task_CountDown_Function (void);


// Предделитель частоты для RTC
// При внешнем кварце 32768Гц дискретность RTC - 1c. 
#define RTC_PRESCALER 32768 

// Константа корректировки скорости хода 0..255
// Задает, сколько тактов RTC будет замаскировано через каждые 2^20 тактов RTC (через каждые 12 суток)
#define RTC_CALIBRATION 0

// Используется формат хранения времени POSIX Timestamp (UNIX Timestamp)
// Считается количество секунд, прошедших с 00:00:00 1 января 1970 года по Всемирному времени (UTC).
// Если мiр простоит, то в будущем возможны следующие проблемы.
//   1. 03:14:07, вторник, 19 января 2038 года по Всемирному времени (UTC) 
//      из-за достижения меткой значения 2^31 и интерпретации некоторыми программами как отрицательного числа. 
//   2. 06:28:14, 06 февраля 2106 года по Всемирному времени (UTC)
//      Переполнение метки. Через секунду будет отметка 01.01.1900 00:00:00.
//      Еще через секунду будет отметка 01.01.1970 00:00:00. Далее повтор отсчета.  

// Начальные дата и время
#define RTC_INIT_TIMESTAMP 1325376000  // 01.01.2012 00:00:00
//#define RTC_INIT_TIMESTAMP 0x7FFFFFF0  // 19.01.2038 03:13:51	  (имитация проблемы 1)
//#define RTC_INIT_TIMESTAMP 0xFFFFFFF0  // 06.02.2106 06:28:00	  (имитация проблемы 2)


// Получить текущие дату и время в виде Unix Timestamp 
time_t U_Alarm_Get_DateTime_Stamp(void);

// Установить текущие дату и время по заданной метке времени
void U_Alarm_Set_DateTime_Stamp(time_t TimeStamp);

// Получить текущие дату и время в виде строки формата: dd.mm.yyyy hh:uu:ss
void U_Alarm_Get_DateTime_String(int8_t* timeString);

// Получить текущее время без использования библиотеки time.h
void U_Alarm_GetTime_String(int8_t* timeString);

#endif 

