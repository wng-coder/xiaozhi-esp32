#ifndef MICROPY_HW_BOARD_NAME
#define MICROPY_HW_BOARD_NAME               "SpotPear ESP32-S3 1.28 Box"
#endif
#define MICROPY_HW_MCU_NAME                 "ESP32S3"

// Enable UART REPL for modules that have an external USB-UART and don't use native USB.
#define MICROPY_HW_ENABLE_UART_REPL         (1)

// Disable native USB as we're using external USB-UART
#define MICROPY_HW_ENABLE_USBDEV            (0)
#define MICROPY_HW_USB_CDC                  (0)

// Disable I2C to avoid driver conflicts with our board wrapper
// The board wrapper manages I2C directly
// #define MICROPY_HW_I2C0_SCL                 (14)
// #define MICROPY_HW_I2C0_SDA                 (15)

// SPI configuration for display
#define MICROPY_HW_SPI1_MOSI                (7)
#define MICROPY_HW_SPI1_MISO                (6)
#define MICROPY_HW_SPI1_SCK                 (5)

// LED configuration
#define MICROPY_HW_LED1                     (48)

// Audio I2S pins
#define MICROPY_HW_I2S0_MCLK                (16)
#define MICROPY_HW_I2S0_WS                  (45)
#define MICROPY_HW_I2S0_SCK                 (9)
#define MICROPY_HW_I2S0_SDO                 (8)
#define MICROPY_HW_I2S0_SDI                 (10)