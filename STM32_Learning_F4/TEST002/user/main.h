#ifndef MAIN_H_
#define MAIN_H_

#include "stm32f4xx.h"
#include "ports.h"

void port_ini(void);
void delay(int n);

void port_ini(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //включим тактирование порта
	GPIOD->MODER = 0x55000001; //включим ножки 12-15 на выход
	GPIOD->OTYPER = 0; //включим подт€гивающее сопротивление на весь порт
	GPIOD->OSPEEDR = 0; //установим скорость LOW на все лапки порта
}

void delay(int n)
{
	while(n>0) n--;
}

#endif /* MAIN_H_ */
