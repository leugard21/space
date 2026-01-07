cmake_minimum_required(VERSION 3.20)

project(space
    VERSION 1.2.0
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
    src/json.cpp
    src/tree.cpp
    src/cache.cpp
)

target_include_directories(space PRIVATE include)
target_compile_definitions(space PRIVATE SPACE_VERSION="${PROJECT_VERSION}")

if (MSVC)
    target_compile_options(space PRIVATE /W4)
else()
    target_compile_options(space PRIVATE -Wall -Wextra -Wpedantic)
endif()

include(GNUInstallDirs)

install(TARGETS space
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/space)
install(FILES README.md DESTINATION ${CMAKE_INSTALL_DOCDIR})

set(CPACK_PACKAGE_NAME "space")
set(CPACK_PACKAGE_VENDOR "Space Project")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Disk Usage Visual Analyzer")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "maintainer@space.local")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Space Maintainer")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")

set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Utilities")
set(CPACK_RPM_PACKAGE_RELEASE 1)

set(CPACK_GENERATOR
    DEB
    RPM
    TGZ
    TXZ
)

include(CPack)
