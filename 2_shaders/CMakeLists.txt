cmake_minimum_required(VERSION 3.5)
project(2_shaders)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(UTILS_SOURCE_FILES utils/file_reader.cc utils/file_reader.hh)
set(TUTO2_SOURCE_FILES tuto/main.cc)
add_executable(shaders ${TUTO2_SOURCE_FILES} ${UTILS_SOURCE_FILES})