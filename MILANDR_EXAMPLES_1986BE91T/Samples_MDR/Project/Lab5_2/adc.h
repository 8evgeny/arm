// ***********************************************************************************
// Проект:      Lab5_2 
// Программа:   Работа с ШИМ. Регулирование ширины импульса с помощью потенциометра и АЦП. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: adc.h 
// Назначение: Управление АЦП      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************
#ifndef __U_ADC
 #define __U_ADC

#include "common.h"
#include "stdio.h"
#include "mlt_lcd.h"


// Использовать потенциометр, имеющийся на отладочной плате и подключеный к каналу ADC7
//#define U_ADC_USE_ONBOARD_POTENTIOMETER

// Если используем потенциометр, имеющийся на отладочной плате
#ifdef U_ADC_USE_ONBOARD_POTENTIOMETER

 // Канал для измерения напряжения
 #define U_ADC_U_CH_MSK  ADC_CH_ADC7_MSK
 #define U_ADC_U_CH      ADC_CH_ADC7
 #define U_ADC_U_PIN     PORT_Pin_7

// Если используем внешний потенциометр
#else

 // Канал для измерения напряжения
 #define U_ADC_U_CH_MSK  ADC_CH_ADC6_MSK
 #define U_ADC_U_CH      ADC_CH_ADC6
 #define U_ADC_U_PIN     PORT_Pin_6

#endif


// Буфер для хранения результатов работы АЦП и его размер
#define U_ADC_BUFFER_SIZE 256
extern uint16_t ADC_Buffer [U_ADC_BUFFER_SIZE];


// Структура для инициализации DMA
extern DMA_CtrlDataInitTypeDef DMA_InitStructure;
// Структура для инициализации канала DMA
extern DMA_ChannelInitTypeDef DMA_Channel_InitStructure;

// Событие (Event) о завершении серии аналого-цифровых преобразований
#define EVENT_ADC_EOC 0x0001

// Инициализировать АЦП
void U_ADC_Init (void);

// Задача по измерению напряжения, снимаемого с потенциометра
__task void U_ADC_Task_Function (void);

// Переменная для хранения идентификатора задачи
extern OS_TID U_ADC_Task_ID;


#endif 

