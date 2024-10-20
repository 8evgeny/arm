/**
  ******************************************************************************
  * @file    main.c
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    21/09/2021
  * @brief   Main program body.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2021 Milandr</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR32F9Qx_port.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32f9Qx_ebc.h"

/** @addtogroup __MDR32Fx_StdPeriph_Examples MDR32Fx StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR1986VE1T_EVAL MDR1986VE1T Evaluation Board
  * @{
  */

/** @addtogroup EXT_BUS_Extern_RAM_1T EXT_BUS_Extern_RAM
  * @{
  */

/* Private variables ---------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;
EBC_InitTypeDef EBC_InitStruct;
EBC_MemRegionInitTypeDef EBC_MemRegionInitStruct;

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Enables the HSI clock for EBC control */
    RST_CLK_PCLKcmd(RST_CLK_PCLK_EBC,ENABLE);

    /* Initializes EBC_InitStruct by default values*/
    EBC_StructInit(&EBC_InitStruct);

    /* Specifies external bus mode RAM*/
    EBC_InitStruct.EBC_Mode = EBC_MODE_RAM;

    /* Calculates the Wait States number for 8 MHz frequency and time interval = 500 ns */
    EBC_InitStruct.EBC_WaitState =  EBC_CalcWaitStates(8000,500);

    /* Initializes the EBC peripheral registers */
    EBC_Init(&EBC_InitStruct);

    /* Inittializes the EBC memory region 0�50000000-0�5FFFFFFF */
    /* Struct init */
    EBC_MemRegionStructInit(&EBC_MemRegionInitStruct);
    /* Initializes the EBC memory region  */
    EBC_MemRegionInit (&EBC_MemRegionInitStruct, EBC_MEM_REGION_50000000);
    /* Enables the specified EBC memory region settigs. */
    EBC_MemRegionCMD(EBC_MEM_REGION_50000000, ENABLE);

    /* Infinite loop */
    while (1);
}

/**
  * @brief  Reports the source file name, the source line number
  *         and expression text (if USE_ASSERT_INFO == 2) where
  *         the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @param  expr:
  * @retval None
  */
#if (USE_ASSERT_INFO == 1)
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the source file name and line number.
       Ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#elif (USE_ASSERT_INFO == 2)
void assert_failed(uint8_t* file, uint32_t line, const uint8_t* expr)
{
    /* User can add his own implementation to report the source file name, line number and
       expression text.
       Ex: printf("Wrong parameters value (%s): file %s on line %d\r\n", expr, file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif /* USE_ASSERT_INFO */

/** @} */ /* End of group EXT_BUS_Extern_RAM_1T */

/** @} */ /* End of group __MDR1986VE1T_EVAL */

/** @} */ /* End of group __MDR32Fx_StdPeriph_Examples */

/******************* (C) COPYRIGHT 2021 Milandr *******************************/

/* END OF FILE main.c */

