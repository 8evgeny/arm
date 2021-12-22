#include "stm32f10x_conf.h"


void delay_ms(uint32_t ms) {
    volatile uint32_t nCount;
    RCC_ClocksTypeDef _rcc;
    RCC_GetClocksFreq (&_rcc);
    nCount = (_rcc.HCLK_Frequency / 10000) * ms;
    for (; nCount != 0; nCount--);
}


int main(void) {

    GPIO_InitTypeDef gs;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
    gs.GPIO_Speed = GPIO_Speed_50MHz; 
    gs.GPIO_Mode  = GPIO_Mode_Out_PP; 
    gs.GPIO_Pin   = GPIO_Pin_1;
    GPIO_Init(GPIOA, &gs);

    while(1) {
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET); 
        delay_ms(500);
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET); 
        delay_ms(500);
    }
}

