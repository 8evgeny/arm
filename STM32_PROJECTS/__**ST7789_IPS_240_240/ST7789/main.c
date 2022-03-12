#include "main.h"
#include "st7789.h"

SPI_HandleTypeDef hspi1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

void delay()
{
    int a = 0;
    for (int i = 0; i < 300000; ++i)
    {
        ++a;
    }
}


int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI1_Init();

  HAL_GPIO_WritePin(BLK_GPIO_Port, BLK_Pin, GPIO_PIN_SET);

  while (1)
  {

    ST7789_Init(240, 240);
	  // Инициализация входа для кнопки
    // Тест вывода основных цветов
    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);
		
    uint16_t color = RGB565(255, 0, 0);
    ST7789_FillScreen(color);
    HAL_Delay(500);
  
    color = RGB565(0, 255, 0);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(50, 55, 50);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(0, 0, 255);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(255, 255, 0);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(255, 0, 255);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(0, 255, 255);
    ST7789_FillScreen(color);
    HAL_Delay(500);

    color = RGB565(255, 255, 255);
    ST7789_FillScreen(color);
    HAL_Delay(500);
		
    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);
		
		for (uint8_t y = 0; y<240 ; y++) {
			ST7789_DrawLine(120, 120, 239, y, RGB565(y+10, 0, 0));
		}
   		
		for (uint8_t x = 0; x<240 ; x++) {
			ST7789_DrawLine(120, 120, x, 239, RGB565(0, x+10, 0));
		}
   
		for (uint8_t y = 0; y<240 ; y++) {
			ST7789_DrawLine(120, 120, 0, y, RGB565(0, 0, y+10));
		}
 
		for (uint8_t x = 0; x<240 ; x++) {
			ST7789_DrawLine(120, 120, x, 0, RGB565(x+10, x+10, x+10));
		}
    HAL_Delay(1000);

    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);

    for (uint8_t x = 0; x < 240 ; x = x + 20) {
			for (uint8_t y = 0; y < 240; y = y + 20) {
				ST7789_DrawRectangleFilled(x + 3, y + 3, x + 17, y + 17, RGB565(x, y, 0));
				ST7789_DrawRectangle(x + 2, y + 2, x + 19, y + 19, RGB565(250, 250, 250));
			}
		}
    HAL_Delay(1000);

    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);

    for (uint8_t x = 0; x < 240 ; x = x + 20) {
			for (uint8_t y = 0; y < 240; y = y + 20) {
        ST7789_DrawCircleFilled(x + 10, y + 10, 8, RGB565(x, y, 0));
        ST7789_DrawCircle(x + 10, y + 10, 9, RGB565(0, y, x));
			}
		}
    HAL_Delay(1000);

    ST7789_FillScreen(BLACK);
    ST7789_SetBL(100);
	
  }

}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
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
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}


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

static void MX_SPI1_Init(void)
{

    /* USER CODE BEGIN SPI1_Init 0 */

    /* USER CODE END SPI1_Init 0 */

    /* USER CODE BEGIN SPI1_Init 1 */

    /* USER CODE END SPI1_Init 1 */
    /* SPI1 parameter configuration*/
    hspi1.Instance = SPI1;
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN SPI1_Init 2 */

    /* USER CODE END SPI1_Init 2 */

}

static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_9|GPIO_PIN_10, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

    /*Configure GPIO pin : PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : PA1 PA9 PA10 */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : PB1 PB4 PB5 */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
