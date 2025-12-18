cmake_minimum_required(VERSION 3.20)

project(space
    VERSION 0.1.0
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
)

if (MSVC)
    target_compile_options(space PRIVATE /W4)
else()
    target_compile_options(space PRIVATE -Wall -Wextra -Wpedantic)
endif()
