// ***********************************************************************************
// Проект:      Lab7_1 
// Программа:   Использование батарейного домена. Таймер на основе RTC. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл:  alarm.с 
// Модуль:  Таймер 
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "alarm.h"


// Буфер для формирования сообщений, выводимых на ЖКИ
static char message[128];


// Инициализация таймера
void U_Alarm_Init(void)
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
  BKP_RTC_WaitForUpdate ();          
  BKP_RTC_SetPrescaler (RTC_PRESCALER);

  // Корректировка скорости хода
  BKP_RTC_WaitForUpdate ();          
  BKP_RTC_Calibration (RTC_CALIBRATION);

  // Разрешить работу RTC
  BKP_RTC_WaitForUpdate ();          
  BKP_RTC_Enable (ENABLE);

  // Установить начальные дату и время
  BKP_RTC_WaitForUpdate ();          
  U_Alarm_Set_DateTime_Stamp (RTC_INIT_TIMESTAMP);
  BKP_RTC_WaitForUpdate ();          
	
  // Задать приоритет прерывания от батарейного домена выше, чем у планировщика задач. 
  NVIC_SetPriority (BACKUP_IRQn, 0x02);
	
  // Разрешить прерывания от батарейного домена
  NVIC_EnableIRQ (BACKUP_IRQn); 		
}


// Получить текущие дату и время в виде Unix Timestamp 
time_t U_Alarm_Get_DateTime_Stamp(void)
{
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  return BKP_RTC_GetCounter ();
}

// Установить текущие дату и время по заданной метке времени
void U_Alarm_Set_DateTime_Stamp (time_t TimeStamp)
{
  BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
  BKP_RTC_SetCounter (TimeStamp);
}


// Задача по управлению таймером
OS_TID U_Alarm_Task_ID;  // Переменная для хранения идентификатора задачи

__task void U_Alarm_Task_Function (void)
{
	time_t current;
	
  U_Alarm_Task_CountDown_ID	= 0;
	
	while(1)
	{
		// Получить текущее время
		current = U_Alarm_Get_DateTime_Stamp();

		// Создать задачу по выводу отсчетов времени оставшегося времени на ЖКИ
		if (!U_Alarm_Task_CountDown_ID)
      U_Alarm_Task_CountDown_ID = os_tsk_create (U_Alarm_Task_CountDown_Function, 20);
		
	  // Установить время срабатывания таймера
    BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
	  BKP_RTC_SetAlarm (current + U_ALARM_WAIT_TIME);

    // Разрешить прерывания по срабатыванию таймера RTC
    BKP_RTC_WaitForUpdate ();          
    BKP_RTC_ITConfig (BKP_RTC_IT_ALRF, ENABLE);
		
		sprintf(message, "Waiting...");   
		U_MLT_Put_String (message, 3);

		// Дождаться окончания измерения
    os_evt_wait_or (EVENT_ALARM, 0xFFFF);

		// Удалить задачу по выводу отсчетов времени оставшегося времени на ЖКИ
		if (U_Alarm_Task_CountDown_ID)
		{
		  os_tsk_delete (U_Alarm_Task_CountDown_ID);
			U_Alarm_Task_CountDown_ID = 0;
		}
		
		// Вывести сообщение на ЖКИ
		sprintf(message, "Alarm!");   
		U_MLT_Put_String (message, 3);
		U_MLT_Put_String ("", 4);
		
		os_dly_wait (3000);		
	}
}


// Задача по выводу отсчетов оставшегося времени на ЖКИ
OS_TID U_Alarm_Task_CountDown_ID;  // Переменная для хранения идентификатора задачи

__task void U_Alarm_Task_CountDown_Function (void)
{
	int32_t i;
	time_t current;
	time_t alarm;
	
	while(1)
	{
		// Получить метку текущего времени
		current = U_Alarm_Get_DateTime_Stamp();
		
		// Получить метку времени, когда таймер должен сработать
    BKP_RTC_WaitForUpdate ();          // Подождать, пока обновятся регистры RTC
		alarm = MDR_BKP -> RTC_ALRM;
		
		i = alarm - current;
		
		// Вывести на ЖКИ количество секунд, оставшихся до срабатывания таймера
		sprintf(message, "Count: %d", i);   
		U_MLT_Put_String (message, 4);
		
		os_dly_wait (1000);
		
	}
}
