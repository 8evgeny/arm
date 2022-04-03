#include "i2c_1637.h"

/*
 * T: Timing time
   * Ticks: How many clock cycles have an interrupt
   * f: Clock frequency 72000000
 * t = Ticks * 1/f = (72000000/1000000) * (1/72000000) = 1us
 */

void SysTick_Delay_Us( volatile uint32_t us )
{
    uint32_t i;
    SysTick_Config( SystemCoreClock / 1000000 );
 
    for( i = 0; i < us; i++ )
    {
                 // When the value of the counter is reduced to 0, the bit 16 of the CRTL register is set.
        while( !( ( SysTick->CTRL ) & ( 1 << 16 ) ) );
    }
         // Turn off the SYSTICK Timer
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
 
void SysTick_Delay_Ms( volatile uint32_t ms )
{
    uint32_t i;
    SysTick_Config( SystemCoreClock / 1000 );
 
    for( i = 0; i < ms; i++ )
    {
                 // When the value of the counter is reduced to 0, the bit 16 of the CRTL register is set.
                 // When you place 1, read this bit will be clear 0
        while( !( ( SysTick->CTRL ) & ( 1 << 16 ) ) );
    }
         // Turn off the SYSTICK Timer
    SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}
