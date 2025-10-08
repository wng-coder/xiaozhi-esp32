// ESP32_S3_1_28_BOX MicroPython board configuration
// Based on working ESP-IDF configuration from main project

#define MICROPY_HW_BOARD_NAME               "ESP32-S3 1.28 BOX"
#define MICROPY_HW_MCU_NAME                 "ESP32S3"

#define MICROPY_PY_BLUETOOTH                (0)
#define MICROPY_HW_ANTENNA_DIVERSITY        (0)

// Disable TinyUSB to avoid linker errors (CDC not available in main project)
#define MICROPY_PY_TINYUSB                  (0)

// Enable I2C with the new ESP-IDF v5.4 compatible driver
#define MICROPY_PY_MACHINE_I2C              (1)
#define MICROPY_HW_ESP_NEW_I2C_DRIVER       (1)

// Enable WiFi
#define MICROPY_PY_NETWORK_WLAN             (1)

// UART configuration for REPL
#define MICROPY_HW_UART_REPL                (UART_NUM_0)
#define MICROPY_HW_UART_REPL_BAUD           (115200)

// Enable PSRAM (matching main project configuration)
#define MICROPY_HW_PSRAM                    (1)
#define MICROPY_HW_PSRAM_SIZE               (8 * 1024 * 1024)  // 8MB PSRAM

// GPIO definitions for ESP32-S3 1.28 BOX
#define MICROPY_HW_SPI1_SCK                 (36)  // SPI1 clock
#define MICROPY_HW_SPI1_MOSI                (35)  // SPI1 MOSI  
#define MICROPY_HW_SPI1_MISO                (37)  // SPI1 MISO

// I2C pins (standard ESP32-S3 I2C)
#define MICROPY_HW_I2C0_SCL                 (9)   // I2C0 SCL
#define MICROPY_HW_I2C0_SDA                 (8)   // I2C0 SDA
#define MICROPY_HW_I2C1_SCL                 (18)  // I2C1 SCL
#define MICROPY_HW_I2C1_SDA                 (17)  // I2C1 SDA

// Enable filesystem on flash
#define MICROPY_HW_ENABLE_FILESYSTEM        (1)

// Enable USB for TinyUSB support
#define MICROPY_HW_ENABLE_USBDEV            (1)
#define MICROPY_HW_USB_CDC                  (1)
#define MICROPY_HW_USB_CDC_DTR_RTS_BOOTLOADER (1)

// ADC configuration
#define MICROPY_HW_ENABLE_ADC               (1)

// LED configuration (if available)
#define MICROPY_HW_LED1                     (48)  // Status LED

// Board-specific features
#define BOARD_FLASH_SIZE                    (16 * 1024 * 1024)  // 16MB Flash