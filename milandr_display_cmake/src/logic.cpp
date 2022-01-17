#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "main.h"
#include "gpio.h"
#include "usb.h"
#include <string>

void Check() {
	LCD_control(1,0,0);		//включение дисплея и выбор курсора
	LCD_entry_mode(1,0);	//установка направления сдвига
	LCD_clear_display();	//установка курсора в начало
	LCD_function(1,1);	    //страница знакогенератора 1
	LCD_clear_display();
    
    PORT_SetBits(MDR_PORTB, LED1_ERROR);	//проверка светодиодов
    PORT_SetBits(MDR_PORTB, LED2_REC);
    delay_ms(1000);
    PORT_ResetBits(MDR_PORTB, LED1_ERROR);
    PORT_ResetBits(MDR_PORTB, LED2_REC);
	//LCD_clear_display();
	
	//проверка зуммера
    PORT_SetBits(MDR_PORTB, BUZZER);
    delay_ms(100);
    PORT_ResetBits(MDR_PORTB, BUZZER);
}

void PrintString1(char* str) {
    LCD_set_XY(1, 1);
    std::string ss{str, 20};
    LCD_write_string((char*)ss.c_str());
//    delay_ms(10);
}

void PrintString2(char* str) {
    LCD_set_XY(1, 2);
    std::string ss{str, 20};
    LCD_write_string((char*)ss.c_str());
//    delay_ms(10);
}

void PrintString3(char* str) {
    LCD_set_XY(1, 3);
    std::string ss{str, 20};
    LCD_write_string((char*)ss.c_str());
//    delay_ms(10);
}

void PrintString4(char* str) {
    LCD_set_XY(1, 4);
    std::string ss{str, 20};
    LCD_write_string((char*)ss.c_str());
//    delay_ms(10);
}
