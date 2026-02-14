cmake_minimum_required(VERSION 3.10)
project(quiz)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(uwufufu src/main.cpp)

target_link_libraries(uwufufu SDL2::SDL2 SDL2_image::SDL2_image)
