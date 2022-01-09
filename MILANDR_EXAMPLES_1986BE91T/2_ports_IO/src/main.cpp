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
#if 0
Описание структуры, управляющей портом
typedef struct
{
    uint16_t PORT_Pin;                 Определяет какие ножки порта будут сконфигурированы
                                       например значение поля в двоичном коде 0b0000 0001 0000 0010
                                       конфигурирует 8 и 1 бит. Для задания значений можно
                                       воспользоваться стандартными битовыми масками PORT_Pin_x,
                                       которые записываются через побитовое ИЛИ: PORT_Pin_1|PORT_Pin_8.

PORT_OE_TypeDef PORT_OE;               Определяет режим работы порта: ввод или вывод.
                                       ввод                                PORT_OE_IN         (0)
                                       вывод                               PORT_OE_OUT -      (1)

PORT_PULL_UP_TypeDef PORT_PULL_UP;     Определяет включение верхнего подтягивающего резистора
                                       выключен                            PORT_PULL_UP_OFF   (0)
                                       включен                             PORT_PULL_UP_ON    (1)

PORT_PULL_DOWN_TypeDef PORT_PULL_DOWN; Определяет включение нижнего подтягивающего резистора
                                       выключен                            PORT_PULL_DOWN_OFF (0)
                                       включен                             PORT_PULL_DOWN_OFF (1)

PORT_PD_SHM_TypeDef PORT_PD_SHM; Определяет включение или выключение триггера Шмидта
                                 выключен  (гистерезис 200мВ)              PORT_PD_SHM_OFF    (0)
                                 включен   (гистерезис 400мВ)              PORT_PD_SHM_ON     (1)

PORT_PD_TypeDef   PORT_PD;       Определяет режим работы ножки.
                                 Управляемый драйвер                       PORT_PD_DRIVER     (0)
                                 Открытый сток                             PORT_PD_OPEN       (1)

PORT_GFEN_TypeDef PORT_GFEN;     Определяет режим работы входного фильтра ножки.
                                 Выключен                                  PORT_GFEN_OFF      (0)
                                 Включен                                   PORT_GFEN_ON       (1)

PORT_FUNC_TypeDef PORT_FUNC;     Определяет режим работы вывода порта:
                                 - Порт                                    PORT_FUNC_PORT     (0)
                                 - Основная функция                        PORT_FUNC_MAIN     (1)
                                 - Альтернативная функция                  PORT_FUNC_ALTER    (2)
                                 - Переопределенная функция                PORT_FUNC_OVERRID  (3)

PORT_SPEED_TypeDef PORT_SPEED;   Определяет скорость работы порта:
                                 зарезервировано (передатчик отключен)     PORT_OUTPUT_OFF    (0)
                                 медленный фронт (порядка 100 нс)          PORT_SPEED_SLOW    (1)
                                 быстрый фронт (порядка 20 нс)             PORT_SPEED_FAST    (2)
                                 максимально быстрый фронт (порядка 10 нс) PORT_SPEED_MAXFAST (3)

PORT_MODE_TypeDef PORT_MODE;     Определяет режим работы контроллера:
                                 аналоговый                                PORT_MODE_ANALOG  = 0x0
                                 цифровой                                  PORT_MODE_DIGITAL = 0x1
}PORT_InitTypeDef;
#endif
