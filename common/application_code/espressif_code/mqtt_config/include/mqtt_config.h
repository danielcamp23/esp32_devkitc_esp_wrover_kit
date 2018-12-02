#ifndef _MQTT_CONFIG_H_
#define _MQTT_CONFIG_H_

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

struct MqttMsg {
    uint32_t gpio;
    int status;
};

extern QueueHandle_t gpio_mqtt_queue;

void mqtt_config_init();

void mqtt_config_task(void * pvParameters);

void mqtt_config_report_status(struct MqttMsg mqtt_msg);


#endif