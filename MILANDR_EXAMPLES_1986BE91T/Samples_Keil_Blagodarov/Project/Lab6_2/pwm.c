// ***********************************************************************************
// Проект:      Lab6_2 
// Программа:   Использование аппаратных таймеров-счетчиков для измерения частоты импульсов.
//              Измерение частоты по периоду. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Модуль: pwm.c 
// Назначение:  Работа с ШИМ      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "pwm.h"

// Инициализировать ШИМ
void U_PWM_Init (void)
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
 RST_CLK_PCLKcmd (RST_CLK_PCLK_PORTF | 	RST_CLK_PCLK_TIMER1,	ENABLE);
	
 // Инициализация линии для ШИМ
 // К ней подключается транзисторный ключ для управления яркостью лампы накаливания.
 PORT_StructInit(&PortInitStructure);
 PortInitStructure.PORT_FUNC  = PORT_FUNC_ALTER;
 PortInitStructure.PORT_OE    = PORT_OE_OUT;
 PortInitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
 PortInitStructure.PORT_Pin   = PWM_Pin; 
 PortInitStructure.PORT_SPEED = PORT_SPEED_MAXFAST; 
 PORT_Init (PWM_PORT, &PortInitStructure);

 // Сбросить все настройки для PWM_TIMER 
 TIMER_DeInit (PWM_TIMER);

 // Задать тактирование таймера 
 TIMER_BRGInit (PWM_TIMER, TIMER_HCLKdiv1);	   // 80МГц 
 
 // Вычислить предделитель для таймера 
 PrescalerValue = (uint16_t) (PWM_System_Core_Clock / PWM_TIMER_CLK) - 1; 
 
 // Инициализация таймера  
 TimerInitStructure.TIMER_Prescaler = PrescalerValue;  										// Предделитель	частоты импульсов, тактирующих таймер
 TimerInitStructure.TIMER_Period = PWM_PULSE_PERIOD (PWM_PULSE_F);        // Период таймера по заданной частоте импульсов 	
 TimerInitStructure.TIMER_CounterDirection = TIMER_CntDir_Up;		          // Считать вверх
 TimerInitStructure.TIMER_CounterMode = TIMER_CntMode_ClkFixedDir;        // Режим фиксированного направления счета (считаем только вверх, не меняя направления).
 TimerInitStructure.TIMER_EventSource = TIMER_EvSrc_None;			   					// Событие, по которому производится счет (событие не задано, считаем все импульсы, тактирующие таймер)
 TimerInitStructure.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;
 TimerInitStructure.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;
 TimerInitStructure.TIMER_ETR_FilterConf = TIMER_Filter_1FF_at_TIMER_CLK;
 TimerInitStructure.TIMER_ETR_Prescaler = TIMER_ETR_Prescaler_None;
 TimerInitStructure.TIMER_ETR_Polarity = TIMER_ETRPolarity_NonInverted;
 TimerInitStructure.TIMER_BRK_Polarity = TIMER_BRKPolarity_NonInverted;
 TIMER_CntInit (PWM_TIMER,&TimerInitStructure);

 // Инициализация канала таймера
 TIMER_ChnStructInit (&TimerChnInitStructure);
 TimerChnInitStructure.TIMER_CH_Number = PWM_CHN; 												// Номер канала
 TimerChnInitStructure.TIMER_CH_Mode = TIMER_CH_MODE_PWM;									// Режим канала - ШИМ
 TimerChnInitStructure.TIMER_CH_REF_Format = TIMER_CH_REF_Format6;        // Формат формирования внутреннего сигнала REF
 TIMER_ChnInit (PWM_TIMER, &TimerChnInitStructure);

 // Инициализация выхода канала таймера
 TIMER_ChnOutStructInit (&TimerChnOutInitStructure);
 TimerChnOutInitStructure.TIMER_CH_Number = PWM_CHN;																	// Номер канала
 TimerChnOutInitStructure.TIMER_CH_DirOut_Polarity = TIMER_CHOPolarity_NonInverted;   // Прямой выход канала неинвертирован
 TimerChnOutInitStructure.TIMER_CH_DirOut_Source = TIMER_CH_OutSrc_REF;								// Прямой выход канала управляется сигналом REF
 TimerChnOutInitStructure.TIMER_CH_DirOut_Mode = TIMER_CH_OutMode_Output;							// Прямой выход канала является выходом :-)
 TimerChnOutInitStructure.TIMER_CH_NegOut_Polarity = TIMER_CHOPolarity_NonInverted;   // Инверсный выход канала неинвертирован
 TimerChnOutInitStructure.TIMER_CH_NegOut_Source = TIMER_CH_OutSrc_REF;               // Инверсный выход канала управляется сигналом REF 
 TimerChnOutInitStructure.TIMER_CH_NegOut_Mode = TIMER_CH_OutMode_Output;							// Инверсный выход канала является выходом 
 TIMER_ChnOutInit (PWM_TIMER, &TimerChnOutInitStructure);

 // Рарешить работу таймера
 TIMER_Cmd (PWM_TIMER, ENABLE);
	
 // Задать ширину импульсов
 U_PWM_Set_Pulse_Width_Percent (PWM_PULSE_WIDTH_PERCENT);
	
}

// Задать коэффициент заполнения импульсов в % 
void U_PWM_Set_Pulse_Width_Percent (uint16_t width_percent)
{
	uint16_t width;
	
	// Вычисляем ширину импульса, взяв нужное количество % от периода импульсов 
	width = PWM_PULSE_PERIOD (PWM_PULSE_F) * width_percent / 100;
	
  TIMER_SetChnCompare (PWM_TIMER, PWM_CHN, width);
}


// Задача по выводу бегущей строки на ЖКИ
__task void U_PWM_Task_Function (void)
{
	uint32_t k = 0;
	
	// Строка, выводимая на индикатор 
	const char s[] =  "FM";          
	
	while(1)
	{
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (1000);  
		
		// Вывести строку c прокруткой
		U_MLT_Scroll_String (s, 5, k++);
		
	}
}






