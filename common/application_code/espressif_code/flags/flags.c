#include "flags.h"
#include <stdio.h>


flags_t CONTROL_FLAGS;

void flags_init(){
    printf("flags_init()\n");
    CONTROL_FLAGS.raw_flags = 0;
}

bool flags_is_nvs_ok(){
    if(CONTROL_FLAGS.nvs){
        return true;
    }
    else{
        return false;
    }
}

void flags_set_nvs_ok(){
    CONTROL_FLAGS.nvs = 1;
}

bool flags_is_wifi_connected(){
        if(CONTROL_FLAGS.wifi_connected){
        return true;
    }
    else{
        return false;
    }
}

void flags_set_wifi_connected(){
    CONTROL_FLAGS.wifi_connected = 1;
}