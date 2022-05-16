#include "MT48LC4M32B2.h"

FMC_SDRAM_CommandTypeDef command;
HAL_StatusTypeDef hal_stat;

void MT48LC4M32B2_init(SDRAM_HandleTypeDef *hsdram)
{
    __IO uint32_t tmpmrd =0;
     command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
     command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
     command.AutoRefreshNumber = 1;
     command.ModeRegisterDefinition = 0;
     hal_stat = HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);
     HAL_Delay(1);
     command.CommandMode = FMC_SDRAM_CMD_PALL;
     command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1;
     command.AutoRefreshNumber = 1;
     command.ModeRegisterDefinition = 0;
     hal_stat = HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);
     HAL_Delay(1);
}
