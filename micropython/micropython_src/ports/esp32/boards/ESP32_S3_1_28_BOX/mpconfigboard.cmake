# MicroPython board configuration for ESP32-S3 1.28 BOX
# Matches working main project configuration

set(IDF_TARGET esp32s3)

# Flash size
set(SDKCONFIG_DEFAULTS
    boards/sdkconfig.base
    ${SDKCONFIG_DEFAULTS}
    boards/sdkconfig.spiram_sx
    boards/ESP32_S3_1_28_BOX/sdkconfig.board
)

# Custom partition table if needed
#set(PARTITION_TABLE_CSV "partitions.csv")