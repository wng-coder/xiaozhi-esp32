#include "sp_esp32_s3_1_28_box_wrapper.h"
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static const char* TAG = "python_test";

// Python-like test functions that call the board wrapper
void test_audio_functions(void* board) {
    ESP_LOGI(TAG, "=== Testing Audio Functions ===");
    
    // Test volume control
    ESP_LOGI(TAG, ">>> board.set_output_volume(80)");
    spotpear_board_set_output_volume(board, 80);
    
    ESP_LOGI(TAG, ">>> volume = board.get_output_volume()");
    int volume = spotpear_board_get_output_volume(board);
    ESP_LOGI(TAG, ">>> print(f'Volume: {volume}')");
    ESP_LOGI(TAG, "Volume: %d", volume);
    
    // Test enable/disable
    ESP_LOGI(TAG, ">>> board.enable_output(True)");
    spotpear_board_enable_output(board, 1);
    
    ESP_LOGI(TAG, ">>> board.enable_input(False)");
    spotpear_board_enable_input(board, 0);
    
    ESP_LOGI(TAG, ">>> output_enabled = board.is_output_enabled()");
    int output_enabled = spotpear_board_is_output_enabled(board);
    ESP_LOGI(TAG, ">>> print(f'Output enabled: {output_enabled}')");
    ESP_LOGI(TAG, "Output enabled: %s", output_enabled ? "True" : "False");
}

void test_display_functions(void* board) {
    ESP_LOGI(TAG, "=== Testing Display Functions ===");
    
    ESP_LOGI(TAG, ">>> board.set_chat_message('user', 'Hello from Python!')");
    spotpear_board_set_chat_message(board, "user", "Hello from Python!");
    
    ESP_LOGI(TAG, ">>> board.set_emotion('excited')");
    spotpear_board_set_emotion(board, "excited");
    
    ESP_LOGI(TAG, ">>> board.set_wifi_status(True)");
    spotpear_board_set_wifi_status(board, 1);
    
    ESP_LOGI(TAG, ">>> board.set_battery_level(95)");
    spotpear_board_set_battery_level(board, 95);
}

void test_led_functions(void* board) {
    ESP_LOGI(TAG, "=== Testing LED Functions ===");
    
    ESP_LOGI(TAG, ">>> board.led_on()");
    spotpear_board_led_on(board);
    vTaskDelay(pdMS_TO_TICKS(1000));
    
    ESP_LOGI(TAG, ">>> board.led_off()");
    spotpear_board_led_off(board);
    vTaskDelay(pdMS_TO_TICKS(500));
    
    ESP_LOGI(TAG, ">>> board.led_blink(5)");
    spotpear_board_led_blink(board, 5);
}

void test_backlight_functions(void* board) {
    ESP_LOGI(TAG, "=== Testing Backlight Functions ===");
    
    ESP_LOGI(TAG, ">>> board.set_brightness(100)");
    spotpear_board_set_brightness(board, 100);
    
    ESP_LOGI(TAG, ">>> brightness = board.get_brightness()");
    int brightness = spotpear_board_get_brightness(board);
    ESP_LOGI(TAG, ">>> print(f'Brightness: {brightness}%%')");
    ESP_LOGI(TAG, "Brightness: %d%%", brightness);
    
    ESP_LOGI(TAG, ">>> board.set_brightness(50)");
    spotpear_board_set_brightness(board, 50);
    
    ESP_LOGI(TAG, ">>> board.restore_brightness()");
    spotpear_board_restore_brightness(board);
}

void test_touchpad_functions(void* board) {
    ESP_LOGI(TAG, "=== Testing Touchpad Functions ===");
    
    ESP_LOGI(TAG, ">>> x = board.get_touch_x()");
    int x = spotpear_board_get_touch_x(board);
    
    ESP_LOGI(TAG, ">>> y = board.get_touch_y()");  
    int y = spotpear_board_get_touch_y(board);
    
    ESP_LOGI(TAG, ">>> touched = board.is_touched()");
    int touched = spotpear_board_is_touched(board);
    
    ESP_LOGI(TAG, ">>> print(f'Touch: x={x}, y={y}, touched={touched}')");
    ESP_LOGI(TAG, "Touch: x=%d, y=%d, touched=%s", x, y, touched ? "True" : "False");
}

void test_power_functions(void* board) {
    ESP_LOGI(TAG, "=== Testing Power Management ===");
    
    ESP_LOGI(TAG, ">>> board.set_power_save_mode(False)");
    spotpear_board_set_power_save_mode(board, 0);
    
    ESP_LOGI(TAG, ">>> board.toggle_chat()");
    spotpear_board_toggle_chat(board);
}

void run_python_like_tests(void* board) {
    ESP_LOGI(TAG, "🐍 Starting Python-like Board Tests 🐍");
    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "# Python equivalent test script:");
    ESP_LOGI(TAG, "# import spotpear");
    ESP_LOGI(TAG, "# board = spotpear.SpotpearBoard()");
    ESP_LOGI(TAG, "");
    
    test_audio_functions(board);
    ESP_LOGI(TAG, "");
    
    test_display_functions(board);
    ESP_LOGI(TAG, "");
    
    test_led_functions(board);
    ESP_LOGI(TAG, "");
    
    test_backlight_functions(board);
    ESP_LOGI(TAG, "");
    
    test_touchpad_functions(board);
    ESP_LOGI(TAG, "");
    
    test_power_functions(board);
    ESP_LOGI(TAG, "");
    
    ESP_LOGI(TAG, "🎉 All Python-style tests completed! 🎉");
}