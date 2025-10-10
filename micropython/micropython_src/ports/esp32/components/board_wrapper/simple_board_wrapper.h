#ifndef SIMPLE_BOARD_WRAPPER_H
#define SIMPLE_BOARD_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

// Simple board functions 
const char* board_get_name(void);
char* board_get_system_info(void);
void board_init(void);
void board_deinit(void);

#ifdef __cplusplus
}
#endif

#endif // SIMPLE_BOARD_WRAPPER_H