#ifndef _MQTT_INFO_H
#define _MQTT_INFO_H

/*
 * Amazon FreeRTOS V1.4.4
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
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


#ifndef __AWS_CLIENTCREDENTIAL__H__
#define __AWS_CLIENTCREDENTIAL__H__

/*
 * Include for device certificate and private key
 */
//#include "aws_clientcredential_keys.h"

/*
 * MQTT Broker endpoint.
 */
//a3b86accc5t4qb.iot.us-east-1.amazonaws.com
//static const char MQTT_BROKER_ENDPOINT[] = "anudiie8w30q6.iot.us-east-1.amazonaws.com";
static const char MQTT_BROKER_ENDPOINT[] = "a3b86accc5t4qb.iot.us-east-1.amazonaws.com";


/* Use of a "define" and not a "static const" here to be able to
* use pre-compile concatenation on the string. */
#define IOT_THING_NAME "cosa90"

/*
 * Port number the MQTT broker is using.
 */
#define MQTT_BROKER_PORT 8883

/*
 * Port number the Green Grass Discovery use for JSON retrieval from cloud is using.
 */
#define GREENGRASS_DISCOVERY_PORT 8443

#define MQTT_SUBSCRIBE_TOPIC    ( ( const uint8_t * ) "output/12345678" )

#define MQTT_PUBLISH_TOPIC      ( ( const uint8_t * ) "input/12345678" )

/* Timeout used when performing MQTT operations that do not need extra time
to perform a TLS negotiation. */
#define MQTT_TIMEOUT            pdMS_TO_TICKS( 3000 )

/* Send AWS IoT MQTT traffic encrypted to destination port 443. */
#define MQTT_AGENT_CONNECT_FLAGS                 ( mqttagentREQUIRE_TLS | mqttagentUSE_AWS_IOT_ALPN_443 )

/* Timeout used when establishing a connection, which required TLS
* negotiation. */
#define MQTT_ECHO_TLS_NEGOTIATION_TIMEOUT        pdMS_TO_TICKS( 12000 )

/**
 * It must be unique per MQTT broker.
 */
#define MQTT_CLIENT_ID            ( ( const uint8_t * ) "MQTTEcho" )

/**
 * @brief Dimension of the character array buffers used to hold data (strings in
 * this case) that is published to and received from the MQTT broker (in the cloud).
 */
#define MQTT_MAX_DATA_LENGTH      500


#endif

#endif
