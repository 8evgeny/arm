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
	LCD_init();
	START_logic();
	IWDT_init();
	//-------------------------------

    VCom_Configuration();
//     CDC layer initialization
    USB_CDC_Init(Buffer, 1, SET);
    Setup_CPU_Clock();
    MAIN_logic();
    Setup_USB();
	//-------------------------------
   
	while (1) {
//		IWDG_ReloadCounter();	//сбрасываем IWDT
	}	
}


