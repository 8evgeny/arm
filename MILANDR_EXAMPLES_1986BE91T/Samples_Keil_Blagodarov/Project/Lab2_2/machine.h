// ***********************************************************************************
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: machine.h 
// Назначение: Конечный автомат 
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#ifndef __U_MACHINE
 #define __U_MACHINE

#include "common.h"
#include <stdint.h>

// Структура конечного автомата 
typedef volatile struct
{       
  // Текущее состояние
	// Состояние 0 считается неопределенным. Его использовать нельзя.
  int8_t State;	 
  // Предыдущее состояние
  int8_t Previous;
  // Следующее состояние
  int8_t Next;
  // Таймер-счетчик
	uint32_t Counter;
	
} TMachine;
  
     
// Инициализация конечного автомата. 
void U_Machine_Init(TMachine *machine,      // Конечный автомат
	                  int8_t start_State      // Начальное состояние
                   );

// Смена состояния конечного автомата
void U_Machine_Change_State(TMachine *machine,	// Конечный автомат
	                          int8_t newState     // Новое состояние
   	                       );

// Остаться в том же состоянии 
void U_Machine_Stay_Here(TMachine *machine);

// Проверить, пришли из другого состояния? 
int8_t U_Machine_Come_From_Another(TMachine *machine);

// Установить таймер 
void U_Machine_Set_Timer(TMachine *machine,			// Конечный автомат
												 uint32_t Period, 			// Период ожидания, проверок таймера
												 int8_t   State				  // Состояние, в которое перейдет автомат по срабатыванию таймера 
											  );

// Сбросить таймер 
void U_Machine_Reset_Timer(TMachine *machine);

// Проверить таймер 
void U_Machine_Test_Timer(TMachine *machine);

#endif

