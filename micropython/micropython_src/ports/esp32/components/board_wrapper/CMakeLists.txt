idf_component_register(
    SRCS "sp_esp32_s3_1_28_box_wrapper.cpp"
         "xiaozhi_launcher.cpp"
    INCLUDE_DIRS "."
    REQUIRES "main"
    PRIV_REQUIRES "esp_common" "esp_hw_support" "freertos" "driver" "esp_driver_gpio"
)

# Set C++ standard for this component
set_property(TARGET ${COMPONENT_LIB} PROPERTY CXX_STANDARD 17)