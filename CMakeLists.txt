


# LIST OF SHIT THAT'S NEEDED:
#   - cmake (obviously)
#   - nasm
#   - ld
#   - g++


# USEFUL LINKS:
# https://cmake.org/cmake/help/latest/module/ProcessorCount.html


cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(PogVM 
    VERSION 1.0
    DESCRIPTION "PogVM is a mini virtual machine designed to run executable files"
    HOMEPAGE_URL "https://github.com/Existential-Kernel/PogVM"
    LANGUAGES CXX ASM
)

target_compile_features(pogvm PUBLIC cxx_std_17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic -pedantic-errors")


add_executable(pogvm src/mainframe.cpp)

target_include_directories(pogvm PUBLIC "${PROJECT_BINARY_DIR}")

message("Processing CMakeLists...")