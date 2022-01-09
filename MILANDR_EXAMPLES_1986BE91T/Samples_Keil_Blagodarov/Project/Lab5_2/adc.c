// ***********************************************************************************
// Проект:      Lab5_2 
// Программа:   Работа с ШИМ. Регулирование ширины импульса с помощью потенциометра и АЦП. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: adc.с 
// Назначение: Управление АЦП      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "adc.h"

// Структура для инициализации DMA
DMA_CtrlDataInitTypeDef DMA_InitStructure;
// Структура для инициализации канала DMA
DMA_ChannelInitTypeDef DMA_Channel_InitStructure;

// Буфер для хранения результатов АЦП
uint16_t ADC_Buffer [U_ADC_BUFFER_SIZE];


// Конфигурирование АЦП
static void ADC_Config(void);

// Конфигурирование DMA (Direct Memory Access - прямой доступ к памяти)
static void DMA_Config(void);

// Инициализировать АЦП
void U_ADC_Init (void)
{
  // Конфигурирование DMA 
  DMA_Config();
	
  // Конфигурирование АЦП
  ADC_Config();
}


// Конфигурирование DMA (Direct Memory Access - прямой доступ к памяти)
static void DMA_Config(void)
{
	// DMA вообще и в частности. http://habrahabr.ru/post/228531/  
  // DMA и все что с ним связано. http://forum.milandr.ru/viewtopic.php?f=33&t=234&hilit=DMA+DMA+ADC&sid=888ddcc861bafe357880b779547a2fd9&start=15 
	
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
	
  DMA_InitStructure.DMA_SourceBaseAddr = (uint32_t)(&(MDR_ADC->ADC1_RESULT));	// Базовый адрес регистра результата преобразования АЦП1, откуда будем читать 
  DMA_InitStructure.DMA_DestBaseAddr = (uint32_t) &ADC_Buffer;			      // Базовый адрес в памяти, куда будем писать результаты работы АЦП
  DMA_InitStructure.DMA_CycleSize = U_ADC_BUFFER_SIZE;							      // Размер буфера
  DMA_InitStructure.DMA_SourceIncSize = DMA_SourceIncNo;				          // Запретить автоувеличение адреса для периферии
  DMA_InitStructure.DMA_DestIncSize = DMA_DestIncHalfword;				        // Разрешить автоувеличение адреса для памяти
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     // ???
  DMA_InitStructure.DMA_NumContinuous = DMA_Transfers_1;				          // Сколько раз повоторяем совокупность циклов - 1 раз
  DMA_InitStructure.DMA_SourceProtCtrl = DMA_SourcePrivileged;			      // Режим защиты источника
  DMA_InitStructure.DMA_DestProtCtrl = DMA_DestPrivileged;			          // Режим защиты приемника
  DMA_InitStructure.DMA_Mode = DMA_Mode_Basic;							              // Режим работы DMA - базовый
  
  // Задать структуру канала
  DMA_Channel_InitStructure.DMA_PriCtrlData = &DMA_InitStructure;
  DMA_Channel_InitStructure.DMA_Priority = DMA_Priority_Default;
  DMA_Channel_InitStructure.DMA_UseBurst = DMA_BurstClear;
  DMA_Channel_InitStructure.DMA_SelectDataStructure = DMA_CTRL_DATA_PRIMARY;
  
	// Инициализировать канал DMA 
  DMA_Init (DMA_Channel_ADC1, &DMA_Channel_InitStructure);							  

  // ??? Enable dma_req or dma_sreq to generate DMA request 
  MDR_DMA->CHNL_REQ_MASK_CLR = 1 << DMA_Channel_ADC1;
  MDR_DMA->CHNL_USEBURST_CLR = 1 << DMA_Channel_ADC1;

  // Разрешить работу DMA1, канала 1 
  DMA_Cmd (DMA_Channel_ADC1, ENABLE);

  // Задать приоритет аппаратного прерывания от DMA
  NVIC_SetPriority (DMA_IRQn, 1); 	  
	
}


// Конфигурирование АЦП
static void ADC_Config(void)
{
	// Структуры для инициализации АЦП
  ADC_InitTypeDef ADC_InitStructure;
	ADCx_InitTypeDef ADCx_InitStructure;
	
  // Разрешить тактирование АЦП
  RST_CLK_PCLKcmd (RST_CLK_PCLK_ADC, ENABLE);  

  ADC_DeInit();
  ADC_StructInit(&ADC_InitStructure);

  // Конфигурация АЦП общая
  ADC_InitStructure.ADC_SynchronousMode      = ADC_SyncMode_Independent;						
  ADC_InitStructure.ADC_StartDelay           = 0;																		
  ADC_InitStructure.ADC_TempSensor           = ADC_TEMP_SENSOR_Disable;             // Запретить работу температурного датчика
  ADC_InitStructure.ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Disable;   // Запретить работу усилителя для температурного датчика
  ADC_InitStructure.ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Disable;  // Запретить преобразования для канала температурного датчика  
  ADC_InitStructure.ADC_IntVRefConversion    = ADC_VREF_CONVERSION_Disable;         // Запретить преобразования для канала VREF (внутренней опоры)
  ADC_InitStructure.ADC_IntVRefTrimming      = 1;                                   
  ADC_Init (&ADC_InitStructure);

  // Конфигурация АЦП1
  ADCx_StructInit (&ADCx_InitStructure);															
  ADCx_InitStructure.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;						
  ADCx_InitStructure.ADC_SamplingMode     = ADC_SAMPLING_MODE_CICLIC_CONV;	// Режим одиночного преобразования 
  ADCx_InitStructure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;				// Режим переключения каналов (запретить)
  ADCx_InitStructure.ADC_ChannelNumber    = U_ADC_U_CH;											// Выбранный канал АЦП (никакой, так как используется режим с переключением нескольких каналов)
  ADCx_InitStructure.ADC_Channels         = 0;															// Выбранные каналы АЦП с последовательным опросом 
  ADCx_InitStructure.ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;			// Контроль уровня входного напряжения (отключено).
  ADCx_InitStructure.ADC_LowLevel         = 0;															// Нижний уровень входного напряжения (не задан)
  ADCx_InitStructure.ADC_HighLevel        = 0;															// Верхний уровень	входного напряжения (не задан) 
  ADCx_InitStructure.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;				// Вид источника опроного напряжения (внутренний)
  ADCx_InitStructure.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;	  // Вид внутреннего источника опроного напряжения (не точный)
  ADCx_InitStructure.ADC_Prescaler        = ADC_CLK_div_512;								// Предделитель частоты тактирования АЦП (512)
  ADCx_InitStructure.ADC_DelayGo          = 7;															// Задержка между запусками АЦП (максимальная)   	
  ADC1_Init (&ADCx_InitStructure);

  // Разрешить работу АЦП1
  ADC1_Cmd (ENABLE);

  // Разрешить прерывания от DMA
  NVIC_EnableIRQ (DMA_IRQn); 
}







