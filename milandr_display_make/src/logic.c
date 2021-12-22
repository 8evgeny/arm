
//---------------------------------
// ptz.c
// ѕлата индикации (MDR32)
//---------------------------------
#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
//---------------------------------
#include "main.h"
#include "gpio.h"
//---------------------------------
// —тартова€ логика
//---------------------------------
void START_logic() {
	//приветствие
	PORT_SetBits(MDR_PORTB, LED1_ERROR|LED2_REC);	//проверка светодиодов
	LCD_control(1,0,0);		//включение диспле€ и выбор курсора
	LCD_entry_mode(1,0);	//установка направлени€ сдвига
	LCD_clear_display();	//установка курсора в начало
	LCD_function(1,1);	//страница знакогенератора 1
	LCD_clear_display();
	//LCD_write_string("  ¬идеорегистратор  ");
  LCD_write_string("  Videorecorder  ");
	LCD_set_line(2);
	LCD_write_string("  GIT-VIDEO SURV   ");
	LCD_set_line(4);
	//LCD_write_string("     верси€ 1.0     ");
	LCD_write_string(" -- version 1.0 -- ");
	delay_ms(5000);
	PORT_ResetBits(MDR_PORTB, LED1_ERROR|LED2_REC);
	
	//LCD_clear_display();
	
	//проверка зуммера
	//PORT_SetBits(MDR_PORTB, BUZZER);	
	//delay_ms(100);
	//PORT_ResetBits(MDR_PORTB, BUZZER);
}
//---------------------------------
// √лавна€ логика
//---------------------------------
void MAIN_logic() {
	//PORT_ResetBits(MDR_PORTB, LED1_ERROR|LED2_REC);
    PORT_ResetBits(MDR_PORTB, LED1_ERROR|LED2_REC);
	delay_ms(2000);
	//PORT_SetBits(MDR_PORTB, LED1_ERROR|LED2_REC);
    PORT_SetBits(MDR_PORTB, LED2_REC);
	delay_ms(5000);
}
