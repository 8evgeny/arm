/* USER CODE BEGIN Header */

/*
EEPROM I2C : Microchip (AT24CS01)
1‑Kbit (128 x 8) 000 - 3FF
128-Bit Unique Factory-Programmed Serial Number

8 pages of 128-bites each
000 - 07F   128b
080 - 0FF   128b
100 - 17F   128b
180 - 1FF   128b
200 - 27F   128b
280 - 2FF   128b
300 - 37F   128b
380 - 3FF   128b
*/

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO2_IN_Pin GPIO_PIN_7
#define GPIO2_IN_GPIO_Port GPIOB
#define IRQ_IN_Pin GPIO_PIN_0
#define IRQ_IN_GPIO_Port GPIOA
#define CE_OUT_Pin GPIO_PIN_1
#define CE_OUT_GPIO_Port GPIOA
#define UART_SEL_OUT_Pin GPIO_PIN_4
#define UART_SEL_OUT_GPIO_Port GPIOA
#define NSHDN_IN_Pin GPIO_PIN_5
#define NSHDN_IN_GPIO_Port GPIOA
#define One_Wire_Pin GPIO_PIN_6
#define One_Wire_GPIO_Port GPIOA
#define WDT_IN_Pin GPIO_PIN_7
#define WDT_IN_GPIO_Port GPIOA
#define XALERT_IN_Pin GPIO_PIN_8
#define XALERT_IN_GPIO_Port GPIOA
#define GPIO1_IN_Pin GPIO_PIN_3
#define GPIO1_IN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
void Printf(const char* fmt, ...);
void simpleTestI2C_EEPROM(uint16_t addr);
#define delayUS_ASM(us) do {                           \
asm volatile ("MOV R0,%[loops]\n                       \
              1: \n                                    \
              SUB R0, #1\n                             \
              CMP R0, #0\n                             \
              BNE 1b \t"                               \
              : : [loops] "r" (34*us) : "memory"       \
              );                                       \
} while(0)


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
