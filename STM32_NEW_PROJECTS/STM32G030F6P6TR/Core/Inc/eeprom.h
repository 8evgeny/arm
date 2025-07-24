#ifndef FSFOREEPROM_H
#define FSFOREEPROM_H
/*
EEPROM I2C : Microchip (AT24CS01)
1‑Kbit (128 x 8) 000 - 3FF
128-Bit Unique Factory-Programmed Serial Number

8 pages of 128-bites each
000 - 07F   128b
080 - 0FF   128b
100 - 17F   128b
180 - 1FF   128b
200 - 27F   128b
280 - 2FF   128b
300 - 37F   128b
380 - 3FF   128b
*/
#include <stdint.h>
#include "main.h"
#include "stm32g0xx_hal_def.h"
//Реальный 50
#define EEPROM_I2C_ADDRESS          0xA0
#define EEPROM_I2C_SERIAL           0xB0
#define EEPROMADRESS8bit
#define EEPROM_OK                   0
#define EEPROM_FAIL                 1
#define EEPROM_TIMEOUT              2

/* EEPROM hardware address and page size */
//#define EEPROM_PAGESIZE             128
//#define EEPROM_PAGESIZE             64
#define EEPROM_PAGESIZE             16  //По другому глючит с маленькой eeprom
#define EEPROM_MAX_SIZE             0x0400 //1024 bit
/* Maximum Timeout values for flags and events waiting loops: This timeout is based
   on systick set to 1ms.
   Timeout for read based if read all the EEPROM: EEPROM_MAX_SIZE * BSP_I2C_SPEED (640ms) */
#define EEPROM_READ_TIMEOUT         ((uint32_t)(1000))
/* Timeout for write based on max write which is EEPROM_PAGESIZE bytes: EEPROM_PAGESIZE * BSP_I2C_SPEED (320us)*/
#define EEPROM_WRITE_TIMEOUT        ((uint32_t)(1000))
/* Maximum number of trials for EEPROM_WaitEepromStandbyState() function */
#define EEPROM_MAX_TRIALS           3000

//uint32_t BSP_EEPROM_ReadBuffer(uint8_t *pBuffer, uint16_t ReadAddr, uint16_t *NumByteToRead);
//uint32_t BSP_EEPROM_WriteBuffer(uint8_t *pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite);
//HAL_StatusTypeDef   EEPROM_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pBuffer, uint32_t BufferSize);
//HAL_StatusTypeDef   EEPROM_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pBuffer, uint32_t BufferSize);
//HAL_StatusTypeDef   EEPROM_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
#endif // FSFOREEPROM_H
