cmake_minimum_required (VERSION 3.27)

# Enable hot reload for MSVC compilers, if enabled.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("RF60X_C" VERSION 1.0.1
  LANGUAGES CXX
)

# Enabling export of all symbols to create a dynamic library
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# creating output directory architecture in accordance with GNU guidelines
set(BINARY_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BINARY_DIR}/lib")

set(BUILD_SHARED_LIBS ON)
add_library (RF60X_C "RF60X_C.cpp" "RF60X_C.h")

if(BUILD_STATIC_WRAPPER)
    target_link_libraries(${PROJECT_NAME} PRIVATE rf60Xsdk_static)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE rf60Xsdk)
endif()

# Make sure rf60Xsdk_static is available if used
if(BUILD_STATIC_WRAPPER)
    if(NOT TARGET rf60Xsdk_static)
        message(FATAL_ERROR "rf60Xsdk_static target not found. Make sure ENABLE_SDK_SOURCE, ENABLE_RF60X_C_WRAPPER and BUILD_STATIC_WRAPPER are ON")
    endif()
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RF60X_C PROPERTY CXX_STANDARD 20)
endif()
