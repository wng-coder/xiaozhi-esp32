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

#define TAG "main"
#define BUF_SIZE 1024

void app_main(void)
{
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "Erasing NVS flash to fix corruption");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    printf("Lua REPL started. Type Lua commands.\n");
    char data[BUF_SIZE];
    int len;
    while (1) {
        printf("> ");
        fflush(stdout);
        len = 0;
        int c;
        while ((c = getchar()) != '\n' && c != EOF && len < BUF_SIZE - 1) {
            data[len++] = (char)c;
            vTaskDelay(1);
        }
        data[len] = '\0';
        if (len > 0) {
            if (luaL_dostring(L, data) != LUA_OK) {
                printf("Lua error: %s\n", lua_tostring(L, -1));
                lua_pop(L, 1);
            }
        }
        vTaskDelay(1);
    }
}
