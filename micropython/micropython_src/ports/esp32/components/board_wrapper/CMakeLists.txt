# ESP-IDF Component registration for full MicroPython board wrapper

# Compute repository root and common paths relative to this CMakeLists.txt
get_filename_component(BOARD_WRAPPER_DIR "${CMAKE_CURRENT_LIST_DIR}" ABSOLUTE)
get_filename_component(COMPONENTS_DIR "${BOARD_WRAPPER_DIR}/.." ABSOLUTE)      # .../ports/esp32/components
get_filename_component(PORTS_DIR "${COMPONENTS_DIR}/.." ABSOLUTE)              # .../ports/esp32
get_filename_component(MICROPY_SRC_DIR "${PORTS_DIR}/.." ABSOLUTE)             # .../micropython_src
get_filename_component(MICROPY_DIR "${MICROPY_SRC_DIR}/.." ABSOLUTE)           # .../micropython
get_filename_component(REPO_ROOT "${MICROPY_DIR}/.." ABSOLUTE)                 # .../xiaozhi-esp32

set(MAIN_DIR            "${REPO_ROOT}/main")
set(MANAGED_DIR         "${REPO_ROOT}/managed_components")
set(MICROPY_PY_DIR      "${MICROPY_SRC_DIR}/py")

idf_component_register(
    SRCS
        "board_wrapper.cpp"
        "/workspaces/xiaozhi-esp32/main/boards/common/board.cc"
        "/workspaces/xiaozhi-esp32/main/system_info.cc"
        "/workspaces/xiaozhi-esp32/main/settings.cc"
        "/workspaces/xiaozhi-esp32/main/display/display.cc"
        "/workspaces/xiaozhi-esp32/main/display/oled_display.cc"
        "/workspaces/xiaozhi-esp32/main/assets.cc"
        "/workspaces/xiaozhi-esp32/micropython/micropython_src/ports/esp32/modboard.c"

    INCLUDE_DIRS
        .
        "/workspaces/xiaozhi-esp32/main"
        "/workspaces/xiaozhi-esp32/main/boards/common"
        "/workspaces/xiaozhi-esp32/main/display"
        "/workspaces/xiaozhi-esp32/main/display/lvgl_display"
        "/workspaces/xiaozhi-esp32/main/audio"
    "/workspaces/xiaozhi-esp32/micropython/micropython_src"
        "/workspaces/xiaozhi-esp32/lib/mbedtls/include"
        "/workspaces/xiaozhi-esp32/main/protocols"
        "/workspaces/xiaozhi-esp32/lib/fsp/ra/fsp/src/rm_freertos_plus_tcp"
        "/workspaces/xiaozhi-esp32/main/boards/jiuchuan-s3"
        "/workspaces/xiaozhi-esp32/main/boards/sensecap-watcher"
        "/workspaces/xiaozhi-esp32/managed_components/lvgl__lvgl"
        "/workspaces/xiaozhi-esp32/managed_components/lvgl__lvgl/src"
        "/workspaces/xiaozhi-esp32/managed_components/78__esp-ml307/include"
        "/workspaces/xiaozhi-esp32/managed_components/78__esp-wifi-connect/include"
        "/workspaces/xiaozhi-esp32/managed_components/espressif__adc_battery_estimation/include"
        "/workspaces/xiaozhi-esp32/managed_components/78__esp-opus/include"
        "/workspaces/xiaozhi-esp32/managed_components/78__esp-opus-encoder/include"
    "/workspaces/xiaozhi-esp32/managed_components/espressif__esp_lcd_panel_io_additions/include"
    "/workspaces/xiaozhi-esp32/managed_components/espressif__esp_lvgl_port/include"
    "/workspaces/xiaozhi-esp32/managed_components/78__xiaozhi-fonts/include"

    REQUIRES 
        esp_timer 
        esp_lcd
        spi_flash
        app_update
        bootloader_support
        esp_app_format
        freertos
        json
        driver
        nvs_flash
        esp_partition
        esp_pm
        lwip
        mbedtls
        mqtt
        espressif__esp_lvgl_port
        lvgl
        78__xiaozhi-fonts
        cxx
        newlib
)

set_target_properties(${COMPONENT_LIB} PROPERTIES CXX_STANDARD 17)
target_compile_definitions(${COMPONENT_LIB} PRIVATE BOARD_NAME="SPOTPEAR_S3_128_BOX")