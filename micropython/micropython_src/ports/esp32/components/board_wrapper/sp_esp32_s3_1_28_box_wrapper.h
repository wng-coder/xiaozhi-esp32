#ifndef SP_ESP32_S3_1_28_BOX_WRAPPER_H
#define SP_ESP32_S3_1_28_BOX_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

// Board management
void* spotpear_board_create(void);
void spotpear_board_destroy(void* board);

// Chat control
void spotpear_board_toggle_chat(void* board);

// Audio codec control
void spotpear_board_set_output_volume(void* board, int volume);
void spotpear_board_enable_input(void* board, int enable);
void spotpear_board_enable_output(void* board, int enable);
int spotpear_board_get_output_volume(void* board);
int spotpear_board_is_input_enabled(void* board);
int spotpear_board_is_output_enabled(void* board);

// Display functions
void spotpear_board_set_chat_message(void* board, const char* role, const char* message);
void spotpear_board_set_emotion(void* board, const char* emotion);
void spotpear_board_set_volume_indicator(void* board, int volume);
void spotpear_board_set_mute_indicator(void* board, int muted);
void spotpear_board_set_wifi_status(void* board, int connected);
void spotpear_board_set_battery_level(void* board, int level);

// LED functions
    void spotpear_board_led_on(void* board);
    void spotpear_board_led_off(void* board);
    void spotpear_board_led_blink(void* board, int count);
    void spotpear_board_set_led(void* board, int r, int g, int b);// Backlight functions
void spotpear_board_set_brightness(void* board, int brightness);
int spotpear_board_get_brightness(void* board);
void spotpear_board_restore_brightness(void* board);

// Touchpad functions
int spotpear_board_get_touch_x(void* board);
int spotpear_board_get_touch_y(void* board);
int spotpear_board_is_touched(void* board);

// Power management functions
void spotpear_board_set_power_save_mode(void* board, int enabled);

// I2C functions
int spotpear_board_i2c_scan(void* board, int* devices, int max_devices);

// Application initialization functions (from main.cc)
// Application initialization functions from main.cc
int spotpear_board_init_nvs(void);
int spotpear_board_init_event_loop(void);
int spotpear_board_start_application(void);
int spotpear_board_get_system_info(char* buffer, int buffer_size);

// Direct app_main wrapper
void spotpear_board_app_main(void);

#ifdef __cplusplus
}
#endif

#endif // SP_ESP32_S3_1_28_BOX_WRAPPER_H
