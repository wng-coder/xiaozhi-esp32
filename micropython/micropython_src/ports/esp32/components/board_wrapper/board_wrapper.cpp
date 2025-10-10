#include "board_wrapper.h"
#include "../../../../../../main/boards/common/board.h"
#include <esp_log.h>
#include <string>

static const char *TAG = "board_wrapper";

// Real Board class wrapper - using the actual Board implementation

extern "C" {
// Create and destroy - use real Board singleton
void* board_wrapper_create() {
    return static_cast<void*>(&Board::GetInstance());
}

void board_wrapper_destroy(void* board) {
    // Board is singleton - don't delete
}

// Get board type - use real Board method
const char* board_wrapper_get_type(void* board) {
    Board* b = static_cast<Board*>(board);
    static std::string type = b->GetBoardType();
    return type.c_str();
}

// Get UUID - use real Board UUID with persistent storage
const char* board_wrapper_get_uuid(void* board) {
    Board* b = static_cast<Board*>(board);
    static std::string uuid = b->GetUuid();
    return uuid.c_str();
}

// Get system info JSON - use real comprehensive system info
const char* board_wrapper_get_system_info(void* board) {
    Board* b = static_cast<Board*>(board);
    static std::string info = b->GetSystemInfoJson();
    return info.c_str();
}

// Get battery level - use real Board functionality
bool board_wrapper_get_battery_level(void* board, int* level, bool* charging, bool* discharging) {
    Board* b = static_cast<Board*>(board);
    return b->GetBatteryLevel(*level, *charging, *discharging);
}

// Get temperature - use real Board functionality  
bool board_wrapper_get_temperature(void* board, float* temperature) {
    Board* b = static_cast<Board*>(board);
    return b->GetTemperature(*temperature);
}
}
