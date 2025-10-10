#include "board_wrapper.h"
#include "boards/common/board.h"

#ifdef __cplusplus
extern "C" {
#endif

// Create and destroy
void* board_wrapper_create() {
    return static_cast<void*>(&Board::GetInstance());
}
void board_wrapper_destroy(void* board) {
    // Board is a singleton, do not delete
}

// Get board type
const char* board_wrapper_get_type(void* board) {
    Board* b = static_cast<Board*>(board);
    static std::string type = b->GetBoardType();
    return type.c_str();
}

// Get UUID
const char* board_wrapper_get_uuid(void* board) {
    Board* b = static_cast<Board*>(board);
    static std::string uuid = b->GetUuid();
    return uuid.c_str();
}

// Add more wrappers as needed (LED, Backlight, etc.)

#ifdef __cplusplus
}
#endif
