// ***********************************************************************************
// Проект:      Lab2_2 
// Программа:   Работа с кнопкой 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: menu.с 
// Назначение: Формирование меню      
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "menu.h"

// Машина состояний для реализации меню
TMachine U_MENU_StateMachine;

// Выбранный пункт меню
uint8_t U_MENU_Item;

// Строка для представления времени
uint8_t U_MENU_Time_String[8];  

// Указатель на сообщение, выводимое в качестве пункта меню
char* U_MENU_Message;


// Подготовить строку для выбранного пункта меню
char* U_MENU_Prepare_Item(uint8_t item); 


// Инициализировать меню
void U_MENU_Init (void)
{
  // Инициализация конечного автомата 
  U_Machine_Init(&U_MENU_StateMachine, U_MENU_SM_BUTTON_TEST_PRESS);
	
	// Выбрать начальный пункт меню
	U_MENU_Item = 0;
}

// Задача по работе с меню
__task void U_MENU_Task_Function (void)
{
	while(1)
	{
		// Пауза, чтобы по-напрасну не грузить процессор
    os_dly_wait (20);  

    // Проверить таймер 
    U_Machine_Test_Timer(&U_MENU_StateMachine);
		
		// Проверка состояния конечного автомата
		switch (U_MENU_StateMachine.State)
		{
			// Состояние "Ожидание нажатия кнопки"
			case U_MENU_SM_BUTTON_TEST_PRESS:

			  // Если пришли из другого состяния
				if (U_Machine_Come_From_Another(&U_MENU_StateMachine))
				  // Остаться в том же состоянии 
				  U_Machine_Stay_Here(&U_MENU_StateMachine);
			
				// Если нажата кнопка
			  if (U_BTN_Read_Button())
					// Сменить состояние конечного автомата
          U_Machine_Change_State(&U_MENU_StateMachine, U_MENU_SM_BUTTON_PRESS_PAUSE);
				
				// Отобразить пункт меню
        // Подготовить строку для выбранного пункта меню
        U_MENU_Message = U_MENU_Prepare_Item (U_MENU_Item); 			
				
				// Вывести на ЖКИ строку пункта меню
				if (U_MENU_Message)
					U_MLT_Put_String (U_MENU_Message, 3);
			
				break;
			
			// Состояние "Пауза для защиты от дребезга контактов кнопки"
			case U_MENU_SM_BUTTON_PRESS_PAUSE:

			  // Если пришли из другого состяния
				if (U_Machine_Come_From_Another(&U_MENU_StateMachine))
				{
				  // Остаться в том же состоянии 
				  U_Machine_Stay_Here(&U_MENU_StateMachine);
					
          // Установить таймер для переход а к указанному состоянию 
					// через 5 периодов проверки конечного автомата
          U_Machine_Set_Timer(&U_MENU_StateMachine,	5, U_MENU_SM_BUTTON_PRESS_CONFIRM);
					
				}
				break;

			// Состояние "Подтверждение нажатия кнопки"
			case U_MENU_SM_BUTTON_PRESS_CONFIRM:

  			// Если пришли из другого состяния
				if (U_Machine_Come_From_Another(&U_MENU_StateMachine))
				  // Остаться в том же состоянии 
				  U_Machine_Stay_Here(&U_MENU_StateMachine);
			
				// Если нажатие кнопки подтвердилось
			  if (U_BTN_Read_Button())
				{
 				 // Перейти к следующему пункту меню, а если прошли все, то к начальному
			   if (++ U_MENU_Item == U_MENU_ITEM_COUNT)
					 U_MENU_Item = 0;
				
					// Сменить состояние конечного автомата
          U_Machine_Change_State(&U_MENU_StateMachine, U_MENU_SM_BUTTON_TEST_UNPRESS);
				}
				
				// Если нажатие кнопки НЕ подтвердилось
				else
					// Сменить состояние конечного автомата
          U_Machine_Change_State(&U_MENU_StateMachine, U_MENU_SM_BUTTON_TEST_PRESS);
			
				break;
			
			// Состояние "Ждём отпускания кнопки"
			case U_MENU_SM_BUTTON_TEST_UNPRESS:
	
  			// Если пришли из другого состяния
				if (U_Machine_Come_From_Another(&U_MENU_StateMachine))
				  // Остаться в том же состоянии 
				  U_Machine_Stay_Here(&U_MENU_StateMachine);


				// Если кнопка отпущена
			  if (!U_BTN_Read_Button())
  			  // Сменить состояние конечного автомата
          U_Machine_Change_State(&U_MENU_StateMachine, U_MENU_SM_BUTTON_TEST_PRESS);
				
				break;

			// Если попадет в "левое" состояние, то инициализировать конечный автомат заново
			default:
				U_Machine_Init (&U_MENU_StateMachine, U_MENU_SM_BUTTON_TEST_PRESS);
		}

	}
}


// Подготовить строку для выбранного пункта меню
char* U_MENU_Prepare_Item (uint8_t item) 
{
	
	switch (item)
	{
		// Пункт 0;
		case 0:
			
			return "\xCF\xF3\xED\xEA\xF2 0";  // Пункт 0
		
		// Пункт 1;
		case 1:
			
			return "\xCF\xF3\xED\xEA\xF2 1";  // Пункт 1

		// Пункт 2;
		case 2:
			
			return "\xCF\xF3\xED\xEA\xF2 2";  // Пункт 2

		// Пункт 3;
		case 3:
		
			return "\xCF\xF3\xED\xEA\xF2 3";  // Пункт 3
		
		default:
			
			return 0;
	}
}


// Задача по выводу бегущей строки на ЖКИ
__task void U_MENU_Running_String_Task_Function (void)
{
	uint32_t k = 0;
	
	// Строка, выводимая на индикатор 
	const char s[] =  "LAB2.2. \xD0\xE0\xE1\xEE\xF2\xE0 \xF1 \xEA\xED\xEE\xEF\xEA\xE0\xEC\xE8   ";  // Работа с кнопками
	
	while(1)
	{
		// Пауза в тиках системного таймера. Здесь 1тик = 1мс. 
    os_dly_wait (1000);  
		
		// Вывести строку c прокруткой
		U_MLT_Scroll_String (s, 6, k++);
		
	}
}
