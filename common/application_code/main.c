/*
 * Amazon FreeRTOS V1.4.3
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "aws_logging_task.h"
#include "aws_system_init.h"



#include "task_config.h"
#include "flags.h"
#include "nvs_storage.h"
#include "spiffs_storage.h"
#include "authentication.h"
#include "wifi_config.h"
#include "mqtt_config.h"
#include "gpio_handler.h"
#include "rtc_config.h"
#include "ota_client.h"
#include "analog_handler.h"
#include "udp_request.h"
#include "queue_conf.h"

/* Logging Task Defines. */
#define mainLOGGING_MESSAGE_QUEUE_LENGTH    ( 32 )
#define mainLOGGING_TASK_STACK_SIZE         ( configMINIMAL_STACK_SIZE * 6 )
#define mainDEVICE_NICK_NAME                "AcuaMatic"

int app_main( void ){
    xLoggingTaskInitialize( mainLOGGING_TASK_STACK_SIZE,
							tskIDLE_PRIORITY + 5,
							mainLOGGING_MESSAGE_QUEUE_LENGTH );
    
    if(SYSTEM_Init() == pdPASS){
        //printf("SYSTEM_Init OK\n");
        flags_init();
        nvs_storage_init();    
        authentication_init();
        queue_conf_init();
        mqtt_config_init();
        rtc_config_init();
        wifi_config_init();
        //ota_client_init();
        gpio_handler_init();
        analog_handler_init();
        udp_req_init();


        WIFIReturnCode_t xWifiStatus = wifi_config_start_driver();


        
        if(xWifiStatus == eWiFiSuccess){
            ( void ) xTaskCreate( wifi_config_task,
                                TASK_WIFI_NAME,
                                TASK_WIFI_STACK_SIZE,
                                NULL,
                                TASK_WIFI_PRIORITY,
                                NULL );
        
            
            ( void ) xTaskCreate( mqtt_config_task,
                                TASK_MQTT_SUBS_NAME,
                                TASK_MQTT_SUBS_STACK_SIZE,
                                NULL,
                                TASK_MQTT_SUBS_PRIORITY,
                                NULL );                          
            
        } 
        
         
    }
    else{
        printf("SYSTEM_Init Fail\n");
    }
    
    
    return 0;
}
