// ***********************************************************************************
// Проект:      Lab6_2 
// Программа:   Использование аппаратных таймеров-счетчиков для измерения частоты импульсов.
//              Измерение частоты по периоду. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл:  generator.h 
// Модуль:  Функциональный генератор аналогового сигнала
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#ifndef __U_FM
 #define __U_FM

#include "common.h"
#include "mlt_lcd.h"

// Размер массива результатов измерения периода импульсов
#define U_FM_BUFFER_SIZE 32

// Частота заполнения, Гц 
#define U_FM_FZ 1250000

// Частота минимальная, Гц 
#define U_FM_FMIN 36

// Частота максимальная, Гц 
#define U_FM_FMAX 12000

// Расчет периода импульсов по заданной частоте
#define FM_PULSE_PERIOD(F) ((uint16_t)((uint32_t)(U_FM_FZ) / (uint32_t)(F)) - 1)

// Конфигурация измерителя частоты
#define FM_PORT	  MDR_PORTC					// Порт, в котором задействуем пин 
#define FM_Pin		PORT_Pin_2        // Пин для измерителя частоты. Выведен на разъем X26.26 
#define FM_TIMER	MDR_TIMER3 				// Таймер, на котором реализуем измеритель частоты
#define FM_CHN	  TIMER_CHANNEL1    // Канал таймера, на котором реализуем измеритель частоты

// Событие (Event) о завершении измерения частоты
#define EVENT_FM_READY 0x0001

// Структура для инициализации DMA
extern DMA_CtrlDataInitTypeDef DMA_InitStructure;
// Структура для инициализации канала DMA
extern DMA_ChannelInitTypeDef DMA_Channel_InitStructure;

// Инициализация измерителя частоты
void U_FM_Init(void);

// Переменная для хранения идентификатора задачи
extern OS_TID U_FM_Task_ID;

// Задача по измерению частоты импульсов
__task void U_FM_Task_Function (void);

#endif 

