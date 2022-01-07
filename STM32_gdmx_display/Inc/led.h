/*!
 * \file		led.h
 * \brief		Header for led.c file.
 * \details		Led control module (Header file).
 * \author		Arthur Markaryan
 * \date		26.03.2021
 * \attention
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _LED_H_
#define _LED_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

#ifdef GV_INFOBOARD_V1
/* LED Alarm */
#define LED1_Pin 				GPIO_PIN_0		//!< LED "Alarm"-pin.
#define LED1_GPIO_Port 			GPIOB			//!< LED "Alarm"-port.
/* LED Write*/
#define LED2_Pin 				GPIO_PIN_1		//!< LED "Write"-pin.
#define LED2_GPIO_Port 			GPIOB			//!< LED "Write"-port.
#endif /* GV_INFOBOARD_V1 */

#ifdef GV_INFOBOARD_V2
/* LED Alarm */
#define LED1_Pin 				GPIO_PIN_12		//!< LED "Alarm"-pin.
#define LED1_GPIO_Port 			GPIOB			//!< LED "Alarm"-port.
/* LED Write*/
#define LED2_Pin 				GPIO_PIN_13		//!< LED "Write"-pin.
#define LED2_GPIO_Port 			GPIOB			//!< LED "Write"-port.
#endif /* GV_INFOBOARD_V2 */

/* Exported functions prototypes ---------------------------------------------*/

/*! \brief		LED control module initialization.
 *  \details	GPIO initialization function to drive LEDs.
 *  \retval		None.
 */	void LED_init(void);

/*! \brief		Turn on LED "Alarm". 
 *  \details	LED lighting control function. 
 *  \retval		None.
 */	void LED_setLED1(void);

/*! \brief		Turn off LED "Alarm".
 *  \details	LED lighting control function. 
 *  \retval		None.
 */	void LED_resetLED1(void);

/*! \brief		Turn on LED "Write".
 *  \details	LED lighting control function. 
 *  \retval		None.
 */	void LED_setLED2(void);

/*! \brief		Turn off LED "Write".
 *  \details	LED lighting control function. 
 *  \retval		None.
 */	void LED_resetLED2(void);

#ifdef __cplusplus
}
#endif

#endif /* _LED_H_ */
