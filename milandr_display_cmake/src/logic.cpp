
//---------------------------------
// ptz.c
// Плата индикации (MDR32)
//---------------------------------
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
//---------------------------------
#include "main.h"
#include "gpio.h"
#include "usb.h"
#include <string>
//---------------------------------
// Стартовая логика
//---------------------------------
void START_logic() {
	//приветствие
    PORT_SetBits(MDR_PORTB, LED1_ERROR);	//проверка светодиодов
//    PORT_SetBits(MDR_PORTB, LED2_REC);
	LCD_control(1,0,0);		//включение дисплея и выбор курсора
	LCD_entry_mode(1,0);	//установка направления сдвига
	LCD_clear_display();	//установка курсора в начало
	LCD_function(1,1);	    //страница знакогенератора 1
	LCD_clear_display();
	
    LCD_set_line(1);
    std::string line1 = "Received: ";
    line1.append(std::to_string(42));
    LCD_write_string((char*)line1.c_str());
    
	LCD_set_line(2);
    std::string line2 = "Sending:  ";
    line2.append(std::to_string(SentByteCount));
    LCD_write_string((char*)line2.c_str());
    
	LCD_set_line(3);
    std::string line3 = "Skipped:  ";
    line3.append(std::to_string(SkippedByteCount));;
    LCD_write_string((char*)line3.c_str());
    
    LCD_set_line(4);
    std::string line4 = "Received";
    line4.append("  --line4--");
    LCD_write_string((char*)line4.c_str());
    
    
	delay_ms(5000);
    PORT_ResetBits(MDR_PORTB, LED1_ERROR);
//    PORT_ResetBits(MDR_PORTB, LED2_REC);
	//LCD_clear_display();
	
	//проверка зуммера
//	PORT_SetBits(MDR_PORTB, BUZZER);
//	delay_ms(100);
//	PORT_ResetBits(MDR_PORTB, BUZZER);
}
//---------------------------------
// Главная логика
//---------------------------------
void MAIN_logic() {
    PORT_ResetBits(MDR_PORTB, LED1_ERROR);
//    PORT_ResetBits(MDR_PORTB, LED2_REC);
    delay_ms(1000);
    PORT_SetBits(MDR_PORTB, LED1_ERROR);
//    PORT_SetBits(MDR_PORTB, LED2_REC);
    delay_ms(1000);
}
