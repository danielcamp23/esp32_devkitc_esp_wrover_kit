#ifndef _GPIO_HANDLER_H_
#define _GPIO_HANDLER_H_

#include <stdint.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

void gpio_handler_init();

void gpio_handler_task(void * pvParameters);

int gpio_handler_read(uint32_t gpio);

void gpio_handler_write(uint32_t gpio, uint32_t level);

void gpio_handler_config_gpios();

#endif