// ***********************************************************************************
// Проект:      Lab7_3 
// Программа:   Использование батарейного домена. Сохранение данных в батарейном домене.
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл:  rtc.h 
// Модуль:  Часы реального времени 
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#ifndef __U_RTC
 #define __U_RTC

#include "common.h"
#include "mlt_lcd.h"

#include <time.h>

// Предделитель частоты для RTC
// При внешнем кварце 32768Гц дискретность RTC - 1c. 
#define RTC_PRESCALER 32768 

// Константа корректировки скорости хода 0..255
// Задает, сколько тактов RTC будет замаскировано через каждые 2^20 тактов RTC (через каждые 12 суток)
#define RTC_CALIBRATION 0

// Событие (Event) срабатывании таймера
#define EVENT_RTC 0x0001

// Инициализация RTC
void U_RTC_Init (void);

// Получить текущие дату и время в виде Unix Timestamp 
time_t U_RTC_Get_DateTime_Stamp (void);

// Установить текущие дату и время по заданной метке времени
void U_RTC_Set_DateTime_Stamp (time_t TimeStamp);

// Установка начальных даты и времени 
void U_RTC_Set_Start_DateTime (void);

// Получить текущие дату и время в виде строк формата: "dd.mm.yyyy"  и  "hh:uu:ss"
time_t U_RTC_Get_DateTime_String (char* dateString, char* timeString);

// Получить текущее время без использования библиотеки time.h
void U_RTC_GetTime_String (char* timeString);

// Сохранить текущие дату и время в батарейном домене 
void U_RTC_Save_DateTime (void);

// Получить дату и время последнего выключения из батарейного домена 
time_t U_RTC_Get_Last_OFF_DateTime (void);

// Задача по выводу текущего времени на ЖКИ
extern OS_TID U_RTC_Task_Show_ID;  // Переменная для хранения идентификатора задачи
__task void U_RTC_Task_Show_Function (void);


#endif 


