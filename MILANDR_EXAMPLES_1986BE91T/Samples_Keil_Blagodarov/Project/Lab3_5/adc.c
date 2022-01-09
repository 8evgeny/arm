// ***********************************************************************************
// Проект:      Lab3_5 
// Программа:   Работа с АЦП. Измерение напряжения на потенциометре 
//              и температуры кристалла МК.
//              Режим режим многократного преобразования c автоматическим переключением 
//              нескольких каналов и использованием прямого доступа к памяти
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: adc.с 
// Назначение: Управление АЦП      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "adc.h"
#include "variant.h"

// Структура для инициализации DMA
DMA_CtrlDataInitTypeDef DMA_InitStructure;
// Структура для инициализации канала DMA
DMA_ChannelInitTypeDef DMA_Channel_InitStructure;

// Буфер для хранения результатов АЦП
static TVariant32 ADC_Buffer [U_ADC_BUFFER_SIZE];


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
  DMA_InitStructure.DMA_DestBaseAddr = (uint32_t) &ADC_Buffer;			          // Базовый адрес в памяти, куда будем писать результаты работы АЦП
  DMA_InitStructure.DMA_CycleSize = U_ADC_BUFFER_SIZE;							          // Размер буфера 
  DMA_InitStructure.DMA_SourceIncSize = DMA_SourceIncNo;				              // Запретить автоувеличение адреса для периферии
  DMA_InitStructure.DMA_DestIncSize = DMA_DestIncWord;				                // Разрешить автоувеличение адреса для памяти (на 4 байта)
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;             // По скольку байт передавать за один раз (4 байта) 
  DMA_InitStructure.DMA_NumContinuous = DMA_Transfers_1;				              // Сколько раз повоторяем совокупность циклов - 1 раз
  DMA_InitStructure.DMA_SourceProtCtrl = DMA_SourcePrivileged;			          // Режим защиты источника
  DMA_InitStructure.DMA_DestProtCtrl = DMA_DestPrivileged;			              // Режим защиты приемника
  DMA_InitStructure.DMA_Mode = DMA_Mode_Basic;							                  // Режим работы DMA - базовый
  
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


	// Структруа для инициализации портов
	PORT_InitTypeDef PortInitStructure;	
	
  // Разрешить тактирование АЦП 
  RST_CLK_PCLKcmd (RST_CLK_PCLK_ADC, ENABLE);  

  // Сделать аналоговым входом линию, к которой подключен потенциометр
  PORT_StructInit (&PortInitStructure);	
  PortInitStructure.PORT_Pin   = U_ADC_U_PIN;
  PortInitStructure.PORT_MODE =  PORT_MODE_ANALOG;
  PORT_Init (MDR_PORTD, &PortInitStructure);	
	
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
  ADCx_InitStructure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Enable;				// Режим переключения каналов (разрешить)
  ADCx_InitStructure.ADC_ChannelNumber    = 0;															// Выбранный канал АЦП (никакой, так как используется режим с переключением нескольких каналов)
  ADCx_InitStructure.ADC_Channels         = U_ADC_U_CH_MSK	|								// Выбранные каналы АЦП с последовательным опросом 
																						ADC_CH_TEMP_SENSOR_MSK;
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

// Строка формируемого сообщения
static char message[64];

// Переменная для хранения идентификатора задачи
OS_TID U_ADC_Task_ID;

// Задача по измерению напряжения на входе АЦП и температуры микроконтроллера
__task void U_ADC_Task_U_T_DMA_Function (void)
{
	uint32_t DU, DT;   // Результаты аналого-цифрового преобразования для напряжения и температуры
	uint32_t KU, KT;   // Количество результатов аналого-цифрового преобразования для напряжения и температуры
  float T;           // Измеренная температура 
  float U;       		 // Измеренное напряжение
	uint32_t i;

	while(1)
	{
		// Разрешить работу АЦП1. Тем самым запускается цикл аналого-цифровых преобразований 
    ADC1_Cmd (ENABLE);
		
		// Дождаться окончания преобразования
    os_evt_wait_or(EVENT_ADC_EOC, 0xFFFF); 

		// Усреднить результаты преобразования
		for (i = 0, DU = 0, DT = 0, KU = 0, KT = 0; 
		     i < U_ADC_BUFFER_SIZE; 
		     i++)
		{
			// По какому каналу АЦП было выполнено преобразование?
			switch(ADC_Buffer[i].Word[1])
			{
				// Канал измерения напряжения
        case U_ADC_U_CH:
					
			    DU += ADC_Buffer[i].Word[0];
				  KU++;
				
				  break;

				// Канал измерения температуры
        case ADC_CH_TEMP_SENSOR:
					
			    DT += ADC_Buffer[i].Word[0];
				  KT++;
				  
				  break;          					
      }
		}
		// Если были преобразования для канала напряжения
		if(KU)
		  DU /= KU;
		// Если были преобразования для канала температуры
		if(KT)
		  DT /= KT;
		
    // Преобразование показаний АЦП в температуру в градусах Цельсия
    T = ((int32_t)DT - (int32_t) ADC_TS_D1) * (ADC_TS_T2 - ADC_TS_T1) / (ADC_TS_D2 - ADC_TS_D1) + ADC_TS_T1; 

    // Преобразование показаний АЦП в измеренное напряжение
    U = (U_ADC_U / U_ADC_D) * DU;
		
		// Вывести результат измерения напряжения на ЖКИ В
    sprintf(message , "U = %5.3fV", U);   
		U_MLT_Put_String (message, 3);
		
		// Вывести результат аналого-цифрового преобразования
    sprintf(message , "ADC: 0x%1x", DU);   
		U_MLT_Put_String (message, 4);		
		
		// Вывести результат измерения температуры на ЖКИ в градусах Цельсия
    sprintf(message , "\xD2\xE5\xEC\xEF\xE5\xF0.:%6.1f\xB0\x43", T);   
		U_MLT_Put_String (message, 5);
		
		// Вывести результат аналого-цифрового преобразования
    sprintf(message , "ADC: 0x%1x", DT);   
		U_MLT_Put_String (message, 6);
		
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (250);  		
	}
}




