cmake_minimum_required(VERSION 3.20)

project(game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(test_exe)

target_sources(test_exe
    PRIVATE
  test.cpp
    
  core/random.hpp

  data/run/world.cpp
  
  logic/simulation/world_gen.cpp
  
  display/render/texture.cpp
  display/render/screen.cpp
)

target_include_directories(test_exe PRIVATE
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/../extern
)

target_link_libraries(test_exe PRIVATE
    SDL2::SDL2
    SDL2_image::SDL2_image
)
