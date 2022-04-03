#include "i2c_1637.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/i2c.h>
#define  I2C_Direction_Transmitter      ((uint8_t)0x00)
#define  I2C_Direction_Receiver         ((uint8_t)0x01)

static QueueHandle_t uart_txq;		// TX queue for UART

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

static void
uart_puts(const char *s) {
	
	for ( ; *s; ++s ) {
		// blocks when queue is full
		xQueueSend(uart_txq,s,portMAX_DELAY); 
	}
}

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

void init_I2C1(void)
{
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_I2C1);
    rcc_periph_clock_enable(RCC_AFIO);

    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
                  GPIO_I2C1_SCL | GPIO_I2C1_SDA);

    /* Disable the I2C before changing any configuration. */
    i2c_peripheral_disable(I2C1);

    /* APB1 is running at 36MHz. */
    i2c_set_clock_frequency(I2C1, 36);

    /* 400KHz - I2C Fast Mode */
    i2c_set_fast_mode(I2C1);
    //    i2c_set_standard_mode(I2C1);

    /*
     * fclock for I2C is 36MHz APB2 -> cycle time 28ns, low time at 400kHz
     * incl trise -> Thigh = 1600ns; CCR = tlow/tcycle = 0x1C,9;
     * Datasheet suggests 0x1e.
     */
    i2c_set_ccr(I2C1, 0x1e);

    /*
     * fclock for I2C is 36MHz -> cycle time 28ns, rise time for
     * 400kHz => 300ns and 100kHz => 1000ns; 300ns/28ns = 10;
     * Incremented by 1 -> 11.
     */
    i2c_set_trise(I2C1, 0x0b);

    /*
     * This is our slave address - needed only if we want to receive from
     * other masters.
     */
    i2c_set_own_7bit_slave_address(I2C1, 0x11);

    /* If everything is configured -> enable the peripheral. */
    i2c_peripheral_enable(I2C1);
}

void I2C_POD_StartTransmission(uint32_t i2c, uint8_t transmissionDirection,  uint8_t slaveAddress)
{

    while((I2C_SR2(i2c) & I2C_SR2_BUSY) != 0x00000000){};

    i2c_send_start(i2c);

    while( // Выход из цикла когда все флаги упадут в 0
        ((I2C_SR1(i2c) & I2C_SR1_TxE) == 0x00000000)  ||  //TXE
        ((I2C_SR1(i2c) & I2C_SR1_ADDR) == 0x00000000) ||  //ADDR
        ((I2C_SR2(i2c) & I2C_SR2_BUSY) == 0x00000000) ||  //BUSY
        ((I2C_SR2(i2c) & I2C_SR2_MSL) == 0x00000000)  ||  //MSL
        ((I2C_SR2(i2c) & I2C_SR2_TRA) == 0x00000000)      //TRA
        );

    i2c_send_7bit_address(i2c, slaveAddress, transmissionDirection);

    if(transmissionDirection== I2C_Direction_Transmitter)
    {
        while( // Выход из цикла когда все флаги упадут в 0
            ((I2C_SR1(i2c) & I2C_SR1_TxE) == 0x00000000)  ||  //TXE
            ((I2C_SR1(i2c) & I2C_SR1_ADDR) == 0x00000000) ||  //ADDR
            ((I2C_SR2(i2c) & I2C_SR2_BUSY) == 0x00000000) ||  //BUSY
            ((I2C_SR2(i2c) & I2C_SR2_MSL) == 0x00000000)  ||  //MSL
            ((I2C_SR2(i2c) & I2C_SR2_TRA) == 0x00000000)      //TRA
            );
    }
    if(transmissionDirection== I2C_Direction_Receiver)
    {
        while( // Выход из цикла когда все флаги упадут в 0
            ((I2C_SR1(i2c) & I2C_SR1_ADDR) == 0x00000000) ||  //ADDR
            ((I2C_SR2(i2c) & I2C_SR2_BUSY) == 0x00000000) ||  //BUSY
            ((I2C_SR2(i2c) & I2C_SR2_MSL) == 0x00000000)      //MSL
            );
    }
}



void send_to_POT(uint8_t data)
{
    //AR - только запись
    //57 - чтение
    //56 - запись
    //56 02 80 выбор WCR
    //56 02 00 выбор DR
    //The WCR is a volatile register and is written with the contents of the nonvolatile Data Register (DR) on power-up.

    //WCR WRITE OPERATION                 start 56 02 80 stop start 56 00 data stop
    //WCR INCREMENT/DECREMENT OPERATION - start 56 02 80 stop start 5E 00 ??
    //WCR READ OPERATION                  start 56 02 80 stop start 56 00 start 57 data stop
    //The WCR is also written during a write to DR
    //DR WRITE OPERATION                  start 56 02 00 stop start 56 00 data stop
    //DR READ OPERATION                   start 56 02 00 stop start 56 00 start 57 data stop

    //start 56 02 00 stop start 56 00 data stop

    //void i2c_send_start(uint32_t i2c)
    //{
    //	I2C_CR1(i2c) |= I2C_CR1_START; !!!!!!!!!!!!!!!!!!!!!!!!!!! тут все
    //}

    //DR WRITE OPERATION  start 56 02 00 stop start 56 00 data stop
    I2C_POD_StartTransmission(I2C1, I2C_Direction_Transmitter, 0x56);
    i2c_send_data(I2C1,0x02);

    while( // Выход из цикла когда все флаги упадут в 0
        ((I2C_SR1(I2C1) & I2C_SR1_TxE) == 0x00000000)  ||  //TXE
        ((I2C_SR1(I2C1) & I2C_SR1_BTF) == 0x00000000) ||   //BTF
        ((I2C_SR2(I2C1) & I2C_SR2_BUSY) == 0x00000000) ||  //BUSY
        ((I2C_SR2(I2C1) & I2C_SR2_MSL) == 0x00000000)  ||  //MSL
        ((I2C_SR2(I2C1) & I2C_SR2_TRA) == 0x00000000)      //TRA
        );

    i2c_send_data(I2C1,0x00);

    while( // Выход из цикла когда все флаги упадут в 0
        ((I2C_SR1(I2C1) & I2C_SR1_TxE) == 0x00000000)  ||  //TXE
        ((I2C_SR1(I2C1) & I2C_SR1_BTF) == 0x00000000) ||   //BTF
        ((I2C_SR2(I2C1) & I2C_SR2_BUSY) == 0x00000000) ||  //BUSY
        ((I2C_SR2(I2C1) & I2C_SR2_MSL) == 0x00000000)  ||  //MSL
        ((I2C_SR2(I2C1) & I2C_SR2_TRA) == 0x00000000)      //TRA
        );

    i2c_send_stop(I2C1);

    I2C_POD_StartTransmission(I2C1, I2C_Direction_Transmitter, 0x56);

    i2c_send_data(I2C1,0x00);

    while( // Выход из цикла когда все флаги упадут в 0
        ((I2C_SR1(I2C1) & I2C_SR1_TxE) == 0x00000000)  ||  //TXE
        ((I2C_SR1(I2C1) & I2C_SR1_BTF) == 0x00000000) ||   //BTF
        ((I2C_SR2(I2C1) & I2C_SR2_BUSY) == 0x00000000) ||  //BUSY
        ((I2C_SR2(I2C1) & I2C_SR2_MSL) == 0x00000000)  ||  //MSL
        ((I2C_SR2(I2C1) & I2C_SR2_TRA) == 0x00000000)      //TRA
        );

    i2c_send_data(I2C1,data);

    while( // Выход из цикла когда все флаги упадут в 0
        ((I2C_SR1(I2C1) & I2C_SR1_TxE) == 0x00000000)  ||  //TXE
        ((I2C_SR1(I2C1) & I2C_SR1_BTF) == 0x00000000) ||   //BTF
        ((I2C_SR2(I2C1) & I2C_SR2_BUSY) == 0x00000000) ||  //BUSY
        ((I2C_SR2(I2C1) & I2C_SR2_MSL) == 0x00000000)  ||  //MSL
        ((I2C_SR2(I2C1) & I2C_SR2_TRA) == 0x00000000)      //TRA
        );

    i2c_send_stop(I2C1);
}

void setup_1637()
{
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_I2C1);
    rcc_periph_clock_enable(RCC_AFIO);

    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ,
                  GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
                  GPIO_I2C1_SCL | GPIO_I2C1_SDA);

// Use a bitmap operation
#define TM1637_CLK           PBout(6)
#define TM1637_DIO           PBout(7)
#define TM1637_READ_DIO      PBin(7)

    // IO direction setting 0011 output mode 1000 pull-up input mode
#define TM1637_DIO_IN()      {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define TM1637_DIO_OUT()     {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}







}


int main(void)
{

    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);

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

