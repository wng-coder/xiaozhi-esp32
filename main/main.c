#include <esp_log.h>
#include <esp_err.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "application_c.h"
#include "system_info_c.h"

#define TAG "main"

void app_main(void)
{
    // Initialize the default event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Initialize NVS flash for WiFi configuration
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Erasing NVS flash to fix corruption");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Launch the application using C interface
    struct Application* app = Application_GetInstance();
    Application_Start(app);

    // Example usage of system info C interface
    size_t flash_size = SystemInfo_GetFlashSize();
    size_t min_heap = SystemInfo_GetMinimumFreeHeapSize();
    size_t free_heap = SystemInfo_GetFreeHeapSize();
    ESP_LOGI(TAG, "Flash size: %zu, Min heap: %zu, Free heap: %zu", flash_size, min_heap, free_heap);
    SystemInfo_PrintTaskList();
    SystemInfo_PrintHeapStats();
}
