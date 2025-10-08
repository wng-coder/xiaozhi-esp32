idf_component_register(
    SRCS "python_tests.c"
    INCLUDE_DIRS "."
    REQUIRES "board_wrapper"
    PRIV_REQUIRES "esp_common" "freertos"
)