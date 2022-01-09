// ***********************************************************************************
// Проект:      Lab7_2 
// Программа:   Использование батарейного домена. Часы реального времени. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл:  rtc.с 
// Модуль:  Часы реального времени 
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "rtc.h"


// Буфер для формирования сообщений, выводимых на ЖКИ
static char message[128];

// Буфер для формирования строки с текущим временем
static char current_time[16];
// Буфер для формирования строки с текущей датой
static char current_date[16];

// Инициализация RTC
void U_RTC_Init (void)
{
	// Структура для инициализации портов
	PORT_InitTypeDef PortInitStructure;	
	
	// Разрешить тактирование батарейного домена и порта PORTE
  RST_CLK_PCLKcmd (RST_CLK_PCLK_BKP | RST_CLK_PCLK_PORTE, ENABLE);
	
  // Сделать аналоговым входом линии (PE6, PE7), к которым подключен часовой кварц
  PORT_StructInit (&PortInitStructure);	
  PortInitStructure.PORT_Pin   = PORT_Pin_6 | PORT_Pin_7;
  PortInitStructure.PORT_MODE =  PORT_MODE_ANALOG;
  PORT_Init (MDR_PORTE, &PortInitStructure);		
	
  // Включить часовой генератор на внешнем кварце
  RST_CLK_LSEconfig (RST_CLK_LSE_ON); 
  while (RST_CLK_LSEstatus() != SUCCESS);	// Дождаться включения генератора
	
  // Выбрать LSE в качестве источника тактирования RTC 
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  BKP_RTCclkSource (BKP_RTC_LSEclk);

  // Задать предделитель RTC
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  BKP_RTC_SetPrescaler (RTC_PRESCALER);

  // Корректировка скорости хода
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  BKP_RTC_Calibration (RTC_CALIBRATION);

  // Разрешить работу RTC
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  BKP_RTC_Enable (ENABLE);

  // Установить начальные дату и время    
  U_RTC_Set_Start_DateTime ();

}


// Установка начальных даты и времени 
void U_RTC_Set_Start_DateTime (void)
{
  struct tm timeinfo;
  time_t TimeStamp;	
	
	// Используется формат хранения времени POSIX Timestamp (UNIX Timestamp)
	// Считается количество секунд, прошедших с 00:00:00 1 января 1970 года по Всемирному времени (UTC).
	// Если мiр простоит, то в будущем возможны следующие проблемы:
	//   1. 03:14:07, вторник, 19 января 2038 года по Всемирному времени (UTC) 
	//      из-за достижения меткой значения 2^31 и интерпретации некоторыми программами как отрицательного числа. 
	//   2. 06:28:14, 06 февраля 2106 года по Всемирному времени (UTC)
	//      Переполнение метки. Через секунду будет отметка 01.01.1900 00:00:00.
	//      Еще через секунду будет отметка 01.01.1970 00:00:00. Далее повтор отсчета.  
	
	
  // Установить начальные дату и время    
	// 30.11.2014 09:55:00
  timeinfo.tm_sec  = 0;               // Секунды (0..60)
  timeinfo.tm_min  = 55;              // Минуты (0..59)
  timeinfo.tm_hour = 9;               // Часы (0..23)
  timeinfo.tm_mday = 30;              // День месяца (1..31)
  timeinfo.tm_mon  = 11 - 1;          // Полных месяцев с начала года (0 - январь, 11 - декабрь) 
  timeinfo.tm_year = 2014 - 1900;     // Полных лет с 1900 года

	// 01.01.1970 00:00:00    (самая ранняя метка времени, метка = 0)
	/*
  timeinfo.tm_sec  = 0;               // Секунды (0..60)
  timeinfo.tm_min  = 0;               // Минуты (0..59)
  timeinfo.tm_hour = 0;               // Часы (0..23)
  timeinfo.tm_mday = 1;               // День месяца (1..31)
  timeinfo.tm_mon  = 1 - 1;           // Полных месяцев с начала года (0 - январь, 11 - декабрь) 
  timeinfo.tm_year = 1970 - 1900;     // Полных лет с 1900 года
  */

  // 19.01.2038 03:13:51	  (имитация проблемы 1, за 16 секунд до возникновения проблемы)
  /*
	timeinfo.tm_sec  = 51;              // Секунды (0..60)
  timeinfo.tm_min  = 13;              // Минуты (0..59)
  timeinfo.tm_hour = 3;               // Часы (0..23)
  timeinfo.tm_mday = 19;              // День месяца (1..31)
  timeinfo.tm_mon  = 1 - 1;           // Полных месяцев с начала года (0 - январь, 11 - декабрь) 
  timeinfo.tm_year = 2038 - 1900;     // Полных лет с 1900 года
  */
 
  // 06.02.2106 06:28:00	  (имитация проблемы 2, за 14 секунд до возникновения проблемы)
  /*
	timeinfo.tm_sec  = 0;               // Секунды (0..60)
  timeinfo.tm_min  = 28;              // Минуты (0..59)
  timeinfo.tm_hour = 6;               // Часы (0..23)
  timeinfo.tm_mday = 6;               // День месяца (1..31)
  timeinfo.tm_mon  = 2 - 1;           // Полных месяцев с начала года (0 - январь, 11 - декабрь) 
  timeinfo.tm_year = 2106 - 1900;     // Полных лет с 1900 года
  */

	TimeStamp = mktime (&timeinfo);         // Преобразовать структуру даты и времени в отметку времени
  
	BKP_RTC_WaitForUpdate ();               // Подождать, пока обновятся регистры RTC
	U_RTC_Set_DateTime_Stamp (TimeStamp);   // Задать дату и время 

}



// Получить текущие дату и время в виде Unix Timestamp 
time_t U_RTC_Get_DateTime_Stamp(void)
{
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  return BKP_RTC_GetCounter ();
}

// Установить дату и время по заданной метке времени
void U_RTC_Set_DateTime_Stamp (time_t TimeStamp)
{
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  BKP_RTC_SetCounter (TimeStamp);
}


// Получить текущие дату и время в виде строк формата: "dd.mm.yyyy"  и  "hh:uu:ss"
time_t U_RTC_Get_DateTime_String (char* dateString, char* timeString)
{
  struct tm *timeinfo;
  time_t TimeStamp;

  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  TimeStamp = BKP_RTC_GetCounter ();
	
  timeinfo = localtime (&TimeStamp);
  strftime (timeString, 16, "%H:%M:%S ", timeinfo);
  strftime (dateString, 16, "%d.%m.%Y", timeinfo);
  //strftime (dateString, 16, "%d %b %Y", timeinfo);
  //strftime (dateString, 16, "%A", timeinfo);
	
	return TimeStamp;
}


// Получить текущее время без использования библиотеки time.h
void U_RTC_GetTime_String (char* timeString)
{
  uint8_t Hours, Minutes, Seconds;
  uint32_t TimeCount = BKP_RTC_GetCounter ();

  // Вычислить часы
  Hours = (uint8_t)(TimeCount / 3600 % 24);
  // Вычислить минуты
  Minutes = (uint8_t)(TimeCount / 60 % 10);
  // Вычислить секунды
  Seconds = (uint8_t)(TimeCount % 60);

  // Результат вывода
  sprintf(timeString, " %02d:%02d:%02d ", Hours, Minutes, Seconds);
}

// Задача по выводу текущего времени на ЖКИ
OS_TID U_RTC_Task_Show_ID;  // Переменная для хранения идентификатора задачи

__task void U_RTC_Task_Show_Function (void)
{
  time_t TimeStamp;	
	
	while(1)
	{
    // Получить текущие дату и время в виде строки формата: dd.mm.yyyy hh:uu:ss 
    BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
    TimeStamp = U_RTC_Get_DateTime_String (current_date, current_time);

		// Вывести на ЖКИ текущую дату
		U_MLT_Put_String (current_date, 4);

		// Вывести на ЖКИ текущее время
		U_MLT_Put_String (current_time, 5);
		
		// Вывести на ЖКИ отметку времени
    sprintf (message, "%u", TimeStamp);		
		U_MLT_Put_String (message, 6);
		
		os_dly_wait(1000);
		
	}
}
