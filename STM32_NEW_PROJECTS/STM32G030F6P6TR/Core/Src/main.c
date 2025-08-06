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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == XALERT_INT_Pin)
  {
    printf("\r\n========== xALERT ===========\r\n");
  } else
  {
      printf("\r\nEXTI ERROR\r\n");
  }
}

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
  HAL_Init();

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

//    HAL_GPIO_WritePin(GPIOA, Enable_I2sC_2790_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_42790_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_RESET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
#if 0
Пишутся регистры 4000 4001 4002 4100
Для записи групп Fuel Gauge Settings Fuel Gauge Model (0x1000 - 0x1806) (0x2000 - 0x2043) подать команду CONFIG_MODE_CMD();


#endif
//    simpleTestI2C_EEPROM(0x10);
    init_2790();
//    HAL_Delay(1000);
//    init_2790();
//    init_42790();
//    read_2790_REGS();

    getV_PACKandV_TOP();

    read_Temp();
    read_U_I();
    HAL_Delay(1000);
    read_Temp();
    HAL_Delay(1000);
    read_Temp();

  while (1)
  {
//    read_Temp();
//    read_U_I();
//    printf("get RD_VA1P8\r\n");
//    print_MP2790(RD_VA1P8);
//    printf("get RD_VA3P3\r\n");
//    print_MP2790(RD_VA3P3);
//    printf("\r\n");

    HAL_Delay(4000);



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
  /* HSI configuration and activation */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Sysclk activation on the HSI */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(16000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

const char *bit_rep[16] =
{
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};
void print_byte(uint8_t byte)
{
    printf("%s%s", bit_rep[byte >> 4], bit_rep[byte & 0x0F]);
}
void simpleTestI2C_EEPROM(uint16_t addr)
{
// Пишет по 8 байт в адреса кратные 8 Читать может больше
    uint16_t num = 8;
    printf("Simple test I2C_EEPROM ...\r\n");

    uint8_t rd_value[20] = {0};
//    uint8_t wr_value[20] = {'1','2','3','4','5','6','7','8'};
    uint8_t wr_value[20] = {'=','=','=','1','2','=','=','='};

    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Read(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, rd_value, num, HAL_MAX_DELAY);
    printf("EEPROM read: %s\r\n",rd_value);

    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, wr_value, num, HAL_MAX_DELAY);
    printf("EEPROM write: %s\r\n", wr_value);

    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Read(&hi2c2, EEPROM_I2C_ADDRESS, addr, I2C_MEMADD_SIZE_8BIT, rd_value, num, HAL_MAX_DELAY);
    printf("EEPROM read: %s\r\n",rd_value);
}
uint32_t crc32 (uint16_t Reg_Address, uint8_t len, uint8_t *data)
{
    short i;
    uint32_t crc = 0xFFFFFFFF;
    unsigned char dataTemp[4];
    for (i=-1; i<len; i++)
    {
        if(i==-1)
        {
            dataTemp[0]=len;
            dataTemp[1]=Reg_Address&0x00FF;
            dataTemp[2]=(Reg_Address&0xFF00)>>8;
            dataTemp[3]=0;
        }
        else
        {
            dataTemp[i%4]=data[i];
        }
        if((i%4)==3 || i == len-1 || i == -1)
        {
            for (char j=0; j<4; j++)
            {
                crc ^= dataTemp[3-j] << 24;
                for (char k = 0; k < 8; ++k)
                {
                    if ((crc & 0x80000000) != 0)
                    {
                        crc = (crc << 1) ^ 0x04C11DB7;
                    }
                    else
                    {
                        crc <<= 1;
                    }
                }
            }
            dataTemp[0]=0;
            dataTemp[1]=0;
            dataTemp[2]=0;
            dataTemp[3]=0;
        }
    }
    return crc;
}
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
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_SET);
    char buff[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buff, sizeof(buff), fmt, args);
    HAL_UART_Transmit(&huart2, (uint8_t*)buff, strlen(buff), HAL_MAX_DELAY );
    va_end(args);
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_RESET);
}
int _write(int fd, char *str, int len)
{
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_SET);
    for(int i=0; i<len; i++)
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)&str[i], 1, 0xFFFF);
        SEGGER_RTT_PutChar(0, str[i]);
    }
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_RESET);
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
