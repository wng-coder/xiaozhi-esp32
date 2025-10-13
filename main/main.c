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

#include <stdlib.h>


#define TAG "main"
#define BUF_SIZE 4096



static void *esp_idf_lua_alloc(void *ud, void *ptr, size_t osize, size_t nsize) {
    (void)ud; (void)osize;
    if (nsize == 0) {
        free(ptr);
        return NULL;
    } else {
        return realloc(ptr, nsize);
    }
}

static int lua_repl_cmd(int argc, char **argv)
{
    size_t heap_before = esp_get_free_heap_size();
    if (heap_before < 65536) {
        printf("Warning: low heap before Lua init: %lu\n", (unsigned long)heap_before);
    }

    lua_State *L = lua_newstate(esp_idf_lua_alloc, NULL);
    if (!L) {
        printf("Failed to create Lua state!\n");
        return 1;
    }
    luaL_openlibs(L);
    printf("Lua REPL started. Type Lua code. End with a single dot '.' on a line.\n");
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
        if (line_len > 0 && data[total_len + line_len - 1] == '\n') {
            data[total_len + line_len - 1] = '\0';
            line_len--;
        }
        if (line_len == 1 && data[total_len] == '.') {
            break;
        }
        total_len += line_len;
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
    lua_close(L);
    return 0;
}

void app_main(void)
{
    // Diagnostics: print heap and stack info
    printf("Free heap: %lu\n", (unsigned long)esp_get_free_heap_size());

    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t repl_config = ESP_CONSOLE_REPL_CONFIG_DEFAULT();
    repl_config.prompt = "repl >";
    repl_config.task_stack_size = 8192; // Increase stack size for Lua
    const esp_console_cmd_t lua_cmd = {
        .command = "lua",
        .help = "Start Lua REPL (end input with '.')",
        .func = &lua_repl_cmd,
    };
    esp_console_dev_usb_cdc_config_t usb_cdc_config = {};
    linenoiseSetDumbMode(1);

    ESP_ERROR_CHECK(esp_console_new_repl_usb_cdc(&usb_cdc_config, &repl_config, &repl));
    ESP_ERROR_CHECK(esp_console_cmd_register(&lua_cmd));
    ESP_ERROR_CHECK(esp_console_start_repl(repl));
}
