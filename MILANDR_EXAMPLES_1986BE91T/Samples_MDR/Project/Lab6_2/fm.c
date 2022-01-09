// ***********************************************************************************
// Проект:      Lab6_2 
// Программа:   Использование аппаратных таймеров-счетчиков для измерения частоты импульсов.
//              Измерение частоты по периоду. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл:  fm.с 
// Модуль:  Функциональный генератор аналогового сигнала
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "fm.h"

// Массив результатов измерения периода импульсов
static  uint16_t TimerCapture [U_FM_BUFFER_SIZE];
static  uint16_t TimerCaptureD [U_FM_BUFFER_SIZE];

// Структура для инициализации DMA
DMA_CtrlDataInitTypeDef DMA_InitStructure;
// Структура для инициализации канала DMA
DMA_ChannelInitTypeDef DMA_Channel_InitStructure;

// Буфер для формирования сообщений, выводимых на ЖКИ
static char message[128];

// Конфигурирование таймера
static void TIM_Config(void);

// Конфигурация DMA
static void DMA_Config(void);



// Инициализация 
void U_FM_Init(void)
{
  // Конфигурирование DMA
  DMA_Config();

  // Конфигурирование таймера
  TIM_Config();

}


// Конфигурирование таймера
static void TIM_Config(void)
{	
  // Предделитель таймера 
  uint16_t PrescalerValue;
	
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
		
	// Инициализация линии входа для измерения частоты
	PORT_StructInit (&PortInitStructure);
	PortInitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
	PortInitStructure.PORT_OE    = PORT_OE_IN;
	PortInitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	PortInitStructure.PORT_Pin   = FM_Pin; 
	PORT_Init (FM_PORT, &PortInitStructure);	
	

  // Сбросить все настройки для PWM_TIMER 
  TIMER_DeInit (FM_TIMER);

  // Задать тактирование таймера 
  TIMER_BRGInit (FM_TIMER, TIMER_HCLKdiv64);	   // 1.25МГц 
 
  // Вычислить предделитель для таймера 
  PrescalerValue = 0; 
 
  // Инициализация таймера  
  TimerInitStructure.TIMER_Prescaler = PrescalerValue;  										// Предделитель	частоты импульсов, тактирующих таймер
  TimerInitStructure.TIMER_Period = 65535;                                  // Период таймера по заданной частоте импульсов (делаем макс. возможным)	
  TimerInitStructure.TIMER_CounterDirection = TIMER_CntDir_Up;		          // Считать вверх
  TimerInitStructure.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;         // Режим фиксированного направления счета (считаем только вверх, не меняя направления).
  TimerInitStructure.TIMER_EventSource = TIMER_EvSrc_None;			   					// Событие, по которому производится счет (событие не задано, считаем все импульсы, тактирующие таймер)
  TimerInitStructure.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;   // Режим обновления регистра сравнения. Обновлять немедленно. 
  TimerInitStructure.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;     
  TimerInitStructure.TIMER_ETR_FilterConf = TIMER_Filter_1FF_at_TIMER_CLK;   
  TimerInitStructure.TIMER_ETR_Prescaler = TIMER_ETR_Prescaler_None;        
  TimerInitStructure.TIMER_ETR_Polarity = TIMER_ETRPolarity_NonInverted;
  TimerInitStructure.TIMER_BRK_Polarity = TIMER_BRKPolarity_NonInverted;
  TIMER_CntInit (FM_TIMER, &TimerInitStructure);

  // Инициализация канала таймера
  TIMER_ChnStructInit (&TimerChnInitStructure);
  TimerChnInitStructure.TIMER_CH_Number = FM_CHN; 												   // Номер канала
  TimerChnInitStructure.TIMER_CH_Mode = TIMER_CH_MODE_CAPTURE;							 // Режим канала - захват
  TimerChnInitStructure.TIMER_CH_EventSource = TIMER_CH_EvSrc_PE;            // Передний фронт импульса  
  TIMER_ChnInit (FM_TIMER, &TimerChnInitStructure);

  // Инициализация выхода канала таймера
  TIMER_ChnOutStructInit (&TimerChnOutInitStructure);
  TimerChnOutInitStructure.TIMER_CH_Number = FM_CHN;																	// Номер канала
  TimerChnOutInitStructure.TIMER_CH_DirOut_Polarity = TIMER_CHOPolarity_NonInverted;  // Прямой выход канала неинвертирован
  TimerChnOutInitStructure.TIMER_CH_DirOut_Source = TIMER_CH_OutSrc_Only_0;						// Прямой выход канала всега 0
  TimerChnOutInitStructure.TIMER_CH_DirOut_Mode = TIMER_CH_OutMode_Input;							// Прямой выход канала является входом
  TIMER_ChnOutInit (FM_TIMER, &TimerChnOutInitStructure);

  // Разрешить работу DMA совместно с таймером  
  TIMER_DMACmd (FM_TIMER, TIMER_STATUS_CCR_CAP_CH1, ENABLE);
	
  // Разрешить работу таймера 
  TIMER_Cmd (FM_TIMER, ENABLE);	

  // Разрешить прерывания от DMA
  NVIC_EnableIRQ (DMA_IRQn);	

}

// Конфигурация DMA (Direct Memory Access - прямой доступ к памяти)
static void DMA_Config(void)
{
  // Разрешить тактирование DMA 
	// Для корректной работы DMA необходимо разрешить тактирование SSP1 и SSP2
  // Если этого не сделать, то всё время будет возникать прерывание от DMA.	
  RST_CLK_PCLKcmd (RST_CLK_PCLK_DMA | RST_CLK_PCLK_SSP1 | RST_CLK_PCLK_SSP2, ENABLE);  
	
  // Запретить все прерывания, в том числе от SSP1 и SSP2.
  NVIC->ICPR[0] = 0xFFFFFFFF;
  NVIC->ICER[0] = 0xFFFFFFFF;	
	
  // Сбросить все настройки DMA
  DMA_DeInit();
  DMA_StructInit (&DMA_Channel_InitStructure);	
	
  DMA_InitStructure.DMA_SourceBaseAddr = (uint32_t)(&(FM_TIMER->CCR1));	  // 
  DMA_InitStructure.DMA_DestBaseAddr = (uint32_t) TimerCapture;	          // 
  DMA_InitStructure.DMA_CycleSize = U_FM_BUFFER_SIZE;							        // Размер буфера
  DMA_InitStructure.DMA_SourceIncSize = DMA_SourceIncNo;				          // 
  DMA_InitStructure.DMA_DestIncSize = DMA_DestIncHalfword;				        // 
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     // Читаем и пишем значения по 16 бит (по полслова)
  DMA_InitStructure.DMA_NumContinuous = DMA_Transfers_1;				          // Сколько раз повоторяем совокупность циклов - 1 раз
  DMA_InitStructure.DMA_SourceProtCtrl = DMA_SourcePrivileged;			      // Режим защиты источника
  DMA_InitStructure.DMA_DestProtCtrl = DMA_DestPrivileged;			          // Режим защиты приемника
  DMA_InitStructure.DMA_Mode = DMA_Mode_Basic;							              // Режим работы DMA - базовый
  
  // Задать структуру канала
  DMA_Channel_InitStructure.DMA_PriCtrlData = &DMA_InitStructure;
  DMA_Channel_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_Channel_InitStructure.DMA_UseBurst = DMA_BurstClear;
  DMA_Channel_InitStructure.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;
  
	// Инициализировать канал DMA 
  DMA_Init (DMA_Channel_TIM3, &DMA_Channel_InitStructure);						  

  MDR_DMA->CHNL_REQ_MASK_CLR = 1 << DMA_Channel_TIM3;
  MDR_DMA->CHNL_USEBURST_CLR = 1 << DMA_Channel_TIM3;

  // Задать приоритет аппаратного прерывания от DMA
  NVIC_SetPriority (DMA_IRQn, 1); 	
	
}




// Задача по измерению частоты импульсов
OS_TID U_FM_Task_ID;  // Переменная для хранения идентификатора задачи

__task void U_FM_Task_Function (void)
{
	float F;        // Измерения
	uint32_t i, j;
	uint16_t T; 
	int32_t D; 
  int32_t wait_result;
	
	while(1)
	{
    // Разрешить работу DMA с таймером. Тем самым запускается цикл измерения частоты 
    DMA_Cmd (DMA_Channel_TIM3, ENABLE);
		
		// Дождаться окончания измерения, но не дольше 2 секунд
    wait_result = os_evt_wait_or (EVENT_FM_READY, 2000);

		// Если ожидание закончилось из-за поступления события
    if (wait_result == OS_R_EVT)		
		{

			// Получить массив со значениями периодов импульсов.
			// Исходный массив содержит лишь возрастающие значения счетчика таймера
			for (i = 0; i < U_FM_BUFFER_SIZE - 1; i++)
			{
				// Находим разницу между соседними измерениями и получаем длину периода
				D = TimerCapture[i] - TimerCapture[i - 1];
				
				// Если между двумя соседними измерениями НЕ возникало переполнение таймера
				if (D >= 0)
					TimerCaptureD[i] = D;
				
				// Если между двумя соседними измерениями возникало переполнение таймера
				else
					TimerCaptureD[i] = 65535 + D;
			}
			
			// Медианный фильтр 
			// Упорядочить массив методом пузырька
			for(i = 2; i < U_FM_BUFFER_SIZE - 2; i++)
				for(j = 2; j < U_FM_BUFFER_SIZE - 1; j++)
					if(TimerCaptureD[j] > TimerCaptureD[j + 1])
					{
						T = TimerCaptureD[j];
						TimerCaptureD[j] = TimerCaptureD[j + 1];
						TimerCaptureD[j + 1] = T;
					}
					
			// Найти значение среднего элемента массива
			T = TimerCaptureD [2 + (U_FM_BUFFER_SIZE - 2) / 2] ;

			// Проверить, допустимый ли период получился
			if(T > FM_PULSE_PERIOD(U_FM_FMIN))
				 T = FM_PULSE_PERIOD(U_FM_FMIN);
			else
				 if(T < FM_PULSE_PERIOD(U_FM_FMAX))
					 T = FM_PULSE_PERIOD(U_FM_FMAX);		
			
			F = U_FM_FZ / (float)T;
					
			// Вывести результат измерения частоты на ЖКИ в Гц
			sprintf(message , "F = %1.1fHz", F);   
			U_MLT_Put_String (message, 3);
		}
		// Ожидание завершилось из-за превышения времени. 
		// Т.е. отсутствует сигнал
		else
		{
			// Вывести результат измерения частоты на ЖКИ в Гц
			sprintf(message , "F = ?");   
			U_MLT_Put_String (message, 3);
    }
		
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (250);  		
	}
}
