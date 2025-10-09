#include "sp_esp32_s3_1_28_box_wrapper.h"
#include "xiaozhi_launcher.h"
#include <esp_log.h>
#include <driver/gpio.h>
#include <nvs_flash.h>
#include <esp_event.h>
#include <esp_system.h>
#include <esp_chip_info.h>
#include <esp_flash.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char* TAG = "board_wrapper";

// Simplified board structure for initial testing
struct SpotpearBoard {
    int volume;
    bool input_enabled;
    bool output_enabled;
    int brightness;
};

extern "C" {

void* spotpear_board_create() {
    ESP_LOGI(TAG, "Creating minimal board wrapper instance");
    SpotpearBoard* board = new SpotpearBoard();
    board->volume = 50;
    board->input_enabled = false;
    board->output_enabled = true;
    board->brightness = 80;
    return board;
}

void spotpear_board_destroy(void* board) {
    ESP_LOGI(TAG, "Destroying board wrapper instance");
    delete static_cast<SpotpearBoard*>(board);
}

void spotpear_board_toggle_chat(void* board) {
    ESP_LOGI(TAG, "Toggle chat state (minimal implementation)");
    // Minimal implementation for testing
}

void spotpear_board_set_output_volume(void* board, int volume) {
    ESP_LOGI(TAG, "Set output volume to %d", volume);
    auto* b = static_cast<SpotpearBoard*>(board);
    b->volume = volume;
}

void spotpear_board_enable_input(void* board, int enable) {
    ESP_LOGI(TAG, "Enable input: %s", enable ? "true" : "false");
    auto* b = static_cast<SpotpearBoard*>(board);
    b->input_enabled = (enable != 0);
}

void spotpear_board_enable_output(void* board, int enable) {
    ESP_LOGI(TAG, "Enable output: %s", enable ? "true" : "false");
    auto* b = static_cast<SpotpearBoard*>(board);
    b->output_enabled = (enable != 0);
}

int spotpear_board_get_output_volume(void* board) {
    auto* b = static_cast<SpotpearBoard*>(board);
    ESP_LOGI(TAG, "Get output volume: %d", b->volume);
    return b->volume;
}

int spotpear_board_is_input_enabled(void* board) {
    auto* b = static_cast<SpotpearBoard*>(board);
    ESP_LOGI(TAG, "Input enabled: %s", b->input_enabled ? "true" : "false");
    return b->input_enabled ? 1 : 0;
}

int spotpear_board_is_output_enabled(void* board) {
    auto* b = static_cast<SpotpearBoard*>(board);
    ESP_LOGI(TAG, "Output enabled: %s", b->output_enabled ? "true" : "false");
    return b->output_enabled ? 1 : 0;
}

// Display functions (minimal implementations)
void spotpear_board_set_chat_message(void* board, const char* role, const char* message) {
    ESP_LOGI(TAG, "Set chat message - Role: %s, Message: %s", role, message);
}

void spotpear_board_set_emotion(void* board, const char* emotion) {
    ESP_LOGI(TAG, "Set emotion: %s", emotion);
}

void spotpear_board_set_volume_indicator(void* board, int volume) {
    ESP_LOGI(TAG, "Set volume indicator: %d", volume);
}

void spotpear_board_set_mute_indicator(void* board, int muted) {
    ESP_LOGI(TAG, "Set mute indicator: %s", muted ? "muted" : "unmuted");
}

void spotpear_board_set_wifi_status(void* board, int connected) {
    ESP_LOGI(TAG, "Set WiFi status: %s", connected ? "connected" : "disconnected");
}

void spotpear_board_set_battery_level(void* board, int level) {
    ESP_LOGI(TAG, "Set battery level: %d%%", level);
}

// LED functions (minimal implementations)  
void spotpear_board_led_on(void* board) {
    ESP_LOGI(TAG, "LED ON");
    // TODO: Implement actual LED control
}

void spotpear_board_led_off(void* board) {
    ESP_LOGI(TAG, "LED OFF");
    // TODO: Implement actual LED control
}

void spotpear_board_led_blink(void* board, int count) {
    ESP_LOGI(TAG, "LED blink %d times", count);
    // TODO: Implement actual LED blink
}

// Backlight functions (minimal implementations)
void spotpear_board_set_brightness(void* board, int brightness) {
    ESP_LOGI(TAG, "Set brightness: %d", brightness);
    auto* b = static_cast<SpotpearBoard*>(board);
    b->brightness = brightness;
}

int spotpear_board_get_brightness(void* board) {
    auto* b = static_cast<SpotpearBoard*>(board);
    ESP_LOGI(TAG, "Get brightness: %d", b->brightness);
    return b->brightness;
}

void spotpear_board_restore_brightness(void* board) {
    ESP_LOGI(TAG, "Restore brightness");
    auto* b = static_cast<SpotpearBoard*>(board);
    b->brightness = 80; // Default brightness
}

// Touchpad functions (minimal implementations)
int spotpear_board_get_touch_x(void* board) {
    ESP_LOGI(TAG, "Get touch X coordinate");
    return -1; // No touch detected
}

int spotpear_board_get_touch_y(void* board) {
    ESP_LOGI(TAG, "Get touch Y coordinate");
    return -1; // No touch detected
}

int spotpear_board_is_touched(void* board) {
    ESP_LOGI(TAG, "Check touch status");
    return 0; // No touch detected
}

// Power management functions (minimal implementations)
void spotpear_board_set_power_save_mode(void* board, int enabled) {
    ESP_LOGI(TAG, "Set power save mode: %s", enabled ? "enabled" : "disabled");
    // TODO: Implement actual power management
}

// Application initialization functions (from main.cc integration)
int spotpear_board_init_nvs(void) {
    ESP_LOGI(TAG, "Initializing NVS flash");
    
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Erasing NVS flash to fix corruption");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "NVS flash initialized successfully");
        return 0;
    } else {
        ESP_LOGE(TAG, "Failed to initialize NVS flash: %s", esp_err_to_name(ret));
        return -1;
    }
}

int spotpear_board_init_event_loop(void) {
    ESP_LOGI(TAG, "Initializing default event loop");
    
    esp_err_t ret = esp_event_loop_create_default();
    if (ret == ESP_OK || ret == ESP_ERR_INVALID_STATE) {
        ESP_LOGI(TAG, "Event loop initialized successfully");
        return 0;
    } else {
        ESP_LOGE(TAG, "Failed to initialize event loop: %s", esp_err_to_name(ret));
        return -1;
    }
}

int spotpear_board_start_application(void) {
    ESP_LOGI(TAG, "Starting main application");
    // Note: We can't directly start the C++ Application class from here
    // This would be used to trigger application-specific initialization
    ESP_LOGI(TAG, "Application initialization placeholder - integrate with main Application class");
    return 0;
}

int spotpear_board_get_system_info(char* buffer, int buffer_size) {
    ESP_LOGI(TAG, "Getting system information");
    
    if (!buffer || buffer_size < 100) {
        return -1;
    }
    
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    
    uint32_t flash_size;
    esp_flash_get_size(NULL, &flash_size);
    
    snprintf(buffer, buffer_size,
        "ESP32-S3 Rev %d, %d CPU cores, WiFi%s%s, %dMB %s flash",
        chip_info.revision,
        chip_info.cores,
        (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
        (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
        (int)(flash_size / (1024 * 1024)),
        (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external"
    );
    
    return 0;
}

// Bridge function to launch xiaozhi application in separate task
static void xiaozhi_app_task(void* arg) {
    ESP_LOGI(TAG, "Starting xiaozhi application task");
    
    // This implements the exact logic from main.cc app_main() function:
    // 1. Event loop already created by spotpear_board_app_main()
    // 2. NVS already initialized by spotpear_board_app_main()  
    // 3. Now launch the actual Application class
    
    ESP_LOGI(TAG, "System initialization complete, launching xiaozhi application");
    
    // Launch the actual xiaozhi application
    // This will eventually call Application::GetInstance().Start()
    launch_xiaozhi_application();
    
    // Monitor application status
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(10000)); // Check every 10 seconds
        
        int status = get_xiaozhi_status();
        if (status <= 0) {
            ESP_LOGW(TAG, "Xiaozhi application stopped, status: %d", status);
            break;
        }
        
        ESP_LOGI(TAG, "Xiaozhi application running normally");
    }
    
    ESP_LOGE(TAG, "Xiaozhi application task ended");
    stop_xiaozhi_application();
    vTaskDelete(NULL);
}

// Direct wrapper for the complete app_main function
void spotpear_board_app_main(void) {
    ESP_LOGI(TAG, "Starting ESP32 system initialization");
    
    // 1. Initialize default event loop
    esp_err_t ret = esp_event_loop_create_default();
    if (ret != ESP_OK && ret != ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "Failed to create event loop: %s", esp_err_to_name(ret));
        return;
    }
    
    // 2. Initialize NVS flash
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Erasing NVS flash to fix corruption");
        nvs_flash_erase();
        ret = nvs_flash_init();
    }
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize NVS: %s", esp_err_to_name(ret));
        return;
    }
    
    // 3. Launch xiaozhi application as separate task
    TaskHandle_t xiaozhi_task_handle;
    BaseType_t task_result = xTaskCreate(
        xiaozhi_app_task,
        "xiaozhi_app",
        8192,  // Stack size
        NULL,  // Parameters
        5,     // Priority
        &xiaozhi_task_handle
    );
    
    if (task_result == pdPASS) {
        ESP_LOGI(TAG, "Xiaozhi application task created successfully");
    } else {
        ESP_LOGE(TAG, "Failed to create xiaozhi application task");
    }
}

}