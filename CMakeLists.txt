cmake_minimum_required(VERSION 3.15)
project(pong VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_executable(pong src/main.cpp
                    src/pong.cpp
                    src/ball.cpp
                    src/paddle.cpp)

target_link_libraries(pong PRIVATE SDL3::SDL3)
target_link_libraries(pong PRIVATE SDL3_ttf::SDL3_ttf)

include_directories(${SDL3_INCLUDE_DIRS})

