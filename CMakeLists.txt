# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated Cmake Pico project file

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_BOARD pico CACHE STRING "Board type")



# Minimum required cmake version for project
cmake_minimum_required(VERSION 3.13)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# Create project called 'pico_testing'
project(pico_testing C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()



# Adding program name and version
# pico_set_program_name(pico_testing "pico_testing")
# pico_set_program_version(pico_testing "0.1")

# Add the standard include files to the build
# target_include_directories(pico_testing PRIVATE
#   ${CMAKE_CURRENT_LIST_DIR}
#   ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
# )

# Generate PIO header
# pico_generate_pio_header(pico_testing ${CMAKE_CURRENT_LIST_DIR}/blink.pio)



# Add executable. Default name is the project name, version 0.1
add_executable(pico_testing
    src/pico_testing.cpp
)


# Setting dir for all of extra libraries
SET(LIBRARIES_DIR ${CMAKE_CURRENT_LIST_DIR}/libs)


# Adding protothreads library (INTERFACE when library has only header (.h) files)
add_library(protothreads INTERFACE)
target_include_directories(protothreads INTERFACE
        ${LIBRARIES_DIR}/protothreads
)

# Adding FreeRTOS c files
add_library(FreeRTOS STATIC
        ${LIBRARIES_DIR}/FreeRTOS/croutine.c
        ${LIBRARIES_DIR}/FreeRTOS/event_groups.c
        ${LIBRARIES_DIR}/FreeRTOS/list.c
        ${LIBRARIES_DIR}/FreeRTOS/queue.c
        ${LIBRARIES_DIR}/FreeRTOS/stream_buffer.c
        ${LIBRARIES_DIR}/FreeRTOS/tasks.c
        ${LIBRARIES_DIR}/FreeRTOS/timers.c
        
        ${LIBRARIES_DIR}/FreeRTOS/heap_4.c
        ${LIBRARIES_DIR}/FreeRTOS/port.c
        # ${LIBRARIES_DIR}/FreeRTOS/portable/GCC/ARM_CM0/port.c
        # ${LIBRARIES_DIR}/FreeRTOS/portable/MemMang/heap_4.c
)
# Including FreeRTOS header files
target_include_directories(FreeRTOS PUBLIC
        ${LIBRARIES_DIR}/FreeRTOS/include
        ${LIBRARIES_DIR}/FreeRTOS/config
        ${LIBRARIES_DIR}/FreeRTOS/portable/GCC/ARM_CM0
)


# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(pico_testing 1)
pico_enable_stdio_usb(pico_testing 1)

# Add the standard library to the build
target_link_libraries(pico_testing
        pico_stdlib
        pico_multicore
        protothreads
        FreeRTOS
)

# message("Libraries path: ${LIBRARIES_DIR}/port.c")

pico_add_extra_outputs(pico_testing)

