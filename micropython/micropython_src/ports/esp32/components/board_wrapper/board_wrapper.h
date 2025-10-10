#ifndef BOARD_WRAPPER_H
#define BOARD_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

void* board_wrapper_create();
void board_wrapper_destroy(void* board);
const char* board_wrapper_get_type(void* board);
const char* board_wrapper_get_uuid(void* board);
// Add more function declarations as needed

#ifdef __cplusplus
}
#endif

#endif // BOARD_WRAPPER_H
