


# LIST OF SHIT THAT'S NEEDED:
#   - cmake (obviously)
#   - nasm
#   - ld
#   - g++

# std::system("git clone git://sourceware.org/git/binutils-gdb.git");


# USEFUL LINKS:
# https://cmake.org/cmake/help/latest/module/ProcessorCount.html


cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(PogVM 
    VERSION 1.0
    DESCRIPTION "PogVM is a mini virtual machine designed to run executable files"
    HOMEPAGE_URL "https://github.com/Existential-Kernel/PogVM"
    LANGUAGES CXX ASM
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++20 -w -Wall -Wextra -Werror -Wshadow -Wpedantic -pedantic -pedantic-errors -time -B ./src -pthread -ffunction-sections -fdata-sections -O3 -ftree-vectorize -flto")

add_executable(pogvm src/mainframe.cpp)

target_include_directories(pogvm PUBLIC "${PROJECT_BINARY_DIR}")

message("Processing CMakeLists...")