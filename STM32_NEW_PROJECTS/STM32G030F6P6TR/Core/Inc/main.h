/* USER CODE BEGIN Header */

#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include <string.h>
#include "eeprom.h"

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
//The CELLS_CTRL command controls the number of stacked cells in use
#define CELLS_CTRL          0x00
#define LOAD_CHARGER_CFG    0x09
//The ADC_CTRL command reports whether an error has occurred when starting the high-resolution voltage scan. It also controls the start of a high-resolution scan for all the selected channels
#define ADC_CTRL 0x99

//Voltage = Reading x 5000 / 32768 (mV)
#define RD_VCELL3           0x70
#define RD_VCELL4           0x72
#define RD_VCELL5           0x74
#define RD_VCELL6           0x76

//Current = Reading x 100 / 32768 / RSENSE (A)
#define RD_ICELL3           0x71
#define RD_ICELL4           0x73
#define RD_ICELL5           0x75
#define RD_ICELL6           0x77

//Temperature = Reading x 0.01481 - 269.12 (°C)
#define RD_TDIE 0x93

#define ACT_CFG 0x05
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO2_IN_Pin GPIO_PIN_7
#define GPIO2_IN_GPIO_Port GPIOB
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
#define XALERT_IN_Pin GPIO_PIN_8
#define XALERT_IN_GPIO_Port GPIOA
#define GPIO1_IN_Pin GPIO_PIN_3
#define GPIO1_IN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

void Printf(const char* fmt, ...);

void init_2790();
void disable_42790_REGS_CRC();
void enable_42790_REGS_CRC();
void read_2790_REGS();
void read_42790_REGS();
void read_Temp();
void set_ACT_CFG_reg_05(uint16_t value);
void read_U_I();
void print_byte(uint8_t byte);
void simpleTestI2C_EEPROM(uint16_t addr);
uint16_t read_MP2790(uint8_t regAddr);
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
void read_MP42790_8(uint16_t regAddr);
void read_MP42790_8_CRC(uint16_t regAddr);
void print_MP42790_8_CRC(uint16_t regAddr);
void write_MP42790_8_CRC(uint16_t regAddr, uint8_t value);
void read_MP42790_16(uint16_t regAddr);
void read_MP42790_16_CRC(uint16_t regAddr);
void print_MP42790_16_CRC(uint16_t regAddr);

void read_MP42790_32(uint16_t regAddr);
void read_MP42790_32_CRC(uint16_t regAddr);

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
