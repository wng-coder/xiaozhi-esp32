#include "board_wrapper.h"
#include <esp_random.h>
#include <esp_log.h>
#include <string>
#include <esp_chip_info.h>
#include <esp_ota_ops.h>

static const char *TAG = "board_wrapper";

// Simple Board class for MicroPython integration - gets functionality from the real Board when needed
class MinimalBoard {
private:
    std::string uuid_;
    
    std::string GenerateUuid() {
        uint8_t uuid[16];
        esp_fill_random(uuid, sizeof(uuid));
        
        uuid[6] = (uuid[6] & 0x0f) | 0x40;  // Version 4
        uuid[8] = (uuid[8] & 0x3f) | 0x80;  // Variant 10
        
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
    MinimalBoard() {
        uuid_ = GenerateUuid();
        ESP_LOGI(TAG, "MinimalBoard created with UUID=%s", uuid_.c_str());
    }
    
    std::string GetBoardType() {
        return "SPOTPEAR_S3_128_BOX";
    }
    
    std::string GetUuid() {
        return uuid_;
    }
    
    std::string GetSystemInfoJson() {
        // Minimal system info
        std::string json = "{";
        json += "\"board_type\":\"SPOTPEAR_S3_128_BOX\",";
        json += "\"uuid\":\"" + uuid_ + "\",";
        
        esp_chip_info_t chip_info;
        esp_chip_info(&chip_info);
        json += "\"chip_model\":" + std::to_string(chip_info.model) + ",";
        json += "\"chip_cores\":" + std::to_string(chip_info.cores) + ",";
        json += "\"chip_revision\":" + std::to_string(chip_info.revision);
        json += "}";
        return json;
    }
    
    bool GetBatteryLevel(int &level, bool& charging, bool& discharging) {
        level = 75;  // Mock battery level
        charging = false;
        discharging = true;
        return true;
    }
    
    bool GetTemperature(float& esp32temp) {
        esp32temp = 35.5f;  // Mock temperature
        return true;
    }
};

extern "C" {
// Create and destroy MinimalBoard
void* board_wrapper_create() {
    return static_cast<void*>(new MinimalBoard());
}

void board_wrapper_destroy(void* board) {
    MinimalBoard* b = static_cast<MinimalBoard*>(board);
    delete b;
}

// Get board type
const char* board_wrapper_get_type(void* board) {
    MinimalBoard* b = static_cast<MinimalBoard*>(board);
    static std::string type = b->GetBoardType();
    return type.c_str();
}

// Get UUID  
const char* board_wrapper_get_uuid(void* board) {
    MinimalBoard* b = static_cast<MinimalBoard*>(board);
    static std::string uuid = b->GetUuid();
    return uuid.c_str();
}

// Get system info JSON
const char* board_wrapper_get_system_info(void* board) {
    MinimalBoard* b = static_cast<MinimalBoard*>(board);
    static std::string info = b->GetSystemInfoJson();
    return info.c_str();
}

// Get battery level
bool board_wrapper_get_battery_level(void* board, int* level, bool* charging, bool* discharging) {
    MinimalBoard* b = static_cast<MinimalBoard*>(board);
    return b->GetBatteryLevel(*level, *charging, *discharging);
}

// Get temperature
bool board_wrapper_get_temperature(void* board, float* temperature) {
    MinimalBoard* b = static_cast<MinimalBoard*>(board);
    return b->GetTemperature(*temperature);
}
}
