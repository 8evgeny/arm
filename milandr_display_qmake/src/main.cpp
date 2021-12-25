
//---------------------------------
// Плата индикации (MDR32)
//---------------------------------
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_iwdg.h"

//---------------------------------
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_usb_handlers.h"
//---------------------------------
#include "gpio.h"
#include "main.h"
#include <string>

//=================================
int main (int argc, char** argv) {
	__disable_irq();
	//SysTick_init();
	RCC_init();
	GPIO_init();
	__enable_irq();
	TIM1_init();
	LCD_init();
	START_logic();
	IWDT_init();
    std::string www = "qwertyu";
	//-------------------------------
	uint8_t Buffer[32];
	VCom_Configuration();
    // CDC layer initialization
    USB_CDC_Init(Buffer, 1, SET);
    Setup_CPU_Clock();
    Setup_USB();
	//-------------------------------
   
	while (1) {
		MAIN_logic();
		IWDG_ReloadCounter();	//сбрасываем IWDT	
	}	
}
//=================================
