// ***********************************************************************************
// Проект:      Lab5_1 
// Программа:   Работа с ШИМ 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Модуль: pwm.h 
// Назначение:  Работа с ШИМ      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#ifndef __U_PWM
 #define __U_PWM

#include "common.h"
#include "mlt_lcd.h"

// Частота импульсов ШИМ, Гц
#define PWM_PULSE_F 10000

// Коэффициент заполнения импульсов в % 
#define PWM_PULSE_WIDTH_PERCENT 25

// Частота импульсов, подаваемых на таймер (CLK), Гц
#define PWM_TIMER_CLK 8000000

// Частота ядра процессор, Гц
#define PWM_System_Core_Clock 80000000

// Конфигурация ШИМ
#define PWM_PORT	MDR_PORTF					// Порт, в котором задействуем пин для ШИМ
#define PWM_Pin		PORT_Pin_6        // Пин для ШИМ. Выведен на разъем X27.25 
#define PWM_TIMER	MDR_TIMER1 				// Таймер, на котором реализуем ШИМ
#define PWM_CHN	  TIMER_CHANNEL1    // Канал таймера, на котором реализуем ШИМ

// Инициализировать ШИМ
void U_PWM_Init (void);

// Задать коэффициент заполнения импульсов в % 
void U_PWM_Set_Pulse_Width_Percent (uint16_t width_percent);

// Задача по выводу бегущей строки на ЖКИ
__task void U_PWM_Task_Function (void);

// Расчет периода импульсов по заданной частоте
#define PWM_PULSE_PERIOD(F) ((uint16_t)((uint32_t)(PWM_TIMER_CLK) / (uint32_t)(F)) - 1) 

#endif 
