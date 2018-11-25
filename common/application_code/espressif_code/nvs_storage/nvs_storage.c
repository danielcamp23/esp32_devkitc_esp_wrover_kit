#include "nvs_storage.h"
#include "nvs_flash.h"
#include "flags.h"

void nvs_storage_init(){
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ) {
        printf("Error nvs_flash_init()\n");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    flags_set_nvs_ok();
    printf("NVS started ok\n");
}