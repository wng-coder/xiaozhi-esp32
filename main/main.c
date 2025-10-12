#include <esp_log.h>
#include <esp_err.h>
#include <nvs.h>
#include <nvs_flash.h>
#include <esp_event.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "esp_console.h"
#include "linenoise/linenoise.h"
#include "esp_vfs_dev.h"


#define TAG "main"
#define BUF_SIZE 4096


// TinyUSB CDC ACM includes
#include "tinyusb.h"
#include "tusb_cdc_acm.h"
#include "tusb_console.h"

void lua_repl(void)
{
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    printf("Lua REPL started. Type Lua commands.\n");
    while (1) {
        printf("Enter Lua code (end with a single dot '.' on a line):\n");
        fflush(stdout);
        char data[BUF_SIZE];
        int total_len = 0;
        while (1) {
            printf(">> ");
            fflush(stdout);
            if (fgets(data + total_len, BUF_SIZE - total_len, stdin) == NULL) {
                printf("Input error or EOF!\n");
                break;
            }
            size_t line_len = strlen(data + total_len);
            // Remove trailing newline
            if (line_len > 0 && data[total_len + line_len - 1] == '\n') {
                data[total_len + line_len - 1] = '\0';
                line_len--;
            }
            if (line_len == 1 && data[total_len] == '.') {
                break;
            }
            total_len += line_len;
            // Add newline after each line except the last
            if (total_len + 1 < BUF_SIZE) {
                data[total_len] = '\n';
                total_len++;
            } else {
                printf("Input too long!\n");
                break;
            }
        }
        data[total_len] = '\0';
        if (total_len > 0) {
            if (luaL_dostring(L, data) != LUA_OK) {
                printf("Lua error: %s\n", lua_tostring(L, -1));
                lua_pop(L, 1);
            }
        }
        vTaskDelay(1);
    }
    lua_close(L);
}

void app_main(void)
{
    // TinyUSB CDC ACM initialization (based on tusb_console_main.c)
    ESP_LOGI(TAG, "USB initialization");
    const tinyusb_config_t tusb_cfg = {
        .device_descriptor = NULL,
        .string_descriptor = NULL,
        .external_phy = false,
#if (TUD_OPT_HIGH_SPEED)
        .fs_configuration_descriptor = NULL,
        .hs_configuration_descriptor = NULL,
        .qualifier_descriptor = NULL,
#else
        .configuration_descriptor = NULL,
#endif
    };
    ESP_ERROR_CHECK(tinyusb_driver_install(&tusb_cfg));

    tinyusb_config_cdcacm_t acm_cfg = { 0 };
    ESP_ERROR_CHECK(tusb_cdc_acm_init(&acm_cfg));

    ESP_LOGI(TAG, "USB initialization DONE");
    esp_tusb_init_console(TINYUSB_CDC_ACM_0);
    ESP_LOGI(TAG, "console routed to USB");

    // Diagnostics: print heap and stack info
    printf("Free heap: %lu\n", (unsigned long)esp_get_free_heap_size());

    // Minimal echo test for serial input
    char buf[128];
    while (1) {
        printf("Type something: ");
        fflush(stdout);
        if (fgets(buf, sizeof(buf), stdin)) {
            printf("You typed: %s\n", buf);
        } else {
            printf("Input error or EOF!\n");
        }
    }
}
