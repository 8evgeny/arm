// ***********************************************************************************
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: MDR32F9Qx_it.c 
// Назначение: Обработчики аппаратных прерываний
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************

#include "MDR32F9Qx_it.h"

// Обработчик для немаскируемого прерывания (NMI)
void NMI_Handler (void)
{
}

// Обработчик для прерывания по аппаратному сбою (Hard Fault)
void HardFault_Handler (void)
{
  // Безконечный цикл
  while (1)
  {
  }
}

// Обработчик для прерывания по исключению при управлении памятью (Memory Manage Exception)
void MemManage_Handler (void)
{
  // Безконечный цикл
  while (1)
  {
  }
}

// Обработчик для прерывания по сбою шины (Bus Fault Exception)
void BusFault_Handler (void)
{
  // Безконечный цикл
  while (1)
  {
  }
}

// Обработчик для прерывания по Usage Fault exception
void UsageFault_Handler (void)
{
  // Безконечный цикл
  while (1)
  {
  }
}

// Обработчик для прерывания по исключению от монитора отладки (Debug Monitor Exception)
void DebugMon_Handler (void)
{
}

// Обработчик для прерывания от CAN1
void CAN1_IRQHandler (void)
{
}

// Обработчик для прерывания от CAN2
void CAN2_IRQHandler (void)
{
}

// Обработчик для прерывания от USB
void USB_IRQHandler (void)
{
}

// Обработчик для прерывания от DMA
void DMA_IRQHandler (void)
{
}

// Обработчик для прерывания от UART1
void UART1_IRQHandler (void)
{
}

// Обработчик для прерывания от UART2
void UART2_IRQHandler (void)
{
}

// Обработчик для прерывания от SSP1
void SSP1_IRQHandler (void)
{
}

// Обработчик для прерывания от SSP1
void SSP2_IRQHandler (void)
{
}

// Обработчик для прерывания от I2C
void I2C_IRQHandler (void)
{
}

// Обработчик для прерывания по питанию
void POWER_IRQHandler (void)
{
}

// Обработчик для прерывания от WWDG
void WWDG_IRQHandler (void)
{
}

// Обработчик для прерывания от Timer1 
void Timer1_IRQHandler (void)
{
}

// Обработчик для прерывания от Timer2 
void Timer2_IRQHandler (void)
{
}

// Обработчик для прерывания от Timer3 
void Timer3_IRQHandler (void)
{
}

// Обработчик для прерывания от АЦП 
void ADC_IRQHandler (void)
{
	volatile uint32_t result;
	
	// Если возникло прерывание по завершению преобразования
	if (ADC1_GetITStatus (ADC1_IT_END_OF_CONVERSION))
	{
		// Считать результат преобразования, чтобы сбросить флаг прерывания по завершению преобразования.
		// Если этого не сделать, то МК будет безконечно заходить в эту подпрограмму, т.е. зависнет.
		result = ADC1_GetResult();
		
	  // Установить событие об окончании цикла аналого-цифрового преобразования
    isr_evt_set (EVENT_ADC_EOC, U_ADC_Task_ID);	
	}
}

// Обработчик для прерывания от аналогового компаратора
void COMPARATOR_IRQHandler (void)
{
}

// Обработчик для прерывания от BACKUP
void BACKUP_IRQHandler (void)
{
}

// Обработчик для прерывания от EXT_INT1
void EXT_INT1_IRQHandler (void)
{
}

// Обработчик для прерывания от EXT_INT2
void EXT_INT2_IRQHandler (void)
{
}

// Обработчик для прерывания от EXT_INT3
void EXT_INT3_IRQHandler (void)
{
}

// Обработчик для прерывания от EXT_INT4
void EXT_INT4_IRQHandler (void)
{
}
