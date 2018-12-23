#include "ota_client.h"
#include "ota_client_static.h"
#include "aws_ota_agent.h"
#include "mqtt_config.h"
#include "mqtt_info.h"


/*
Lleva control del ota_client
*/
static bool ota_client_launched;

void ota_client_init(){
    ota_client_launched = false;
}

void ota_client_check_firmware(){
    
    if(ota_client_launched){//Previene que se lance la tarea más de una vez.
        return;
    }

    ota_client_launched = true;
    OTA_AgentInit(mqtt_config_get_handler(), ( const uint8_t * ) (MQTT_CLIENT_ID), _ota_client_complete_callback, ( TickType_t ) ~0);
}




static void _ota_client_complete_callback(OTA_JobEvent_t eEvent){
	OTA_Err_t xErr = kOTA_Err_Uninitialized;
	
    if (eEvent == eOTA_JobEvent_Activate){
        configPRINTF( ( "Received eOTA_JobEvent_Activate callback from OTA Agent.\r\n" ) );
        OTA_ActivateNewImage();
    }
    else if (eEvent == eOTA_JobEvent_Fail){
        configPRINTF( ( "Received eOTA_JobEvent_Fail callback from OTA Agent.\r\n" ) );
        /* Nothing special to do. The OTA agent handles it. */
    }
	else if (eEvent == eOTA_JobEvent_StartTest){
		/* This demo just accepts the image since it was a good OTA update and networking
		 * and services are all working (or we wouldn't have made it this far). If this
		 * were some custom device that wants to test other things before calling it OK,
		 * this would be the place to kick off those tests before calling OTA_SetImageState()
		 * with the final result of either accepted or rejected. */
        configPRINTF( ( "Received eOTA_JobEvent_StartTest callback from OTA Agent.\r\n" ) );
	    xErr = OTA_SetImageState (eOTA_ImageState_Accepted);
        if(xErr != kOTA_Err_None){
            OTA_LOG_L1( " Error! Failed to set image state as accepted.\r\n" );    
        }
	}
    ota_client_launched = false;
}