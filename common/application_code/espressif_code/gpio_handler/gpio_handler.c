#include "gpio_handler.h"
#include "gpio_handler_static.h"
#include "gpio_info.h"
#include "mqtt_config.h"
#include "task_config.h"
#include "rtc_config.h"
#include "queue_conf.h"

#include <stdint.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
//#include "queue.h"

static QueueHandle_t gpio_evt_queue;
QueueHandle_t gpio_queue;


void gpio_handler_init(){
    gpio_handler_config_gpios();
    gpio_evt_queue = xQueueCreate(15, sizeof(uint32_t));
    if(gpio_evt_queue != NULL){
        ( void ) xTaskCreate( gpio_handler_read_task,
                              TASK_GPIO_READ_NAME,
                              TASK_GPIO_READ_STACK_SIZE,
                              NULL,
                              TASK_READ_GPIO_PRIORITY,
                              NULL );

        ( void ) xTaskCreate( gpio_handler_write_task,
                              TASK_GPIO_WRITE_NAME,
                              TASK_GPIO_WRITE_STACK_SIZE,
                              NULL,
                              TASK_WRITE_GPIO_PRIORITY,
                              NULL );                              
    }
}


static void IRAM_ATTR gpio_handler_ISR(void* arg){
    uint32_t gpio_num = (uint32_t) arg;
    //printf("status: %d - \n", gpio_num);    
    xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

int gpio_handler_read(uint32_t gpio){
    return gpio_get_level(gpio);
}

void gpio_handler_write(uint32_t gpio, uint32_t level){
    switch(gpio){
        case 1: gpio = GPIO_DO01;
                break;
        case 2: gpio = GPIO_DO02;
                break;
        case 3: gpio = GPIO_DO03;
                break;
        case 4: gpio = GPIO_DO04;
                break;                
    }
    printf("write gpio-> %d:", gpio);    
    printf("%d\n", level);
    gpio_set_level(gpio, level);
}


void gpio_handler_read_task(void * pvParameters){
    (void) pvParameters;
    uint32_t gpio;
    printf("gpio task created\n");
    struct MqttMsg mqtt_msg;
    uint32_t interrupt_time = 0;
    bool report_change = false;
    int prev_status = 0;
    int curr_status = 0;
    BaseType_t xTaskWokenByReceive = pdFALSE;
    for(;;){
        while(xQueueReceiveFromISR(gpio_evt_queue, &gpio, NULL)){
            prev_status = gpio_handler_read(gpio);
            interrupt_time = rtc_config_get_ticks_MS();
            report_change = true;        
        }

        if( report_change &&  (rtc_config_get_ticks_MS() - interrupt_time > 50) ){
            curr_status = gpio_handler_read(gpio);
            report_change = false;
            if(prev_status == curr_status){
                mqtt_msg.gpio = gpio;
                mqtt_msg.status = curr_status;

                //printf("status: %d\n", prev_status);    
                //printf("GPIO: %d -- %d\n", gpio, prev_status);
                switch(gpio){
                    case GPIO_DI01:
                        snprintf(mqtt_msg.name, 10, "%s", DI01_NAME);
                        break;
                    case GPIO_DI02:
                        snprintf(mqtt_msg.name, 10, "%s", DI02_NAME);
                        break;
                    case GPIO_DI03:
                        snprintf(mqtt_msg.name, 10, "%s", DI03_NAME);
                        break;
                    case GPIO_DI04:
                        snprintf(mqtt_msg.name, 10, "%s", DI04_NAME);
                        break;
                    case GPIO_DI05:
                        snprintf(mqtt_msg.name, 10, "%s", DI05_NAME);
                        break;
                    case GPIO_DI06:
                        snprintf(mqtt_msg.name, 10, "%s", DI06_NAME);
                        break;
                    case GPIO_DI07:
                        snprintf(mqtt_msg.name, 10, "%s", DI07_NAME);
                        break;
                    case GPIO_DI08:
                        snprintf(mqtt_msg.name, 10, "%s", DI08_NAME);
                        break;                                                                                                                                                                        
                }

                queue_conf_send_mqtt(mqtt_msg);
            }
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}


void gpio_handler_write_task(void * pvParameters){
    (void) pvParameters;
    struct GPIOMsg gpio_msg;

    for(;;){
        while(xQueueReceive(gpio_queue, &gpio_msg, NULL) != errQUEUE_EMPTY){
            gpio_handler_write(gpio_msg.gpio, gpio_msg.status);            
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void gpio_handler_config_gpios(){
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;//disable interrupt    
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = gpio_handler_get_output_mask(); // Toma la mascara de bit de gpios de entrada
    io_conf.pull_down_en = 0;//disable pull-down mode
    io_conf.pull_up_en = 0;//disable pull-up mode    
    gpio_config(&io_conf);//configure GPIO with the given settings

    io_conf.intr_type = GPIO_INTR_ANYEDGE;//interrupt of rising edge
    io_conf.pin_bit_mask = gpio_handler_get_input_mask();
    io_conf.mode = GPIO_MODE_INPUT;    
    io_conf.pull_down_en = 0;//disable pull-down mode
    io_conf.pull_up_en = 1;//enable pull-up mode
    gpio_config(&io_conf);

    //change gpio intrrupt type for one pin
    //gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);

    gpio_install_isr_service(0);//Activa llamada a ISR cuando hay interrupciones
    //gpio_isr_handler_add(GPIO_IN_D36_36, gpio_handler_ISR, (void*) GPIO_IN_D36_36);
    if(USE_GPIO_DI01){
        gpio_isr_handler_add(GPIO_DI01, gpio_handler_ISR, (void*) GPIO_DI01);
        //gpio_set_intr_type(GPIO_DI01, GPIO_INTR_ANYEDGE);
    }
    if(USE_GPIO_DI02){
        gpio_isr_handler_add(GPIO_DI02, gpio_handler_ISR, (void*) GPIO_DI02);
        //gpio_set_intr_type(GPIO_DI02, GPIO_INTR_ANYEDGE);
    }
    if(USE_GPIO_DI03){
        gpio_isr_handler_add(GPIO_DI03, gpio_handler_ISR, (void*) GPIO_DI03);
        gpio_set_intr_type(GPIO_DI03, GPIO_INTR_ANYEDGE);
    }
    if(USE_GPIO_DI04){
        gpio_isr_handler_add(GPIO_DI04, gpio_handler_ISR, (void*) GPIO_DI04);
        //gpio_set_intr_type(GPIO_DI04, GPIO_INTR_ANYEDGE);
    }
    if(USE_GPIO_DI05){
        gpio_isr_handler_add(GPIO_DI05, gpio_handler_ISR, (void*) GPIO_DI05);
        //gpio_set_intr_type(GPIO_DI05, GPIO_INTR_ANYEDGE);
    }
    if(USE_GPIO_DI06){
        gpio_isr_handler_add(GPIO_DI06, gpio_handler_ISR, (void*) GPIO_DI06);
        //gpio_set_intr_type(GPIO_DI06, GPIO_INTR_ANYEDGE);
    }
    if(USE_GPIO_DI07){
        gpio_isr_handler_add(GPIO_DI07, gpio_handler_ISR, (void*) GPIO_DI07);
        //gpio_set_intr_type(GPIO_DI07, GPIO_INTR_ANYEDGE);
    }
    if(USE_GPIO_DI08){
        gpio_isr_handler_add(GPIO_DI08, gpio_handler_ISR, (void*) GPIO_DI08);
        //gpio_set_intr_type(GPIO_DI08, GPIO_INTR_ANYEDGE);
    }


}

static uint64_t gpio_handler_get_input_mask(){
    uint64_t input = 0;
    if(USE_GPIO_DI01){
        input |= 1ULL<<GPIO_DI01;
    }
    if(USE_GPIO_DI02){
        input |= 1ULL<<GPIO_DI02;
    }    
    if(USE_GPIO_DI03){
        input |= 1ULL<<GPIO_DI03;
    }    
    if(USE_GPIO_DI04){
        input |= 1ULL<<GPIO_DI04;
    }
    if(USE_GPIO_DI05){
        input |= 1ULL<<GPIO_DI05;
    }
    if(USE_GPIO_DI06){
        input |= 1ULL<<GPIO_DI06;
    }    
    if(USE_GPIO_DI07){
        input |= 1ULL<<GPIO_DI07;
    }    
    if(USE_GPIO_DI08){
        input |= 1ULL<<GPIO_DI08;
    }
                         

    return input;
}


static uint64_t gpio_handler_get_output_mask(){
    uint64_t output = 0;
    output |= 1ULL<<GPIO_DO01;
    output |= 1ULL<<GPIO_DO02;
    output |= 1ULL<<GPIO_DO03;
    output |= 1ULL<<GPIO_DO04;

    return output;
}