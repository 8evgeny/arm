/* Task based UART demo, using queued communication.
 *
 *	TX:	A9  ====> RX of TTL serial
 *	RX:	A10 <==== TX of TTL serial (not used)
 *	CTS:	A11 (not used)
 *	RTS:	A12 (not used)
 *	Config:	8N1
 *	Baud:	38400
 * Caution:
 *	Not all GPIO pins are 5V tolerant, so be careful to
 *	get the wiring correct.
 */
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

static QueueHandle_t uart_txq;		// TX queue for UART

/*********************************************************************
 * Configure and initialize USART1:
 *********************************************************************/
static void
uart_setup(void) {

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);

    // UART TX on PA2 (GPIO_USART4_TX)
    gpio_set_mode(GPIOA,
		GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
        GPIO_USART2_TX);

    usart_set_baudrate(USART2,115200);
    usart_set_databits(USART2,8);
    usart_set_stopbits(USART2,USART_STOPBITS_1);
    usart_set_mode(USART2,USART_MODE_TX);
    usart_set_parity(USART2,USART_PARITY_NONE);
    usart_set_flow_control(USART2,USART_FLOWCONTROL_NONE);
    usart_enable(USART2);

	// Create a queue for data to transmit from UART
	uart_txq = xQueueCreate(256,sizeof(char));
}

/*********************************************************************
 * USART Task: 
 *********************************************************************/
static void
uart_task(void *args __attribute__((unused))) {
	char ch;

    for (;;)
    {
		// Receive char to be TX
        if ( xQueueReceive(uart_txq,&ch,10) == pdPASS ) {
            while ( !usart_get_flag(USART2, USART_SR_TXE) )
				taskYIELD();	// Yield until ready
            usart_send(USART2, ch);
		}

	}
}

/*********************************************************************
 * Queue a string of characters to be TX
 *********************************************************************/
static void
uart_puts(const char *s) {
	
	for ( ; *s; ++s ) {
		// blocks when queue is full
		xQueueSend(uart_txq,s,portMAX_DELAY); 
	}
}

/*********************************************************************
 * Demo Task:
 *	Simply queues up two line messages to be TX, one second
 *	apart.
 *********************************************************************/

static void
demo_task(void *args __attribute__((unused)))
{

    for (;;)
    {

        uart_puts("Now this is a message sent via FreeRTOS queues");
        uart_puts("\n\r");
        vTaskDelay(pdMS_TO_TICKS(1000));
        // Toggle LED to show signs of life
        gpio_toggle(GPIOC,GPIO13);
	}
}

/*********************************************************************
 * Main program & scheduler:
 *********************************************************************/
int
main(void) {

    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);

	// GPIO PC13:
    rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(
        GPIOC,
		GPIO_MODE_OUTPUT_2_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL,
        GPIO13);

	uart_setup();

    xTaskCreate(uart_task,"UART",100,NULL,configMAX_PRIORITIES-1,NULL);
	xTaskCreate(demo_task,"DEMO",100,NULL,configMAX_PRIORITIES-1,NULL);

	vTaskStartScheduler();
	for (;;);
	return 0;
}

/* End */
