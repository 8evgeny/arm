#ifndef NET_H_
#define NET_H_
//-----------------------------------------------
#include "stm32f7xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "lwip.h"
#include "lwip/tcp.h"
//-----------------------------------------------
void net_ini(void);
void tcp_server_init(void);
void UART6_RxCpltCallback(void);
//-----------------------------------------------
typedef struct USART_prop{
  uint8_t usart_buf[26];
  uint8_t usart_cnt;
  uint8_t is_tcp_connect;//статус попытки создать соединение TCP с сервером
  uint8_t is_text;//статус попытки передать текст серверу
} USART_prop_ptr;
//-----------------------------------------------
#endif /* NET_H_ */
