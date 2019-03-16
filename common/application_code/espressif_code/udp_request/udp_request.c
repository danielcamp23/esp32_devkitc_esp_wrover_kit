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
    //aFunction();
}

Socket_t createUDPSocket( void ){
/* Variable to hold the created socket. */
Socket_t xSocket;
struct freertos_sockaddr xBindAddress;

    /* Create a UDP socket. */
    xSocket = FreeRTOS_socket( FREERTOS_AF_INET,
                               FREERTOS_SOCK_DGRAM,
                               FREERTOS_IPPROTO_UDP );

    /* Check the socket was created successfully. */
    if( xSocket != FREERTOS_INVALID_SOCKET )
    {
        /* The socket was created successfully and can now be used to send data
        using the FreeRTOS_sendto() API function.  Sending to a socket that has
        not first been bound will result in the socket being automatically bound
        to a port number.  Use FreeRTOS_bind() to bind the socket to a
        specific port number.  This example binds the socket to port 9999.  The
        port number is specified in network byte order, so FreeRTOS_htons() is
        used. */
        xBindAddress.sin_port = FreeRTOS_htons( 9999 );
        if( FreeRTOS_bind( xSocket, &xBindAddress, sizeof( &xBindAddress ) ) == 0 )
        {
            printf("BIND succesfull\n");
            /* The bind was successful. */
            return xSocket;
        }
        else{
            printf("BIND FAILED\n");
        }

    }
    else
    {
        printf("Unable to create socket\n");
        /* There was insufficient FreeRTOS heap memory available for the socket
        to be created. */
    }

    return NULL;
}


void vStandardSendExample(){
/* Note - the RTOS task stack must be big enough to hold this array!. */

Socket_t xSocket = createUDPSocket();
uint8_t ucBuffer[ 128 ] = {'h', 'o', 'l', 'a', '\0'};
struct freertos_sockaddr xDestinationAddress;
int32_t iReturned;

    /* Fill in the destination address and port number, which in this case is
    port 1024 on IP address 192.168.0.100. */
    xDestinationAddress.sin_addr = FreeRTOS_inet_addr_quick( 192, 168, 0, 8 );
    xDestinationAddress.sin_port = FreeRTOS_htons( 1024 );

    /* The local buffer is filled with the data to be sent, in this case it is
    just filled with 0xff. */
    //memset( ucBuffer, 0xff, 128 );
    stpncpy((char *)ucBuffer, "Hola Probando UDP...", 20);

    /* Send the buffer with ulFlags set to 0, so the FREERTOS_ZERO_COPY bit
    is clear. */
    if(xSocket == NULL){
        printf("SOCKET NOT CREATED\n");
    }
    else{
        printf("SOCKET CREATED XD\n");
    }

    iReturned = FreeRTOS_sendto(
                                    /* The socket being send to. */
                                    xSocket,
                                    /* The data being sent. */
                                    ucBuffer,
                                    /* The length of the data being sent. */
                                    4,
                                    /* ulFlags with the FREERTOS_ZERO_COPY bit clear. */
                                    0,
                                    /* Where the data is being sent. */
                                    &xDestinationAddress,
                                    /* Not used but should be set as shown. */
                                    sizeof( xDestinationAddress )
                               );

    printf("Returned: %d\n", iReturned);
    if( iReturned == 128 )
    {
        /* The data was successfully queued for sending.  128 bytes will have
        been copied out of ucBuffer and into a buffer inside the TCP/IP stack.
        ucBuffer can be re-used now. */
    }
}