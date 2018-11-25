#ifndef _FLAGS_H_
#define _FLAGS_H_

#include <stdbool.h>

typedef unsigned int boolean_t;

typedef union {
    struct{
        boolean_t nvs : 1;
        boolean_t spiffs : 1;
        int not_used : 30;        
    };
    int raw_flags;
} flags_t;

extern flags_t CONTROL_FLAGS;
 
void flags_init();

bool flags_is_nvs_ok();

void flags_set_nvs_ok();

#endif