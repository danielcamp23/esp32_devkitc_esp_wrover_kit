#include "ntp.h"
#include "ntp_static.h"
#include "ntp_info.h"
#include "task_config.h"
#include "udp_request.h"
#include "flags.h"
#include "rtc_config.h"

#include "freertos/task.h"

const int NTP_PACKET_SIZE = 48;
char NTP_FRAME[48];

void ntp_init(){
    memset(NTP_FRAME, 0, NTP_PACKET_SIZE);
    NTP_FRAME[0] = 0b11100011;
    NTP_FRAME[1] = 0;
    NTP_FRAME[2] = 6;
    NTP_FRAME[3] = 0xEC;
    NTP_FRAME[12]  = 49;
    NTP_FRAME[13]  = 0x4E;
    NTP_FRAME[14]  = 49;
    NTP_FRAME[15]  = 52; 
    
    ( void ) xTaskCreate( ntp_task,
                        TASK_NTP_NAME,
                        TASK_NTP_STACK_SIZE,
                        NULL,
                        TASK_NTP_PRIORITY,
                        NULL );   
}


bool ntp_get_date(){
    Socket_t socket = udp_create_socket(NTP_LOCAL_PORT);
    char packetBuffer[48]; 

    if(socket < 0){
        return false;
    }

    if(udp_send_msg(socket, NTP_HOST, NTP_HOST_PORT, NTP_FRAME, NTP_PACKET_SIZE) < 0){
        udp_close_socket(socket);
        return false;
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    if(udp_recv_msg(socket, NTP_HOST, NTP_HOST_PORT, packetBuffer, 48) > 0){
        int32_t tmp = 0;
        tmp |= packetBuffer[40] << 24;
        tmp |= packetBuffer[41] << 16;
        tmp |= packetBuffer[42] << 8;
        tmp |= packetBuffer[43] << 0;
        //tmp = tmp - NTP_1970_TIMESTAMP + NTP_RELATIVE_GMT_BOG;
        tmp = tmp - NTP_1970_TIMESTAMP;
        udp_close_socket(socket);
        printf("captured timestamp: %u\n", tmp);
        rtc_config_set_time(tmp);
        return true;
    }

    udp_close_socket(socket);
    return false;
}



static void ntp_task(void * pvParameters){
    for(;;){
        if(!flags_is_wifi_connected()){
            vTaskDelay(2000 / portTICK_PERIOD_MS);
            continue;
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS);
        if(ntp_get_date()){
            printf("ntp_task DELETE\n");
            vTaskDelete(NULL);
        }
    }
}