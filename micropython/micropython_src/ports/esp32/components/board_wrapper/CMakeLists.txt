idf_component_register(
      SRCS #"sp_esp32_s3_1_28_box_wrapper.cpp"
             #"xiaozhi_launcher.cpp"
             #"xiaozhi_application_stub.cpp"
             "board_wrapper.cpp"
    INCLUDE_DIRS "." "/workspaces/xiaozhi-esp32/main"
    REQUIRES "main" "json"
    PRIV_REQUIRES "esp_common" "esp_hw_support" "freertos" "driver" "esp_driver_gpio"
                  "nvs_flash" "esp_event" "esp_timer" "esp_wifi" "lwip" "esp_netif"
)

# Set C++ standard for this component
set_property(TARGET ${COMPONENT_LIB} PROPERTY CXX_STANDARD 17)