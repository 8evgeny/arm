#include "MDR32Fx.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_timer.h"
#include "MDR32F9Qx_iwdg.h"
//---------------------------------
#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_usb_handlers.h"
//---------------------------------
#include "main.h"
//=================================
PORT_InitTypeDef PORTDInit;
void PortsInit(){                // Процедура инициализации светодиодов
    PORT_StructInit(&PORTDInit); //Load defaults
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
    PORTDInit.PORT_Pin
        = PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14;
    PORTDInit.PORT_OE
        = PORT_OE_OUT;
    PORTDInit.PORT_MODE = PORT_MODE_DIGITAL;
    PORTDInit.PORT_SPEED = PORT_SPEED_SLOW;
    PORT_Init(MDR_PORTD, &PORTDInit);
}

//Процедура переключения светодиодов
uint8_t cur_i;
void NextLED(){
    switch(cur_i++ % 5) {
    case 0:
        PORT_ResetBits(MDR_PORTD, PORT_Pin_14);
        PORT_SetBits(MDR_PORTD, PORT_Pin_10);
        break;
    case 1:
        PORT_ResetBits(MDR_PORTD, PORT_Pin_10);
        PORT_SetBits(MDR_PORTD, PORT_Pin_11);
        break;
    case 2:
        PORT_ResetBits(MDR_PORTD, PORT_Pin_11);
        PORT_SetBits(MDR_PORTD, PORT_Pin_12);
        break;
    case 3:
        PORT_ResetBits(MDR_PORTD, PORT_Pin_12);
        PORT_SetBits(MDR_PORTD, PORT_Pin_13);
        break;
    case 4:
        PORT_ResetBits(MDR_PORTD, PORT_Pin_13);
        PORT_SetBits(MDR_PORTD, PORT_Pin_14);
        break;
    }
}

TIMER_CntInitTypeDef TIM1Init;
//Процедура инициализации таймера
void TimerInit(){
    RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER1, ENABLE);     // Включение тактирования
    TIMER_BRGInit(MDR_TIMER1, TIMER_HCLKdiv1);        // Настройка делителя тактовой частоты
    TIMER_CntStructInit(&TIM1Init);                   // Заполнение структуры значениями по умолчанию
    TIM1Init.TIMER_Prescaler = 8000;                  // Задание предделителя тактовой частоты
    TIM1Init.TIMER_Period    = 1000;                  // Задание модуля счета
    TIMER_CntInit(MDR_TIMER1, &TIM1Init);             // Процедура инициализации с помощью структуры
    NVIC_EnableIRQ(Timer1_IRQn);                      // Включение прерываний
    NVIC_SetPriority(Timer1_IRQn, 0);                 // Установка приоритета прерываний
    TIMER_ITConfig(MDR_TIMER1, TIMER_STATUS_CNT_ZERO, ENABLE);
    TIMER_Cmd(MDR_TIMER1, ENABLE);
}
//Процедура обработки прерывания вызванного таймером
void Timer1_IRQHandler() {
    if(TIMER_GetITStatus(MDR_TIMER1, TIMER_STATUS_CNT_ZERO)){
        NextLED();
        // Очистка флага прерывания в таймере (предотвращает повторный вызов того же прерывания)
        TIMER_ClearITPendingBit(MDR_TIMER1, TIMER_STATUS_CNT_ZERO);
    }
}

int main() {
    PortsInit();
    TimerInit();
    cur_i = 0;
    while(1){
        // Silence is priceless
    }
}

#if 0
Описание структуры, инициализации таймера
typedef struct {
uint16_t TIMER_IniCounter;              Определяет начальное значение счетчика, может быть задан в
                                        диапазоне 0x0000 and 0xFFFF.

uint16_t TIMER_Prescaler;          Определяет второй делитель тактовой частоты таймера. Может
                                   быть задан в диапазоне 0x0000 and 0xFFFF. Расчет тактовой
                                   частоты таймера можно вести по формуле
                                   CLK = TIMER_CLK/(TIMER_Prescaler + 1)

uint16_t TIMER_Period;             Определяет основание счета счетчика которое зашлется в
                                   регистр Auto-Reload Register (ARR) при следующем обновлении.
                                   Может быть задан в диапазоне 0x0000 and 0xFFFF.

uint16_t TIMER_CounterMode;        Определяет режим работы таймера:
                                   TIMER_CntMode_ClkFixedDir   счет тактовой частоты в одном направлении
                                   TIMER_CntMode_ClkChangeDir  счет тактовой частоты с автоматическим реверсированием
                                   TIMER_CntMode_EvtFixedDir   счет событий в одном направлении
                                   TIMER_CntMode_EvtChangeDir  счет событий с автоматическим реверсированием

uint16_t TIMER_CounterDirection;   Определяет направление счета:
                                   TIMER_CntDir_Up             суммирующий счетчик
                                   TIMER_CntDir_Dn             вычитающий счетчик

uint16_t TIMER_EventSource;        Определяет источник событий (тактирования) для таймера.
                                   TIMER_EvSrc_None  не определен (тактируется от тактовой частоты)
                                   TIMER_EvSrc_TM1  Таймер 1 (переключается по обновлению таймера 1)
                                   TIMER_EvSrc_TM2  Таймер 2 (переключается по обновлению таймера 2)
                                   TIMER_EvSrc_TM3  Таймер 3 (переключается по обновлению таймера 3)
                                   TIMER_EvSrc_CH1  Событие в канале 1
                                   TIMER_EvSrc_CH2  Событие в канале 2
                                   TIMER_EvSrc_CH3  Событие в канале 3
                                   TIMER_EvSrc_CH4  Событие в канале 4
                                   TIMER_EvSrc_ETR  Событие на входе ETR

uint16_t TIMER_FilterSampling;     Определяет частоту сэмплирования входных данных(FDTS).
                                   TIMER_FDTS_TIMER_CLK_div_1  Частота сэмплирования равна частоте таймера
                                   TIMER_FDTS_TIMER_CLK_div_2  Частота сэмплирования равна частоте таймера/2
                                   TIMER_FDTS_TIMER_CLK_div_3  Частота сэмплирования равна частоте таймера/3
                                   TIMER_FDTS_TIMER_CLK_div_4  Частота сэмплирования равна частоте таймера/4

uint16_t TIMER_ARR_UpdateMode;     Разрешение мгновенного обновления ARR
                                   TIMER_ARR_Update_Immediately       ARR будет перезаписан в момент записи в ARR
                                   TIMER_ARR_Update_On_CNT_Overflow   ARR будет перезаписан при завершении счета CNT

uint16_t TIMER_ETR_FilterConf;     Определяет конфигурацию фильтра на входе ETR. Более
                                   подробно можно посмотреть в файле MDR32F9Qx_timer.h
                                   определение @ref IMER_FilterConfiguration

uint16_t TIMER_ETR_Prescaler;      Определяет предделитель тактовой частоты на входе ETR
                                   Более подробно можно посмотреть в файле MDR32F9Qx_timer.h
                                   определение @ref TIMER_ETR_Prescaler

uint16_t TIMER_ETR_Polarity;       Определяет полярность ETR сигнала.
                                   определение в @ref TIMER_ETR_Polarity

uint16_t TIMER_BRK_Polarity;       Определяет полярность BRK сигнала.
                                   определение в @ref TIMER_BRK_Polarity
} TIMER_CntInitTypeDef;
#endif
