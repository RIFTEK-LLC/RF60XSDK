# CMakeList.txt: проект CMake для RF60X_C; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.27)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
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

include(FetchContent)
FetchContent_Declare(
  rf60Xsdk
  GIT_REPOSITORY https://corp.riftek.com/gitlab/rfsdk/rf60xsdk.git
  GIT_TAG master)
FetchContent_MakeAvailable(rf60Xsdk)

# Добавьте источник в исполняемый файл этого проекта.
add_library (RF60X_C "RF60X_C.cpp" "RF60X_C.h")

target_link_libraries(${PROJECT_NAME} PRIVATE rf60Xsdk)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET RF60X_C PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
