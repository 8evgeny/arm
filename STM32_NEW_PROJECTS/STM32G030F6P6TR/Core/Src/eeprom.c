#include "eeprom.h"
#include <string.h>
#include "main.h"
extern void printf_DMA(const char* fmt, ...);
extern int AT24C_ReadBytes (uint16_t addr, uint8_t *buf, uint16_t bytes_count);
extern int AT24C_WriteBytes (uint16_t addr,uint8_t *buf, uint16_t bytes_count);

__IO uint16_t  EEPROMDataRead;
__IO uint8_t   EEPROMDataWrite;
// variables used by the filesystem

extern I2C_HandleTypeDef hi2c2;
char *pindex;
__weak void BSP_EEPROM_TIMEOUT_UserCallback(void)
{
}

static uint32_t EEPROM_WaitEepromStandbyState(void)
{
    /* Check if the maximum allowed number of trials has bee reached */
    if (EEPROM_IO_IsDeviceReady(EEPROM_I2C_ADDRESS, EEPROM_MAX_TRIALS) != HAL_OK) {
        /* If the maximum number of trials has been reached, exit the function */
        BSP_EEPROM_TIMEOUT_UserCallback();
        return EEPROM_TIMEOUT;
    }
    return EEPROM_OK;
}

static uint32_t EEPROM_WritePage(uint8_t *pBuffer, uint16_t WriteAddr, uint8_t *NumByteToWrite)
{
    uint32_t buffersize = *NumByteToWrite;
    uint32_t status = EEPROM_OK;

    /* Set the pointer to the Number of data to be written */
    EEPROMDataWrite = *NumByteToWrite;
    if (EEPROM_IO_WriteData(EEPROM_I2C_ADDRESS, WriteAddr, pBuffer, buffersize) != HAL_OK)
    {
        BSP_EEPROM_TIMEOUT_UserCallback();
        status = EEPROM_FAIL;
    }


    while (EEPROM_WaitEepromStandbyState() != EEPROM_OK) {
        return EEPROM_FAIL;
    }


    /* If all operations OK, return EEPROM_OK (0) */
    return status;
}



HAL_StatusTypeDef readData(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY)
        HAL_Delay(10);
    HAL_StatusTypeDef status = HAL_I2C_Mem_Read(&hi2c2,
                                                DevAddress, MemAddress,
#ifdef EEPROMADRESS8bit
                                                I2C_MEMADD_SIZE_8BIT,
#endif
#ifndef EEPROMADRESS8bit
                                                I2C_MEMADD_SIZE_16BIT,
#endif
                                                pData, Size, HAL_MAX_DELAY);

//    while(i2cReadReady != SET); //Выпилил
//    i2cReadReady = RESET;

    return status;
}

HAL_StatusTypeDef writeData(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{

    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY);

    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c2,
                                                 DevAddress, MemAddress,
#ifdef EEPROMADRESS8bit
                                             I2C_MEMADD_SIZE_8BIT,
#endif
#ifndef EEPROMADRESS8bit
                                             I2C_MEMADD_SIZE_16BIT,
#endif
                                                pData, Size, HAL_MAX_DELAY);
    for(;;)
    { // wait...
        status = HAL_I2C_IsDeviceReady(&hi2c2, DevAddress, 1, HAL_MAX_DELAY);
        if(status == HAL_OK)
            break;
    }

//    while( i2cWriteReady != SET); //Выпилил
//    i2cWriteReady = RESET;

    return status;
}

HAL_StatusTypeDef EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pBuffer, uint32_t BufferSize)
{
    HAL_StatusTypeDef status = readData(DevAddress, MemAddress, pBuffer, BufferSize);
    return status;
}

HAL_StatusTypeDef EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pBuffer, uint32_t BufferSize)
{
    HAL_StatusTypeDef status = writeData(DevAddress, MemAddress, pBuffer, BufferSize);
    return status;
}

uint32_t BSP_EEPROM_ReadBuffer(uint8_t *pBuffer, uint16_t ReadAddr, uint16_t *NumByteToRead)
{
    uint32_t buffersize = *NumByteToRead;

    /* Set the pointer to the Number of data to be read */
    EEPROMDataRead = *NumByteToRead;

    if (EEPROM_IO_ReadData(EEPROM_I2C_ADDRESS, ReadAddr, pBuffer, buffersize) != HAL_OK)
    {

        BSP_EEPROM_TIMEOUT_UserCallback();
        return EEPROM_FAIL;
    }

    /* If all operations OK, return EEPROM_OK (0) */
    return EEPROM_OK;
}

uint32_t BSP_EEPROM_WriteBuffer(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t  numofpage = 0, numofsingle = 0, count = 0;
    uint16_t addr = 0;
    uint8_t  dataindex = 0;
    uint32_t status = EEPROM_OK;

    addr = WriteAddr % EEPROM_PAGESIZE;
    count = EEPROM_PAGESIZE - addr;
    numofpage =  NumByteToWrite / EEPROM_PAGESIZE;
    numofsingle = NumByteToWrite % EEPROM_PAGESIZE;

    /* If WriteAddr is EEPROM_PAGESIZE aligned */
    if (addr == 0) {
        /* If NumByteToWrite < EEPROM_PAGESIZE */
        if (numofpage == 0) {
            /* Store the number of data to be written */
            dataindex = numofsingle;
            /* Start writing data */

            status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t *)(&dataindex));
            if (status != EEPROM_OK) {
                return status;
            }
        }
        /* If NumByteToWrite > EEPROM_PAGESIZE */
        else {
            while (numofpage--) {
                /* Store the number of data to be written */
                dataindex = EEPROM_PAGESIZE;
                status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t *)(&dataindex));
                if (status != EEPROM_OK) {
                    return status;
                }

                WriteAddr +=  EEPROM_PAGESIZE;
                pBuffer += EEPROM_PAGESIZE;
            }

            if (numofsingle != 0) {
                /* Store the number of data to be written */
                dataindex = numofsingle;
                status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t *)(&dataindex));
                if (status != EEPROM_OK) {
                    return status;
                }
            }
        }
    }
    /* If WriteAddr is not EEPROM_PAGESIZE aligned */
    else {
        /* If NumByteToWrite < EEPROM_PAGESIZE */
        if (numofpage == 0) {
            /* If the number of data to be written is more than the remaining space
            in the current page: */
            if (NumByteToWrite > count) {
                /* Store the number of data to be written */
                dataindex = count;
                /* Write the data contained in same page */
                status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t *)(&dataindex));
                if (status != EEPROM_OK) {
                    return status;
                }

                /* Store the number of data to be written */
                dataindex = (NumByteToWrite - count);
                /* Write the remaining data in the following page */
                status = EEPROM_WritePage((uint8_t *)(pBuffer + count), (WriteAddr + count), (uint8_t *)(&dataindex));
                if (status != EEPROM_OK) {
                    return status;
                }
            } else {
                /* Store the number of data to be written */
                dataindex = numofsingle;
                status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t *)(&dataindex));
                if (status != EEPROM_OK) {
                    return status;
                }
            }
        }
        /* If NumByteToWrite > EEPROM_PAGESIZE */
        else {
            NumByteToWrite -= count;
            numofpage =  NumByteToWrite / EEPROM_PAGESIZE;
            numofsingle = NumByteToWrite % EEPROM_PAGESIZE;

            if (count != 0) {
                /* Store the number of data to be written */
                dataindex = count;
                status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t *)(&dataindex));
                if (status != EEPROM_OK) {
                    return status;
                }
                WriteAddr += count;
                pBuffer += count;
            }

            while (numofpage--) {
                /* Store the number of data to be written */
                dataindex = EEPROM_PAGESIZE;
                status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t *)(&dataindex));
                if (status != EEPROM_OK) {
                    return status;
                }
                WriteAddr +=  EEPROM_PAGESIZE;
                pBuffer += EEPROM_PAGESIZE;
            }
            if (numofsingle != 0) {
                /* Store the number of data to be written */
                dataindex = numofsingle;
                status = EEPROM_WritePage(pBuffer, WriteAddr, (uint8_t *)(&dataindex));
                if (status != EEPROM_OK) {
                    return status;
                }
            }
        }
    }

    /* If all operations OK, return EEPROM_OK (0) */
    return EEPROM_OK;
}

HAL_StatusTypeDef EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{
    HAL_StatusTypeDef status = HAL_I2C_IsDeviceReady(&hi2c2, DevAddress, Trials, 300);
    return status;
}

void printFileFromAdressEEPROM(uint16_t ReadAddr, uint16_t numByteFile)
{
    printf("Print %d byte from 0x%.4X adress i2c eeprom\n",numByteFile, ReadAddr);
    uint16_t * numByte = &numByteFile;
    pindex = malloc(numByteFile);
    memset(pindex, 0x00, numByteFile);
    int result = BSP_EEPROM_ReadBuffer((uint8_t*)pindex, ReadAddr, numByte);
    printf("read %d byte from adress 0x%.4X on eprom: %d\n", numByteFile, ReadAddr, result);
    Printf("print reading file\n");
    for (int i = 0; i < numByteFile; ++i)
    {
        Printf("%c", pindex[i]);
    }
    Printf("\n");
    free (pindex);
}
