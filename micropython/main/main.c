#include <stdio.h>
#include "esp_log.h"

static const char* TAG = "micropython_mod";

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32-S3 Box Board Module initialized");
    ESP_LOGI(TAG, "libmain.a linked successfully!");
}
