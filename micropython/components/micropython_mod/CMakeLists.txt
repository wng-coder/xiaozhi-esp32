idf_component_register(
    SRCS "modspotpear.c"
    INCLUDE_DIRS "." "../../micropython_src"
    REQUIRES "board_wrapper"
    PRIV_REQUIRES "esp_common" "freertos"
)