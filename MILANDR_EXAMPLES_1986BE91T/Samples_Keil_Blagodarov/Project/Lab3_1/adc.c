// ***********************************************************************************
// Проект:      Lab3_1 
// Программа:   Работа с АЦП. Измерение напряжения на потенциометре.
//              Режим одиночного преобразования по одному каналу 
//              с опросом бита окончания преобразования.
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

	// Структруа для инициализации портов
	PORT_InitTypeDef PortInitStructure;	
	
  // Разрешить тактирование АЦП и порта PORTD
  RST_CLK_PCLKcmd (RST_CLK_PCLK_ADC | RST_CLK_PCLK_PORTD, ENABLE);  

  // Сделать аналоговым входом линию, к которой подключен потенциометр
  PORT_StructInit (&PortInitStructure);	
  PortInitStructure.PORT_Pin   = U_ADC_U_PIN;
  PortInitStructure.PORT_MODE =  PORT_MODE_ANALOG;
  PORT_Init (MDR_PORTD, &PortInitStructure);	
	
  ADC_DeInit();
  ADC_StructInit(&ADC_InitStructure);

  // Конфигурация АЦП общая (для обоих АЦП сразу)
  ADC_InitStructure.ADC_SynchronousMode      = ADC_SyncMode_Independent;						// Режим запуска (независимый)
  ADC_InitStructure.ADC_StartDelay           = 0;																		// Задержка между запусками АЦП1 и АЦП2 для режима синхронного запуска (отсутствует)
  ADC_InitStructure.ADC_TempSensor           = ADC_TEMP_SENSOR_Disable;             // Работа температурного датчика (запретить)
  ADC_InitStructure.ADC_TempSensorAmplifier  = ADC_TEMP_SENSOR_AMPLIFIER_Disable;   // Работа усилителя для температурного датчика (запретить)
  ADC_InitStructure.ADC_TempSensorConversion = ADC_TEMP_SENSOR_CONVERSION_Disable;  // Преобразования для канала температурного датчика (запретить) 
  ADC_InitStructure.ADC_IntVRefConversion    = ADC_VREF_CONVERSION_Disable;         // Преобразования для канала VREF - внутреннего источника опорного напряжения (запретить)
  ADC_InitStructure.ADC_IntVRefTrimming      = 0;                                   // Подстройка опорного напряжения (не выполняется)
  ADC_Init (&ADC_InitStructure);

  // Конфигурация АЦП1
  ADCx_StructInit (&ADCx_InitStructure);															
  ADCx_InitStructure.ADC_ClockSource      = ADC_CLOCK_SOURCE_CPU;						// Источник тактирования АЦП (тактовая частота с ЦПУ)
  ADCx_InitStructure.ADC_Prescaler        = ADC_CLK_div_512;								// Предделитель частоты тактирования АЦП (512)
  ADCx_InitStructure.ADC_SamplingMode     = ADC_SAMPLING_MODE_SINGLE_CONV;	// Режим преобразования (одиночный)
  ADCx_InitStructure.ADC_ChannelSwitching = ADC_CH_SWITCHING_Disable;				// Режим автоматического переключения каналов (запретить)
  ADCx_InitStructure.ADC_ChannelNumber    = U_ADC_U_CH;											// Выбранный канал АЦП 
  ADCx_InitStructure.ADC_Channels         = 0;															// Выбранные каналы АЦП для режима автоматического переключения каналов с последовательным опросом (не указаны, так как этот режим запрещен)
  ADCx_InitStructure.ADC_DelayGo          = 7;															// Дополнительная задержка перед запуском АЦП после выбора канала (максимальная)   	
  ADCx_InitStructure.ADC_LevelControl     = ADC_LEVEL_CONTROL_Disable;			// Контроль уровня входного напряжения (отключено).
  ADCx_InitStructure.ADC_LowLevel         = 0;															// Нижний уровень входного напряжения (не задан)
  ADCx_InitStructure.ADC_HighLevel        = 0;															// Верхний уровень	входного напряжения (не задан) 
  ADCx_InitStructure.ADC_VRefSource       = ADC_VREF_SOURCE_INTERNAL;				// Вид источника опорного напряжения (внутренний)
  ADCx_InitStructure.ADC_IntVRefSource    = ADC_INT_VREF_SOURCE_INEXACT;	  // Вид внутреннего источника опроного напряжения (неточный, без температурной компенсации)
  ADC1_Init (&ADCx_InitStructure);

  // Разрешить работу АЦП1
  ADC1_Cmd (ENABLE);
}

// Строка формируемого сообщения
static char message[64];

// Переменная для хранения идентификатора задачи
OS_TID U_ADC_Task_ID;

// Задача по измерению напряжения на входе АЦП 
__task void U_ADC_Task_Function (void)
{
	uint32_t DU;       // Результат аналого-цифрового преобразования для напряжения 
  float U;       		 // Измеренное напряжение

	while(1)
	{
		// Запустить процесс аналого-цифрового преобразования
    ADC1_Start();
		
		// Дождаться завершения преобразования, 
		// постоянно опрашивая соответствующий флаг в регистре состояния АЦП1
		while ((ADC1_GetStatus() & ADC_STATUS_FLG_REG_EOCIF) == 0);
		
		// Пауза, в течение которой преобразование гарантированно успеет завершиться
		// Можно поставить ее вместо предыдущего оператора по опросу флага в регистре состояния АЦП1
    //os_dly_wait (1);  		
		
		// Получить результат преобразования
		DU = ADC1_GetResult() & 0x0000FFFF;
		
    // Преобразование показаний АЦП в измеренное напряжение
    U = (U_ADC_U / U_ADC_D) * DU;
		
		// Вывести результат измерения напряжения на ЖКИ в вольтах
    sprintf(message , "U = %5.3fV", U);   
		U_MLT_Put_String (message, 3);
		
		// Вывести результат аналого-цифрового преобразования
    sprintf(message , "ADC: 0x%1x", DU);   
		U_MLT_Put_String (message, 4);		
		
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (250);  		
	}
}




