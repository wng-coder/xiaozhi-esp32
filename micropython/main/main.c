#include <esp_log.h>
#include <esp_err.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Board wrapper header - now as ESP-IDF component
#include "sp_esp32_s3_1_28_box_wrapper.h"
// Python-like test functions
#include "python_tests.h"

#define TAG "micropython_mod"

// Forward declarations for libmain.a functions
extern void board_init(void);
extern int board_get_status(void);

void app_main(void)
{
    ESP_LOGI(TAG, "Starting ESP32-S3 MicroPython Board Module");
    
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

    ESP_LOGI(TAG, "Initializing board functions...");
    
    // Initialize board wrapper
    void* board = spotpear_board_create();
    if (board) {
        ESP_LOGI(TAG, "Board instance created successfully");
        
        // Run comprehensive Python-style tests
        run_python_like_tests(board);
    } else {
        ESP_LOGE(TAG, "Failed to create board instance");
    }
    
    // Initialize board from libmain.a
    // TODO: Uncomment when board functions are available
    // board_init();
    // int status = board_get_status();
    // ESP_LOGI(TAG, "Board status: %d", status);
    
    ESP_LOGI(TAG, "libmain.a linked successfully!");
    ESP_LOGI(TAG, "Board initialization complete");
    
    // Main application loop
    while (1) {
        ESP_LOGI(TAG, "MicroPython module running...");
        vTaskDelay(pdMS_TO_TICKS(5000)); // Print every 5 seconds
    }
}
