#include "gpio_handler.h"
#include "gpio_handler_static.h"
#include "gpio_info.h"
#include "mqtt_config.h"
#include "task_config.h"

#include <stdint.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
//#include "queue.h"

static QueueHandle_t gpio_evt_queue;


void gpio_handler_init(){
    gpio_handler_config_gpios();
    gpio_evt_queue = xQueueCreate(5, sizeof(uint32_t));
    if(gpio_evt_queue != NULL){
        ( void ) xTaskCreate( gpio_handler_task,
                              TASK_GPIO_NAME,
                              TASK_GPIO_STACK_SIZE,
                              NULL,
                              TASK_GPIO_PRIORITY,
                              NULL );
    }
}


static void IRAM_ATTR gpio_handler_ISR(void* arg){
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

int gpio_handler_read(uint32_t gpio){
    return gpio_get_level(gpio);
}

void gpio_handler_write(uint32_t gpio, uint32_t level){
    gpio_set_level(gpio, level);
}


void gpio_handler_task(void * pvParameters){
    (void) pvParameters;
    uint32_t gpio;
    printf("gpio task created\n");
    struct MqttMsg mqtt_msg;
    for(;;){
        if(xQueueReceiveFromISR(gpio_evt_queue, &gpio, NULL)){
            int prev = gpio_handler_read(gpio);
            vTaskDelay(100 / portTICK_PERIOD_MS);
            if(prev == gpio_handler_read(gpio)){
                mqtt_msg.gpio = gpio;
                mqtt_msg.status = gpio_handler_read(gpio);
                printf("ENVIO A MQTT\n");
                xQueueSendToBack(gpio_mqtt_queue, &mqtt_msg, 0);
                //printf("Interrupt-> %d: %s\n", gpio, (prev ? "HIGH" : "LOW"));
            }
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}


void gpio_handler_config_gpios(){
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt    
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    io_conf.pull_down_en = 0;//disable pull-down mode
    io_conf.pull_up_en = 0;//disable pull-up mode    
    gpio_config(&io_conf);//configure GPIO with the given settings

    io_conf.intr_type = GPIO_INTR_ANYEDGE;//interrupt of rising edge
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;    
    io_conf.pull_up_en = 1;//enable pull-up mode
    gpio_config(&io_conf);

    //change gpio intrrupt type for one pin
    //gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);

    gpio_install_isr_service(0);//Activa llamada a ISR cuando hay interrupciones
    //gpio_isr_handler_add(GPIO_IN_D36_36, gpio_handler_ISR, (void*) GPIO_IN_D36_36);
    gpio_isr_handler_add(GPIO_IN_D34_34, gpio_handler_ISR, (void*) GPIO_IN_D34_34);
    //gpio_isr_handler_remove(GPIO_IN_D34_34);
}