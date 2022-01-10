/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.h
  * @version        : v2.0_Cube
  * @brief          : Header for usbd_cdc_if.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 Dmitriy Donskih, Arthur Markaryan
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Donskih Dmitriy under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_IF_H__
#define __USBD_CDC_IF_H__

#ifdef __cplusplus
	extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc.h"
#include "display.h"

/* Defines -------------------------------------------------------------------*/
#define USBD_CDC_IF_WAIT			0x00
#define USBD_CDC_IF_DATAREADY		0x01
#define USBD_CDC_IF_ESC				0x02
#define USBD_CDC_IF_ERROR			0xFF

#define VT100_ERASE_SCREEN			"\x1B[2J"		//!< Erase Screen		(Byte sequence: 0x1B 0x5B 0x32 0x4A)
#define VT100_YELLOW_ON				"\x1B[\x21m"	//!< Foreground Yellow	(Byte sequence: 0x1B 0x5B 0x21 0x6D)
#define VT100_YELLOW_OFF			"\x1B[\x2Bm"	//!< Background Yellow	(Byte sequence: 0x1B 0x5B 0x2B 0x6D)
#define VT100_RED_ON				"\x1B[\x1Fm"	//!< Foreground Red		(Byte sequence: 0x1B 0x5B 0x1F 0x6D)
#define VT100_RED_OFF				"\x1B[\x29m"	//!< Background Red		(Byte sequence: 0x1B 0x5B 0x29 0x6D)
#define VT100_BUZZER_ON				"\x1B[\x32m"	//!< Foreground Green	(Byte sequence: 0x1B 0x5B 0x32 0x6D)
#define VT100_BUZZER_OFF			"\x1B[\x42m"	//!< Background Green	(Byte sequence: 0x1B 0x5B 0x42 0x6D)

//
#define MESSAGE_YELLOW_ON			"                    " \
									"                    " \
									"                    " \
									"      YELLOW ON     "
//
#define MESSAGE_YELLOW_OFF			"                    " \
									"                    " \
									"                    " \
									"      YELLOW OFF    "

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief For Usb device.
  * @{
  */
  
/** @defgroup USBD_CDC_IF USBD_CDC_IF
  * @brief Usb VCP device module
  * @{
  */ 

/** @defgroup USBD_CDC_IF_Exported_Defines USBD_CDC_IF_Exported_Defines
  * @brief Defines.
  * @{
  */
/* USER CODE BEGIN EXPORTED_DEFINES */

/* USER CODE END EXPORTED_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Types USBD_CDC_IF_Exported_Types
  * @brief Types.
  * @{
  */

/* USER CODE BEGIN EXPORTED_TYPES */

/* USER CODE END EXPORTED_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Macros USBD_CDC_IF_Exported_Macros
  * @brief Aliases.
  * @{
  */

/* USER CODE BEGIN EXPORTED_MACRO */

/* USER CODE END EXPORTED_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

/** CDC Interface callback. */
extern USBD_CDC_ItfTypeDef USBD_Interface_fops_FS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_FunctionsPrototype USBD_CDC_IF_Exported_FunctionsPrototype
  * @brief Public functions declaration.
  * @{
  */

/*!
 * \brief		CDC Transmit function
 * \details		Data to send over USB IN endpoint are sent over CDC interface through this function.
 * \param		Buf: Buffer of data to be sent
 * \param		Len: Number of data to be sent (in bytes)
 * \retval		USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
 */	uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len);

//
void USBD_CDC_IF_clear(void);

//
void USBD_CDC_IF_write(void);

//
int USBD_CDC_IF_procRcvData(uint8_t *data, uint16_t size);

/*!
 * \brief		Analyze Received data
 * \details		Analyze data from RcvBuffer if ESC-sequence is received.
 * \param		None
 * \retval		USBD_CDC_IF_ESC if ESC-sequence is found else USBD_CDC_IF_ERROR
 */	int USBD_CDC_IF_analyzeRcvData(void);

#ifdef __cplusplus
}
#endif

#endif /* __USBD_CDC_IF_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
