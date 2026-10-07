set(UART_RELAY_APP_SOURCES uart_relay.c)

#declaring uart_relay_app as a static lib(on my computer standalone to be built into the produced file)
add_library(uart_relay_app STATIC)
target_sources(uart_relay_app PRIVATE ${UART_RELAY_APP_SOURCES} include/uart_relay.h)

# where to look when it sees an #include and PUBLIC such that any other module can look here as well)
target_include_directories(uart_relay_app PUBLIC include/)

target_link_libraries(uart_relay_app PUBLIC hal PRIVATE minmea)
set_source_files_properties(${UART_RELAY_APP_SOURCES}
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion"
)
