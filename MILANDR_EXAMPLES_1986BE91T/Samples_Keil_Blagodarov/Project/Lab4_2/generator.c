// ***********************************************************************************
// Проект:      Lab4_2 
// Программа:   Работа с ЦАП. Генерация сигналов с использованием DMA 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл:  generator.с 
// Модуль:  Функциональный генератор аналогового сигнала
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "generator.h"
#include <math.h>


// Структура для инициализации DMA
DMA_CtrlDataInitTypeDef DMA_InitStructure;
// Структура для инициализации канала DMA
DMA_ChannelInitTypeDef DMA_Channel_InitStructure;


// Массив отсчетов для сигнала
static  uint16_t Signal [U_GENERATOR_BUFFER_SIZE];

// Конфигурирование таймера
static void TIM_Config(void);

// Конфигурирование ЦАП
static void DAC_Config(void);

// Конфигурация DMA
static void DMA_Config(void);

// Задание Функции генератора гармонического (синусоидального) сигнала
static void Function_Sin_Setup(void);

// Задание Функции генератора пилообразного сигнала
static void Function_Triangle_Setup(void);


// Инициализация 
void U_Generator_Init(void)
{
  // Задание Функции генератора гармонического (синусоидального) сигнала
  Function_Sin_Setup();

  // Задание Функции генератора пилообразного сигнала
  //Function_Triangle_Setup();
	
  // Конфигурирование DMA
  DMA_Config();

  // Конфигурирование DAC
  DAC_Config();

  // Конфигурирование таймера
  TIM_Config();

}


// Задание Функции генератора гармонического (синусоидального) сигнала
static void Function_Sin_Setup(void)
{
	uint32_t i;
	float w;
	
	// Заполнить массив с отсчетами синусоиды
  w = 2 * 3.1415926535 / U_GENERATOR_BUFFER_SIZE; 
	
	for (i = 0; i < U_GENERATOR_BUFFER_SIZE; i++)
	{
     Signal[i] = U_GENERATOR_C + U_GENERATOR_SIN_A * sin(w * i);
  }
}

// Задание Функции генератора пилообразного сигнала
static void Function_Triangle_Setup(void)
{
	uint32_t i;
	float k;
	
	// Заполнить массив с отсчетами сигнала
  k = (float)(U_GENERATOR_TRIANGLE_A) / U_GENERATOR_BUFFER_SIZE; 
	
	for (i = 0; i < U_GENERATOR_BUFFER_SIZE; i++)
	{
     Signal[i] = U_GENERATOR_C + k * i;
  }
}



// Конфигурирование таймера
static void TIM_Config(void)
{
	// Структура для инициализации таймера
  TIMER_CntInitTypeDef TIM_CntInit;	
	
  // Сбросить настройки таймера TIMER1
  TIMER_DeInit (MDR_TIMER1);

  // Разрешить тактирование таймера TIMER1
  RST_CLK_PCLKcmd (RST_CLK_PCLK_TIMER1, ENABLE);  
	
	// Задать для таймера TIMER1 частоту тактирования
  TIMER_BRGInit (MDR_TIMER1, TIMER_HCLKdiv1);
	
  TIM_CntInit.TIMER_Prescaler                = 0;                                  // Предделитель частоты (без деления)
  TIM_CntInit.TIMER_Period                   = U_GENERATOR_PERIOD (U_GENERATOR_F); // Период таймера
  TIM_CntInit.TIMER_CounterMode              = TIMER_CntMode_ClkFixedDir;          // Режим счета (фиксированное направление счета)
  TIM_CntInit.TIMER_CounterDirection         = TIMER_CntDir_Up;                    // Считать вверх 
  TIM_CntInit.TIMER_EventSource              = TIMER_EvSrc_None;                   // Источник события для счета (без событий, т.е. считаем каждый импульс тактирования таймера) 
  TIM_CntInit.TIMER_FilterSampling           = TIMER_FDTS_TIMER_CLK_div_1;         // Частота тактирования фильтра на входе таймера ()
  TIM_CntInit.TIMER_ARR_UpdateMode           = TIMER_ARR_Update_Immediately;			  
  TIM_CntInit.TIMER_ETR_FilterConf           = TIMER_Filter_1FF_at_TIMER_CLK;
  TIM_CntInit.TIMER_ETR_Prescaler            = TIMER_ETR_Prescaler_None;
  TIM_CntInit.TIMER_ETR_Polarity             = TIMER_ETRPolarity_NonInverted;
  TIM_CntInit.TIMER_BRK_Polarity             = TIMER_BRKPolarity_NonInverted;
  TIMER_CntInit (MDR_TIMER1, &TIM_CntInit);                                        // Инициализировать таймер

  // Разрешить работу DMA совместно с таймером TIMER1 
  TIMER_DMACmd (MDR_TIMER1, TIMER_STATUS_CNT_ARR, ENABLE);

  // Разрешить работу таймера TIMER1 
  TIMER_Cmd (MDR_TIMER1, ENABLE);	

  // Разрешить прерывания от DMA
  NVIC_EnableIRQ(DMA_IRQn);	

}

// Конфигурирование ЦАП
static void DAC_Config(void)
{
	// Структруа для инициализации портов
	PORT_InitTypeDef PortInitStructure;	
	
  // Разрешить тактирование ЦАП и порта E
  RST_CLK_PCLKcmd (RST_CLK_PCLK_DAC | RST_CLK_PCLK_PORTE, ENABLE);  

  // Линию PE0, с которой связан выход  DAC2, сделать аналоговым выходом
  PORT_StructInit (&PortInitStructure);	
  PortInitStructure.PORT_Pin   = PORT_Pin_0;
  PortInitStructure.PORT_OE    = PORT_OE_OUT;
  PortInitStructure.PORT_MODE =  PORT_MODE_ANALOG;
  PORT_Init (MDR_PORTE, &PortInitStructure);		

	// Сбросить все настройки ЦАП
  DAC_DeInit();

	// Инициализировать ЦАП2, задав в качестве опоры напряжение питания аналоговой части МК
  DAC2_Init(DAC2_AVCC);

  // Разрешить работу канала ЦАП2 
  DAC2_Cmd (ENABLE);
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
	
  DMA_InitStructure.DMA_SourceBaseAddr = (uint32_t) Signal;	              // Базовый адрес в памяти, где расположен массив исходных данных. Отсюда будем читать данные через DMA.
  DMA_InitStructure.DMA_DestBaseAddr = (uint32_t)(&(MDR_DAC->DAC2_DATA));	// Базовый адрес в памяти, где расположен регистр данных ЦАП2. Сюда будем писать через DMA.
  DMA_InitStructure.DMA_CycleSize = U_GENERATOR_BUFFER_SIZE;							// Размер буфера
  DMA_InitStructure.DMA_SourceIncSize = DMA_SourceIncHalfword;				    // Разрешить автоувеличение адреса для памяти (адрес увеличиваем на 2)
  DMA_InitStructure.DMA_DestIncSize = DMA_DestIncNo;				              // Запретить автоувеличение адреса для периферии
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     // Читаем и пишем значения по 16 бит (по полслова)
  DMA_InitStructure.DMA_NumContinuous = DMA_Transfers_32;				          // Сколько раз повоторяем совокупность циклов - 32 раза
  DMA_InitStructure.DMA_SourceProtCtrl = DMA_SourcePrivileged;			      // Режим защиты источника
  DMA_InitStructure.DMA_DestProtCtrl = DMA_DestPrivileged;			          // Режим защиты приемника
  DMA_InitStructure.DMA_Mode = DMA_Mode_Basic;							              // Режим работы DMA - базовый
  
  // Задать структуру канала
  DMA_Channel_InitStructure.DMA_PriCtrlData = &DMA_InitStructure;
  DMA_Channel_InitStructure.DMA_Priority = DMA_Priority_Default;
  DMA_Channel_InitStructure.DMA_UseBurst = DMA_BurstClear;
  DMA_Channel_InitStructure.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;
  
	// Инициализировать канал DMA 
  DMA_Init (DMA_Channel_TIM1, &DMA_Channel_InitStructure);						  

  // ??? Enable dma_req or dma_sreq to generate DMA request 
  MDR_DMA->CHNL_REQ_MASK_CLR = 1 << DMA_Channel_TIM1;
  MDR_DMA->CHNL_USEBURST_CLR = 1 << DMA_Channel_TIM1;

  // Разрешить работу DMA, с каналом для таймера TIM1 
  DMA_Cmd (DMA_Channel_TIM1, ENABLE);

  // Задать приоритет аппаратного прерывания от DMA
  NVIC_SetPriority (DMA_IRQn, 1); 	

	
}
