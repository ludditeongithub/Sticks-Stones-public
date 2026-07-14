cmake_minimum_required(VERSION 3.16)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

list(FILTER SOURCES EXCLUDE REGEX "/\\.#")

add_executable(main_exe ${SOURCES})

message(STATUS "Found sources:")
foreach(src IN LISTS SOURCES)
    message(STATUS "  ${src}")
endforeach()


