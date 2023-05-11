#include "ntp.h"
#include "cmsis_os.h"
#include "stdint.h"
#include "lwip/opt.h"
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/timeouts.h"
#include "ltdc.h"
#include <time.h>
//---------------------------------------------------------------
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
PACK_STRUCT_BEGIN
struct ntp_msg_struct {
  PACK_STRUCT_FLD_8(u8_t  li_vn_mode);
  PACK_STRUCT_FLD_8(u8_t  stratum);
  PACK_STRUCT_FLD_8(u8_t  poll);
  PACK_STRUCT_FLD_8(u8_t  precision);
  PACK_STRUCT_FIELD(u32_t root_delay);
  PACK_STRUCT_FIELD(u32_t root_dispersion);
  PACK_STRUCT_FIELD(u32_t reference_identifier);
  PACK_STRUCT_FIELD(u32_t reference_timestamp[2]);
  PACK_STRUCT_FIELD(u32_t originate_timestamp[2]);
  PACK_STRUCT_FIELD(u32_t receive_timestamp[2]);
  PACK_STRUCT_FIELD(u32_t transmit_timestamp[2]);
} PACK_STRUCT_STRUCT;
PACK_STRUCT_END
#ifdef PACK_STRUCT_USE_INCLUDES
#  include "arch/bpstruct.h"
#endif
//--------------------------------------------------
#define RANGE_SEC_1900_1970         (2208988800UL)
#define RANGE_SEC_1970_2036         (2085978496UL)
#define TIMEZONE 3
//---------------------------------------------------------------
extern RTC_HandleTypeDef hrtc;
extern uint32_t time_count;
extern osMessageQId timeout_Queue;
uint32_t old_time_count = 0, new_time_count = 0;
//--------------------------------------------------
void ntp_receive_callback(struct netconn* conn, enum netconn_evt evt, u16_t len);
//---------------------------------------------------------------
void ntp_thread(void *arg)
{
  osEvent event;
	struct netconn *conn;
	err_t err;
	ip_addr_t DestIPaddr;
	struct netbuf *buf;
	volatile uint16_t timeout = 0;
	conn = netconn_new_with_callback(NETCONN_UDP,ntp_receive_callback);
	IP4_ADDR(&DestIPaddr, 85, 21, 78, 23);
  if (conn!= NULL)
  {
  	err = netconn_bind(conn, NULL, 1551);
    if (err == ERR_OK)
    {
    	err = netconn_connect(conn, &DestIPaddr, 123);
      if (err == ERR_OK)
      {
        for(;;)
        {
          buf = netbuf_new();
          netbuf_alloc(buf, 48);
          if (buf != NULL)
          {
          	struct ntp_msg_struct *ntpmsg = (struct ntp_msg_struct *)buf->p->payload;
          	memset(ntpmsg, 0, 48);
          	ntpmsg->li_vn_mode = 0x00 | (4<<3) | 0x03; //version: 4, mode: client
          	old_time_count = osKernelSysTick();
          	netconn_send(conn,buf);
          	netbuf_delete(buf);
          }
          osDelay(20000);
          event = osMessageGet(timeout_Queue, 100);
          if (event.status == osEventMessage)
          {
            timeout = event.value.v;
          }
          if(timeout==1)
          {
            osDelay(3580000);
            timeout = 0;
          }
        }
      }
    }
    else
    {
      netconn_delete(conn);
    }
  }
  for(;;)
  {
    osDelay(1);
  }
}
//---------------------------------------------------------------
void ntp_receive_callback(struct netconn* conn, enum netconn_evt evt, u16_t len)
{
	err_t recv_err;
	struct netbuf *buf;
	char str[60];
	u8_t mode;
	u32_t receive_timestamp;
	u32_t rx_secs;
	int is_1900_based;
	u32_t t;
	struct tm *timestruct;
	time_t tim1;
  RTC_TimeTypeDef user_sTimeStructure;
  RTC_DateTypeDef user_sDateStructure;
  if(evt==NETCONN_EVT_RCVPLUS)
  {
  	recv_err = netconn_recv(conn, &buf);
    if (recv_err == ERR_OK)
    {
      if (buf->p->tot_len == 48)
      {
      	pbuf_copy_partial(buf->p, &mode, 1, 0);
      	mode &= 0x07; //mode mask
        if(mode == 0x04)
        {
          pbuf_copy_partial(buf->p, &receive_timestamp, 4, 40);
          rx_secs = lwip_ntohl(receive_timestamp);
        	sprintf(str,"%10lu: %lu", time_count, rx_secs);
        	TFT_DisplayString(10, 100, (uint8_t *)str, LEFT_MODE);
          is_1900_based = ((rx_secs & 0x80000000) != 0);
          t = is_1900_based ? (rx_secs - RANGE_SEC_1900_1970) : (rx_secs + RANGE_SEC_1970_2036);
          tim1 = t + 60UL*60*TIMEZONE;
          timestruct = localtime(&tim1);
          user_sTimeStructure.Hours = timestruct->tm_hour;
          user_sTimeStructure.Minutes = timestruct->tm_min;
          user_sTimeStructure.Seconds = timestruct->tm_sec;
          if (HAL_RTC_SetTime(&hrtc, &user_sTimeStructure, RTC_FORMAT_BIN) != HAL_OK)
          {
            _Error_Handler(__FILE__, __LINE__);
          }
          user_sDateStructure.WeekDay = timestruct->tm_wday;
          user_sDateStructure.Month = timestruct->tm_mon + 1;
          user_sDateStructure.Date = timestruct->tm_mday;
          user_sDateStructure.Year = (uint8_t) timestruct->tm_year % 100;
          if (HAL_RTC_SetDate(&hrtc, &user_sDateStructure, RTC_FORMAT_BIN) != HAL_OK)
          {
            _Error_Handler(__FILE__, __LINE__);
          }
          new_time_count = osKernelSysTick();
          if(new_time_count - old_time_count < 3000)
          {
          	osMessagePut(timeout_Queue, 1, 100);
          }
        }
      }
      netbuf_delete(buf);
    }
  }
}
//---------------------------------------------------------------
