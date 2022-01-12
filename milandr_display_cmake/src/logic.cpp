
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
#include <string>
#include "usb.h"
//---------------------------------
// Стартовая логика
//---------------------------------
void START_logic() {
	//приветствие
	PORT_SetBits(MDR_PORTB, LED1_ERROR|LED2_REC);	//проверка светодиодов
	LCD_control(1,0,0);		//включение дисплея и выбор курсора
	LCD_entry_mode(1,0);	//установка направления сдвига
	LCD_clear_display();	//установка курсора в начало
    LCD_function(1,1);	    //страница знакогенератора 1
	LCD_clear_display();
	//LCD_write_string("  Видеорегистратор  ");

    std::string line1, line2, line3, line4;
    LCD_set_line(1);
    line1 = "Received :" + std::to_string(ReceivedByteCount);
    LCD_write_string((char*)line1.c_str());

	LCD_set_line(2);
    line2 = "Sending :" + std::to_string(SentByteCount);
    LCD_write_string((char*)line2.c_str());

    LCD_set_line(3);
    line3 = "Skipped :" + std::to_string(SkippedByteCount);
    LCD_write_string((char*)line3.c_str());

    LCD_set_line(4);
    line4 = "Test :" + std::to_string(SkippedByteCount);
    LCD_write_string((char*)line3.c_str());

    delay_ms(5000);
	PORT_ResetBits(MDR_PORTB, LED1_ERROR|LED2_REC);
	
    LCD_clear_display();
	
//	проверка зуммера
    PORT_SetBits(MDR_PORTB, BUZZER);
    delay_ms(100);
    PORT_ResetBits(MDR_PORTB, BUZZER);
}
//---------------------------------
// Главная логика
//---------------------------------
void MAIN_logic() {
	//PORT_ResetBits(MDR_PORTB, LED1_ERROR|LED2_REC);
    PORT_ResetBits(MDR_PORTB, LED1_ERROR|LED2_REC);
	delay_ms(2000);
	//PORT_SetBits(MDR_PORTB, LED1_ERROR|LED2_REC);
    PORT_SetBits(MDR_PORTB, LED2_REC);
	delay_ms(5000);
}
