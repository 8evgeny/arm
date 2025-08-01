/* USER CODE BEGIN Header */

#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include <string.h>
#include "eeprom.h"
#include "MP2790_reg.h"
#include "i2c.h"
#define MP2790_I2C_ADDRESS          0x02
#define MP42790_I2C_ADDRESS         0x10

/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_gpio.h"

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
#define GPIO_2_Pin GPIO_PIN_7
#define GPIO_2_GPIO_Port GPIOB
#define IRQ_IN_Pin GPIO_PIN_0
#define IRQ_IN_GPIO_Port GPIOA
#define Enable_I2C_42790_Pin GPIO_PIN_1
#define Enable_I2C_42790_GPIO_Port GPIOA
#define UART_SEL_OUT_Pin GPIO_PIN_4
#define UART_SEL_OUT_GPIO_Port GPIOA
#define Enable_I2C_2790_Pin GPIO_PIN_5
#define Enable_I2C_2790_GPIO_Port GPIOA
#define One_Wire_Pin GPIO_PIN_6
#define One_Wire_GPIO_Port GPIOA
#define WDT_IN_Pin GPIO_PIN_7
#define WDT_IN_GPIO_Port GPIOA
#define XALERT_INT_Pin GPIO_PIN_8
#define XALERT_INT_GPIO_Port GPIOA
#define XALERT_INT_EXTI_IRQn EXTI4_15_IRQn
#define GPIO_1_Pin GPIO_PIN_3
#define GPIO_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

void Printf(const char* fmt, ...);

void init_2790();
void init_42790();
void disable_42790_REGS_CRC();
void enable_42790_REGS_CRC();
void read_2790_REGS();
void read_42790_REGS();
void read_Temp();

void read_U_I();
void print_byte(uint8_t byte);
void simpleTestI2C_EEPROM(uint16_t addr);
uint16_t read_MP2790(uint8_t regAddr);
void print_MP2790(uint8_t regAddr);
void write_MP2790(uint8_t regAddr, uint16_t regValue);
void pulse_SDA();
void disable_CRC();
void send_Address_Len_8(uint16_t regAddr);
void send_Address_Len_16(uint16_t regAddr);
void send_Address_Len_32(uint16_t regAddr);
void receive_Data_8(uint16_t regAddr);
void receive_Data_8_CRC(uint16_t regAddr, int8_t * pCRC_OK);
void receive_Data_16(uint16_t regAddr);
void receive_Data_16_CRC(uint16_t regAddr);
void receive_Data_32(uint16_t regAddr);
void receive_Data_32_CRC(uint16_t regAddr);
uint32_t crc32 (uint16_t Reg_Address, uint8_t len, uint8_t *data);
uint8_t read_MP42790_8_CRC(uint16_t regAddr);
void print_MP42790_8_CRC(uint16_t regAddr);
void write_MP42790_8_CRC(uint16_t regAddr, uint8_t value);
uint16_t read_MP42790_16_CRC(uint16_t regAddr);
void print_MP42790_16_CRC(uint16_t regAddr);
void write_MP42790_16_CRC(uint16_t regAddr, uint16_t value);
uint32_t read_MP42790_32_CRC(uint16_t regAddr);
void print_MP42790_32_CRC(uint16_t regAddr);
void write_MP42790_32_CRC(uint16_t regAddr, uint32_t value);
void test_write_42790();
//Команды 42790
void RST_CMD();             //Reset the fuel gauge. This is a self-clearing function
void EXE_CMD();             //Trigger a fuel gauge update refresh
void EDIT_CONFIG_CMD();     //The fuel gauge settings can be edited
void END_EDIT_CONFIG_CMD(); //The fuel gauge settings cannot be edited
void CONFIG_MODE_CMD();     //Enter configuration mode
void CONFIG_EXIT_CMD();     //Exit configuration mode. The new configuration is stored in the NVM
void CONFIG_RST_CMD();      //Reset the configuration. This is a self-clearing function
void LOG_RST_CMD();         //Re-initialize the lifetime log registers. This is a self-clearing function

int _write(int fd, char *str, int len);
void init_crc_calculation();
uint8_t crc_calc(uint8_t *data, uint8_t size);
void generateRandomString(char *str, int length);
void Printf(const char* fmt, ...);

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
