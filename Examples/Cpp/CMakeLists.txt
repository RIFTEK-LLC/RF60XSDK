cmake_minimum_required(VERSION 3.18)
project(Examples_CPP)


option(EXAMPLE_SDK_PARAMS "Example sdk is built if enabled" ON)
option(EXAMPLE_SDK_UART_MEASURE "Example sdk is built if enabled" ON)
option(EXAMPLE_SDK_UART_EXTENDED_MEASURE_PROTOCOLS "Example sdk is built if enabled" ON)
option(EXAMPLE_SDK_UDP_MEASURE "Example sdk is built if enabled" ON)
option(EXAMPLE_SDK_ENCODER "Example sdk is built if enabled" ON)
option(EXAMPLE_SDK_FLASH_FACTORY_RESTORE_PARAMS "Example sdk is built if enabled" ON)
###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################

if(EXAMPLE_SDK_PARAMS)
    add_subdirectory(RF60X_PARAMS)
endif()

if(EXAMPLE_SDK_UART_MEASURE)
    add_subdirectory(RF60X_UART_Measure)
endif()

if(EXAMPLE_SDK_UART_EXTENDED_MEASURE_PROTOCOLS)
    add_subdirectory(RF60X_UART_MEASURE_EXTENDED_PROTOCOLS)
endif()

if(EXAMPLE_SDK_UDP_MEASURE)
    add_subdirectory(RF60X_UDP_Measure)
endif()

if(EXAMPLE_SDK_ENCODER)
    add_subdirectory(RF60X_ENCODER)
endif()

 if(EXAMPLE_SDK_FLASH_FACTORY_RESTORE_PARAMS)
    add_subdirectory(R60X_UART_FLASH_FACTORY_RESTORE_PARAMS)
endif()


