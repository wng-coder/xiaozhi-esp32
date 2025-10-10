#include <string.h>
#include "esp_system.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "cJSON.h"

static const char *TAG = "board_wrapper";

// Simple board information
const char* board_get_name(void) {
    return BOARD_NAME;
}

// Basic system info without complex dependencies
char* board_get_system_info(void) {
    cJSON *json = cJSON_CreateObject();
    if (!json) {
        ESP_LOGE(TAG, "Failed to create JSON object");
        return NULL;
    }

    // Basic system information
    cJSON_AddStringToObject(json, "board", BOARD_NAME);
    cJSON_AddStringToObject(json, "chip", CONFIG_IDF_TARGET);
    cJSON_AddStringToObject(json, "idf_version", IDF_VER);
    
    // Add heap info
    cJSON_AddNumberToObject(json, "free_heap", esp_get_free_heap_size());
    cJSON_AddNumberToObject(json, "min_free_heap", esp_get_minimum_free_heap_size());
    
    char *json_string = cJSON_Print(json);
    cJSON_Delete(json);
    
    if (!json_string) {
        ESP_LOGE(TAG, "Failed to serialize JSON");
        return NULL;
    }
    
    return json_string;
}

// Simple init function
void board_init(void) {
    ESP_LOGI(TAG, "Simple board wrapper initialized for %s", BOARD_NAME);
}

// Simple deinit function  
void board_deinit(void) {
    ESP_LOGI(TAG, "Simple board wrapper deinitialized");
}