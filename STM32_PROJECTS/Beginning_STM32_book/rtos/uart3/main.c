/* Task based UART demo, using queued communication and
 * non-blocking I/O call.
 *
 * 115200 baud, 8N1, rts/cts flow control.
 */
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "uartlib.h"

#define mainECHO_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )

bool uart4 = false;

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask,signed portCHAR *pcTaskName);

static QueueHandle_t uart_txq;				// TX queue for UART

void
vApplicationStackOverflowHook(xTaskHandle *pxTask,signed portCHAR *pcTaskName) {
	(void)pxTask;
	(void)pcTaskName;
	for(;;);
}

/*********************************************************************
 * Configure and initialize GPIO Interfaces
 *********************************************************************/

static void
gpio_setup(void) {

    rcc_clock_setup_in_hse_8mhz_out_72mhz();	// CPU clock is 72 MHz
    rcc_periph_clock_enable(RCC_GPIOD);
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOD,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO2);
    gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO13);

    if(!uart4) rcc_periph_clock_enable(RCC_GPIOA);
    if(uart4) rcc_periph_clock_enable(RCC_UART4);

    if(!uart4) gpio_set_mode(GPIOA,GPIO_MODE_OUTPUT_50_MHZ,GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,GPIO_USART1_TX);
    if(uart4) gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_50_MHZ,GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,GPIO_UART4_TX);
//	gpio_set_mode(GPIOA,GPIO_MODE_OUTPUT_50_MHZ,GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,GPIO11);

    if(!uart4) gpio_set_mode(GPIOA,GPIO_MODE_INPUT,GPIO_CNF_INPUT_FLOAT,GPIO_USART1_RX);
    if(uart4) gpio_set_mode(GPIOC,GPIO_MODE_INPUT,GPIO_CNF_INPUT_FLOAT,GPIO_UART4_RX);
//	gpio_set_mode(GPIOA,GPIO_MODE_INPUT,GPIO_CNF_INPUT_FLOAT,GPIO12);
}

/*********************************************************************
 * Configure and initialize USART1:
 *********************************************************************/

static void
uart_setup(void) {

    if(!uart4) open_uart(1,115200,"8N1","rw",0,0);
    if(uart4) open_uart(4,115200,"8N1","rw",0,0);
	uart_txq = xQueueCreate(256,sizeof(char));
}

/*********************************************************************
 * USART Task: 
 *********************************************************************/

static void
uart_task(void *args) {
	int gc;
	char kbuf[256], ch;
	
	(void)args;

    if(!uart4) puts_uart(1,"\n\ruart_task() has begun:\n\r");
    if(uart4) puts_uart(4,"\n\ruart_task() has begun:\n\r");
	for (;;) {
        if(!uart4) gc = getc_uart_nb(1);
        if(uart4) gc = getc_uart_nb(4);

        if ( gc != -1 ) {
            if(!uart4) puts_uart(1,"\r\n\nENTER INPUT: ");
            if(uart4) puts_uart(4,"\r\n\nENTER INPUT: ");
			ch = (char)gc;
			if ( ch != '\r' && ch != '\n' ) {
				/* Already received first character */
				kbuf[0] = ch;
                if(!uart4) putc_uart(1,ch);
                if(uart4) putc_uart(4,ch);

                if(!uart4) getline_uart(1,kbuf+1,sizeof kbuf-1);
                if(uart4) getline_uart(4,kbuf+1,sizeof kbuf-1);
			} else	{
				/* Read the entire line */
                if(!uart4) getline_uart(1,kbuf,sizeof kbuf);
                if(uart4) getline_uart(4,kbuf,sizeof kbuf);
			}
            if(!uart4)
            {
                puts_uart(1,"\r\nReceived input '");
                puts_uart(1,kbuf);
                puts_uart(1,"'\n\r\nResuming prints...\n\r");
            }
            if(uart4)
            {
                puts_uart(4,"\r\nReceived input '");
                puts_uart(4,kbuf);
                puts_uart(4,"'\n\r\nResuming prints...\n\r");
            }

		}

		/* Receive char to be TX */
		if ( xQueueReceive(uart_txq,&ch,10) == pdPASS )
            if(!uart4) putc_uart(1,ch);
            if(uart4) putc_uart(4,ch);

		/* Toggle LED to show signs of life */
        gpio_toggle(GPIOD,GPIO2);
//        gpio_toggle(GPIOC,GPIO13);
	}
}

/*********************************************************************
 * Queue a string of characters to be TX
 *********************************************************************/

static inline void
uart_puts(const char *s) {
	
	for ( ; *s; ++s )
		xQueueSend(uart_txq,s,portMAX_DELAY); /* blocks when queue is full */
}

/*********************************************************************
 * Demo Task:
 *	Simply queues up two line messages to be TX, one seconds
 *	apart.
 *********************************************************************/

static void
demo_task(void *args) {

	(void)args;

	for (;;) {
		uart_puts("Now this is a message..\n\r");
		uart_puts("  sent via FreeRTOS queues.\n\n\r");
		vTaskDelay(pdMS_TO_TICKS(1000));
		uart_puts("Just start typing to enter a line, or..\n\r"
			"hit Enter first, then enter your input.\n\n\r");
		vTaskDelay(pdMS_TO_TICKS(1500));
	}
}

/*********************************************************************
 * Main program & scheduler:
 *********************************************************************/

int
main(void) {

	gpio_setup();
	uart_setup();

	xTaskCreate(uart_task,"UART",200,NULL,configMAX_PRIORITIES-1,NULL);	/* Highest priority */
	xTaskCreate(demo_task,"DEMO",100,NULL,configMAX_PRIORITIES-2,NULL);	/* Lower priority */

	vTaskStartScheduler();
	for (;;)
		;
	return 0;
}

/* End */
