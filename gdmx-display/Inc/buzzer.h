/*!
 * \file		buzzer.h
 * \brief		Header for buzzer.c file.
 * \details		Buzzer control module (Header file).
 * \author		Arthur Markaryan
 * \date		26.03.2021
 * \copiright
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BUZZER_H_
#define _BUZZER_H_

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
/* Buzzer */
#define BUZZER_Pin 			GPIO_PIN_6
#define BUZZER_GPIO_Port 	GPIOB
#endif /* GV_INFOBOARD_V1 */

#ifdef GV_INFOBOARD_V2
#define BUZZER_Pin 			GPIO_PIN_14
#define BUZZER_GPIO_Port 	GPIOB
#endif /* GV_INFOBOARD_V2 */

/* Exported functions prototypes ---------------------------------------------*/

/*! \brief		Инциализация модуля управления основным питанием.
 *  \details	Функция инициализации модуля управления основным питанием.
 *  \retval		None
 */	void BUZZER_init(void);

/*! \brief		Инциализация модуля управления основным питанием.
 *  \details	Функция инициализации модуля управления основным питанием.
 *  \retval		None
 */	void BUZZER_set(void);

/*! \brief		Инциализация модуля управления основным питанием.
 *  \details	Функция инициализации модуля управления основным питанием.
 *  \retval		None
 */	void BUZZER_reset(void);

#ifdef __cplusplus
}
#endif

#endif /* _BUZZER_H_ */
