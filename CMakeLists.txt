cmake_minimum_required(VERSION 3.20)
project(cpp_learning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# compile_commands.json is what clangd reads to understand the project
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main main.cpp five_rule_test.cpp)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})
target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
