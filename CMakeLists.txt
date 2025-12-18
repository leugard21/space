cmake_minimum_required(VERSION 3.20)

project(space
    VERSION 0.5.0
    DESCRIPTION "Disk Usage Visual Analyzer"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(space
    src/main.cpp
    src/scanner.cpp
    src/format.cpp
    src/config.cpp
)

if (MSVC)
    target_compile_options(space PRIVATE /W4)
else()
    target_compile_options(space PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GNUInstallDirs)

install(TARGETS space
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(CPACK_PACKAGE_NAME "space")
set(CPACK_PACKAGE_VENDOR "Luna")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Disk Usage Visual Analyzer")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "islahulkafa01@gmail.com")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Luna")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Utilities")
set(CPACK_RPM_PACKAGE_RELEASE 1)

set(CPACK_GENERATOR
    "DEB"
    "RPM"
    "TGZ"
    "TXZ"
)

include(CPack)
