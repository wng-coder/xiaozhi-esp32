#include "../main/boards/common/wifi_board.h"

#include "sp_esp32_s3_1_28_box_wrapper.h"
#include "../main/boards/sp-esp32-s3-1.28-box/sp_esp32_s3_1_28_box.h"
#include "../main/boards/sp-esp32-s3-1.28-box/application.h"

extern "C" {

void* spotpear_board_create() {
    return new Spotpear_ESP32_S3_1_28_BOX();
}

void spotpear_board_destroy(void* board) {
    delete static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
}

void spotpear_board_toggle_chat(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    Application::GetInstance().ToggleChatState();
}

void spotpear_board_set_output_volume(void* board, int volume) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetAudioCodec()->SetOutputVolume(volume);
}

void spotpear_board_enable_input(void* board, int enable) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetAudioCodec()->EnableInput(enable != 0);
}

void spotpear_board_enable_output(void* board, int enable) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetAudioCodec()->EnableOutput(enable != 0);
}

int spotpear_board_get_output_volume(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    return b->GetAudioCodec()->output_volume();
}

int spotpear_board_is_input_enabled(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    return b->GetAudioCodec()->input_enabled() ? 1 : 0;
}

int spotpear_board_is_output_enabled(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    return b->GetAudioCodec()->output_enabled() ? 1 : 0;
}

// Display functions
void spotpear_board_set_chat_message(void* board, const char* role, const char* message) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetDisplay()->SetChatMessage(role, message);
}

void spotpear_board_set_emotion(void* board, const char* emotion) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetDisplay()->SetEmotion(emotion);
}

void spotpear_board_set_volume_indicator(void* board, int volume) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetDisplay()->SetVolumeIndicator(volume);
}

void spotpear_board_set_mute_indicator(void* board, int muted) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetDisplay()->SetMuteIndicator(muted != 0);
}

void spotpear_board_set_wifi_status(void* board, int connected) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetDisplay()->SetWifiStatus(connected != 0);
}

void spotpear_board_set_battery_level(void* board, int level) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetDisplay()->SetBatteryLevel(level);
}

// LED functions
void spotpear_board_led_on(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetLed()->On();
}

void spotpear_board_led_off(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetLed()->Off();
}

void spotpear_board_led_blink(void* board, int count) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetLed()->Blink(count);
}

// Backlight functions
void spotpear_board_set_brightness(void* board, int brightness) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetBacklight()->SetBrightness(brightness);
}

int spotpear_board_get_brightness(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    return b->GetBacklight()->GetBrightness();
}

void spotpear_board_restore_brightness(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->GetBacklight()->RestoreBrightness();
}

// Touchpad functions
int spotpear_board_get_touch_x(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    auto* touchpad = b->GetTouchpad();
    if (touchpad) {
        return touchpad->GetTouchPoint().x;
    }
    return -1;
}

int spotpear_board_get_touch_y(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    auto* touchpad = b->GetTouchpad();
    if (touchpad) {
        return touchpad->GetTouchPoint().y;
    }
    return -1;
}

int spotpear_board_is_touched(void* board) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    auto* touchpad = b->GetTouchpad();
    if (touchpad) {
        return touchpad->GetTouchPoint().num > 0 ? 1 : 0;
    }
    return 0;
}

// Power management functions
void spotpear_board_set_power_save_mode(void* board, int enabled) {
    auto* b = static_cast<Spotpear_ESP32_S3_1_28_BOX*>(board);
    b->SetPowerSaveMode(enabled != 0);
}

}