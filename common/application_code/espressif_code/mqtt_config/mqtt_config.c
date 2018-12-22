#include "mqtt_config.h"
#include "mqtt_config_static.h"
#include "mqtt_info.h"
#include "task_config.h"
#include "flags.h"

#include "string.h"
#include "stdio.h"

#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
#include "aws_mqtt_agent.h"
#include "aws_hello_world.h"


static MQTTAgentHandle_t xMQTTHandle = NULL;
static MessageBufferHandle_t xEchoMessageBuffer = NULL;
QueueHandle_t mqtt_queue;

void mqtt_config_init(void * param){
    mqtt_queue = xQueueCreate(5, sizeof(struct MqttMsg));
}

void mqtt_config_task(void * pvParameters){
    BaseType_t xX;
    BaseType_t xReturned;
    const TickType_t xFiveSeconds = pdMS_TO_TICKS( 5000UL );
    const BaseType_t xIterationsInAMinute = 60 / 5;
    TaskHandle_t xEchoingTask = NULL;

    ( void ) pvParameters;

    for(;;){
        if(flags_is_wifi_connected()){
            break;
        }

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }


    /* Create the MQTT client object and connect it to the MQTT broker. */
    xReturned = mqtt_config_connect_to_broker();


    if( xReturned == pdPASS ){
        flags_set_mqtt_connected();
        configPRINTF( ( "MQTT echo test echoing task created.\r\n" ) );
        xReturned = mqtt_config_subcribe();
    }
    for(;;){
        struct MqttMsg mqtt_msg;
        if(xQueueReceive(mqtt_queue, &mqtt_msg, 0 )){
            mqtt_config_report_status(mqtt_msg);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }


    /* Disconnect the client. */
    ( void ) MQTT_AGENT_Disconnect( xMQTTHandle, MQTT_TIMEOUT );

    /* End the demo by deleting all created resources. */
    configPRINTF( ( "MQTT echo demo finished.\r\n" ) );
    configPRINTF( ( "----Demo finished----\r\n" ) );
    vMessageBufferDelete( xEchoMessageBuffer );
    vTaskDelete( xEchoingTask );
    vTaskDelete( NULL ); /* Delete this task. */
}

void mqtt_config_report_status(struct MqttMsg mqtt_msg){
    MQTTAgentReturnCode_t xReturned;
    MQTTAgentPublishParams_t xPublishParameters;
    char cDataBuffer[ MQTT_MAX_DATA_LENGTH ];

    ( void ) snprintf( cDataBuffer, MQTT_MAX_DATA_LENGTH, "{\"data\": %s, \"date\":1543717507, \"connection\":true}", (mqtt_msg.status ? "1.0" : "0.0") );
    memset( &( xPublishParameters ), 0x00, sizeof( xPublishParameters ) );
    xPublishParameters.pucTopic = MQTT_PUBLISH_TOPIC;
    xPublishParameters.pvData = cDataBuffer;
    xPublishParameters.usTopicLength = ( uint16_t ) strlen( ( const char * ) MQTT_PUBLISH_TOPIC );
    xPublishParameters.ulDataLength = ( uint32_t ) strlen( cDataBuffer );
    xPublishParameters.xQoS = eMQTTQoS1;
    xReturned = MQTT_AGENT_Publish( xMQTTHandle, &( xPublishParameters ), MQTT_TIMEOUT );

}

static BaseType_t mqtt_config_connect_to_broker( void )
{
    MQTTAgentReturnCode_t xReturned;
    BaseType_t xReturn = pdFAIL;
    MQTTAgentConnectParams_t xConnectParameters =
    {
        MQTT_BROKER_ENDPOINT, /* The URL of the MQTT broker to connect to. */
        MQTT_AGENT_CONNECT_FLAGS,             /* Connection flags. */
        pdFALSE,                              /* Deprecated. */
        MQTT_BROKER_PORT,                     /* Port number on which the MQTT broker is listening. Can be overridden by ALPN connection flag. */
        MQTT_CLIENT_ID,                       /* Client Identifier of the MQTT client. It should be unique per broker. */
        0,                                    /* The length of the client Id, filled in later as not const. */
        pdFALSE,                              /* Deprecated. */
        NULL,                                 /* User data supplied to the callback. Can be NULL. */
        NULL,                                 /* Callback used to report various events. Can be NULL. */
        NULL,                                 /* Certificate used for secure connection. Can be NULL. */
        0                                     /* Size of certificate used for secure connection. */
    };

    /* Check this function has not already been executed. */
    configASSERT( xMQTTHandle == NULL );

    /* The MQTT client object must be created before it can be used.  The
     * maximum number of MQTT client objects that can exist simultaneously
     * is set by mqttconfigMAX_BROKERS. */
    xReturned = MQTT_AGENT_Create( &xMQTTHandle );

    if( xReturned == eMQTTAgentSuccess )
    {
        /* Fill in the MQTTAgentConnectParams_t member that is not const,
         * and therefore could not be set in the initializer (where
         * xConnectParameters is declared in this function). */
        xConnectParameters.usClientIdLength = ( uint16_t ) strlen( ( const char * ) MQTT_CLIENT_ID );

        /* Connect to the broker. */
        configPRINTF( ( "MQTT echo attempting to connect to %s.\r\n", MQTT_BROKER_ENDPOINT ) );
        xReturned = MQTT_AGENT_Connect( xMQTTHandle,
                                        &xConnectParameters,
                                        MQTT_ECHO_TLS_NEGOTIATION_TIMEOUT );

        if( xReturned != eMQTTAgentSuccess )
        {
            /* Could not connect, so delete the MQTT client. */
            ( void ) MQTT_AGENT_Delete( xMQTTHandle );
            configPRINTF( ( "ERROR:  MQTT echo failed to connect with error %d.\r\n", xReturned ) );
        }
        else
        {
            configPRINTF( ( "MQTT echo connected.\r\n" ) );
            xReturn = pdPASS;
        }
    }

    return xReturn;
}


static BaseType_t mqtt_config_subcribe(void){
    MQTTAgentReturnCode_t xReturned;
    BaseType_t xReturn;
    MQTTAgentSubscribeParams_t xSubscribeParams;
    printf("TOPIC: %s\n", MQTT_SUBSCRIBE_TOPIC);
    /* Setup subscribe parameters to subscribe to MQTT_SUBSCRIBE_TOPIC topic. */
    xSubscribeParams.pucTopic = MQTT_SUBSCRIBE_TOPIC;
    xSubscribeParams.pvPublishCallbackContext = NULL;
    xSubscribeParams.pxPublishCallback = mqtt_config_subs_callback;
    xSubscribeParams.usTopicLength = ( uint16_t ) strlen( ( const char * ) MQTT_SUBSCRIBE_TOPIC );
    xSubscribeParams.xQoS = eMQTTQoS1;

    /* Subscribe to the topic. */
    xReturned = MQTT_AGENT_Subscribe( xMQTTHandle,
                                      &xSubscribeParams,
                                      MQTT_TIMEOUT );

    if( xReturned == eMQTTAgentSuccess )
    {
        configPRINTF( ( "MQTT Echo demo subscribed to %s\r\n", MQTT_SUBSCRIBE_TOPIC ) );
        xReturn = pdPASS;
    }
    else
    {
        configPRINTF( ( "ERROR:  MQTT Echo demo could not subscribe to %s\r\n", MQTT_SUBSCRIBE_TOPIC ) );
        xReturn = pdFAIL;
    }

    return xReturn;
}

static MQTTBool_t mqtt_config_subs_callback(void * pvUserData, const MQTTPublishData_t * const pxCallbackParams){
    char cBuffer[ MQTT_MAX_DATA_LENGTH];
    uint32_t ulBytesToCopy = ( MQTT_MAX_DATA_LENGTH - 1 ); /* Bytes to copy initialized to ensure it
                                                                                   * fits in the buffer. One place is left
                                                                                   * for NULL terminator. */

    /* Remove warnings about the unused parameters. */
    ( void ) pvUserData;

    /* Don't expect the callback to be invoked for any other topics. */
    //configASSERT( ( size_t ) ( pxCallbackParams->usTopicLength ) == strlen( ( const char * ) MQTT_SUBSCRIBE_TOPIC ) );
    //configASSERT( memcmp( pxCallbackParams->pucTopic, MQTT_SUBSCRIBE_TOPIC, ( size_t ) ( pxCallbackParams->usTopicLength ) ) == 0 );

    printf("TOPIC recibo: %s\n", pxCallbackParams->pucTopic);
    //memcmp(pxCallbackParams->pucTopic, MQTT_SUBSCRIBE_TOPIC, ( size_t ) ( pxCallbackParams->usTopicLength )) ;

    /* THe ulBytesToCopy has already been initialized to ensure it does not copy
     * more bytes than will fit in the buffer.  Now check it does not copy more
     * bytes than are available. */
    if( pxCallbackParams->ulDataLength <= ulBytesToCopy ){
        ulBytesToCopy = pxCallbackParams->ulDataLength;

        /* Set the buffer to zero and copy the data into the buffer to ensure
         * there is a NULL terminator and the buffer can be accessed as a
         * string. */
        memset( cBuffer, 0x00, sizeof( cBuffer ) );
        memcpy( cBuffer, pxCallbackParams->pvData, ( size_t ) ulBytesToCopy );

        /* Only echo the message back if it has not already been echoed.  If the
         * data has already been echoed then it will already contain the echoACK_STRING
         * string. */
        printf("Data received: %s\n", cBuffer);
        //if( strstr( cBuffer, echoACK_STRING ) == NULL ){
        //    /* The string has not been echoed before, so send it to the publish
        //     * task, which will then echo the data back.  Make sure to send the
        //     * terminating null character as well so that the received buffer in
        //     * EchoingTask can be printed as a C string.  THE DATA CANNOT BE ECHOED
        //     * BACK WITHIN THE CALLBACK AS THE CALLBACK IS EXECUTING WITHINT THE
        //     * CONTEXT OF THE MQTT TASK.  Calling an MQTT API function here could cause
        //     * a deadlock. */
        //    ( void ) xMessageBufferSend( xEchoMessageBuffer, cBuffer, ( size_t ) ulBytesToCopy + ( size_t ) 1, echoDONT_BLOCK );
        //}
    }
    else{
        configPRINTF( ( "[WARN]: Dropping received message as it does not fit in the buffer.\r\n" ) );
    }

    /* The data was copied into the FreeRTOS message buffer, so the buffer
     * containing the data is no longer required.  Returning eMQTTFalse tells the
     * MQTT agent that the ownership of the buffer containing the message lies with
     * the agent and it is responsible for freeing the buffer. */
    return eMQTTFalse;
}