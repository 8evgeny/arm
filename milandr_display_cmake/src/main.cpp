#include "gpio.h"
#include "main.h"
#include "usb.h"
#include <string>
#include <vector>
#include <string.h>

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
        checkLCD1();
        checkLCD2();
        checkBUZZER();

        char  str1[21]; //4 строки на экране
        char  str2[21];
        char  str3[21];
        char  str4[21];
        memcpy (str1, Buffer+3, 20);
        memcpy (str2, Buffer + 23 , 20);
        memcpy (str3, Buffer + 43 , 20);
        memcpy (str4, Buffer + 63 , 20);
        PrintString1(str1);
        PrintString2(str2);
        PrintString3(str3);
        PrintString4(str4);

        IWDG_ReloadCounter();	//сбрасываем IWDT
	}	
}



