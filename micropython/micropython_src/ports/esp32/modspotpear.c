#include "py/runtime.h"
#include "sp_esp32_s3_1_28_box_wrapper.h"
#include <string.h>

typedef struct _mp_obj_spotpear_t {
    mp_obj_base_t base;
    void* board;
} mp_obj_spotpear_t;

static mp_obj_t spotpear_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_obj_spotpear_t *self = m_new_obj(mp_obj_spotpear_t);
    self->base.type = type;
    self->board = spotpear_board_create();
    return MP_OBJ_FROM_PTR(self);
}

static mp_obj_t spotpear_toggle_chat(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    spotpear_board_toggle_chat(self->board);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_toggle_chat_obj, spotpear_toggle_chat);

static mp_obj_t spotpear_set_output_volume(mp_obj_t self_in, mp_obj_t volume_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int volume = mp_obj_get_int(volume_obj);
    spotpear_board_set_output_volume(self->board, volume);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_output_volume_obj, spotpear_set_output_volume);

static mp_obj_t spotpear_enable_input(mp_obj_t self_in, mp_obj_t enable_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int enable = mp_obj_is_true(enable_obj) ? 1 : 0;
    spotpear_board_enable_input(self->board, enable);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_enable_input_obj, spotpear_enable_input);

static mp_obj_t spotpear_enable_output(mp_obj_t self_in, mp_obj_t enable_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int enable = mp_obj_is_true(enable_obj) ? 1 : 0;
    spotpear_board_enable_output(self->board, enable);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_enable_output_obj, spotpear_enable_output);

static mp_obj_t spotpear_get_output_volume(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int volume = spotpear_board_get_output_volume(self->board);
    return mp_obj_new_int(volume);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_get_output_volume_obj, spotpear_get_output_volume);

static mp_obj_t spotpear_is_input_enabled(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int enabled = spotpear_board_is_input_enabled(self->board);
    return mp_obj_new_bool(enabled);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_is_input_enabled_obj, spotpear_is_input_enabled);

static mp_obj_t spotpear_is_output_enabled(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int enabled = spotpear_board_is_output_enabled(self->board);
    return mp_obj_new_bool(enabled);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_is_output_enabled_obj, spotpear_is_output_enabled);

// Display functions
static mp_obj_t spotpear_set_chat_message(mp_obj_t self_in, mp_obj_t role_obj, mp_obj_t message_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    const char *role = mp_obj_str_get_str(role_obj);
    const char *message = mp_obj_str_get_str(message_obj);
    spotpear_board_set_chat_message(self->board, role, message);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_3(spotpear_set_chat_message_obj, spotpear_set_chat_message);

static mp_obj_t spotpear_set_emotion(mp_obj_t self_in, mp_obj_t emotion_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    const char *emotion = mp_obj_str_get_str(emotion_obj);
    spotpear_board_set_emotion(self->board, emotion);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_emotion_obj, spotpear_set_emotion);

static mp_obj_t spotpear_set_volume_indicator(mp_obj_t self_in, mp_obj_t volume_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int volume = mp_obj_get_int(volume_obj);
    spotpear_board_set_volume_indicator(self->board, volume);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_volume_indicator_obj, spotpear_set_volume_indicator);

static mp_obj_t spotpear_set_mute_indicator(mp_obj_t self_in, mp_obj_t muted_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int muted = mp_obj_is_true(muted_obj) ? 1 : 0;
    spotpear_board_set_mute_indicator(self->board, muted);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_mute_indicator_obj, spotpear_set_mute_indicator);

static mp_obj_t spotpear_set_wifi_status(mp_obj_t self_in, mp_obj_t connected_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int connected = mp_obj_is_true(connected_obj) ? 1 : 0;
    spotpear_board_set_wifi_status(self->board, connected);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_wifi_status_obj, spotpear_set_wifi_status);

static mp_obj_t spotpear_set_battery_level(mp_obj_t self_in, mp_obj_t level_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int level = mp_obj_get_int(level_obj);
    spotpear_board_set_battery_level(self->board, level);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_battery_level_obj, spotpear_set_battery_level);

// LED functions
static mp_obj_t spotpear_led_on(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    spotpear_board_led_on(self->board);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_led_on_obj, spotpear_led_on);

static mp_obj_t spotpear_led_off(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    spotpear_board_led_off(self->board);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_led_off_obj, spotpear_led_off);

static mp_obj_t spotpear_led_blink(mp_obj_t self_in, mp_obj_t count_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int count = mp_obj_get_int(count_obj);
    spotpear_board_led_blink(self->board, count);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_led_blink_obj, spotpear_led_blink);

// Backlight functions
static mp_obj_t spotpear_set_brightness(mp_obj_t self_in, mp_obj_t brightness_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int brightness = mp_obj_get_int(brightness_obj);
    spotpear_board_set_brightness(self->board, brightness);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_brightness_obj, spotpear_set_brightness);

static mp_obj_t spotpear_get_brightness(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int brightness = spotpear_board_get_brightness(self->board);
    return mp_obj_new_int(brightness);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_get_brightness_obj, spotpear_get_brightness);

static mp_obj_t spotpear_restore_brightness(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    spotpear_board_restore_brightness(self->board);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_restore_brightness_obj, spotpear_restore_brightness);

// Touchpad functions
static mp_obj_t spotpear_get_touch_x(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int x = spotpear_board_get_touch_x(self->board);
    return mp_obj_new_int(x);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_get_touch_x_obj, spotpear_get_touch_x);

static mp_obj_t spotpear_get_touch_y(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int y = spotpear_board_get_touch_y(self->board);
    return mp_obj_new_int(y);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_get_touch_y_obj, spotpear_get_touch_y);

static mp_obj_t spotpear_is_touched(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int touched = spotpear_board_is_touched(self->board);
    return mp_obj_new_bool(touched);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_is_touched_obj, spotpear_is_touched);

// Power management functions
static mp_obj_t spotpear_set_power_save_mode(mp_obj_t self_in, mp_obj_t enabled_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int enabled = mp_obj_is_true(enabled_obj) ? 1 : 0;
    spotpear_board_set_power_save_mode(self->board, enabled);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_power_save_mode_obj, spotpear_set_power_save_mode);

// Application initialization functions (from main.cc integration)
static mp_obj_t spotpear_init_nvs(mp_obj_t self_in) {
    int result = spotpear_board_init_nvs();
    return mp_obj_new_bool(result == 0);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_init_nvs_obj, spotpear_init_nvs);

static mp_obj_t spotpear_init_event_loop(mp_obj_t self_in) {
    int result = spotpear_board_init_event_loop();
    return mp_obj_new_bool(result == 0);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_init_event_loop_obj, spotpear_init_event_loop);

static mp_obj_t spotpear_start_application(mp_obj_t self_in) {
    int result = spotpear_board_start_application();
    return mp_obj_new_bool(result == 0);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_start_application_obj, spotpear_start_application);

static mp_obj_t spotpear_get_system_info(mp_obj_t self_in) {
    char buffer[256];
    int result = spotpear_board_get_system_info(buffer, sizeof(buffer));
    if (result == 0) {
        return mp_obj_new_str(buffer, strlen(buffer));
    } else {
        return mp_const_none;
    }
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_get_system_info_obj, spotpear_get_system_info);

// Convenience aliases for volume control
static mp_obj_t spotpear_set_volume(mp_obj_t self_in, mp_obj_t volume_obj) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int volume = mp_obj_get_int(volume_obj);
    spotpear_board_set_output_volume(self->board, volume);
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(spotpear_set_volume_obj, spotpear_set_volume);

static mp_obj_t spotpear_get_volume(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    int volume = spotpear_board_get_output_volume(self->board);
    return mp_obj_new_int(volume);
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_get_volume_obj, spotpear_get_volume);

// Direct app_main wrapper
static mp_obj_t spotpear_app_main(mp_obj_t self_in) {
    spotpear_board_app_main();
    return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(spotpear_app_main_obj, spotpear_app_main);

static void spotpear_deinit(mp_obj_t self_in) {
    mp_obj_spotpear_t *self = MP_OBJ_TO_PTR(self_in);
    spotpear_board_destroy(self->board);
}

static const mp_rom_map_elem_t spotpear_locals_dict_table[] = {
    // Chat control
    { MP_ROM_QSTR(MP_QSTR_toggle_chat), MP_ROM_PTR(&spotpear_toggle_chat_obj) },
    
    // Audio codec control
    { MP_ROM_QSTR(MP_QSTR_set_output_volume), MP_ROM_PTR(&spotpear_set_output_volume_obj) },
    { MP_ROM_QSTR(MP_QSTR_enable_input), MP_ROM_PTR(&spotpear_enable_input_obj) },
    { MP_ROM_QSTR(MP_QSTR_enable_output), MP_ROM_PTR(&spotpear_enable_output_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_output_volume), MP_ROM_PTR(&spotpear_get_output_volume_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_input_enabled), MP_ROM_PTR(&spotpear_is_input_enabled_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_output_enabled), MP_ROM_PTR(&spotpear_is_output_enabled_obj) },
    
    // Convenience volume aliases
    { MP_ROM_QSTR(MP_QSTR_set_volume), MP_ROM_PTR(&spotpear_set_volume_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_volume), MP_ROM_PTR(&spotpear_get_volume_obj) },
    
    // Display control
    { MP_ROM_QSTR(MP_QSTR_set_chat_message), MP_ROM_PTR(&spotpear_set_chat_message_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_emotion), MP_ROM_PTR(&spotpear_set_emotion_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_volume_indicator), MP_ROM_PTR(&spotpear_set_volume_indicator_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_mute_indicator), MP_ROM_PTR(&spotpear_set_mute_indicator_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_wifi_status), MP_ROM_PTR(&spotpear_set_wifi_status_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_battery_level), MP_ROM_PTR(&spotpear_set_battery_level_obj) },
    
    // LED control
    { MP_ROM_QSTR(MP_QSTR_led_on), MP_ROM_PTR(&spotpear_led_on_obj) },
    { MP_ROM_QSTR(MP_QSTR_led_off), MP_ROM_PTR(&spotpear_led_off_obj) },
    { MP_ROM_QSTR(MP_QSTR_led_blink), MP_ROM_PTR(&spotpear_led_blink_obj) },
    
    // Backlight control
    { MP_ROM_QSTR(MP_QSTR_set_brightness), MP_ROM_PTR(&spotpear_set_brightness_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_brightness), MP_ROM_PTR(&spotpear_get_brightness_obj) },
    { MP_ROM_QSTR(MP_QSTR_restore_brightness), MP_ROM_PTR(&spotpear_restore_brightness_obj) },
    
    // Touchpad control
    { MP_ROM_QSTR(MP_QSTR_get_touch_x), MP_ROM_PTR(&spotpear_get_touch_x_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_touch_y), MP_ROM_PTR(&spotpear_get_touch_y_obj) },
    { MP_ROM_QSTR(MP_QSTR_is_touched), MP_ROM_PTR(&spotpear_is_touched_obj) },
    
    // Power management
    { MP_ROM_QSTR(MP_QSTR_set_power_save_mode), MP_ROM_PTR(&spotpear_set_power_save_mode_obj) },
    
    // Application initialization (from main.cc)
    { MP_ROM_QSTR(MP_QSTR_init_nvs), MP_ROM_PTR(&spotpear_init_nvs_obj) },
    { MP_ROM_QSTR(MP_QSTR_init_event_loop), MP_ROM_PTR(&spotpear_init_event_loop_obj) },
    { MP_ROM_QSTR(MP_QSTR_start_application), MP_ROM_PTR(&spotpear_start_application_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_system_info), MP_ROM_PTR(&spotpear_get_system_info_obj) },
    
    // Direct app_main wrapper (complete main.cc functionality)
    { MP_ROM_QSTR(MP_QSTR_app_main), MP_ROM_PTR(&spotpear_app_main_obj) },
};
static MP_DEFINE_CONST_DICT(spotpear_locals_dict, spotpear_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
    spotpear_type,
    MP_QSTR_SpotpearBoard,
    MP_TYPE_FLAG_NONE,
    make_new, spotpear_make_new,
    locals_dict, &spotpear_locals_dict
);

static const mp_rom_map_elem_t spotpear_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR_SpotpearBoard), MP_ROM_PTR(&spotpear_type) },
};
static MP_DEFINE_CONST_DICT(spotpear_module_globals, spotpear_module_globals_table);

const mp_obj_module_t spotpear_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&spotpear_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_spotpear, spotpear_user_cmodule);
