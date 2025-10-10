#pragma once

// Minimal stub for model_path.h - only the definitions needed for compilation
// Full implementation would be in the main xiaozhi application

#define SRMODEL_STRING_LENGTH 32
#define MODEL_NAME_MAX_LENGTH 64

#ifdef ESP_PLATFORM
#include "esp_partition.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Minimal stub structures - only what's needed for header compilation
typedef struct {
    int num;
    char **files;
    char **data;
    int *sizes;
} srmodel_data_t;

typedef struct {
    char **model_name;
    char **model_info;
#ifdef ESP_PLATFORM
    esp_partition_t *partition;
#endif
    void *mmap_handle;
    int num;
    srmodel_data_t **model_data;
} srmodel_list_t;

#ifdef __cplusplus
}
#endif