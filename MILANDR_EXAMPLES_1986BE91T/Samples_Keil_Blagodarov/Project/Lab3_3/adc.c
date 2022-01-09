// ***********************************************************************************
// Проект:      Lab3_3 
// Программа:   Работа с АЦП. Измерение температуры кристалла МК.
//              Режим одиночного преобразования по одному каналу 
//              с прерыванием по окончанию преобразования
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: adc.с 
// Назначение: Управление АЦП      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "adc.h"
#include "variant.h"

// Инициализировать АЦП
void U_ADC_Init (void)
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

	// Разрешить прерывания по окончанию аналого-цифрового преобразования
  ADC1_ITConfig (ADC1_IT_END_OF_CONVERSION, ENABLE);

  // Разрешить работу АЦП1
  ADC1_Cmd (ENABLE);

  // Задать приоритет аппаратного прерывания от АЦП
  NVIC_SetPriority (ADC_IRQn, 1); 
	// Разрешить прерывания от АЦП
  NVIC_EnableIRQ (ADC_IRQn); 	
}

// Строка формируемого сообщения
static char message[64];

// Переменная для хранения идентификатора задачи
OS_TID U_ADC_Task_ID;

// Задача по измерению напряжения на входе АЦП 
__task void U_ADC_Task_Function (void)
{
	uint32_t DU;       // Результат аналого-цифрового преобразования для напряжения 
  float T;       // Измеренная температура 

	while(1)
	{
		// Запустить процесс аналого-цифрового преобразования
    ADC1_Start();
		
		// Дождаться окончания преобразования.
		// Ждем события об окончании преобразования от обработчика прерываний от АЦП1
    os_evt_wait_or (EVENT_ADC_EOC, 0xFFFF); 

		// Получить результат преобразования
		DU = ADC1_GetResult () & 0x0000FFFF;
		
    // Преобразование показаний АЦП в температуру в градусах Цельсия
    T = ((int32_t)DU - (int32_t) ADC_TS_D1) * (ADC_TS_T2 - ADC_TS_T1) / (ADC_TS_D2 - ADC_TS_D1) + ADC_TS_T1; 
		
		// Вывести результат измерения температуры на ЖКИ в градусах Цельсия
    sprintf(message , "\xD2\xE5\xEC\xEF\xE5\xF0.:%6.1f\xB0\x43", T);   
		U_MLT_Put_String (message, 3);
		
		// Вывести результат аналого-цифрового преобразования
    sprintf(message , "ADC: 0x%1x", DU);   
		U_MLT_Put_String (message, 4);	
		
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (250);  		
	}
}




