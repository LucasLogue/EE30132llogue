#dont touch
cmake_minimum_required(VERSION 3.13)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Run cmake from the build/ folder, not the project folder.")
endif()
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(USERHOME $ENV{HOME})
set(sdkVersion 2.3.0)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.0)
set(PICO_BOARD pico CACHE STRING "Board type")


include(pico_sdk_import.cmake)

# Project name is entered here
project(Monomodule C CXX ASM)
pico_sdk_init()

#target file
add_executable(${PROJECT_NAME} monolith.c)

#source .c files
target_sources(${PROJECT_NAME} PRIVATE monolith.c)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

add_subdirectory(lib/minmea)
target_link_libraries(${PROJECT_NAME} PRIVATE minmea pico_stdlib)

set_source_files_properties(monolith.c
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion"
)

#these 2 are just decorations
pico_set_program_name(${PROJECT_NAME} "Monomodule")
pico_set_program_version(${PROJECT_NAME} "0.1")

pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})
