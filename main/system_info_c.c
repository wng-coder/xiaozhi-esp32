
#include "system_info_c.h"
#include "system_info.h"

extern "C" {
size_t SystemInfo_GetFlashSize(void) {
    return SystemInfo::GetFlashSize();
}
size_t SystemInfo_GetMinimumFreeHeapSize(void) {
    return SystemInfo::GetMinimumFreeHeapSize();
}
size_t SystemInfo_GetFreeHeapSize(void) {
    return SystemInfo::GetFreeHeapSize();
}
esp_err_t SystemInfo_PrintTaskCpuUsage(TickType_t xTicksToWait) {
    return SystemInfo::PrintTaskCpuUsage(xTicksToWait);
}
void SystemInfo_PrintTaskList(void) {
    SystemInfo::PrintTaskList();
}
void SystemInfo_PrintHeapStats(void) {
    SystemInfo::PrintHeapStats();
}
}
