#modified to work with the module specific CMakeLists.txt (Module 3 of notes or smthng)
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

project(module6.5 C CXX ASM)
pico_sdk_init()

#FIRST CHANGE IS MOVING MAIN.C TO TARGET SOURCES
#right after adding the executable. this is reorganization
# from later target_sources
#add_executable(${PROJECT_NAME} main.c)
add_executable(${PROJECT_NAME})
#also now its private
target_sources(${PROJECT_NAME} PRIVATE main.c)


#this for hal is now done in its local CMake
# file(GLOB HAL_SOURCES CONFIGURE_DEPENDS hal/rp2040/*.c)
# target_sources(${PROJECT_NAME} PRIVATE main.c
#     ${HAL_SOURCES}
#     app/uart_relay.c
# )

#instead of explicitly stating directories, will now use add_subdir
#so it can find the CMakeLists.txt in those directories and use them
#!!!! MINMEA must proceed app since app uses minmea
add_subdirectory(lib/minmea)
add_subdirectory(hal)
add_subdirectory(app)
# target_include_directories(${PROJECT_NAME} PRIVATE
#         hal/include
#         app/include
#         ${CMAKE_CURRENT_LIST_DIR}
# )

#only now adding PRIVATE and those subdir module names
target_link_libraries(${PROJECT_NAME} PRIVATE pico_stdlib hal uart_relay_app)

set_source_files_properties(main.c 
    PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion"
)

#these 2 are just decorations
pico_set_program_name(${PROJECT_NAME} "Monomodule")
pico_set_program_version(${PROJECT_NAME} "0.1")

pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})
