/* Simple LED task demo, using timed delays:
 *
 * The LED on PC13 is toggled in task1.
 */
#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

extern void vApplicationStackOverflowHook(
	xTaskHandle *pxTask,
	signed portCHAR *pcTaskName);

void
vApplicationStackOverflowHook(
  xTaskHandle *pxTask __attribute((unused)),
  signed portCHAR *pcTaskName __attribute((unused))
) {
	for(;;);	// Loop forever here..
}

void task0(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOC,GPIO13);  vTaskDelay(pdMS_TO_TICKS(50)); } }

void task1(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOB,GPIO5);  vTaskDelay(pdMS_TO_TICKS(100)); } }
void task2(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOB,GPIO6);  vTaskDelay(pdMS_TO_TICKS(300)); } }
void task3(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOB,GPIO7);  vTaskDelay(pdMS_TO_TICKS(500)); } }
void task4(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOB,GPIO8);  vTaskDelay(pdMS_TO_TICKS(1000)); } }
void task5(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOB,GPIO9);  vTaskDelay(pdMS_TO_TICKS(1500)); } }

void task6(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOA,GPIO0);  vTaskDelay(pdMS_TO_TICKS(100)); } }
void task7(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOA,GPIO1);  vTaskDelay(pdMS_TO_TICKS(300)); } }
void task8(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOA,GPIO2);  vTaskDelay(pdMS_TO_TICKS(500)); } }
void task9(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOA,GPIO3);  vTaskDelay(pdMS_TO_TICKS(1000)); } }
void task10(void *args __attribute((unused))) {for (;;) { gpio_toggle(GPIOA,GPIO4);  vTaskDelay(pdMS_TO_TICKS(1500)); } }

int
main(void) {
rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
//	rcc_clock_setup_in_hse_8mhz_out_72mhz(); // For "blue pill"

    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO13); //Встроенный LED

    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO5);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO6);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO7);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO8);
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO9);

    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO0);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO1);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO2);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO3);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,GPIO4);

    xTaskCreate(task0,"LED0",100,NULL,configMAX_PRIORITIES-1,NULL);

    xTaskCreate(task1,"LED1",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(task2,"LED2",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(task3,"LED3",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(task4,"LED4",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(task5,"LED5",100,NULL,configMAX_PRIORITIES-1,NULL);

    xTaskCreate(task6,"LED1",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(task7,"LED2",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(task8,"LED3",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(task9,"LED4",100,NULL,configMAX_PRIORITIES-1,NULL);
    xTaskCreate(task10,"LED5",100,NULL,configMAX_PRIORITIES-1,NULL);

	vTaskStartScheduler();

	for (;;);
	return 0;
}

// End
