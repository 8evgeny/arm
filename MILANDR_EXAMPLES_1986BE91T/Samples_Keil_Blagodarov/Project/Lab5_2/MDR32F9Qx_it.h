// ***********************************************************************************
// Микроконтроллер: 1986ВЕ92У
// Устройство: Отладочная плата К1986ВЕ92QI
// Файл: MDR32F9Qx_it.c 
// Назначение: Обработчики аппаратных прерываний
// Компилятор:  Armcc 5.03.0.76 из комплекта Keil uVision 4.72.1.0 
// ***********************************************************************************
#ifndef __1986BE9X_IT_H
  #define __1986BE9X_IT_H

#include "common.h"
#include "regulator.h"
#include "adc.h"

void NMI_Handler (void);
void HardFault_Handler (void);
void MemManage_Handler (void);
void BusFault_Handler (void);
void UsageFault_Handler (void);
void DebugMon_Handler (void);
void CAN1_IRQHandler (void);
void CAN2_IRQHandler (void);
void USB_IRQHandler (void);
void DMA_IRQHandler (void);
void UART1_IRQHandler (void);
void UART2_IRQHandler (void);
void SSP1_IRQHandler (void);
void SSP2_IRQHandler (void);
void I2C_IRQHandler (void);
void POWER_IRQHandler (void);
void WWDG_IRQHandler (void);
void Timer1_IRQHandler (void);
void Timer2_IRQHandler (void);
void Timer3_IRQHandler (void);
void ADC_IRQHandler (void);
void COMPARATOR_IRQHandler (void);
void BACKUP_IRQHandler (void);
void EXT_INT1_IRQHandler (void);
void EXT_INT2_IRQHandler (void);
void EXT_INT3_IRQHandler (void);
void EXT_INT4_IRQHandler (void);

#endif
 
