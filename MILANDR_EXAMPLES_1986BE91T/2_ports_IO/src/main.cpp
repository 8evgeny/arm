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

#define delay(T) for(i = T; i > 0; i--) // Определение функции задержки (см. примечение 1)
PORT_InitTypeDef PORTDInit; // Объявление структуры, с помощью которой будет происходить инициализация порта
int i; // Глобальная переменная счетчика, которая используется в функции delay()

int main (int argc, char** argv) {
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE); // Включение тактования порта D
    PORTDInit.PORT_Pin =
        PORT_Pin_10 |
        PORT_Pin_11 |
        PORT_Pin_12 |
        PORT_Pin_13 |                          // Объявляем номера ножек порта, которые
        PORT_Pin_14;                           // настраиваются данной структурой
    PORTDInit.PORT_OE = PORT_OE_OUT;           // Конфигурация группы выводов как выход
    PORTDInit.PORT_FUNC = PORT_FUNC_PORT;      // Работа а режиме порта ввода-вывода
    PORTDInit.PORT_MODE = PORT_MODE_DIGITAL;   // Цифровой режим
    PORTDInit.PORT_SPEED = PORT_SPEED_SLOW;    // Низкая частота тактования порта
    PORT_Init(MDR_PORTD, &PORTDInit);          // Инициализация порта D объявленной структурой

    while(1){
        PORT_SetBits(MDR_PORTD, PORT_Pin_10);  // Установка единицы на 10 пине в порту D
        delay(0xFFFF);                         // Задержка
        PORT_ResetBits(MDR_PORTD, PORT_Pin_10);// Установка нуля на 10 пине в порту D
        PORT_SetBits(MDR_PORTD, PORT_Pin_11);
        delay(0xFFFF);
        PORT_ResetBits(MDR_PORTD, PORT_Pin_11);
        PORT_SetBits(MDR_PORTD, PORT_Pin_12);
        delay(0xFFFF);
        PORT_ResetBits(MDR_PORTD, PORT_Pin_12);
        PORT_SetBits(MDR_PORTD, PORT_Pin_13);
        delay(0xFFFF);
        PORT_ResetBits(MDR_PORTD, PORT_Pin_13);
        PORT_SetBits(MDR_PORTD, PORT_Pin_14);
        delay(0xFFFF);
        PORT_ResetBits(MDR_PORTD, PORT_Pin_14);
    }
}
//=================================
