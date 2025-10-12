#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include <stdio.h>
#include <string.h>

#define UART_NUM UART_NUM_0
#define BUF_SIZE 1024

static lua_State *L = NULL;

void lua_repl_task(void *pvParameters) {
    char data[BUF_SIZE];
    int len;
    L = luaL_newstate();
    luaL_openlibs(L);
    printf("Lua REPL started. Type Lua commands.\n");
    while (1) {
        printf("> ");
        fflush(stdout);
        len = 0;
        int c;
        while ((c = getchar()) != '\n' && c != EOF && len < BUF_SIZE - 1) {
            data[len++] = (char)c;
            vTaskDelay(1); // Yield to FreeRTOS to prevent watchdog
        }
        data[len] = '\0';
        if (len > 0) {
            if (luaL_dostring(L, data) != LUA_OK) {
                printf("Lua error: %s\n", lua_tostring(L, -1));
                lua_pop(L, 1);
            }
        }
        vTaskDelay(1); // Yield after each command
    }
}

void start_lua_repl() {
    xTaskCreate(lua_repl_task, "lua_repl", 4096, NULL, 5, NULL);
}
