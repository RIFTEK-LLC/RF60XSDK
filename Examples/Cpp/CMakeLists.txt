cmake_minimum_required(VERSION 3.18)
project(SDK)


option(EXAMPLE_SDK_PARAMS "Example sdk is built if enabled" ON)
option(EXAMPLE_SDK_UART_MEASURE "Example sdk is built if enabled" ON)
option(EXAMPLE_SDK_UDP_MEASURE "Example sdk is built if enabled" ON)

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

if(EXAMPLE_SDK_UDP_MEASURE)
    add_subdirectory(RF60X_UDP_Measure)
endif()
