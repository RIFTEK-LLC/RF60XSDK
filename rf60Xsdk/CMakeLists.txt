cmake_minimum_required(VERSION 3.5)

#
# PROJECT name and version
#
project(
  rf60Xsdk
  VERSION 1.0.1
  LANGUAGES CXX)

#
# CONFIGURATION
#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")

set(FETCHCONTENT_FULLY_DISCONNECTED "ON")
include(FetchContent)
FetchContent_Declare(
  asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG d6b95c0188e0359a8cdbdb6571f0cbacf11a538c)
FetchContent_MakeAvailable(asio)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# create glob files for *.h, *.cpp
file(GLOB H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# concatenate the results (glob files) to variable
set(SOURCES ${CPP_FILES} ${H_FILES})

#
# TARGET create target and add include path
#
add_library(${PROJECT_NAME} ${SOURCES}
    rf60xencoder.h rf60xencoder.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${asio_SOURCE_DIR}/asio/include)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${asio_SOURCE_DIR}/asio/include/asio/detail)

if(MINGW)
  target_compile_definitions(${PROJECT_NAME} PUBLIC _WIN32_WINNT=0x0601)
  target_link_libraries(${PROJECT_NAME} PUBLIC ws2_32)
  target_link_libraries(${PROJECT_NAME} PUBLIC iphlpapi)
endif(MINGW)

get_filename_component(_vs_bin_path "${CMAKE_LINKER}" DIRECTORY)

#
# INSTALL install header files, generate .lib or .dll file.
#
# include the GNUInstallDirs module to get the canonical install paths defined
include(GNUInstallDirs)

# Install the library and export the CMake targets
install(
    TARGETS  ${PROJECT_NAME}
    EXPORT  ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Library
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Library
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT Library
    CONFIGURATIONS DEBUG|RELEASE)

# install the public headers
install(FILES ${H_FILES} DESTINATION include COMPONENT Library)



