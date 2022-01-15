#include "gpio.h"
#include "main.h"
#include "usb.h"
#include <string>
#include <vector>
#include <string.h>
//=================================

int main (int argc, char** argv) {

	__disable_irq();
	RCC_init();
	GPIO_init();
	__enable_irq();

    TIM1_init();
    IWDT_init();
    VCom_Configuration();

    USB_CDC_Init(Buffer, 80, SET);
    Setup_CPU_Clock();
    Setup_USB();

    LCD_init();
    START_logic();

    //-------------------------------

	while (1) {
        char  str1[21];
        memcpy (str1, Buffer, 20);
        char  str2[21];
        memcpy (str2, Buffer + 20 , 20);
        char  str3[21];
        memcpy (str3, Buffer + 40 , 20);
        char  str4[21];
        memcpy (str4, Buffer + 60 , 20);

        PrintString1(str1);
        PrintString2(str2);
        PrintString3(str3);
        PrintString4(str4);

        IWDG_ReloadCounter();	//сбрасываем IWDT
	}	
}

void PrintLcd(char* string)
{

}

