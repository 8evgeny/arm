// ***********************************************************************************
// Проект:      Lab5_2 
// Программа:   Работа с ШИМ. Регулирование ширины импульса с помощью потенциометра и АЦП. 
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Модуль: regulator.c 
// Назначение: Регулятор ширины импульсов     
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "regulator.h"


// Буфер для сообщений, выводимых на ЖКИ
static char message[128];

// Переменная для хранения идентификатора задачи
OS_TID U_Regulator_Task_ID;

// Задача по реализации регулятора
__task void U_Regulator_Task_Function (void)
{
	uint32_t D;        // Результат аналого-цифрового преобразования
	uint32_t i;        // Индексаня переменная
	float Pulse_Width; // Ширина импульса
	uint32_t Pulse_Width_Percent; // Коэф. заполнения импульса ШИМ

	// Начальная ширина импульсов
	Pulse_Width = 0;

	while(1)
	{
    // Разрешить работу DMA с АЦП. Тем самым запускается цикл аналого-цифровых преобразований 
    DMA_Cmd (DMA_Channel_ADC1, ENABLE);
		
		// Дождаться окончания преобразования
    os_evt_wait_or(EVENT_ADC_EOC, 0xFFFF); 
		
		// Усреднить результат
		for (i = 0, D = 0; i < U_ADC_BUFFER_SIZE; i++)
		  D += ADC_Buffer[i];
		D /= U_ADC_BUFFER_SIZE;
	
    // Преобразование показаний АЦП в ширину импульса
    Pulse_Width = D * PWM_PULSE_PERIOD(PWM_PULSE_F) / 4095;

		// Коэффициент заполнения импульсов в %
		Pulse_Width_Percent = D * 100 / 4095;
		
		// Вывести ширину импульса в % на ЖКИ
    sprintf(message , "Width %3d%", Pulse_Width_Percent);   
		U_MLT_Put_String (message, 3);
		
		
    // Проверить, не вылазим ли за пределы допустимой ширины импульсов? 
    if(Pulse_Width < 0) 
			 Pulse_Width = 0;
    if(Pulse_Width > PWM_PULSE_PERIOD(PWM_PULSE_F)) 
			 Pulse_Width = PWM_PULSE_PERIOD(PWM_PULSE_F);
   
		// Задать ширину импульсов, питающих лампочку
    //U_PWM_Set_Pulse_Width (floor(Pulse_Width));
		U_PWM_Set_Pulse_Width_Percent (Pulse_Width_Percent);
	  
		// Пауза, задающая период работы регулятора.
    os_dly_wait (100);  
	}
}






