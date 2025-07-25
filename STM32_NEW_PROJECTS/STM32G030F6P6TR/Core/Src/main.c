/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define CRC_TABLE_SIZE 256
uint8_t _CRC8Table[CRC_TABLE_SIZE];
uint32_t _poly_width = 8;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
// CRC   https://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
    SEGGER_RTT_Init();
    SEGGER_RTT_printf(0, "SEGGER RTT Initialized\n");
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, 3);

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */

    init_crc_calculation();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//    simpleTestI2C_EEPROM(0x10);

//    for (int i=0; i < 144; ++i)
//    {
//        uint8_t reg_number = i;
//        uint8_t * pRreg_number = &reg_number;
//        read_MP2790(pRreg_number);
//    }


//    read_MP2790(0x10);
    read_MP42790(0x10);



  while (1)
  {
//    HAL_GPIO_WritePin(GPIOA, CE_OUT_Pin, GPIO_PIN_SET);           //8pin
    Printf("CE_OUT_Pin_SET\r\n");
//    HAL_Delay(10000);
//    HAL_GPIO_WritePin(GPIOA, CE_OUT_Pin, GPIO_PIN_RESET);
    Printf("CE_OUT_Pin_RESET\r\n");
//    HAL_Delay(10000);





//HAL_I2C_Mem_Write(hi2c2, DevAddress, RegAddress, )
//HAL_I2C_IsDeviceReady
//HAL_I2C_Master_Transmit
//HAL_I2C_Master_Receive
//HAL_I2C_Master_Seq_Transmit_IT



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
  while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_1)
  {
  }

  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLLM_DIV_1, 12, LL_RCC_PLLR_DIV_6);
  LL_RCC_PLL_Enable();
  LL_RCC_PLL_EnableDomain_SYS();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the main PLL */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

  LL_Init1msTick(32000000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(32000000);
}

/* USER CODE BEGIN 4 */
void init_crc_calculation()
{
    uint8_t poly = 0x31;
    const uint32_t bits_mask = (1 << _poly_width) - 1;
    const uint32_t top_bit = 1 << (_poly_width - 1);
    uint32_t index;
    for (index = 0; index < CRC_TABLE_SIZE; ++index)
    {
        uint32_t value = index << (_poly_width - 8);
        uint32_t bit_index;
        for (bit_index = 0; bit_index < 8; ++bit_index)
        {
            if (value & top_bit)
            {
                value = (value << 1) ^ poly;
            }
            else
            {
                value = value << 1;
            }
            value &= bits_mask;
        }//END for (bit_index = 0; bit_index < 8; ++bit_index)
        _CRC8Table[index] = value;
    }//END for (index = 0; index < CRC_TABLE_SIZE; ++index)
}

uint8_t crc_calc(uint8_t *data, uint8_t size)
{
    uint8_t init_value = 0xFF;
    uint8_t crc = init_value;
    while (size--)
    {
        crc = _CRC8Table[crc ^ *data++];
    }
    return crc;
}

uint8_t crc8(uint16_t input)
{
    uint8_t crc[8] = { };
    uint8_t i;
    uint8_t inv;
    uint8_t output = 0;

    for(i = 0; i < 16; i++)
    {
        inv = ((((input >> i) & 1) ^ crc[7]) & 1);

        crc[7] = (crc[6] & 1);
        crc[6] = (crc[5] & 1);
        crc[5] = (crc[4] ^ inv & 1);
        crc[4] = (crc[3] ^ inv & 1);
        crc[3] = (crc[2] & 1);
        crc[2] = (crc[1] & 1);
        crc[1] = (crc[0] & 1);
        crc[0] = (inv & 1);
    }

    for(i = 0; i < 8; i++){
        output |= ((crc[i] << i) & (1 << i));
    }


    return output;
}

void generateRandomString(char *str, int length)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charset_size = strlen(charset);
    if (length <= 0)
    {
        str[0] = '\0'; // Empty string for length 0 or less
        return;
    }
    for (int i = 0; i < length; i++)
    {
        str[i] = charset[rand() % charset_size];
    }
    str[length] = '\0'; // Null-terminate the string
}

void Printf(const char* fmt, ...)
{
//    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_SET);
//    char buff[512];
//    va_list args;
//    va_start(args, fmt);
//    vsnprintf(buff, sizeof(buff), fmt, args);
//    HAL_UART_Transmit(&huart2, (uint8_t*)buff, strlen(buff), HAL_MAX_DELAY );
//    va_end(args);
//    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_RESET);
}

void simpleTestI2C_EEPROM(uint16_t addr)
{
// Пишет по 8 байт в адреса кратные 8 Читать может больше
    uint16_t num = 8;
    printf("Simple test I2C_EEPROM ...\r\n");

    uint8_t rd_value[20] = {0};
    uint8_t wr_value[20] = {'1','2','3','4','5','6','7','8'};
//    uint8_t wr_value[20] = {'=','=','=','1','2','=','=','='};

//    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
//    HAL_I2C_Mem_Read(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, rd_value, num, HAL_MAX_DELAY);
//    printf("EEPROM read: %s\r\n",rd_value);

//    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
//    HAL_I2C_Mem_Write(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, wr_value, num, HAL_MAX_DELAY);
//    printf("EEPROM write: %s\r\n", wr_value);

//    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
//    HAL_I2C_Mem_Read(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, rd_value, num, HAL_MAX_DELAY);
//    printf("EEPROM read: %s\r\n",rd_value);
}

void read_MP2790(uint16_t regAddr)
{
//    uint8_t reg_value[10] = {0};
//    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
//    HAL_I2C_Mem_Read(&hi2c2, MP2790_I2C_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, reg_value, 2, HAL_MAX_DELAY);
//    printf("MP2790 read: %s\r\n", reg_value);
//delayUS_ASM(10);

}

void read_MP42790(uint16_t regAddr)
{
//    uint8_t reg_value[10] = {0};
//    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
//    HAL_I2C_Mem_Read(&hi2c2, MP42790_I2C_ADDRESS, regAddr, I2C_MEMADD_SIZE_16BIT, reg_value, 8, HAL_MAX_DELAY);
//    printf("MP42790 read: %s\r\n", reg_value);
//delayUS_ASM(10);
}



int _write(int fd, char *str, int len)
{
    for(int i=0; i<len; i++)
    {
//        HAL_UART_Transmit(&huart2, (uint8_t *)&str[i], 1, 0xFFFF);
        SEGGER_RTT_PutChar(0, str[i]);
    }
    return len;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
