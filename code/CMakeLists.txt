cmake_minimum_required(VERSION 3.16)

project(MyProject LANGUAGES CXX)

# Use C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Specify include directories
include_directories(${PROJECT_SOURCE_DIR})

# Collect all source files
file(GLOB_RECURSE SOURCES "*.cpp")

# Create executable
add_executable(main_exe main.cpp)
