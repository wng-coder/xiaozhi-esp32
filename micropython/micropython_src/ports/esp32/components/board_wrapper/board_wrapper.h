#ifndef BOARD_WRAPPER_H
#define BOARD_WRAPPER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// C interface for Board class
void* board_wrapper_create();
void board_wrapper_destroy(void* board);
const char* board_wrapper_get_type(void* board);
const char* board_wrapper_get_uuid(void* board);
const char* board_wrapper_get_system_info(void* board);
bool board_wrapper_get_battery_level(void* board, int* level, bool* charging, bool* discharging);
bool board_wrapper_get_temperature(void* board, float* temperature);

#ifdef __cplusplus
}
#endif

#endif // BOARD_WRAPPER_H
