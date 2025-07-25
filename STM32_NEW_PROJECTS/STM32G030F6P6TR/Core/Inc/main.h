/* USER CODE BEGIN Header */

#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include <string.h>
#include "eeprom.h"

// Реальный 0x02
#define MP2790_I2C_ADDRESS          0x04
// Реальный 0x08
#define MP42790_I2C_ADDRESS         0x08

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32g0xx_ll_i2c.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_usart.h"
#include "stm32g0xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

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
#define GPIO2_IN_Pin LL_GPIO_PIN_7
#define GPIO2_IN_GPIO_Port GPIOB
#define IRQ_IN_Pin LL_GPIO_PIN_0
#define IRQ_IN_GPIO_Port GPIOA
#define CE_OUT_Pin LL_GPIO_PIN_1
#define CE_OUT_GPIO_Port GPIOA
#define UART_SEL_OUT_Pin LL_GPIO_PIN_4
#define UART_SEL_OUT_GPIO_Port GPIOA
#define NSHDN_IN_Pin LL_GPIO_PIN_5
#define NSHDN_IN_GPIO_Port GPIOA
#define One_Wire_Pin LL_GPIO_PIN_6
#define One_Wire_GPIO_Port GPIOA
#define WDT_IN_Pin LL_GPIO_PIN_7
#define WDT_IN_GPIO_Port GPIOA
#define XALERT_IN_Pin LL_GPIO_PIN_8
#define XALERT_IN_GPIO_Port GPIOA
#define GPIO1_IN_Pin LL_GPIO_PIN_3
#define GPIO1_IN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

void Printf(const char* fmt, ...);
void simpleTestI2C_EEPROM(uint16_t addr);
void read_MP2790(uint16_t regAddr);
void read_MP42790(uint16_t regAddr);
uint8_t crc_calc(uint8_t *data, uint8_t size);
void init_crc_calculation();
uint8_t crc8(uint16_t input);
void generateRandomString(char *str, int length);

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
