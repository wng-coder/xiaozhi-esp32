#include "board_wrapper.h"
#include <esp_log.h>
#include <esp_random.h>
#include <esp_chip_info.h>
#include <esp_ota_ops.h>
#include <esp_system.h>
#include <esp_heap_caps.h>
#include <nvs_flash.h>
#include <nvs.h>
#include <string>
#include <cstring>

static const char *TAG = "board_wrapper";

// Simple Board implementation without external dependencies
class SimpleBoard {
private:
    std::string uuid_;
    std::string board_type_;
    
    std::string GenerateUuid() {
        // UUID v4 generation
        uint8_t uuid[16];
        esp_fill_random(uuid, sizeof(uuid));
        
        // Set version (4) and variant bits
        uuid[6] = (uuid[6] & 0x0f) | 0x40;
        uuid[8] = (uuid[8] & 0x3f) | 0x80;
        
        char uuid_str[37];
        snprintf(uuid_str, sizeof(uuid_str),
                "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                uuid[0], uuid[1], uuid[2], uuid[3],
                uuid[4], uuid[5], uuid[6], uuid[7],
                uuid[8], uuid[9], uuid[10], uuid[11],
                uuid[12], uuid[13], uuid[14], uuid[15]);
        return std::string(uuid_str);
    }
    
public:
    SimpleBoard() : board_type_("SPOTPEAR_S3_128_BOX") {
        // Initialize NVS
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
            ESP_ERROR_CHECK(nvs_flash_erase());
            ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);
        
        // Load or generate UUID
        nvs_handle_t nvs_handle;
        ret = nvs_open("board", NVS_READONLY, &nvs_handle);
        if (ret == ESP_OK) {
            size_t required_size = 0;
            ret = nvs_get_str(nvs_handle, "uuid", NULL, &required_size);
            if (ret == ESP_OK && required_size > 0) {
                char* uuid_buf = (char*)malloc(required_size);
                ret = nvs_get_str(nvs_handle, "uuid", uuid_buf, &required_size);
                if (ret == ESP_OK) {
                    uuid_ = std::string(uuid_buf);
                }
                free(uuid_buf);
            }
            nvs_close(nvs_handle);
        }
        
        // Generate new UUID if not found
        if (uuid_.empty()) {
            uuid_ = GenerateUuid();
            ret = nvs_open("board", NVS_READWRITE, &nvs_handle);
            if (ret == ESP_OK) {
                nvs_set_str(nvs_handle, "uuid", uuid_.c_str());
                nvs_commit(nvs_handle);
                nvs_close(nvs_handle);
            }
        }
        
        ESP_LOGI(TAG, "Board initialized - UUID=%s SKU=%s", uuid_.c_str(), board_type_.c_str());
    }
    
    const std::string& GetUuid() const { return uuid_; }
    const std::string& GetBoardType() const { return board_type_; }
    
    std::string GetSystemInfo() const {
        esp_chip_info_t chip_info;
        esp_chip_info(&chip_info);
        
        const esp_app_desc_t* app_desc = esp_ota_get_app_description();
        
        char info[512];
        snprintf(info, sizeof(info),
                "Chip: %s Rev %d, CPU Cores: %d, WiFi%s%s, Flash: %dMB %s, Heap: %d bytes free, Version: %s",
                (chip_info.model == CHIP_ESP32) ? "ESP32" :
                (chip_info.model == CHIP_ESP32S2) ? "ESP32-S2" :
                (chip_info.model == CHIP_ESP32S3) ? "ESP32-S3" :
                (chip_info.model == CHIP_ESP32C3) ? "ESP32-C3" : "Unknown",
                chip_info.revision,
                chip_info.cores,
                (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "/802.11bgn" : "",
                (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
                spi_flash_get_chip_size() / (1024 * 1024),
                (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external",
                esp_get_free_heap_size(),
                app_desc->version);
        return std::string(info);
    }
    
    int GetBatteryLevel() const {
        // Simulated battery level - replace with actual ADC reading if available
        return 85;
    }
    
    float GetTemperature() const {
        // Simulated temperature - replace with actual sensor reading if available  
        return 25.5f;
    }
};

static SimpleBoard* g_board = nullptr;

extern "C" {

void* board_wrapper_create() {
    if (!g_board) {
        g_board = new SimpleBoard();
    }
    return static_cast<void*>(g_board);
}

void board_wrapper_destroy(void* board) {
    // Keep singleton alive
}

const char* board_wrapper_get_board_type(void* board) {
    if (!board) return "unknown";
    SimpleBoard* b = static_cast<SimpleBoard*>(board);
    return b->GetBoardType().c_str();
}

const char* board_wrapper_get_uuid(void* board) {
    if (!board) return "";
    SimpleBoard* b = static_cast<SimpleBoard*>(board);
    return b->GetUuid().c_str();
}

const char* board_wrapper_get_system_info(void* board) {
    if (!board) return "";
    SimpleBoard* b = static_cast<SimpleBoard*>(board);
    static std::string info = b->GetSystemInfo();
    return info.c_str();
}

int board_wrapper_get_battery_level(void* board) {
    if (!board) return 0;
    SimpleBoard* b = static_cast<SimpleBoard*>(board);
    return b->GetBatteryLevel();
}

float board_wrapper_get_temperature(void* board) {
    if (!board) return 0.0f;
    SimpleBoard* b = static_cast<SimpleBoard*>(board);
    return b->GetTemperature();
}

} // extern "C"