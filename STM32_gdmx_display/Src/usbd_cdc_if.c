/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_cdc_if.c
  * @version        : v2.0_Cube
  * @brief          : Usb device for Virtual Com Port.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 Donskih Dmitriy.
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc_if.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device library.
  * @{
  */

/** @addtogroup USBD_CDC_IF
  * @{
  */

struct t_RcvBuffer{
	uint8_t buffer[HD44780_SCREEN_SIZE];
	uint8_t inbuff[256];
	uint8_t pos_x, pos_y, psize;
	uint8_t *pdata;
	uint16_t b_pos;
}RcvBuffer;

/** @defgroup USBD_CDC_IF_Private_TypesDefinitions USBD_CDC_IF_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Defines USBD_CDC_IF_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */
/* Define size for the receive and transmit buffer over CDC */
/* It's up to user to redefine and/or remove those define */
#define APP_RX_DATA_SIZE  1000
#define APP_TX_DATA_SIZE  128
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Macros USBD_CDC_IF_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_Variables USBD_CDC_IF_Private_Variables
  * @brief Private variables.
  * @{
  */
/* Create buffer for reception and transmission           */
/* It's up to user to redefine and/or remove those define */
/** Received data over USB are stored in this buffer      */
uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

/** Data to send over USB CDC are stored in this buffer   */
uint8_t UserTxBufferFS[APP_TX_DATA_SIZE];

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Exported_Variables USBD_CDC_IF_Exported_Variables
  * @brief Public variables.
  * @{
  */

extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CDC_IF_Private_FunctionPrototypes USBD_CDC_IF_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CDC_Init_FS(void);
static int8_t CDC_DeInit_FS(void);
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length);
static int8_t CDC_Receive_FS(uint8_t* pbuf, uint32_t *Len);

/**
  * @}
  */

USBD_CDC_ItfTypeDef USBD_Interface_fops_FS =
{
  CDC_Init_FS,
  CDC_DeInit_FS,
  CDC_Control_FS,
  CDC_Receive_FS
};

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Initializes the CDC media low layer over the FS USB IP
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Init_FS(void)
{
	/* Set Application Buffers */
	for (int i=0; i<HD44780_SCREEN_SIZE; i++){
			RcvBuffer.buffer[i]=' ';
	}
	RcvBuffer.pos_x = 0;
	RcvBuffer.pos_y = 0;
	RcvBuffer.psize = 0;
	RcvBuffer.pdata = NULL;
	RcvBuffer.b_pos = 0;

	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBufferFS, 0);
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBufferFS);

	return (USBD_OK);

}

/**
  * @brief  DeInitializes the CDC media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_DeInit_FS(void)
{
  return (USBD_OK);
}

/**
  * @brief  Manage the CDC class requests
  * @param  cmd: Command code
  * @param  pbuf: Buffer containing command data (request parameters)
  * @param  length: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Control_FS(uint8_t cmd, uint8_t* pbuf, uint16_t length)
{
  /* USER CODE BEGIN 5 */
  switch(cmd)
  {
    case CDC_SEND_ENCAPSULATED_COMMAND:

    break;

    case CDC_GET_ENCAPSULATED_RESPONSE:

    break;

    case CDC_SET_COMM_FEATURE:

    break;

    case CDC_GET_COMM_FEATURE:

    break;

    case CDC_CLEAR_COMM_FEATURE:

    break;

  /*******************************************************************************/
  /* Line Coding Structure                                                       */
  /*-----------------------------------------------------------------------------*/
  /* Offset | Field       | Size | Value  | Description                          */
  /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
  /* 4      | bCharFormat |   1  | Number | Stop bits                            */
  /*                                        0 - 1 Stop bit                       */
  /*                                        1 - 1.5 Stop bits                    */
  /*                                        2 - 2 Stop bits                      */
  /* 5      | bParityType |  1   | Number | Parity                               */
  /*                                        0 - None                             */
  /*                                        1 - Odd                              */
  /*                                        2 - Even                             */
  /*                                        3 - Mark                             */
  /*                                        4 - Space                            */
  /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
  /*******************************************************************************/
    case CDC_SET_LINE_CODING:

    break;

    case CDC_GET_LINE_CODING:

    break;

    case CDC_SET_CONTROL_LINE_STATE:

    break;

    case CDC_SEND_BREAK:

    break;

  default:
    break;
  }

  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  *
  *         @note
  *         This function will block any OUT packet reception on USB endpoint
  *         untill exiting this function. If you exit this function before transfer
  *         is complete on CDC interface (ie. using DMA controller) it will result
  *         in receiving more data while previous ones are still not sent.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Receive_FS(uint8_t* Buf, uint32_t *Len)
{
	USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
	USBD_CDC_ReceivePacket(&hUsbDeviceFS);

	if (USBD_CDC_IF_DATAREADY == USBD_CDC_IF_procRcvData(Buf, *Len)){
		DISPLAY_printScreen(RcvBuffer.buffer);
		RcvBuffer.b_pos = 0;//added
	}

	return (USBD_OK);
}

/* CDC_Transmit_FS */
uint8_t CDC_Transmit_FS(uint8_t* Buf, uint16_t Len)
{
	uint8_t result = USBD_OK;

	USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
	if (hcdc->TxState != 0){
		return USBD_BUSY;
	}
	USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
	result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);

	return result;
}

/* Clear RcvBuffer function */
void USBD_CDC_IF_clear(void){
	for (int i=0; i<13; i++){
		RcvBuffer.inbuff[i]='\x00';
	}
	RcvBuffer.psize = 0;
	RcvBuffer.pdata = NULL;
	RcvBuffer.b_pos = 0;
	for (int i=0; i<HD44780_SCREEN_SIZE; i++){
		RcvBuffer.buffer[i]=' ';
	}
	DISPLAY_printScreen(RcvBuffer.buffer);
}

//
void USBD_CDC_IF_write(void){
	for (int i=0;i<=RcvBuffer.psize;i++){
		if ((RcvBuffer.inbuff[i]>=0x20)&&(RcvBuffer.inbuff[i]<=0x7E)){
			RcvBuffer.buffer[i]=RcvBuffer.inbuff[i];
		};
	}
	RcvBuffer.psize=0;
	RcvBuffer.pdata = NULL;
}

//
int USBD_CDC_IF_procRcvData(uint8_t *data, uint16_t size){
	int result = USBD_CDC_IF_WAIT;

	if (size){
		RcvBuffer.pdata = data;
		//
		for (int i=0; i<size; i++){
			// Checking for completion of data reception for LCD
			if((RcvBuffer.pdata[i]==0x0d)||(RcvBuffer.pdata[i]==0x0a)){
				for (int i=0;i<=RcvBuffer.psize;i++){
					if ((RcvBuffer.inbuff[i]>=0x20)&&(RcvBuffer.inbuff[i]<=0x7E)){
						RcvBuffer.buffer[i]=RcvBuffer.inbuff[i];
					};
				}
				for (int i=0; i<13; i++){
					RcvBuffer.inbuff[i]='\x00';
				}
				RcvBuffer.psize = 0;
				RcvBuffer.pdata = NULL;
				RcvBuffer.b_pos = 0;
				result = USBD_CDC_IF_DATAREADY;
				break;
			}
			// Continue to receive data into the buffer
			if ((RcvBuffer.b_pos) < 256){
				RcvBuffer.inbuff[RcvBuffer.b_pos] = RcvBuffer.pdata[i];
				RcvBuffer.psize++;
				RcvBuffer.b_pos++;
			}else{
				result = USBD_CDC_IF_ERROR;
				break;
			}

			// Checking for the beginning of receiving an ESC sequence
			if(RcvBuffer.inbuff[0] == 0x1B){
				// Analyzing ESC sequence matches
				if(USBD_CDC_IF_ESC == USBD_CDC_IF_analyzeRcvData()){
					// RcvBuffer reset (except framebuffer)
					for (int i=0; i<256; i++){
						RcvBuffer.inbuff[i]='\x00';
					}
					RcvBuffer.psize = 0;
					RcvBuffer.pdata = NULL;
					RcvBuffer.b_pos = 0;
					result = USBD_CDC_IF_ESC;
					break;
				}
			}
		}
	}
	return result;
}

/* Analyze data from RcvBuffer if ESC-sequence is received */
int USBD_CDC_IF_analyzeRcvData(void){
	int result = USBD_CDC_IF_ERROR;
	if ('\x1B' == RcvBuffer.inbuff[0]){
		//
		if(0 == strcmp((char*)VT100_ERASE_SCREEN, (char*)RcvBuffer.inbuff)){
			USBD_CDC_IF_clear();
			result = USBD_CDC_IF_ESC;
		}
		//
		if(0 == strcmp((char*)VT100_RED_ON, (char*)RcvBuffer.inbuff)){
			LED_setLED1();
			result = USBD_CDC_IF_ESC;
		}
		//
		if(0 == strcmp((char*)VT100_RED_OFF, (char*)RcvBuffer.inbuff)){
			LED_resetLED1();
			result = USBD_CDC_IF_ESC;
		}
		//
		if(0 == strcmp((char*)VT100_YELLOW_ON, (char*)RcvBuffer.inbuff)){
			LED_setLED2();
			result = USBD_CDC_IF_ESC;
		}
		//
		if(0 == strcmp((char*)VT100_YELLOW_OFF, (char*)RcvBuffer.inbuff)){
			LED_resetLED2();
			result = USBD_CDC_IF_ESC;
		}
		//
		if(0 == strcmp((char*)VT100_BUZZER_ON, (char*)RcvBuffer.inbuff)){
			BUZZER_set();
			result = USBD_CDC_IF_ESC;
		}
		//
		if(0 == strcmp((char*)VT100_BUZZER_OFF, (char*)RcvBuffer.inbuff)){
			BUZZER_reset();
			result = USBD_CDC_IF_ESC;
		}
	}
	return result;
}
