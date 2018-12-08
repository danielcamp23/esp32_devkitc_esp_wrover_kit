#ifndef _RTC_CONFIG_H_
#define _RTC_CONFIG_H_
#include <stdint.h>
#include "freertos/FreeRTOSConfig.h"

#if configTICK_RATE_HZ == 100
    #define RTC_CONFIG_FACTOR 10
#else
    #define RTC_CONFIG_FACTOR 1
#endif

void rtc_config_init();
uint32_t rtc_config_get_time();

#endif

