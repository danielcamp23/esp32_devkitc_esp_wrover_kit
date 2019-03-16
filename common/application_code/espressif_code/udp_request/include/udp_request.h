#ifndef _UDP_REQUEST_H_
#define _UDP_REQUEST_H_

#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_Sockets.h"

#define configECHO_SERVER_ADDR0              192
#define configECHO_SERVER_ADDR1              168
#define configECHO_SERVER_ADDR2              2
#define configECHO_SERVER_ADDR3              7

void aFunction( void );
void udp_req_init();
void vStandardSendExample();

#endif