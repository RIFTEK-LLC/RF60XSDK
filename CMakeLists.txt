cmake_minimum_required(VERSION 3.18)
project(SDK)


option(ENABLE_SDK_SOURCE "SDK libraries are built if enabled" ON)
option(ENABLE_SDK_EXAMPLES "Example sdk is built if enabled" ON)


###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################

if(ENABLE_SDK_SOURCE)
    add_subdirectory(rf60Xsdk)
endif()

if(ENABLE_SDK_EXAMPLES)
    add_subdirectory(Examples)
endif()
