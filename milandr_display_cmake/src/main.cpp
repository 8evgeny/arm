#include "gpio.h"
#include "main.h"
#include "usb.h"
#include <string>
#include <vector>
//=================================

int main (int argc, char** argv) {
	__disable_irq();
//	SysTick_init();
 //   delay_ms(2000);
	RCC_init();
//    std::string aa = "qqq";
//    std::vector<int> vec{1,2,3,45};
//    vec.push_back(55);
	GPIO_init();
	__enable_irq();
	TIM1_init();
	IWDT_init();
    VCom_Configuration();

    USB_CDC_Init(Buffer, 1, SET);
    Setup_CPU_Clock();
    Setup_USB();

    LCD_init();
    START_logic();

	//-------------------------------
   
	while (1) {
        MAIN_logic();
//		IWDG_ReloadCounter();	//сбрасываем IWDT
	}	
}


