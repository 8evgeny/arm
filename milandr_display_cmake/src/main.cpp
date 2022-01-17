#include "gpio.h"
#include "main.h"
#include "usb.h"
#include <string>
#include <vector>
#include <string.h>
#include <chrono>


int main (int argc, char** argv) {

	__disable_irq();
	RCC_init();
	GPIO_init();
	__enable_irq();

    TIM1_init();
    IWDT_init();
    VCom_Configuration();

    USB_CDC_Init(Buffer, 84, SET);
    Setup_CPU_Clock();
    Setup_USB();

    LCD_init();
    Check();

	while (1) {
        parcingBuffer();

        if(BufferLCD[0] == 49) //если 1 то горит первый светодиод
        {
            PORT_SetBits(MDR_PORTB, LED2_REC);
        }
        else
        {
            PORT_ResetBits(MDR_PORTB, LED2_REC);
        }
        if(BufferLCD[1] == 49) //если 1 то горит второй светодиод
        {
            PORT_SetBits(MDR_PORTB, LED1_ERROR);
        }
        else
        {
            PORT_ResetBits(MDR_PORTB, LED1_ERROR);
        }
        if (BufferLCD[2] == 49) //Постоянный сигнал
        {
            PORT_SetBits(MDR_PORTB, BUZZER);
        }
        else //Выключен
        {
            PORT_ResetBits(MDR_PORTB, BUZZER);
        }
//        checkLCD1();
//        checkLCD2();
//        checkBUZZER();

        char  str1[21]; //4 строки на экране
        char  str2[21];
        char  str3[21];
        char  str4[21];

        memcpy (str1, BufferLCD + 3, 20);
        memcpy (str2, BufferLCD + 23 , 20);
        memcpy (str3, BufferLCD + 43 , 20);
        memcpy (str4, BufferLCD + 63 , 20);

        PrintString1(str1);
        PrintString2(str2);
        PrintString3(str3);
        PrintString4(str4);

        IWDG_ReloadCounter();	//сбрасываем IWDT
	}	
}

void parcingBuffer()
{
    memcpy ((uint8_t *)BufferLCD, (uint8_t *) Buffer, 83);
}


