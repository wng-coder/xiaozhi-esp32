set(IDF_TARGET esp32s3)

set(SDKCONFIG_DEFAULTS
    boards/sdkconfig.base
    boards/sdkconfig.ble
    boards/sdkconfig.240mhz
    boards/SPOTPEAR_S3_128_BOX/sdkconfig.board
)

# Disable I2C completely to avoid driver conflicts
list(APPEND MICROPY_DEF_BOARD
    MICROPY_HW_ENABLE_I2C=0
    MICROPY_HW_USB_CDC=0
    MICROPY_HW_ENABLE_USBDEV=0
)

# Explicitly disable TinyUSB to avoid linker errors
set(MICROPY_PY_TINYUSB OFF)