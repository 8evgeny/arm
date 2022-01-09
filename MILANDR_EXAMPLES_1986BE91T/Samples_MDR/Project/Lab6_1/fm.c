// ***********************************************************************************
// Проект:      Lab6_1 
// Программа:   Использование аппаратных таймеров-счетчиков для измерения частоты импульсов.
//              Измерение частоты по частоте. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл:  fm.с 
// Модуль:  Функциональный генератор аналогового сигнала
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "fm.h"

// Количество подсчитанных подсчитанных импульсов K за период измерения T
volatile uint32_t U_FM_K = 0;


// Буфер для формирования сообщений, выводимых на ЖКИ
static char message[128];

// Конфигурирование таймера для задания периода измерений T
static void TIM_T_Config(void);

// Конфигурирование таймера для подсчета количества импульсов K
static void TIM_K_Config(void);


// Инициализация 
void U_FM_Init(void)
{
  // Конфигурирование таймера для задания периода измерений T
  TIM_T_Config();

  // Конфигурирование таймера для подсчета количества импульсов K
  TIM_K_Config();
}


// Конфигурирование таймера для задания периода измерений T
void TIM_T_Config(void)
{
  // Структура данных для инициализации таймера
  TIMER_CntInitTypeDef TimerInitStructure;
	
  // Разрешить тактирование требуемого порта ввода-вывода и таймера
  RST_CLK_PCLKcmd (RST_CLK_PCLK_TIMER2,	ENABLE);	
	
  // Деинициализировать таймер
  TIMER_DeInit (FM_TIMER_T);
	
	// Задать тактирование таймера
  TIMER_BRGInit (FM_TIMER_T, TIMER_HCLKdiv1);  // 80МГц    

  TimerInitStructure.TIMER_Prescaler                = 7999;    // 80МГц / (7999 + 1) = 10кГц 
  TimerInitStructure.TIMER_Period                   = (uint16_t)(U_FM_T * 10000);   
  TimerInitStructure.TIMER_CounterMode              = TIMER_CntMode_ClkFixedDir;
  TimerInitStructure.TIMER_CounterDirection         = TIMER_CntDir_Up;
  TimerInitStructure.TIMER_EventSource              = TIMER_EvSrc_None;
  TimerInitStructure.TIMER_FilterSampling           = TIMER_FDTS_TIMER_CLK_div_1;
  TimerInitStructure.TIMER_ARR_UpdateMode           = TIMER_ARR_Update_Immediately;
  TimerInitStructure.TIMER_ETR_FilterConf           = TIMER_Filter_1FF_at_TIMER_CLK;
  TimerInitStructure.TIMER_ETR_Prescaler            = TIMER_ETR_Prescaler_None;
  TimerInitStructure.TIMER_ETR_Polarity             = TIMER_ETRPolarity_NonInverted;
  TimerInitStructure.TIMER_BRK_Polarity             = TIMER_BRKPolarity_NonInverted;
  TIMER_CntInit (FM_TIMER_T, &TimerInitStructure);

  // Разрешить прерывания от захвата таймера	по каналу 1	задним фронтом сигнала или по переполнению
  TIMER_ITConfig (FM_TIMER_T, TIMER_STATUS_CNT_ARR, ENABLE);

  // Разрешить работу таймера 
  TIMER_Cmd (FM_TIMER_T, ENABLE);	
	
  // Задать приоритет выше, чем у планировщика задач. 
  NVIC_SetPriority (Timer2_IRQn, 0x02);
	
  // Разрешить прерывания от FM_TIMER_T
  NVIC_EnableIRQ (Timer2_IRQn); 		

}


// Конфигурирование таймера для подсчета количества импульсов K
static void TIM_K_Config(void)
{	
  // Структура данных для инициализации линий ввода-вывода
  PORT_InitTypeDef PortInitStructure;

  // Структура данных для инициализации таймера
  TIMER_CntInitTypeDef TimerInitStructure;

  // Структура данных для инициализации канала таймера
  TIMER_ChnInitTypeDef TimerChnInitStructure;
	
  // Структура данных для инициализации выхода канала таймера
  TIMER_ChnOutInitTypeDef	TimerChnOutInitStructure;

	// Разрешить тактирование требуемого порта ввода-вывода и таймера
	RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTC | RST_CLK_PCLK_TIMER3,	ENABLE);

	// Задать тактирование таймера
  TIMER_BRGInit (FM_TIMER_K, TIMER_HCLKdiv1);  // 80МГц    
	
	// Инициализация линии входа для измерения частоты
	PORT_StructInit (&PortInitStructure);
	PortInitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
	PortInitStructure.PORT_OE    = PORT_OE_IN;
	PortInitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	PortInitStructure.PORT_Pin   = FM_Pin; 
	PORT_Init (FM_PORT, &PortInitStructure);	

  // Сбросить все настройки для PWM_TIMER 
  TIMER_DeInit (FM_TIMER_K);

  // Инициализация таймера  
	TIMER_CntStructInit (&TimerInitStructure);
  TimerInitStructure.TIMER_Prescaler = 0;  										              // Предделитель	частоты импульсов, тактирующих таймер (делить на 1)
  TimerInitStructure.TIMER_Period = 65535;                                  // Период таймера по заданной частоте импульсов (делаем макс. возможным)	
  TimerInitStructure.TIMER_CounterDirection = TIMER_CntDir_Up;		          // Считать вверх
  TimerInitStructure.TIMER_CounterMode = TIMER_CntMode_EvtFixedDir;         // Режим фиксированного направления счета (считаем только вверх, не меняя направления).
  TimerInitStructure.TIMER_EventSource = TIMER_EvSrc_CH1;			   					  // Событие, по которому производится счет (Считаем импульсы	с канала 1)
  TimerInitStructure.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;   // Режим обновления регистра сравнения. Обновлять немедленно. 
  TimerInitStructure.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;     
  TimerInitStructure.TIMER_ETR_FilterConf = TIMER_Filter_1FF_at_TIMER_CLK;   
  TimerInitStructure.TIMER_ETR_Prescaler = TIMER_ETR_Prescaler_None;        
  TimerInitStructure.TIMER_ETR_Polarity = TIMER_ETRPolarity_NonInverted;
  TimerInitStructure.TIMER_BRK_Polarity = TIMER_BRKPolarity_NonInverted;
  TIMER_CntInit (FM_TIMER_K, &TimerInitStructure);

  // Инициализация канала таймера
  TIMER_ChnStructInit (&TimerChnInitStructure);
  TimerChnInitStructure.TIMER_CH_Number = FM_CHN_K; 											   // Номер канала
  TimerChnInitStructure.TIMER_CH_Mode = TIMER_CH_MODE_CAPTURE;							 // Режим канала - захват
  TimerChnInitStructure.TIMER_CH_EventSource = TIMER_CH_EvSrc_PE;            // Передний фронт импульса  
	TIMER_ChnInit (FM_TIMER_K, &TimerChnInitStructure);

  // Инициализация выхода канала таймера
  TIMER_ChnOutStructInit (&TimerChnOutInitStructure);
  TimerChnOutInitStructure.TIMER_CH_Number = FM_CHN_K;																// Номер канала
  TimerChnOutInitStructure.TIMER_CH_DirOut_Polarity = TIMER_CHOPolarity_NonInverted;  // Прямой выход канала неинвертирован
  TimerChnOutInitStructure.TIMER_CH_DirOut_Source = TIMER_CH_OutSrc_Only_0;						// Прямой выход канала всега 0
  TimerChnOutInitStructure.TIMER_CH_DirOut_Mode = TIMER_CH_OutMode_Input;							// Прямой выход канала является входом
  TIMER_ChnOutInit (FM_TIMER_K, &TimerChnOutInitStructure);

  // Разрешить работу таймера 
  TIMER_Cmd (FM_TIMER_K, ENABLE);	

}


// Задача по измерению частоты импульсов
OS_TID U_FM_Task_ID;  // Переменная для хранения идентификатора задачи

__task void U_FM_Task_Function (void)
{
	volatile float F;        // Измеренная частота
	
	while(1)
	{
    // Запустить процесс измерения частоты
    FM_Start();
		
		// Дождаться окончания измерения
    os_evt_wait_or (EVENT_FM_READY, 0xFFFF);

		// Вычислить частоту
		F = U_FM_K / U_FM_T;	 
				
		// Вывести результат измерения частоты на ЖКИ в Гц
		sprintf(message , "F = %1.1fHz", F);   
		U_MLT_Put_String (message, 3);
		
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (250);  		
	}
}



// SVC-Функция запуска измерения частоты
void __SVC_1 (void) 
{
  __disable_irq();
   
    // Сброс таймера FM_TIMER_T 
    FM_TIMER_T->CNT = 0;

	  // Сброс таймера FM_TIMER_K 
    FM_TIMER_K->CNT = 0;
	
    // Разрешить работу FM_TIMER_T 
    TIMER_Cmd (FM_TIMER_T, ENABLE);
 
  
  __enable_irq();
}
