# Create an INTERFACE library for our module
add_library(usermod_modspotpear INTERFACE)

# Add our source files
target_sources(usermod_modspotpear INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/modspotpear.c
)

# Add include directories if needed
target_include_directories(usermod_modspotpear INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Add to user modules, if found (MicroPython user C module pattern)
target_link_libraries(usermod INTERFACE usermod_modspotpear)
