// ***********************************************************************************
// Проект:      Lab3_4 
// Программа:   Работа с АЦП. Измерение температуры кристалла МК.
//              Режим многократного преобразования по одному каналу 
//              с использованием прямого доступа к памяти.
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
static uint16_t ADC_Buffer [U_ADC_BUFFER_SIZE];


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
  DMA_InitStructure.DMA_DestIncSize = DMA_DestIncHalfword;				        // Разрешить автоувеличение адреса для памяти на 2
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;     // Передаем данные по 2 байта (полслова)  
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

  // Снять запрет на запросы и одиночные запросы к DMA  
  MDR_DMA->CHNL_REQ_MASK_CLR = 1 << DMA_Channel_ADC1;
  MDR_DMA->CHNL_USEBURST_CLR = 1 << DMA_Channel_ADC1;

  // Разрешить работу DMA
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
  ADC_InitStructure.ADC_SynchronousMode      = ADC_SyncMode_Independent;						// Независимый запуск АЦП
  ADC_InitStructure.ADC_StartDelay           = 0;																		// Задрежка между запусками АЦП1 и АЦП2
  ADC_InitStructure.ADC_TempSensor           = ADC_TEMP_SENSOR_Enable;              // Разрешить работу температурного датчика
  ADC_InitStructure.ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Enable;    // Разрешить работу усилителя для температурного датчика
  ADC_InitStructure.ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Enable;   // Разрешить преобразования для канала температурного датчика  
  ADC_InitStructure.ADC_IntVRefConversion    = ADC_VREF_CONVERSION_Disable;         // Запретить преобразования для канала VREF (внутренней опоры)
  ADC_InitStructure.ADC_IntVRefTrimming      = 1;                                   // Подстройка источника напряжения VREF
  ADC_Init (&ADC_InitStructure);

  // Конфигурация АЦП1
  ADCx_StructInit (&ADCx_InitStructure);															
  ADCx_InitStructure.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;						// Тактировать АЦП той же частотой, что и ядро МК 
  ADCx_InitStructure.ADC_SamplingMode     = ADC_SAMPLING_MODE_CICLIC_CONV;	// Режим циклического преобразования (несколько раз подряд)
  ADCx_InitStructure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;				// Режим переключения каналов (запретить)
  ADCx_InitStructure.ADC_ChannelNumber    = ADC_CH_TEMP_SENSOR;							// Выбранный канал АЦП (температурный датчик)
  ADCx_InitStructure.ADC_Channels         = 0;															// Выбранные каналы АЦП с последовательным опросом (не выбраны) 
  ADCx_InitStructure.ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;			// Контроль уровня входнрого напряжения (отключено)
  ADCx_InitStructure.ADC_LowLevel         = 0;															// Нижний уровень
  ADCx_InitStructure.ADC_HighLevel        = 0;															// Верхний уровень	
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

// Строка формируемого сообщения
static char message[64];

// Переменная для хранения идентификатора задачи
OS_TID U_ADC_Task_ID;

// Задача по измерению температуры микроконтроллера
__task void U_ADC_Task_Function (void)
{
	uint32_t D;    // Результат аналого-цифрового преобразования
  float T;       // Измеренная температура 
	uint32_t i;

	while(1)
	{
    // Разрешить работу DMA с АЦП. Тем самым запускается цикл аналого-цифровых преобразований 
    DMA_Cmd (DMA_Channel_ADC1, ENABLE);
		
		// Дождаться окончания преобразования
    os_evt_wait_or(EVENT_ADC_EOC, 0xFFFF); 

		// Усреднить результат
		for (i = 0, D = 0; i < U_ADC_BUFFER_SIZE; i++)
		  D += ADC_Buffer[i];
		D /= U_ADC_BUFFER_SIZE;
		
    // Преобразование показаний АЦП в температуру в градусах Цельсия
    T = ((int32_t)D - (int32_t) ADC_TS_D1) * (ADC_TS_T2 - ADC_TS_T1) / (ADC_TS_D2 - ADC_TS_D1) + ADC_TS_T1; 
		
		// Вывести результат измерения температуры на ЖКИ в градусах Цельсия
    sprintf(message , "\xD2\xE5\xEC\xEF\xE5\xF0.:%6.1f\xB0\x43", T);   
		U_MLT_Put_String (message, 3);
		
		// Вывести результат аналого-цифрового преобразования
    sprintf(message , "ADC: 0x%1x", D);   
		U_MLT_Put_String (message, 4);
		
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (250);  		
	}
}




