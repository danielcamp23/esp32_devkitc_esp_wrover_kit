#include "udp_request.h"
#include "stdio.h"
#include "FreeRTOS.h"
#include "task.h"

/* FreeRTOS+TCP includes. */
/* TCP/IP abstraction includes. */
#include "aws_secure_sockets.h" 

 
void udp_req_init(){
    #ifdef configDNS_SERVER_ADDR0
        printf("configDNS_SERVER_ADDR0: %d\n", configDNS_SERVER_ADDR0);
    #elif
        printf("configDNS_SERVER_ADDR0 NOT DEFINED\n");
    #endif    
    printf("HOLA****\n");
}