idf_component_register(
      SRCS "board_wrapper.cpp"
    INCLUDE_DIRS "."
    REQUIRES "json"
    PRIV_REQUIRES "esp_common" "esp_hw_support" "freertos" "driver" "esp_driver_gpio"
                  "nvs_flash" "esp_event" "esp_timer" "esp_wifi" "lwip" "esp_netif"
                  "spi_flash" "esp_adc" "app_update"
)

# Set C++ standard for this component
set_property(TARGET ${COMPONENT_LIB} PROPERTY CXX_STANDARD 17)