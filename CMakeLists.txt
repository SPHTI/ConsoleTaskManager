cmake_minimum_required(VERSION 3.10)
project(TaskManager)

# Настройки кодировки для Windows
if (MSVC)
    add_compile_options(/utf-8)
endif()

set(CMAKE_CXX_STANDARD 11)
add_executable(TaskManager src/main.cpp)