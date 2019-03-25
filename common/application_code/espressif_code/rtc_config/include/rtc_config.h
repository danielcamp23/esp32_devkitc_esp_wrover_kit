#ifndef _RTC_CONFIG_H_
#define _RTC_CONFIG_H_

#include "freertos/FreeRTOSConfig.h"
#include <stdint.h>

#if configTICK_RATE_HZ == 100
    #define RTC_CONFIG_FACTOR 10
    #define RTC_CONFIG_NORM_FACTOR 100
#else
    #define RTC_CONFIG_FACTOR 1
    #define RTC_CONFIG_NORM_FACTOR 1000
#endif

void rtc_config_init();
uint32_t rtc_config_get_time();
uint32_t rtc_config_get_ticks_MS();
void rtc_config_set_time(uint32_t in_time);
void rtc_config_set_time_(char * timeString, int len);



#endif

