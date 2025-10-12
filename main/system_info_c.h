#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <esp_err.h>
#include <freertos/FreeRTOS.h>

size_t SystemInfo_GetFlashSize(void);
size_t SystemInfo_GetMinimumFreeHeapSize(void);
size_t SystemInfo_GetFreeHeapSize(void);
esp_err_t SystemInfo_PrintTaskCpuUsage(TickType_t xTicksToWait);
void SystemInfo_PrintTaskList(void);
void SystemInfo_PrintHeapStats(void);

#ifdef __cplusplus
}
#endif
