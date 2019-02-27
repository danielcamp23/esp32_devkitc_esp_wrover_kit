#include "queue_conf.h"


static struct MqttMsg mqtt_msg;
static struct GPIOMsg gpio_msg;

void queue_conf_init(){
    mqtt_queue = xQueueCreate(5, sizeof(struct MqttMsg));
    gpio_queue = xQueueCreate(15, sizeof(struct GPIOMsg));
}

void queue_conf_send_mqtt(uint32_t _gpio, uint32_t _status){
     mqtt_msg.gpio = _gpio;
     mqtt_msg.status = _status;
    xQueueSendToBack(mqtt_queue, &mqtt_msg, 0);
}

void queue_conf_send_gpio(uint32_t _gpio, uint32_t _status){
    gpio_msg.gpio = _gpio;
    gpio_msg.status = _status;
    xQueueSendToBack(gpio_queue, &gpio_msg, 0);
}
 