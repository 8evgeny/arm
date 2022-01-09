// ***********************************************************************************
// Проект:      Lab7_3 
// Программа:   Использование батарейного домена. Сохранение данных в батарейном домене.
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
void U_RTC_Init(void)
{
  time_t TimeStamp;	
  struct tm *timeinfo;

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
  BKP_RTC_WaitForUpdate();
  BKP_RTC_SetPrescaler (RTC_PRESCALER);

  // Корректировка скорости хода
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  BKP_RTC_Calibration (RTC_CALIBRATION);

  // Разрешить работу RTC
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  BKP_RTC_Enable (ENABLE);

  // Получить дату и время последнего выключения из батарейного домена 
  TimeStamp = U_RTC_Get_Last_OFF_DateTime ();

  // Вывести время последнего отключения на ЖКИ 
  timeinfo = localtime (&TimeStamp);
  strftime (current_time, 16, "%H:%M:%S", timeinfo);	
	U_MLT_Put_String (current_time, 3);
}


// Получить текущие дату и время в виде Unix Timestamp 
time_t U_RTC_Get_DateTime_Stamp (void)
{
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  return BKP_RTC_GetCounter();
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
  strftime (timeString, 16, "%H:%M:%S", timeinfo);
  strftime (dateString, 16, "%d.%m.%Y", timeinfo);
	
	return TimeStamp;
}


// Получить текущее время без использования библиотеки time.h
void U_RTC_GetTime_String (char* timeString)
{
  uint8_t Hours, Minutes, Seconds;
  uint32_t TimeCount = BKP_RTC_GetCounter();

  // Вычислить часы
  Hours = (uint8_t)(TimeCount / 3600 % 24);
  // Вычислить минуты
  Minutes = (uint8_t)(TimeCount / 60 % 10);
  // Вычислить секунды
  Seconds = (uint8_t)(TimeCount % 60);

  // Результат вывода
  sprintf (timeString, " %02d:%02d:%02d ", Hours, Minutes, Seconds);
}


// Сохранить текущие дату и время в батарейном домене 
void U_RTC_Save_DateTime (void)
{
	time_t TimeStamp;

  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  TimeStamp = BKP_RTC_GetCounter ();
	MDR_BKP->REG_02 = TimeStamp;  

}

// Получить дату и время последнего выключения из батарейного домена 
time_t U_RTC_Get_Last_OFF_DateTime (void)
{
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  return  MDR_BKP->REG_02; 
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

		// Сохранить текущие дату и время в батарейном домене 
		U_RTC_Save_DateTime ();
		
		// Вывести на ЖКИ текущую дату
		U_MLT_Put_String (current_date, 4);

		// Вывести на ЖКИ текущее время
		U_MLT_Put_String (current_time, 5);
		
		// Вывести на ЖКИ отметку времени
    sprintf (message, "%u", TimeStamp);		
		U_MLT_Put_String (message, 6);
		
		os_dly_wait (1000);
	}
}





