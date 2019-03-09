#ifndef _QUEUE_CONF_H_
#define _QUEUE_CONF_H_


#include "aws_mqtt_agent.h"
#include "freertos/queue.h"

extern QueueHandle_t gpio_queue;
extern QueueHandle_t mqtt_queue;

struct MqttMsg {
    uint32_t gpio;
    uint32_t status;
    char name[10];
};

struct GPIOMsg {
    uint32_t gpio;
    uint32_t status;
    char name[10];
};


void queue_conf_init();


void queue_conf_send_mqtt(struct MqttMsg msg);


void queue_conf_send_gpio(uint32_t _gpio, uint32_t _status);



#endif
