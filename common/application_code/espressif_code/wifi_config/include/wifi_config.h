#ifndef _WIFI_CONFIG_STATIC_H_
#define _WIFI_CONFIG_STATIC_H_

#include "acua_wifi.h"

void wifi_config_init();

void wifi_config_task(void * pvParameters);

WIFIReturnCode_t wifi_config_start_driver();
#endif