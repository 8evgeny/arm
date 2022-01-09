#include <MDR32Fx.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_timer.h>
#include <MDR32F9Qx_iwdg.h>
#include <MDR32F9Qx_dac.h>
#include <math.h>
//---------------------------------
#include <MDR32F9Qx_config.h>
#include <MDR32F9Qx_usb_handlers.h>

//---------------------------------
#include "main.h"
//=================================

#define PI 3.14159265
#define MAX 3 /*Volt*/
#define SCALE (0xFFF * MAX) / 3.3

PORT_InitTypeDef PORTEInit;                      //Объявление структуры
void DACPortInit(){
    PORT_StructInit(&PORTEInit);                 //Загрузка умолчаний
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE); //Тактование
    /* Настройка DAC1 (стр.11 спецификации) */
    PORTEInit.PORT_Pin = PORT_Pin_9;             //Пин 9
    PORTEInit.PORT_OE  = PORT_OE_OUT;            // Порт E
    PORTEInit.PORT_MODE = PORT_MODE_ANALOG;      //Режим Аналоговый
    PORT_Init(MDR_PORTE, &PORTEInit);            //Настройка порта
}

void DACInit(){
    RST_CLK_PCLKcmd(RST_CLK_PCLK_DAC, ENABLE);   //Тактование
    DAC1_Init(DAC1_AVCC);                        //Настройка DAC1 на работу с AVCC
    DAC1_Cmd(ENABLE);                            //Активация DAC1
}

float a;
int i; //4 task 2

int main() {
    RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK, ENABLE);
    DACPortInit();
    DACInit();
    while(1){
        //Jumper to EXT_CON!!!
        //Base part
        for (a=0; a<360; a+=5)
            DAC1_SetData((sinf(a*PI/180)*SCALE + SCALE)/2);

        //Task 1
        for (a=0; a<0xFFF; a+=5) DAC1_SetData(a);
        for (a=0xFFF-1; a>1; a-=5) DAC1_SetData(a);

        //Task 2
        for (a=-0x7FF; a<0; a+=5)
        DAC1_SetData(a*a/(0x7FF*0x7FF)*SCALE);
        for (a=0; a<0x7FF; a+=5) DAC1_SetData(a*a/(0x7FF*0x7FF)*SCALE);
        DAC1_SetData(SCALE);
        for (i=0; i<0xFFFF; i++);
    }
}


#if 0

#endif
