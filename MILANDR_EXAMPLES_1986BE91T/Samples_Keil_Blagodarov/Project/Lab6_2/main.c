// ***********************************************************************************
// Проект:      Lab6_2 
// Программа:   Использование аппаратных таймеров-счетчиков для измерения частоты импульсов.
//              Измерение частоты по периоду. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: main.с 
// Назначение: Главный модуль  
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

/*************************************************************************************
	 Измеряется частота импульсов, поступающих на вход МК, 
	 используя аппаратный таймер-счетчик и метод измерения по периоду импульсов. 
	 На ЖКИ выводится измеренная частота, выраженная в Гц. 
	 Импульсы генерируются самим же МК на выходе PF6 с помощью канала 1 таймера TIMER1, 
	 работающего в режиме ШИМ, и по соединительному проводу поступают на вход PC2, 
	 который подключен к каналу 1 таймера TIMER3. 
	 На базе таймера TIMER3 организовано измерение частоты импульсов. 
	 Получается, что МК сам генерирует импульсы и сам же их принимает. 
	 Частота импульсов, генерируемых с помощью ШИМ, 
	 задается в виде константы PWM_PULSE_F в заголовке pwm.h.
	 
	 Подключите соединительный провод к отладочной плате. Один конец провода подключите 
	 к линии PF6 (штырек 25 разъема  X27), а второй конец – к линии PC2 
	 (штырек 26  разъема  X26). 
   На обратной стороне платы установите переключатель PC2 в положение OFF. 
	 Это нужно для того, чтобы отключить кнопку UP линии PC2. 
	 	 
**************************************************************************************/  
#include "main.h"

// Точка входа
int main (void)
{
  // Инициализация системы тактирования микроконтроллера
  U_RST_Init ();	
	
	// Инициализация ЖКИ
	U_MLT_Init ();

  // Инициализация ШИМ
  U_PWM_Init();	

  // Инициализация измерителя частоты
  U_FM_Init();	
	
  // Инициализация задач RTX
  os_sys_init (Main_Task_Init);

  return 0;
}

// Инициализация задач
__task void Main_Task_Init (void)
{
  os_tsk_prio_self (100);

 	// Вывод бегущей строки на экран
  //os_tsk_create (U_PWM_Task_Function, 10);	
	
 	// Измерение частоты
  U_FM_Task_ID = os_tsk_create (U_FM_Task_Function, 20);

  os_tsk_delete_self ();
}


	
