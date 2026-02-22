cmake_minimum_required(VERSION 3.10)
project(quiz)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(uwufufu ${SOURCES})

target_include_directories(uwufufu PRIVATE include)

target_link_libraries(uwufufu SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})