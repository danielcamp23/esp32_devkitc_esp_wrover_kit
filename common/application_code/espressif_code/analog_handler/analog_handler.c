#include "analog_handler.h"
#include "analog_handler_static.h"
#include "analog_info.h"
#include "task_config.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static esp_adc_cal_characteristics_t *adc_chars;
//static const adc_channel_t channel = ADC_CHANNEL_6;     //GPIO34 if ADC1, GPIO14 if ADC2
static const adc_atten_t atten = ADC_ATTEN_DB_0;
static const adc_unit_t unit = ADC_UNIT_1; //TODO por revisar - al parecer solo funciona el módulo 1

void analog_handler_init(){
    analog_handler_check_efuse();

    //Configure ADC
  
    if (unit == ADC_UNIT_1) {
        adc1_config_width(ADC_WIDTH_BIT_12);

        if(USE_GPIO_AN01){
            adc1_config_channel_atten(GPIO_AN01, atten);
        }
        if(USE_GPIO_AN02){
            adc1_config_channel_atten(GPIO_AN02, atten);
        }
        if(USE_GPIO_AN03){
            adc2_config_channel_atten(GPIO_AN03, atten);
        }
        if(USE_GPIO_AN04){
            adc2_config_channel_atten(GPIO_AN04, atten);
        }
        if(USE_GPIO_AN05){
            adc2_config_channel_atten(GPIO_AN05, atten);
        }
        if(USE_GPIO_AN06){
            adc2_config_channel_atten(GPIO_AN06, atten);
        }                                                        
    } 

    //Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    //esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
    //print_char_val_type(val_type);

    ( void ) xTaskCreate( analog_handler_task,
                            TASK_ANALOG_NAME,
                            TASK_ANALOG_STACK_SIZE,
                            NULL,
                            TASK_ANALOG_PRIORITY,
                            NULL );
}

 static void analog_handler_check_efuse(){
    //Check TP is burned into eFuse
    /*if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }*/
}

void analog_handler_task(void * pvParameters){
    for(;;){
        uint32_t adc_reading_an01 = 0;
        uint32_t adc_reading_an02 = 0;
        uint32_t adc_reading_an03 = 0;
        uint32_t adc_reading_an04 = 0;
        uint32_t adc_reading_an05 = 0;
        uint32_t adc_reading_an06 = 0;

        uint32_t an01_last_read = 0;
        uint32_t an02_last_read = 0;
        uint32_t an03_last_read = 0;
        uint32_t an04_last_read = 0;
        uint32_t an05_last_read = 0;
        uint32_t an06_last_read = 0;

        int raw;
        bool init = false;
        
        for(int i = 0 ; i < NO_OF_SAMPLES; ++i) {
            if(USE_GPIO_AN01){
                adc_reading_an01 += adc1_get_raw((adc1_channel_t)GPIO_AN01);
            }
            if(USE_GPIO_AN02){
                adc_reading_an02 += adc1_get_raw((adc1_channel_t)GPIO_AN02);
            }
            if(USE_GPIO_AN03){
                (void)adc2_get_raw((adc2_channel_t)GPIO_AN03, ADC_WIDTH_BIT_12, &raw);
                adc_reading_an03 += raw;
            }
            if(USE_GPIO_AN04){
                (void)adc2_get_raw((adc2_channel_t)GPIO_AN04, ADC_WIDTH_BIT_12, &raw);
                adc_reading_an04 += raw;
            }
            if(USE_GPIO_AN05){
                (void)adc2_get_raw((adc2_channel_t)GPIO_AN05, ADC_WIDTH_BIT_12, &raw);
                adc_reading_an05 += raw;
            }
            if(USE_GPIO_AN06){
                (void)adc2_get_raw((adc2_channel_t)GPIO_AN06, ADC_WIDTH_BIT_12, &raw);
                adc_reading_an06 += raw;
            }
        }


        adc_reading_an01 /= NO_OF_SAMPLES;
        adc_reading_an02 /= NO_OF_SAMPLES;
        adc_reading_an03 /= NO_OF_SAMPLES;
        adc_reading_an04 /= NO_OF_SAMPLES;
        adc_reading_an05 /= NO_OF_SAMPLES;


        if(init){
            if(USE_GPIO_AN01){
                if(analog_handler_compare(an01_last_read, adc_reading_an01)){
                    an01_last_read = adc_reading_an01;
                }
            }
            if(USE_GPIO_AN02){
                if(analog_handler_compare(an02_last_read, adc_reading_an02)){
                    an02_last_read = adc_reading_an02;                    
                }
            }
            if(USE_GPIO_AN03){
                if(analog_handler_compare(an03_last_read, adc_reading_an03)){
                    an03_last_read = adc_reading_an03;                    
                }
            }
            if(USE_GPIO_AN04){
                if(analog_handler_compare(an04_last_read, adc_reading_an04)){
                    an04_last_read = adc_reading_an04;                    
                }
            }
            if(USE_GPIO_AN05){
                if(analog_handler_compare(an05_last_read, adc_reading_an05)){
                    an05_last_read = adc_reading_an05;                    
                }
            }
            if(USE_GPIO_AN06){
                if(analog_handler_compare(an06_last_read, adc_reading_an06)){
                    an06_last_read = adc_reading_an06;                    
                }
            }
        }
        else{
            an01_last_read = adc_reading_an01;
            an02_last_read = adc_reading_an02;
            an03_last_read = adc_reading_an03;
            an04_last_read = adc_reading_an04;
            an05_last_read = adc_reading_an05;
            an06_last_read = adc_reading_an06;
            init = true;
        }



        
        /*printf("adc_reading_an01: %d\n", adc_reading_an01);
        printf("adc_reading_an02: %d\n", adc_reading_an02);*/
        //TODO comentado por pruebas
        init = true;
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}


static bool analog_handler_compare(uint32_t past_val, uint32_t cur_val){
    if(cur_val >= past_val){
        return cur_val - past_val > ANALOG_RANGE;
    }
    else{
        return past_val - cur_val > ANALOG_RANGE;
    }
}
