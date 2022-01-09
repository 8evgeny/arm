// ***********************************************************************************
// Проект:      Lab2_2 
// Программа:   Работа с кнопкой 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: menu.h 
// Назначение: Формирование меню      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#ifndef __U_MENU
 #define __U_MENU

#include "common.h"
#include "button.h"
#include "mlt_lcd.h"
#include "machine.h"


// Количество пунктов меню
#define U_MENU_ITEM_COUNT 4

// Конечный автомат для реализации меню
extern TMachine U_MENU_StateMachine;

// Возможные состяния автомата
enum
{
  U_MENU_SM_BUTTON_TEST_PRESS = 1, // Состояние "Ожидание нажатия кнопки"
  U_MENU_SM_BUTTON_PRESS_PAUSE,    // Состояние "Пауза для защиты от дребезга контактов и случайных нажатий"
  U_MENU_SM_BUTTON_PRESS_CONFIRM,  // Состояние "Подтверждение нажатия кнопки"
  U_MENU_SM_BUTTON_TEST_UNPRESS    // Состояние "Ожидание отпускания кнопки"
};

// Инициализировать меню
void U_MENU_Init (void);

// Задача по работе с меню
__task void U_MENU_Task_Function (void);
// Задача по выводу бегущей строки на ЖКИ
__task void U_MENU_Running_String_Task_Function (void);


#endif 


