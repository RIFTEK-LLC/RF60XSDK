cmake_minimum_required(VERSION 3.18)
project(SDK)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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


set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP")
# Настройка CPack для создания отдельных компонентов
set(CPACK_ARCHIVE_COMPONENT_INSTALL ON) # Включение архивирования компонентов
set(CPACK_PACKAGE_VERSION 1.1.0) # Задает версию пакета
set(CPACK_PACKAGE_FILE_NAME "SDK-rf60XSDK-${CPACK_PACKAGE_VERSION}")
# Настройка компонента Examples (exe)
install(DIRECTORY ${CMAKE_BINARY_DIR}/bin
        DESTINATION Examples/CPP/
        COMPONENT Examples
        FILES_MATCHING PATTERN "*.exe"
        PATTERN "*.dll"
)


set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION "Example programs") # Описание компонента
set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples") # Имя компонента

set(CPACK_COMPONENTS_ALL Examples Library)
set(CPACK_COMPONENT_LIBRARY_DESCRIPTION "Library files") # Описание компонента
set(CPACK_COMPONENT_LIBRARY_DISPLAY_NAME "Libraries") # Имя компонента
set(CPACK_COMPONENT_LIBRARY_DEPENDS Library)

include(CPack)
include(CPackComponent)
include(InstallRequiredSystemLibraries)

