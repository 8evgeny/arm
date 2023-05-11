/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void
gpio_setup(void) {

    /* Enable GPIOA GPIOB GPIOC clock. */
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOD);  //для платы F103RCT6

    /* Set GPIO to 'output push-pull'. */
    gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
    gpio_set_mode(GPIOD,GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO2); //для платы F103RCT6
    gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO6); //для платы F103RCT6
    gpio_set_mode(GPIOA,GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO8);
    gpio_set_mode(GPIOB,GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO1);
    gpio_set_mode(GPIOB,GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO10);
    gpio_set_mode(GPIOB,GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO12);
    gpio_set_mode(GPIOB,GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO14);


}

void delay()
{
    for (int i = 0; i < 200000; i++)
        __asm__("nop");
}


int
main(void) {

    gpio_setup();

    while(1)
    {
        gpio_set(GPIOC,GPIO13);
//        gpio_set(GPIOD,GPIO2); //для платы F103RCT6
        delay();
        gpio_clear(GPIOC,GPIO13);
//        gpio_clear(GPIOD,GPIO2);
        delay();

//        gpio_set(GPIOB,GPIO1);
//        delay();
//        gpio_clear(GPIOB,GPIO1);
//        delay();

//        gpio_set(GPIOB,GPIO10);
//        delay();
//        gpio_clear(GPIOB,GPIO10);
//        delay();

//        gpio_set(GPIOB,GPIO12);
//        delay();
//        gpio_clear(GPIOB,GPIO12);
//        delay();

//        gpio_set(GPIOB,GPIO14);
//        delay();
//        gpio_clear(GPIOB,GPIO14);
//        delay();

//        gpio_set(GPIOA,GPIO8);
//        gpio_set(GPIOC,GPIO6); //для платы F103RCT6
//        delay();
//        gpio_clear(GPIOA,GPIO8);
//        gpio_clear(GPIOC,GPIO6);
        delay();
	}

	return 0;
}
