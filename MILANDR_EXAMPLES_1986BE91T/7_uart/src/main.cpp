#include <MDR32Fx.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_timer.h>
#include <MDR32F9Qx_iwdg.h>
#include <MDR32F9Qx_dac.h>
#include <MDR32F9Qx_adc.h>
#include <stdbool.h>
#include <math.h>
#include <MDR32F9Qx_uart.h>
//---------------------------------
#include <MDR32F9Qx_config.h>
#include <MDR32F9Qx_usb_handlers.h>

//---------------------------------
#include "main.h"
//=================================

PORT_InitTypeDef PortInit;              // определение переменной для инициализации портов ввода вывода
UART_InitTypeDef UART_InitStructure;    // определение переменной для инициализации UART
uint32_t uart2_IT_TX_flag = RESET;      // Флаг устанавливается после передачи одного байта
uint32_t uart2_IT_RX_flag = RESET;      // Флаг устанавливается после приема одного байта

void UART2_IRQHandler(void)
{
    if(UART_GetITStatusMasked(MDR_UART2, UART_IT_RX) == SET)
    //проверка установки флага прерывания по окончании приема данных
    {
        UART_ClearITPendingBit(MDR_UART2, UART_IT_RX);   //Очистка флага прерывания
        uart2_IT_RX_flag = SET;                          //установка флага передача данных завершена
    }
    if (UART_GetITStatusMasked(MDR_UART2, UART_IT_TX) == SET)
    //проверка установки флага прерывания по окончании передачи данных
    {
        UART_ClearITPendingBit(MDR_UART2, UART_IT_TX);    //Очистка флага прерывания
        uart2_IT_TX_flag = SET;                           //установка флага передача данных завершена
    }
}

int main (void) {
    static uint8_t ReciveByte=0x00;                       //данные для приема
    // Включение HSE осциллятора (внешнего кварцевого резонатора) для обеспечения стабильной частоты UART
    RST_CLK_HSEconfig(RST_CLK_HSE_ON);
    if (RST_CLK_HSEstatus() == SUCCESS){
        // Если HSE осциллятор включился и прошел текст, выбор HSE осциллятора в качестве источника
        //тактовых импульсов для CPU_PLL и установка умножителя тактовой частоты CPU_PLL равного 8 = 7+1
        RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, 7);
        RST_CLK_CPU_PLLcmd(ENABLE);                       // Включение схемы PLL
        if (RST_CLK_HSEstatus() == SUCCESS){              //Если включение CPU_PLL прошло успешно
            RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV2);  // Установка CPU_C3_prescaler = 2
            RST_CLK_CPU_PLLuse(ENABLE);   // Установка CPU_C2_SEL от CPU_PLL выхода вместо CPU_C1 такта
            // Выбор CPU_C3 такта на мультиплексоре тактовых импульсов микропроцессора (CPU clock MUX)
            RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
        }
        else while(1);                                    // блок CPU_PLL не включился
    }
    else while(1);                                        // кварцевый резонатор HSE не включился
    RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);          //Разрешение тактирования порта F

    // заполнение полей переменной PortInit для обеспечения работы UART
    PortInit.PORT_PULL_UP   = PORT_PULL_UP_OFF;
    PortInit.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
    PortInit.PORT_PD_SHM    = PORT_PD_SHM_OFF;
    PortInit.PORT_PD        = PORT_PD_DRIVER;
    PortInit.PORT_GFEN      = PORT_GFEN_OFF;
    PortInit.PORT_FUNC      = PORT_FUNC_OVERRID;
    PortInit.PORT_SPEED     = PORT_SPEED_MAXFAST;
    PortInit.PORT_MODE      = PORT_MODE_DIGITAL;

    // Конфигурация 1 ножки порта PORTF как выхода (UART2_TX)
    PortInit.PORT_OE        = PORT_OE_OUT;
    PortInit.PORT_Pin       = PORT_Pin_1;
    PORT_Init(MDR_PORTF, &PortInit);

    // Конфигурация 0 ножки порта PORTF как входа (UART2_RX)
    PortInit.PORT_OE        = PORT_OE_IN;
    PortInit.PORT_Pin       = PORT_Pin_0;
    PORT_Init(MDR_PORTF, &PortInit);

    //Разрешение тактирования UART2
    RST_CLK_PCLKcmd(RST_CLK_PCLK_UART2, ENABLE);

    // Инициализация делителя тактовой частоты для UART2
    UART_BRGInit(MDR_UART2, UART_HCLKdiv1);

    // Разрешение прерывания для UART2
    NVIC_EnableIRQ(UART2_IRQn);

    // Заполнение полей для переменной UART_InitStructure
    UART_InitStructure.UART_BaudRate = 115200;

    //тактовая частота передачи данных
    UART_InitStructure.UART_WordLength = UART_WordLength8b; //длина символов 8 бит
    UART_InitStructure.UART_StopBits   = UART_StopBits1;    //1 стоп бит
    UART_InitStructure.UART_Parity     = UART_Parity_No;    // нет контроля четности
    UART_InitStructure.UART_FIFOMode   = UART_FIFO_OFF;     // выключение FIFO буфера

    // Аппаратный контроль за передачей и приемом
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;

    UART_Init (MDR_UART2, &UART_InitStructure);              //Инициализация UART2
    UART_ITConfig (MDR_UART2, UART_IT_RX, ENABLE);           //Разрешение прерывания по приему
    UART_ITConfig (MDR_UART2, UART_IT_TX, ENABLE);           //Разрешение прерывания по окончани передачи
    UART_Cmd(MDR_UART2, ENABLE);                             //Разрешение работы UART2

    while (1) {
        while (uart2_IT_RX_flag != SET);                     //Ждем пока не установиться флаг по приему байта
        uart2_IT_RX_flag = RESET;                            //Очищаем флаг приема

        ReciveByte = UART_ReceiveData (MDR_UART2);           //Считываем принятый байт
        UART_SendData (MDR_UART2, ReciveByte);               //Отправляем принятый байт обратно

        while (uart2_IT_TX_flag != SET);                     //Ждем пока байт уйдет
        uart2_IT_TX_flag = RESET;                            //Очищаем флаг передачи
    }
}

#if 0
Для инициализации UART в библиотеке предусмотрена структура
UART_InitTypeDef;
typedef struct
{
uint32_t UART_BaudRate;              Задается частота передачи данных
uint16_t UART_WordLength;            Задается число передаваемых бит данных
uint16_t UART_StopBits;              Задается число стоповых битов
uint16_t UART_Parity;                Задается контрольна четность или на нечетность
uint16_t UART_FIFOMode;              Задается режим работы FiFO буфера (включен или выключен)
uint16_t UART_HardwareFlowControl;   Разрешение аппаратного контроля за линиями интерфейса RS232C
}UART_InitTypeDef;
#endif
