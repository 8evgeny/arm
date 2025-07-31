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
uint16_t U1,U2,U3,U4,I1,I2,I3,I4;
uint16_t Temperature;
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

    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_42790_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    init_2790();


//    simpleTestI2C_EEPROM(0x10);
//    read_42790_REGS();
//    read_2790_REGS();
    disable_42790_REGS_CRC();


    read_MP42790_16_CRC(0x72);
    read_MP42790_8_CRC(0x1001);
    read_MP42790_8_CRC(0x1100);
    read_MP42790_8_CRC(0x1204);
    read_MP42790_8_CRC(0x1205);
    read_MP42790_8_CRC(0x1206);
    read_MP42790_8_CRC(0x122F);

    enable_42790_REGS_CRC();

    read_MP42790_16_CRC(0x72);
    read_MP42790_8_CRC(0x1001);
    read_MP42790_8_CRC(0x1100);
    read_MP42790_8_CRC(0x1204);
    read_MP42790_8_CRC(0x1205);
    read_MP42790_8_CRC(0x1206);
    read_MP42790_8_CRC(0x122F);


  while (1)
  {
//    read_Temp();
//    read_U_I();


    HAL_Delay(3000);
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void init_2790()
{
    printf("\r\n------ init_2790 ------\r\n\n");
    write_MP2790(CELLS_CTRL, 0x0003);
    printf("init reg_CELLS_CTRL_00 \t\t0x%04X\r\n", read_MP2790(CELLS_CTRL));

    set_ACT_CFG_reg_05(0x0218);//on  3 4 bits
    printf("init reg_LOAD_CHARGER_CFG_09 \t0x%04X\r\n", read_MP2790(LOAD_CHARGER_CFG));



}

void disable_42790_REGS_CRC()
{
    printf("\r\n----- Disable CRC ------\r\n");
//    read_MP42790_8_CRC(0x4100);
    write_MP42790_8_CRC(0x4100,0x08);
//    read_MP42790_8_CRC(0x4100);
    printf("\r\n");
    HAL_Delay(50);
}

void enable_42790_REGS_CRC()
{
    printf("\r\n----- Enable CRC ------\r\n");
//    read_MP42790_8_CRC(0x4100);
    write_MP42790_8_CRC(0x4100,0x88);
//    read_MP42790_8_CRC(0x4100);
    printf("\r\n");
    HAL_Delay(50);
}

void read_2790_REGS()
{
    for (int i=0; i <= 0xB9; ++i)
    {
        read_MP2790(i);
        HAL_Delay(1);
    }
}
void read_42790_REGS()
{
    for (int i=0; i < 0x78; i+=2)
    {
        read_MP42790_16_CRC(i);
    }
    for (int i=0x200; i <= 0x023C; i+=4)
    {
        read_MP42790_32_CRC(i);
    }
    for (int i=0x280; i <= 0x02C0; i+=0xF)
    {
        read_MP42790_16_CRC(i);
    }
    for (int i=0x0564; i <= 0x058C; i+=1)
    {
        read_MP42790_8_CRC(i);
    }

    read_MP42790_16_CRC(0x058D);
    read_MP42790_16_CRC(0x0590);
    read_MP42790_16_CRC(0x0593);
    read_MP42790_16_CRC(0x0597);
    read_MP42790_16_CRC(0x059B);
    read_MP42790_16_CRC(0x059F);
    read_MP42790_16_CRC(0x05A3);
    read_MP42790_16_CRC(0x05A5);

    for (int i=0x05A8; i <= 0x05B7; i+=1)
    {
        read_MP42790_8_CRC(i);
    }
    for (int i=0x608; i <= 0x0648; i+=4)
    {
        read_MP42790_32_CRC(i);
    }
    for (int i=0x0C00; i <= 0x0C3E; i+=2)
    {
        read_MP42790_16_CRC(i);
    }
    for (int i=0x0C62; i <= 0x0C6A; i+=1)
    {
        read_MP42790_8_CRC(i);
    }
    read_MP42790_8_CRC(0x0C89);
    read_MP42790_8_CRC(0x1000);
    read_MP42790_8_CRC(0x1001);
    read_MP42790_8_CRC(0x1100);
    for (int i=0x1200; i <= 0x1206; i+=1)
    {
        read_MP42790_8_CRC(i);
    }
    for (int i=0x1207; i <= 0x122D; i+=2)
    {
        read_MP42790_16_CRC(i);
    }
    read_MP42790_8_CRC(0x122F);
    read_MP42790_16_CRC(0x1230);
    read_MP42790_8_CRC(0x1232);
    read_MP42790_16_CRC(0x1233);
    read_MP42790_8_CRC(0x1235);
    read_MP42790_16_CRC(0x1236);
    read_MP42790_8_CRC(0x1238);
    read_MP42790_16_CRC(0x1239);
    read_MP42790_8_CRC(0x123B);
    read_MP42790_16_CRC(0x123C);
    read_MP42790_8_CRC(0x123E);
    read_MP42790_16_CRC(0x1400);
    read_MP42790_16_CRC(0x1402);
    read_MP42790_8_CRC(0x1406);
    read_MP42790_16_CRC(0x1500);
    read_MP42790_16_CRC(0x1502);
    read_MP42790_16_CRC(0x1504);
    read_MP42790_8_CRC(0x1506);
    read_MP42790_8_CRC(0x150A);
    for (int i=0x1600; i <= 0x1605; i+=1)
    {
        read_MP42790_8_CRC(i);
    }
    for (int i=0x1700; i <= 0x1704; i+=1)
    {
        read_MP42790_8_CRC(i);
    }
    for (int i=0x1800; i <= 0x1806; i+=1)
    {
        read_MP42790_8_CRC(i);
    }
    read_MP42790_8_CRC(0x4000);
    read_MP42790_8_CRC(0x4100);
}
void read_Temp()
{
    write_MP2790(ADC_CTRL, 0x0001);
    while((read_MP2790(ADC_CTRL) & 0x0002) != 0x0002);
    Temperature = read_MP2790(RD_TDIE);
    printf("T=%04X\r\n",Temperature);
}

void set_ACT_CFG_reg_05(uint16_t value)
{
    write_MP2790(ADC_CTRL, 0x0001);
    while((read_MP2790(ADC_CTRL) & 0x0002) != 0x0002);
    write_MP2790(ACT_CFG, value);
    printf("init reg_ACT_CFG_05  \t\t0x%04X\r\n", read_MP2790(ACT_CFG));
}

void read_U_I()
{
    write_MP2790(ADC_CTRL, 0x0001);
    while((read_MP2790(ADC_CTRL) & 0x0002) != 0x0002);
    U1 = read_MP2790(RD_VCELL3);
    U2 = read_MP2790(RD_VCELL4);
    U3 = read_MP2790(RD_VCELL5);
    U4 = read_MP2790(RD_VCELL6);
    I1 = read_MP2790(RD_ICELL3);
    I2 = read_MP2790(RD_ICELL4);
    I3 = read_MP2790(RD_ICELL5);
    I4 = read_MP2790(RD_ICELL6);
    printf("U1=%04X I1=%04X\r\n",U1,I1);
    printf("U2=%04X I2=%04X\r\n",U2,I2);
    printf("U3=%04X I3=%04X\r\n",U3,I3);
    printf("U4=%04X I4=%04X\r\n",U4,I4);
    printf("\r\n");
}

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

uint16_t read_MP2790(uint8_t regAddr)
{
    union
    {
        uint8_t reg_value[2];
        uint16_t regValue;
    }data;
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_SET);
//    HAL_Delay(1);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Read(&hi2c2, MP2790_I2C_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, data.reg_value, 2, HAL_MAX_DELAY);
//    printf("MP2790 register 0x%02X - %04X   ", regAddr, data.regValue);
//    print_byte(data.reg_value[1]);
//    printf(" ");
//    print_byte(data.reg_value[0]);
//    printf("\r\n");
//    delayUS_ASM(10);

    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_RESET);
    return data.regValue;
}

void write_MP2790(uint8_t regAddr, uint16_t regValue)
{
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c2, MP2790_I2C_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&regValue, 2, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(GPIOA, UART_SEL_OUT_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, Enable_I2C_2790_Pin, GPIO_PIN_RESET);
}

void pulse_SDA()
{
    HAL_I2C_DeInit(&hi2c2);
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);

    /*Configure GPIO pins : GPIO2_IN_Pin GPIO1_IN_Pin */
    GPIO_InitStruct.Pin = GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
    HAL_Delay(5);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
//    delayUS_ASM(1);
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12);
    MX_I2C2_Init();
}

void disable_CRC()
{
    uint8_t DisableCRC[8] = {0x00, 0x41, 0x01, 0x08, 0x94, 0xA0, 0xDE, 0xDD};
//    uint8_t DisableCRC[8] = {0x00, 0x41, 0x01, 0x08, 0xA1, 0x2D, 0xE5, 0x17};
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, DisableCRC, 8, HAL_MAX_DELAY);
}

void send_Address_Len_8(uint16_t regAddr)
{
    union
    {
        uint32_t regAddressLentch;
        uint8_t tmp[4];
    }dataWrite;
    uint8_t toWrite[3];
    dataWrite.regAddressLentch = 0;
    dataWrite.regAddressLentch |= regAddr<<16;
    dataWrite.regAddressLentch |= 0x00000100;
//    printf("regAddressLentch 0x%02X%02X%02X%02X \r\n", dataWrite.tmp[3],  dataWrite.tmp[2], dataWrite.tmp[1], dataWrite.tmp[0]);

    toWrite[0] = dataWrite.tmp[2];
    toWrite[1] = dataWrite.tmp[3];
    toWrite[2] = dataWrite.tmp[1];

    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 3, HAL_MAX_DELAY);
}

void send_Address_Len_16(uint16_t regAddr)
{
    union
    {
        uint32_t regAddressLentch;
        uint8_t tmp[4];
    }dataWrite;
    uint8_t toWrite[3];
    dataWrite.regAddressLentch = 0;
    dataWrite.regAddressLentch |= regAddr<<16;
    dataWrite.regAddressLentch |= 0x00000200;
//    printf("regAddressLentch 0x%02X%02X%02X%02X \r\n", dataWrite.tmp[3],  dataWrite.tmp[2], dataWrite.tmp[1], dataWrite.tmp[0]);

    toWrite[0] = dataWrite.tmp[2];
    toWrite[1] = dataWrite.tmp[3];
    toWrite[2] = dataWrite.tmp[1];

    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 3, HAL_MAX_DELAY);
}

void send_Address_Len_32(uint16_t regAddr)
{
    union
    {
        uint32_t regAddressLentch;
        uint8_t tmp[4];
    }dataWrite;
    uint8_t toWrite[3];
    dataWrite.regAddressLentch = 0;
    dataWrite.regAddressLentch |= regAddr<<16;
    dataWrite.regAddressLentch |= 0x00000400;
//    printf("regAddressLentch 0x%02X%02X%02X%02X \r\n", dataWrite.tmp[3],  dataWrite.tmp[2], dataWrite.tmp[1], dataWrite.tmp[0]);

    toWrite[0] = dataWrite.tmp[2];
    toWrite[1] = dataWrite.tmp[3];
    toWrite[2] = dataWrite.tmp[1];

    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 3, HAL_MAX_DELAY);
}

void receive_Data_8(uint16_t regAddr)
{
    uint8_t toRead8[1];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead8, 1, HAL_MAX_DELAY);
    printf("reg 0x%04X data - 0x%02X\r\n", regAddr,toRead8[0]);
}

uint8_t receive_Data_8_CRC(uint16_t regAddr, int8_t * pCRC_OK)
{
    uint8_t toRead8CRC[5];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead8CRC, 5, HAL_MAX_DELAY);
    uint32_t sum = crc32(regAddr, 1, toRead8CRC);
    printf("reg 0x%04X data - 0x%02X \t\tCRC - %02X%02X%02X%02X \tcalcCRC - %08lX\r\n",
    regAddr, toRead8CRC[0], toRead8CRC[4], toRead8CRC[3], toRead8CRC[2], toRead8CRC[1], (unsigned long)sum);

    return toRead8CRC[0];
}

void receive_Data_16(uint16_t regAddr)
{
    uint8_t toRead16[2];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead16, 2, HAL_MAX_DELAY);
    printf("reg 0x%04X data - 0x%02X%02X\r\n", regAddr,toRead16[1],toRead16[0]);
}

void receive_Data_16_CRC(uint16_t regAddr)
{
    uint8_t toRead16CRC[6];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead16CRC, 6, HAL_MAX_DELAY);
    uint32_t sum = crc32(regAddr, 2, toRead16CRC);
    printf("reg 0x%04X data - 0x%02X%02X \tCRC - %02X%02X%02X%02X \tcalcCRC - %08lX\r\n",
    regAddr, toRead16CRC[0], toRead16CRC[1], toRead16CRC[5], toRead16CRC[4], toRead16CRC[3], toRead16CRC[2], (unsigned long)sum);
}

void receive_Data_32(uint16_t regAddr)
{
    uint8_t toRead[4];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead, 4, HAL_MAX_DELAY);
    printf("reg 0x%04X data - 0x%02X%02X%02X%02X\r\n", regAddr,toRead[3],toRead[2],toRead[1],toRead[0]);
}

void receive_Data_32_CRC(uint16_t regAddr)
{
    uint8_t toRead32CRC[8];
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Receive(&hi2c2, MP42790_I2C_ADDRESS, toRead32CRC, 8, HAL_MAX_DELAY);
    uint32_t sum = crc32(regAddr, 4, toRead32CRC);
    printf("reg 0x%04X data - 0x%02X%02X%02X%02X \tCRC - %02X%02X%02X%02X \tcalcCRC - %08lX\r\n",
        regAddr, toRead32CRC[0], toRead32CRC[1], toRead32CRC[2], toRead32CRC[3],
        toRead32CRC[7], toRead32CRC[6], toRead32CRC[5], toRead32CRC[4], (unsigned long)sum);
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

void read_MP42790_8(uint16_t regAddr)
{
    HAL_Delay(10);
    pulse_SDA();
    send_Address_Len_8(regAddr);
    receive_Data_8(regAddr);
}

uint8_t read_MP42790_8_CRC(uint16_t regAddr)
{
    HAL_Delay(10);
    pulse_SDA();
    send_Address_Len_8(regAddr);
    int8_t CRC_OK = -1;
    int8_t * pCRC_OK = &CRC_OK;
    return receive_Data_8_CRC(regAddr, pCRC_OK);
}

void write_MP42790_8_CRC(uint16_t regAddr, uint8_t value)
{
    uint8_t toWrite[8];
    HAL_Delay(10);
    pulse_SDA();
    union
    {
        uint32_t toSend1;
        uint8_t tmp1[4];
    }dataWrite1;
    union
    {
        uint32_t toSend2;
        uint8_t tmp2[4];
    }dataWrite2;

    dataWrite1.toSend1 = 0;
    dataWrite1.toSend1 |= regAddr<<16;
    dataWrite1.toSend1 |= 0x00000100;
    dataWrite1.toSend1 |= value;

    dataWrite2.toSend2 = crc32(regAddr, 1, &value);

    toWrite[0] = dataWrite1.tmp1[2];  //младший адреса
    toWrite[1] = dataWrite1.tmp1[3];  //старший адреса
    toWrite[2] = dataWrite1.tmp1[1];  //длина - 1
    toWrite[3] = dataWrite1.tmp1[0];  //value
    toWrite[4] = dataWrite2.tmp2[0];  //младший CRC
    toWrite[5] = dataWrite2.tmp2[1];
    toWrite[6] = dataWrite2.tmp2[2];
    toWrite[7] = dataWrite2.tmp2[3];  //старший CRC

//    printf("toSend - %02X%02X%02X%02X%02X%02X%02X%02X \r\n", toWrite[0], toWrite[1], toWrite[2], toWrite[3], toWrite[4], toWrite[5],  toWrite[6], toWrite[7]);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Master_Transmit(&hi2c2, MP42790_I2C_ADDRESS, toWrite, 8, HAL_MAX_DELAY);
}

void read_MP42790_16(uint16_t regAddr)
{
    HAL_Delay(10);
    pulse_SDA();
    send_Address_Len_16(regAddr);
    receive_Data_16(regAddr);
}

void read_MP42790_16_CRC(uint16_t regAddr)
{
    HAL_Delay(60);
    pulse_SDA();
    send_Address_Len_16(regAddr);
    receive_Data_16_CRC(regAddr);
}

void read_MP42790_32(uint16_t regAddr)
{
    HAL_Delay(10);
    pulse_SDA();
    send_Address_Len_32(regAddr);
    receive_Data_32(regAddr);
}

void read_MP42790_32_CRC(uint16_t regAddr)
{
    HAL_Delay(10);
    pulse_SDA();
    send_Address_Len_32(regAddr);
    receive_Data_32_CRC(regAddr);
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
