/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v2.0_Cube
  * @brief          : This file implements the USB Device
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

/* Includes ------------------------------------------------------------------*/

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

USBD_HandleTypeDef hUsbDeviceFS;

/*!
 * \brief		MX USB Device library initialization function.
 * \details		Init USB device Library, add supported class and start the library.
 * \param		None.
 * \retval		None.
 */
void MX_USB_DEVICE_Init(void)
{
	if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
	{
		Error_Handler();
	}

	if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
	{
		Error_Handler();
	}

	if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
	{
		Error_Handler();
	}

	if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
	{
		Error_Handler();
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
