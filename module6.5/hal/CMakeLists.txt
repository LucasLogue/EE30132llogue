#this is in fact where we link to a specific MCU
#im using my glob set sources instead so we'll see
file(GLOB HAL_SOURCES CONFIGURE_DEPENDS rp2040/*.c)
#same thing for headers
file(GLOB HAL_INCLUDES CONFIGURE_DEPENDS include/*.h)

add_library(hal STATIC)
target_sources(hal PRIVATE ${HAL_SOURCES} ${HAL_INCLUDES})
target_include_directories(hal PUBLIC include/)
# its like the hal declares its in /hal/ and then include is made to be public, nothing else

target_link_libraries(hal PRIVATE pico_stdlib)
#keeps the RP2040 MCU specific stuff private, meant to go thru HAL headers right
#this is withholding the #include "pico and "hardware stuff. not sure why thats important tho

set_source_files_properties(${HAL_RP2040_SOURCES}
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion"
)
