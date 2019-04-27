#ifndef _QUEUE_CONF_H_
#define _QUEUE_CONF_H_


#include "aws_mqtt_agent.h"
#include "freertos/queue.h"

extern QueueHandle_t gpio_queue;
extern QueueHandle_t mqtt_queue;
extern QueueHandle_t wifi_queue;


struct MqttMsg {
    uint32_t gpio;
    uint32_t status;
    char name[10];
    uint32_t timestamp;
};

struct GPIOMsg {
    uint32_t gpio;
    uint32_t status;
    char name[10];
};

struct WIFIMsg{
    int status;
};


void queue_conf_init();


void queue_conf_send_mqtt(struct MqttMsg msg);


void queue_conf_send_gpio(uint32_t _gpio, uint32_t _status);


void queue_conf_send_wifi(struct WIFIMsg msg);



#endif
