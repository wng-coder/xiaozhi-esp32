#!/bin/bash
# Compile and link modspotpear.c and sp_esp32_s3_1_28_box_wrapper.cpp with libmain.a for MicroPython native module

set -e

# Paths
MAIN_DIR="./main"
MICROPY_DIR="./micropython"
COMMON_DIR="$MAIN_DIR/boards/common"
ML307_DIR="./managed_components/78__esp-ml307/include"
FREERTOS_DIR="$IDF_PATH/components/freertos/include"
FREERTOS_KERNEL_DIR="$IDF_PATH/components/freertos/FreeRTOS-Kernel/include"
BUILD_CONFIG_DIR="./build/config"
LIBMAIN="./libmain.a"

# Compile C++ wrapper
 g++ -c $MICROPY_DIR/sp_esp32_s3_1_28_box_wrapper.cpp -o $MICROPY_DIR/sp_esp32_s3_1_28_box_wrapper.o \
    -I$MAIN_DIR -I$MICROPY_DIR -I$COMMON_DIR -I$ML307_DIR -I$FREERTOS_DIR -I$FREERTOS_KERNEL_DIR -I$BUILD_CONFIG_DIR

# Compile C module
 gcc -c $MICROPY_DIR/modspotpear.c -o $MICROPY_DIR/modspotpear.o \
    -I$MAIN_DIR -I$MICROPY_DIR -I$COMMON_DIR -I$ML307_DIR -I$FREERTOS_DIR -I$FREERTOS_KERNEL_DIR -I$BUILD_CONFIG_DIR

# Link to shared object
 g++ -shared -o $MICROPY_DIR/modspotpear.so $MICROPY_DIR/modspotpear.o $MICROPY_DIR/sp_esp32_s3_1_28_box_wrapper.o $LIBMAIN -lstdc++ -fPIC

echo "Build complete: $MICROPY_DIR/modspotpear.so"
