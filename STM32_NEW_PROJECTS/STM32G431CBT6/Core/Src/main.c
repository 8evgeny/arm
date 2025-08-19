/* USER CODE BEGIN Header */

/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

const char *bit_rep[16] =
{
    [ 0] = "0000", [ 1] = "0001", [ 2] = "0010", [ 3] = "0011",
    [ 4] = "0100", [ 5] = "0101", [ 6] = "0110", [ 7] = "0111",
    [ 8] = "1000", [ 9] = "1001", [10] = "1010", [11] = "1011",
    [12] = "1100", [13] = "1101", [14] = "1110", [15] = "1111",
};

typedef struct _data16
{
    union
    {
        uint16_t value;
        uint8_t val[2];
    }value;
}data_16;
data_16 data16; //2650

typedef struct _data8
{
    uint8_t value;
}data_8;

data_16 data16;
data_8 data8;


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
ADC_HandleTypeDef hadc2;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

PCD_HandleTypeDef hpcd_USB_FS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC2_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_USB_PCD_Init(void);
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
  MX_ADC2_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_USB_PCD_Init();
  /* USER CODE BEGIN 2 */

    SEGGER_RTT_Init();
    SEGGER_RTT_printf(0, "\nSEGGER RTT Initialized\r\n\n");

    all_led_OFF();
//    simpleTestI2C_EEPROM(0x00);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

    REG_00_set_Input_Current_Limit(1500);               //1500 mA default
    REG_01_set_Input_Voltage_Limit(4500);               //4,5V default
    REG_02_set_Charge_Current(300);                     //1000 mA default
    REG_03_set_PreCharge_Current(180);                  //180 mA default  Range: 180 - 840 mA
    REG_03_set_Termination_Current(200);                //200 mA default  Range: 0mA to 1500mA
    REG_04_set_Battery_Full_Voltage_for_one_Cell(4200); //Default: 4.2V/cell Range: 3.7125V/cell to 4.5V/cell
    REG_04_set_Battery_Threshold_for_one_Cell_100mV();



    set_4_battery();
    disable_BATTFET();
//    enable_BATTFET();
    disable_CHARGE();
//    enable_CHARGE();
    disable_NTC_GCOMP_SEL();
//    enable_NTC_GCOMP_SEL();
//    disable_Battery_Voltage_Loop();
//    enable_Battery_Voltage_Loop();

    print_Regs8();
    print_Regs16();


  while (1)
  {
      led_Test();

//      if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ACOK_1_GPIO_Port, ACOK_1_Pin))
//      {
//          printf("ACOK_1_Pin SET\r\n");
//      }
//      if (GPIO_PIN_SET == HAL_GPIO_ReadPin(ACOK_2_GPIO_Port, ACOK_2_Pin))
//      {
//          printf("ACOK_2_Pin SET\r\n");
//      }
//      if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(INT_1_GPIO_Port, INT_1_Pin))
//      {
//          printf("INT_1_Pin RESET\r\n");
//      }
//      if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(INT_2_GPIO_Port, INT_2_Pin))
//      {
//          printf("INT_2_Pin RESET\r\n");
//      }
//      if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(PROCHOT_1_GPIO_Port, PROCHOT_1_Pin))
//      {
//          printf("PROCHOT_1_Pin RESET\r\n");
//      }
//      if (GPIO_PIN_RESET == HAL_GPIO_ReadPin(PROCHOT_2_GPIO_Port, PROCHOT_2_Pin))
//      {
//          printf("PROCHOT_2_Pin RESET\r\n");
//      }





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
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 12;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV4;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */

  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc2.Init.Resolution = ADC_RESOLUTION_12B;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.GainCompensation = 0;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc2.Init.LowPowerAutoWait = DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.NbrOfConversion = 1;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc2.Init.DMAContinuousRequests = DISABLE;
  hadc2.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  hadc2.Init.OversamplingMode = DISABLE;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
  sConfig.SingleDiff = ADC_DIFFERENTIAL_ENDED;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
  sConfig.Offset = 0;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00201D2B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x00201D2B;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USART2_CS_GPIO_Port, USART2_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PROCHOT_1_Pin|Blue_LED_Pin|Red_LED_Pin|Green_LED_Pin
                          |Yellow_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USART3_CS_GPIO_Port, USART3_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PROCHOT_2_GPIO_Port, PROCHOT_2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : Power_GOOD_Pin */
  GPIO_InitStruct.Pin = Power_GOOD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Power_GOOD_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ACOK_1_Pin */
  GPIO_InitStruct.Pin = ACOK_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ACOK_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : USART2_CS_Pin PROCHOT_2_Pin */
  GPIO_InitStruct.Pin = USART2_CS_Pin|PROCHOT_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : INT_1_Pin ACOK_2_Pin INT_2_Pin */
  GPIO_InitStruct.Pin = INT_1_Pin|ACOK_2_Pin|INT_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PROCHOT_1_Pin USART3_CS_Pin Blue_LED_Pin Red_LED_Pin
                           Green_LED_Pin Yellow_LED_Pin */
  GPIO_InitStruct.Pin = PROCHOT_1_Pin|USART3_CS_Pin|Blue_LED_Pin|Red_LED_Pin
                          |Green_LED_Pin|Yellow_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void all_led_OFF()
{
    GPIO_OFF(Blue_LED_Pin);
    GPIO_OFF(Red_LED_Pin);
    GPIO_OFF(Green_LED_Pin);
    GPIO_OFF(Yellow_LED_Pin);
}
int _write(int fd, char *str, int len)
{
    HAL_GPIO_WritePin(USART2_CS_GPIO_Port, USART2_CS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(USART3_CS_GPIO_Port, USART3_CS_Pin, GPIO_PIN_SET);
    for(int i=0; i<len; ++i)
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)&str[i], 1, 0xFFFF);
        HAL_UART_Transmit(&huart3, (uint8_t *)&str[i], 1, 0xFFFF);
        SEGGER_RTT_PutChar(0, str[i]);
//        delayUS_ASM(30);
    }
    HAL_GPIO_WritePin(USART2_CS_GPIO_Port, USART2_CS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(USART3_CS_GPIO_Port, USART3_CS_Pin, GPIO_PIN_RESET);
    return len;
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

void led_Test()
{
    GPIO_ON(Blue_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Blue_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Red_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Red_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Green_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Green_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Yellow_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Yellow_LED_Pin);

    HAL_Delay(500);

    GPIO_ON(Yellow_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Yellow_LED_Pin);
    GPIO_ON(Green_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Green_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Red_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Red_LED_Pin);
    HAL_Delay(30);
    GPIO_ON(Blue_LED_Pin);
    HAL_Delay(30);
    GPIO_OFF(Blue_LED_Pin);

    HAL_Delay(500);
}

uint16_t read_MP2650_16(uint8_t regAddr)
{
    data16.value.value = 0xFFFF;
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_StatusTypeDef ret;
    ret = HAL_I2C_Mem_Read(&hi2c2, MP2650_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, data16.value.val, 2, HAL_MAX_DELAY);
    if(HAL_OK == ret)
    {
        return data16.value.value;
    }
    else
    {
        printf("error code = %d\r\n", ret);
        return 0xFFFF;
    }
}

void write_MP2650_16(uint8_t regAddr, uint16_t regValue)
{
    HAL_Delay(3);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c2, MP2650_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&regValue, 2, HAL_MAX_DELAY);
}

void print_MP2650_16(uint8_t regAddr)
{
    data16.value.value = read_MP2650_16(regAddr);
    printf("MP2650_16 reg %02X     0x%04X\t", regAddr, data16.value.value);
    print_byte(data16.value.val[1]);
    printf(" ");
    print_byte(data16.value.val[0]);
    ext_print_16(regAddr);
    printf("\r\n");
}

void ext_print_16(uint8_t regAddr)
{
    if(regAddr == ADC_Battery_Voltage_Result_16BIT)
    {
        uint16_t V = 0;
        V += ((data16.value.value >>6) & 0x0001) * 125; //больше в 10 раз
        V += ((data16.value.value >>7) & 0x0001) * 250;
        V += ((data16.value.value >>8) & 0x0001) * 500;
        V += ((data16.value.value >>9) & 0x0001) * 1000;
        V += ((data16.value.value >>10) & 0x0001) * 2000;
        V += ((data16.value.value >>11) & 0x0001) * 4000;
        V += ((data16.value.value >>12) & 0x0001) * 8000;
        V += ((data16.value.value >>13) & 0x0001) * 16000;
        V += ((data16.value.value >>14) & 0x0001) * 32000;
        V += ((data16.value.value >>15) & 0x0001) * 64000;
        printf("  ADC_Battery_Voltage             %d.%03d V", V/10000, V%10000);
    }
    if(regAddr == ADC_System_Voltage_Result_16BIT)
    {
        uint16_t V = 0;
        V += ((data16.value.value >>6) & 0x0001) * 125; //больше в 10 раз
        V += ((data16.value.value >>7) & 0x0001) * 250;
        V += ((data16.value.value >>8) & 0x0001) * 500;
        V += ((data16.value.value >>9) & 0x0001) * 1000;
        V += ((data16.value.value >>10) & 0x0001) * 2000;
        V += ((data16.value.value >>11) & 0x0001) * 4000;
        V += ((data16.value.value >>12) & 0x0001) * 8000;
        V += ((data16.value.value >>13) & 0x0001) * 16000;
        V += ((data16.value.value >>14) & 0x0001) * 32000;
        V += ((data16.value.value >>15) & 0x0001) * 64000;
        printf("  ADC_System_Voltage              %d.%03d V", V/10000, V%10000);
    }
    if(regAddr == ADC_Battery_Charge_Current_Result_16BIT)
    {
        uint16_t I = 0;
        I += ((data16.value.value >>6) & 0x0001) * 125; //больше в 10 раз
        I += ((data16.value.value >>7) & 0x0001) * 250;
        I += ((data16.value.value >>8) & 0x0001) * 500;
        I += ((data16.value.value >>9) & 0x0001) * 1000;
        I += ((data16.value.value >>10) & 0x0001) * 2000;
        I += ((data16.value.value >>11) & 0x0001) * 4000;
        I += ((data16.value.value >>12) & 0x0001) * 8000;
        I += ((data16.value.value >>13) & 0x0001) * 16000;
        I += ((data16.value.value >>14) & 0x0001) * 32000;
        I += ((data16.value.value >>15) & 0x0001) * 64000;
        printf("  ADC_Battery_Charge_Current      %d.%03d mA", I/10, I%10);
    }
    if(regAddr == ADC_Input_Voltage_Result_16BIT)
    {
        uint16_t U = 0;
        U += ((data16.value.value >>6) & 0x0001) * 25; //mV
        U += ((data16.value.value >>7) & 0x0001) * 50;
        U += ((data16.value.value >>8) & 0x0001) * 100;
        U += ((data16.value.value >>9) & 0x0001) * 200;
        U += ((data16.value.value >>10) & 0x0001) * 400;
        U += ((data16.value.value >>11) & 0x0001) * 800;
        U += ((data16.value.value >>12) & 0x0001) * 1600;
        U += ((data16.value.value >>13) & 0x0001) * 3200;
        U += ((data16.value.value >>14) & 0x0001) * 6400;
        U += ((data16.value.value >>15) & 0x0001) * 12800;
        printf("  ADC_Input_Voltage               %d.%03d V",U/1000,U%1000);
    }
    if(regAddr == ADC_Input_Current_Result_16BIT)
    {
        uint16_t I = 0;
        I += ((data16.value.value >>6) & 0x0001) * 13; //В 2 раза больше
        I += ((data16.value.value >>7) & 0x0001) * 25;
        I += ((data16.value.value >>8) & 0x0001) * 50;
        I += ((data16.value.value >>9) & 0x0001) * 100;
        I += ((data16.value.value >>10) & 0x0001) * 200;
        I += ((data16.value.value >>11) & 0x0001) * 400;
        I += ((data16.value.value >>12) & 0x0001) * 800;
        I += ((data16.value.value >>13) & 0x0001) * 1600;
        I += ((data16.value.value >>14) & 0x0001) * 3200;
        I += ((data16.value.value >>15) & 0x0001) * 6400;
        printf("  ADC_Input_Current               %d.%d mA", I/2, I%2);
    }
    if(regAddr == ADC_OTG_Output_Voltage_Result_16BIT)
    {
        uint16_t U = 0;
        U += ((data16.value.value >>6) & 0x0001) * 25; //mV
        U += ((data16.value.value >>7) & 0x0001) * 50;
        U += ((data16.value.value >>8) & 0x0001) * 100;
        U += ((data16.value.value >>9) & 0x0001) * 200;
        U += ((data16.value.value >>10) & 0x0001) * 400;
        U += ((data16.value.value >>11) & 0x0001) * 800;
        U += ((data16.value.value >>12) & 0x0001) * 1600;
        U += ((data16.value.value >>13) & 0x0001) * 3200;
        U += ((data16.value.value >>14) & 0x0001) * 6400;
        U += ((data16.value.value >>15) & 0x0001) * 12800;
        printf("  ADC_OTG_Output_Voltage          %d.%03d V",U/1000,U%1000);
    }
    if(regAddr == ADC_OTG_Output_Current_Result_16BIT)
    {
        uint16_t I = 0;
        I += ((data16.value.value >>6) & 0x0001) * 13; //В 2 раза больше
        I += ((data16.value.value >>7) & 0x0001) * 25;
        I += ((data16.value.value >>8) & 0x0001) * 50;
        I += ((data16.value.value >>9) & 0x0001) * 100;
        I += ((data16.value.value >>10) & 0x0001) * 200;
        I += ((data16.value.value >>11) & 0x0001) * 400;
        I += ((data16.value.value >>12) & 0x0001) * 800;
        I += ((data16.value.value >>13) & 0x0001) * 1600;
        I += ((data16.value.value >>14) & 0x0001) * 3200;
        I += ((data16.value.value >>15) & 0x0001) * 6400;
        printf("  ADC_OTG_Output_Current          %d.%d mA", I/2, I%2);
    }
    if(regAddr == ADC_Junction_Temperature_Result_16BIT)
    {
        uint16_t T = 0;
        T += ((data16.value.value >>6) & 0x0001);
        T += ((data16.value.value >>7) & 0x0001) * 2;
        T += ((data16.value.value >>8) & 0x0001) * 4;
        T += ((data16.value.value >>9) & 0x0001) * 8;
        T += ((data16.value.value >>10) & 0x0001) * 16;
        T += ((data16.value.value >>11) & 0x0001) * 32;
        T += ((data16.value.value >>12) & 0x0001) * 64;
        T += ((data16.value.value >>13) & 0x0001) * 128;
        T += ((data16.value.value >>14) & 0x0001) * 256;
        T += ((data16.value.value >>15) & 0x0001) * 512;
        uint16_t temp = 903000 - 2578 * T;
        printf("  ADC_Junction_Temperature        %d.%02d C", temp/1000, temp%100);
    }
    if(regAddr == ADC_System_Power_Result_16BIT)
    {
        uint16_t W = 0;
        W += ((data16.value.value >>6) & 0x0001) * 125; //больше в 1000 раз
        W += ((data16.value.value >>7) & 0x0001) * 250;
        W += ((data16.value.value >>8) & 0x0001) * 500;
        W += ((data16.value.value >>9) & 0x0001) * 1000;
        W += ((data16.value.value >>10) & 0x0001) * 2000;
        W += ((data16.value.value >>11) & 0x0001) * 4000;
        W += ((data16.value.value >>12) & 0x0001) * 8000;
        W += ((data16.value.value >>13) & 0x0001) * 16000;
        W += ((data16.value.value >>14) & 0x0001) * 32000;
        W += ((data16.value.value >>15) & 0x0001) * 64000;
        printf("  ADC_System_Power                %d.%03d W", W/1000, W%1000);
    }
    if(regAddr == ADC_Battery_Discharge_Current_Result_16BIT)
    {
        uint16_t I = 0;
        I += ((data16.value.value >>6) & 0x0001) * 125; //больше в 10 раз
        I += ((data16.value.value >>7) & 0x0001) * 250;
        I += ((data16.value.value >>8) & 0x0001) * 500;
        I += ((data16.value.value >>9) & 0x0001) * 1000;
        I += ((data16.value.value >>10) & 0x0001) * 2000;
        I += ((data16.value.value >>11) & 0x0001) * 4000;
        I += ((data16.value.value >>12) & 0x0001) * 8000;
        I += ((data16.value.value >>13) & 0x0001) * 16000;
        I += ((data16.value.value >>14) & 0x0001) * 32000;
        I += ((data16.value.value >>15) & 0x0001) * 64000;
        printf("  ADC_Battery_Discharge_Current   %d.%03d mA", I/10, I%10);
    }
    if(regAddr == ADC_Result_for_NTC_Voltage_16BIT) //NTC[11:0] x 1.6V / 4096
    {
        uint16_t V = 0;
        V = (data16.value.value & 0b0000111111111111) ;
        V *= 16000;
        V /= 4096;
        printf("  ADC_Result_for_NTC_Voltage      %d.%01d mV", V/10, V%10);
    }
}

void print_byte(uint8_t byte)
{
    printf("%s%s", bit_rep[byte >> 4], bit_rep[byte & 0x0F]);
}

void print_Regs16()
{
    print_MP2650_16(ADC_Battery_Voltage_Result_16BIT);
    print_MP2650_16(ADC_System_Voltage_Result_16BIT);
    print_MP2650_16(ADC_Battery_Charge_Current_Result_16BIT);
    print_MP2650_16(ADC_Input_Voltage_Result_16BIT);
    print_MP2650_16(ADC_Input_Current_Result_16BIT);
    print_MP2650_16(ADC_OTG_Output_Voltage_Result_16BIT);
    print_MP2650_16(ADC_OTG_Output_Current_Result_16BIT);
    print_MP2650_16(ADC_Junction_Temperature_Result_16BIT);
    print_MP2650_16(ADC_System_Power_Result_16BIT);
    print_MP2650_16(ADC_Battery_Discharge_Current_Result_16BIT);
    print_MP2650_16(ADC_Result_for_NTC_Voltage_16BIT);
    printf("\r\n");
}

uint8_t read_MP2650_8(uint8_t regAddr)
{
    data8.value = 0xFF;
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_StatusTypeDef ret;
    ret = HAL_I2C_Mem_Read(&hi2c2, MP2650_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, &data8.value, 1, HAL_MAX_DELAY);
    if(HAL_OK == ret)
    {
        return data8.value;
    }
    else
    {
        printf("error code = %d\r\n", ret);
        return 0xFF;
    }
}

void write_MP2650_8(uint8_t regAddr, uint8_t regValue)
{
    HAL_Delay(3);
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);
    HAL_I2C_Mem_Write(&hi2c2, MP2650_ADDRESS, regAddr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)&regValue, 1, HAL_MAX_DELAY);
}

void print_MP2650_8(uint8_t regAddr)
{
    data8.value = read_MP2650_8(regAddr);
    printf("MP2650_8  reg %02X     0x%02X\t", regAddr, data8.value);
    print_byte(data8.value);
    printf("\r\n");
}

void print_Regs8()
{
    print_MP2650_8(Input_Current_Limit_1_Setting);
    print_MP2650_8(Input_Voltage_Limit_Setting);
    print_MP2650_8(Charge_Current_Setting);
    print_MP2650_8(Pre_Charge_and_Termination_Current_Setting);
    print_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting);
    print_MP2650_8(Battery_Impedance_Compensation_Junction_Temperature_Regulation);
    print_MP2650_8(OTG_Voltage_Setting);
    print_MP2650_8(Pre_Charge_Threshold_and_OTG_Output_Current_Limit_Setting);
    print_MP2650_8(Configuration_Register_0);
    print_MP2650_8(Configuration_Register_1);
    print_MP2650_8(Configuration_Register_2);
    print_MP2650_8(Configuration_Register_3);
    print_MP2650_8(Configuration_Register_4);
    print_MP2650_8(System_OTG_Under_Voltage_and_Over_Voltage_Setting);
    print_MP2650_8(PROCHOT_Interrupt_Debounce_Time_and_Duration_Time_Setting);
    print_MP2650_8(Input_Current_Limit_2_Setting);
    print_MP2650_8(Input_Current_Limit_2_Duration_Setting);
    print_MP2650_8(Two_Level_Input_Current_Limit_Period_Setting);
    print_MP2650_8(Input_OCP_Threshold_for_Triggering_PROCHOT);
    print_MP2650_8(Status_Register);
    print_MP2650_8(Fault_Register);
    print_MP2650_8(Battery_OVP_Deglitch_Time);
    print_MP2650_8(Battery_Voltage_Loop_Enable);
    print_MP2650_8(Battery_Pre_Charge_Threshold_Option);
    print_MP2650_8(System_Voltage_Threshold_for_Pulse_Skipping);
    print_MP2650_8(INT_Mask_for_Hi_Z_Mode_Entry_and_Exit);
    print_MP2650_8(Analog_Frequency_Loop_Enable);
    print_MP2650_8(Hi_Z_Mode_Indication_DC_DC_Switcher_is_Off);
    printf("\r\n");
}

void set_4_battery()
{
    read_MP2650_8(Pre_Charge_Threshold_and_OTG_Output_Current_Limit_Setting);
    write_MP2650_8(Pre_Charge_Threshold_and_OTG_Output_Current_Limit_Setting, data8.value |= 0b11000000);
}
void disable_BATTFET()
{
    read_MP2650_8(Configuration_Register_0);
    write_MP2650_8(Configuration_Register_0, data8.value &= 0b11111101);
}
void enable_BATTFET()
{
    read_MP2650_8(Configuration_Register_0);
    write_MP2650_8(Configuration_Register_0, data8.value |= 0b00000010);
}
void disable_CHARGE()
{
    read_MP2650_8(Configuration_Register_0);
    write_MP2650_8(Configuration_Register_0, data8.value &= 0b11101111);
}
void enable_CHARGE()
{
    read_MP2650_8(Configuration_Register_0);
    write_MP2650_8(Configuration_Register_0, data8.value |= 0b00010000);
}
void disable_NTC_GCOMP_SEL()
{
    read_MP2650_8(Configuration_Register_0);
    write_MP2650_8(Configuration_Register_0, data8.value &= 0b11111011);
}
void enable_NTC_GCOMP_SEL()
{
    read_MP2650_8(Configuration_Register_0);
    write_MP2650_8(Configuration_Register_0, data8.value |= 0b00000100);
}
void disable_Battery_Voltage_Loop()
{
    read_MP2650_8(Battery_Voltage_Loop_Enable);
    write_MP2650_8(Battery_Voltage_Loop_Enable, data8.value &= 0b11111110);
}
void enable_Battery_Voltage_Loop()
{
    read_MP2650_8(Battery_Voltage_Loop_Enable);
    write_MP2650_8(Battery_Voltage_Loop_Enable, data8.value |= 0b00000001);
}
void REG_00_set_Input_Current_Limit(u_int16_t value) //in mA
{
    if (value > (0b01111111 * 50)) value = 0b01111111 * 50;
    uint8_t val = 0;
    val += value/50;
    write_MP2650_8(Input_Current_Limit_1_Setting, val);
}
void REG_01_set_Input_Voltage_Limit(u_int16_t value)
{
    if (value > (0b01111111 * 100)) value = 0b01111111 * 100;
    uint8_t val = 0;
    val += value/100;
    write_MP2650_8(Input_Voltage_Limit_Setting, val);
}
void REG_02_set_Charge_Current(u_int16_t value) //in mA
{
    if (value > (0b01111111 * 50)) value = 0b01111111 * 50;
    uint8_t val = 0;
    val += value/50;
    write_MP2650_8(Charge_Current_Setting, val);
}
void REG_03_set_PreCharge_Current(u_int16_t value) //180 - 840
{
//    data8.value &= 0b00001111;
//    data8.value |= 0b00110000;
    if (value <=180)
    {
        data8.value &= 0b00001111;
        data8.value |= 0b01000000;
    }
    if ((value > 180) && (value <= 240))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b01010000;
    }
    if ((value > 240) && (value <= 300))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b01100000;
    }
    if ((value > 300) && (value <= 360))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b01110000;
    }
    if ((value > 360) && (value <= 420))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b10000000;
    }
    if ((value > 420) && (value <= 480))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b10010000;
    }
    if ((value > 480) && (value <= 540))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b10100000;
    }
    if ((value > 540) && (value <= 600))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b10110000;
    }
    if ((value > 600) && (value <= 660))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b11000000;
    }
    if ((value > 660) && (value <= 720))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b11010000;
    }
    if ((value > 720) && (value <= 780))
    {
        data8.value &= 0b00001111;
        data8.value |= 0b11100000;
    }
    if (value > 780)
    {
        data8.value &= 0b00001111;
        data8.value |= 0b11110000;
    }
}
void REG_03_set_Termination_Current(u_int16_t value)
{
    if (value > (0b00001111 * 100)) value = 0b00001111 * 100;
    uint8_t val = 0;
    val += value/100;
    val &= 0b00001111;
    read_MP2650_8(Pre_Charge_and_Termination_Current_Setting);
    data8.value &= 0b11110000;
    data8.value |= val;
    write_MP2650_8(Pre_Charge_and_Termination_Current_Setting, data8.value);
}
void REG_04_set_Battery_Full_Voltage_for_one_Cell(u_int16_t value)
{
    value *= 10;
    read_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting);
    data8.value &= 0b10000001;

    if (value < 37125) value = 37125;
    if (value > 45000) value = 45000;
    value -= 37125;
    uint8_t val = value / 125;
    data8.value |= (val<<1);
    write_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting, data8.value);
}
void REG_04_set_Battery_Threshold_for_one_Cell_100mV()
{
    read_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting);
    data8.value &= 0b11111110;
    write_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting, data8.value);
}
void REG_04_set_Battery_Threshold_for_one_Cell_200mV()
{
    read_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting);
    data8.value |= 0b00000001;
    write_MP2650_8(Battery_Full_Voltage_and_Recharge_Threshold_Setting, data8.value);
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
