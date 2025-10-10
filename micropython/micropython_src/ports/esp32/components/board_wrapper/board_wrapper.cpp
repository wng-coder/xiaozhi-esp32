#include "board_wrapper.h"
#include <esp_random.h>
#include <esp_log.h>
#include <string>

static const char *TAG = "board_wrapper";

// Forward declarations for stub classes
class Led;
class AudioCodec;
class Display;
class Camera;
class NetworkInterface;
class Backlight;

// Minimal Board implementation as a standalone class for MicroPython wrapper
class MinimalBoard {
private:
    std::string uuid_;
    
    std::string GenerateUuid() {
        // Simple UUID v4 generation
        uint8_t uuid[16];
        esp_fill_random(uuid, sizeof(uuid));
        
        // Set version (4) and variant bits
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
        ESP_LOGI(TAG, "MinimalBoard UUID=%s", uuid_.c_str());
    }
    
    ~MinimalBoard() = default;
    
    std::string GetBoardType() {
        return "SPOTPEAR_S3_128_BOX";
    }
    
    Backlight* GetBacklight() {
        return nullptr; // Stub implementation  
    }
    
    Led* GetLed() {
        return nullptr; // Stub implementation
    }
    
    AudioCodec* GetAudioCodec() {
        return nullptr; // Stub implementation
    }
    
    bool GetTemperature(float& esp32temp) {
        esp32temp = 25.0f; // Stub temperature
        return false; // Stub implementation
    }
    
    Display* GetDisplay() {
        return nullptr; // Stub implementation
    }
    
    Camera* GetCamera() {
        return nullptr; // Stub implementation
    }
    
    NetworkInterface* GetNetwork() {
        return nullptr; // Stub implementation
    }
    
    void StartNetwork() {
        // Stub implementation
    }
    
    const char* GetNetworkStateIcon() {
        return ""; // Stub implementation
    }
    
    bool GetBatteryLevel(int &level, bool& charging, bool& discharging) {
        level = 50; // Stub battery level
        charging = false;
        discharging = false;
        return false; // Stub implementation
    }
    
    std::string GetSystemInfoJson() {
        return "{}"; // Stub implementation
    }
    
    void SetPowerSaveMode(bool enabled) {
        // Stub implementation
    }
    
    std::string GetBoardJson() {
        return "{}"; // Stub implementation
    }
    
    std::string GetDeviceStatusJson() {
        return "{}"; // Stub implementation
    }
    
    std::string GetUuid() {
        return uuid_;
    }
};

extern "C" {
// Create and destroy
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
// Add more wrappers as needed (LED, Backlight, etc.)
}
