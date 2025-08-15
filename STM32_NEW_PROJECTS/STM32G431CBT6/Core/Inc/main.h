/* USER CODE BEGIN Header */

#include "eeprom.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "MP2650_reg.h"

//#define MP2650_ADDRESS 0x5C  //7bit address
#define MP2650_ADDRESS 0xB8    //8bit address

#define delayUS_ASM(us) do {                           \
asm volatile ("MOV R0,%[loops]\n                       \
              1: \n                                    \
              SUB R0, #1\n                             \
              CMP R0, #0\n                             \
              BNE 1b \t"                               \
              : : [loops] "r" (40*us) : "memory"       \
              );                                       \
} while(0)

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Power_GOOD_Pin GPIO_PIN_13
#define Power_GOOD_GPIO_Port GPIOC
#define ACOK_1_Pin GPIO_PIN_0
#define ACOK_1_GPIO_Port GPIOA
#define USART2_CS_Pin GPIO_PIN_1
#define USART2_CS_GPIO_Port GPIOA
#define ADC_IAM_1_Pin GPIO_PIN_4
#define ADC_IAM_1_GPIO_Port GPIOA
#define ADC_IBM_1_Pin GPIO_PIN_5
#define ADC_IBM_1_GPIO_Port GPIOA
#define ADC_IAM_2_Pin GPIO_PIN_6
#define ADC_IAM_2_GPIO_Port GPIOA
#define ADC_IBM_2_Pin GPIO_PIN_7
#define ADC_IBM_2_GPIO_Port GPIOA
#define INT_1_Pin GPIO_PIN_0
#define INT_1_GPIO_Port GPIOB
#define PROCHOT_1_Pin GPIO_PIN_1
#define PROCHOT_1_GPIO_Port GPIOB
#define ADC_PSYS_1_Pin GPIO_PIN_2
#define ADC_PSYS_1_GPIO_Port GPIOB
#define ACOK_2_Pin GPIO_PIN_12
#define ACOK_2_GPIO_Port GPIOB
#define INT_2_Pin GPIO_PIN_13
#define INT_2_GPIO_Port GPIOB
#define USART3_CS_Pin GPIO_PIN_14
#define USART3_CS_GPIO_Port GPIOB
#define PROCHOT_2_Pin GPIO_PIN_10
#define PROCHOT_2_GPIO_Port GPIOA
#define Blue_LED_Pin GPIO_PIN_3
#define Blue_LED_GPIO_Port GPIOB
#define Red_LED_Pin GPIO_PIN_5
#define Red_LED_GPIO_Port GPIOB
#define Green_LED_Pin GPIO_PIN_6
#define Green_LED_GPIO_Port GPIOB
#define Yellow_LED_Pin GPIO_PIN_9
#define Yellow_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define GPIO_ON(x) HAL_GPIO_WritePin(GPIOB, x, GPIO_PIN_RESET)
#define GPIO_OFF(x) HAL_GPIO_WritePin(GPIOB, x, GPIO_PIN_SET)

void simpleTestI2C_EEPROM(uint16_t addr);
void led_Test();
void all_led_OFF();
uint16_t read_MP2650_16(uint8_t regAddr);
void write_MP2650_16(uint8_t regAddr, uint16_t regValue);
void print_MP2650_16(uint8_t regAddr);
void print_byte(uint8_t byte);
void print_Regs16();

uint8_t read_MP2650_8(uint8_t regAddr);
void write_MP2650_8(uint8_t regAddr, uint8_t regValue);
void print_MP2650_8(uint8_t regAddr);
void print_Regs8();

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
