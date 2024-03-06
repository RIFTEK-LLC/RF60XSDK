cmake_minimum_required(VERSION 3.18)
project(SDK)


option(EXAMPLE_SDK_CPP "Example CPP is built if enabled" ON)

###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the configuration
###############################################################################

if(EXAMPLE_SDK_CPP)
    add_subdirectory(Cpp)
endif()
