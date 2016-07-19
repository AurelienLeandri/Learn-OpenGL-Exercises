cmake_minimum_required(VERSION 3.5)
project(tuto1)

find_package(GL)
find_package(sfml-graphics)
find_package(sfml-window)
find_package(sfml-system)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(tuto1 ${SOURCE_FILES})
target_link_libraries(tuto1 GL; sfml-graphics; sfml-window; sfml-system)