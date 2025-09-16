/* USER CODE BEGIN Header */

#include <stdbool.h>
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
#define INT_1_Pin GPIO_PIN_0
#define INT_1_GPIO_Port GPIOB
#define ACOK_2_Pin GPIO_PIN_12
#define ACOK_2_GPIO_Port GPIOB
#define INT_2_Pin GPIO_PIN_13
#define INT_2_GPIO_Port GPIOB
#define USART3_CS_Pin GPIO_PIN_14
#define USART3_CS_GPIO_Port GPIOB
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

void test_EEPROM(uint16_t addr, const char * data);
void led_Test();
void all_led_OFF();
uint16_t read_MP2650_16(uint8_t regAddr);
void write_MP2650_16(uint8_t regAddr, uint16_t regValue);
void print_MP2650_16(uint8_t regAddr);
void print_byte(uint8_t byte);
void ext_print_16(uint8_t regAddr);
void print_Regs16();
void init_MP2650();
uint8_t read_MP2650_8(uint8_t regAddr);
void write_MP2650_8(uint8_t regAddr, uint8_t regValue);
void print_MP2650_8(uint8_t regAddr);
void print_Regs8();
void REG_00_set_Input_Current_Limit_1(u_int16_t);               //in mA
void REG_01_set_Input_Voltage_Limit(u_int16_t);                 //in mV
void REG_02_set_Charge_Current(u_int16_t);                      //in mA
void REG_03_set_PreCharge_Current(u_int16_t);                   //in mA
void REG_03_set_Termination_Current(u_int16_t);                 //in mA
void REG_04_set_Battery_Full_Voltage_for_one_Cell(u_int16_t);   //in mV
void REG_04_set_Battery_Threshold_for_one_Cell_100mV();
void REG_04_set_Battery_Threshold_for_one_Cell_200mV();
void REG_07_set_4_cells();
void REG_07_set_Pre_Charge_Threshold_for_one_Cell_3700mV();
void REG_08_BATTFET_EN(_Bool);
void REG_08_CHARGE_EN(_Bool);
void REG_08_SUSP_EN(_Bool);
void REG_08_NTC_GCOMP_SEL(_Bool);
void REG_08_OTG_set(_Bool);
void REG_09_EN_TERM_set(_Bool);
void REG_0A_NTC_WARM_set(_Bool);
void REG_0B_Reflect_batterycharge_current_set(_Bool val);
void REG_0C_VIRTUAL_DIODE_set(_Bool);
void REG_0F_set_Input_Current_Limit_2(u_int16_t);
void REG_2D_VBATT_LP_EN(_Bool);
void REG_30_set_VBATT_PRE_SEL();

uint8_t CMD_print_from_485();
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
