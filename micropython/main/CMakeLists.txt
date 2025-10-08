idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "." 
                 ".."
)

# Link with the static library
target_link_libraries(${COMPONENT_LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../libmain.a)

# TODO: Add MicroPython module when ready
# SRCS "main.c" "../modspotpear.c"
