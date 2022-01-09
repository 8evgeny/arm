#include <MDR32Fx.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_timer.h>
#include <MDR32F9Qx_iwdg.h>
#include <MDR32F9Qx_dac.h>
#include <MDR32F9Qx_adc.h>
#include <stdbool.h>
#include <math.h>
//---------------------------------
#include <MDR32F9Qx_config.h>
#include <MDR32F9Qx_usb_handlers.h>

//---------------------------------
#include "main.h"
//=================================

#define delay(T) for(i = T; i > 0; i--)
#define SCALE 1252.5

ADC_InitTypeDef ADC;          //Общая инициализацинная структура подсистемы АЦП
ADCx_InitTypeDef ADC1;        //Инициализацинная структура для АЦП1

void ADCInit(){
    RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK | RST_CLK_PCLK_ADC, ENABLE); //Подача тактования на процессор и АЦП
    ADC_StructInit(&ADC);     //Заполнение структуры умолч. значениями
    ADC_Init(&ADC);           //Инициализация
    ADCx_StructInit(&ADC1);
    ADC1.ADC_ChannelNumber = ADC_CH_ADC7; //Выбор седьмого канала
    ADC1_Init(&ADC1);

    //Инициализация прерываний АЦП
    NVIC_EnableIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, 0);

    //Включение прерываний по окончанию преобразования
    ADC1_ITConfig(ADCx_IT_END_OF_CONVERSION, ENABLE);

    //Включение АЦП1
    ADC1_Cmd(ENABLE);
}

bool conInProgress;                 //Флаг «в процессе преобразования»
unsigned int rawResult;             //Необработанный результат
unsigned char channel;              //Номер канала
float result;                       //Результат в вольтах

void ADC_IRQHandler() { //Обработчик прерываний АЦП

    if(ADC_GetITStatus(ADC1_IT_END_OF_CONVERSION)){    //Проверка что причина прерывания соответствует концу преобразования
        rawResult = ADC1_GetResult();                  //Получение результата
        channel = (rawResult & 0x1F0000) >> 16;        //Сохранение номера канала
        rawResult &= 0xFFF;                            //Удаление номера канала из результата
        result = (float)rawResult / (float)SCALE;      //Преобразование результата в вольты
        conInProgress = false;                         //Очистка флага «в процессе преобр-я»
        NVIC_ClearPendingIRQ(ADC_IRQn);                //Очистка флага прерывания
    }
}

int i;                                                 //Счетчик для задержки циклом
int main() {
    ADCInit();
    while(1){
        for(i = 0xFFFF; i > 0; i--);                   //Задержка циклом (плохой вариант)
        if (!conInProgress){                           //Не выполняется ли преобразование?
            ADC1_Start();                              //Начать преобразование!
            conInProgress = true;                      //Преобразование выполняется
       }
    }
}

#if 0

#endif
