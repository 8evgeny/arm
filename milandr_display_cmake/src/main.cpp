#include "gpio.h"
#include "main.h"
#include "usb.h"
#include <string>
#include <vector>
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
        char * str = (char*) Buffer;
        MAIN_logic(str);
        IWDG_ReloadCounter();	//сбрасываем IWDT
	}	
}

void PrintLcd(char* string)
{

}

