cmake_minimum_required(VERSION 3.5)
project(2_shaders)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set (CMAKE_BINARY_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(UTILS_HEADER_FILES
        ${UTILS_DIR}/shader_compiler.hh
        ${UTILS_DIR}/file_reader.hh
        ${UTILS_DIR}/shader.hh)
set(UTILS_SOURCE_FILES
        ${UTILS_DIR}/shader_compiler.cc
        ${UTILS_DIR}/file_reader.cc
        ${UTILS_DIR}/shader.cc)
set(TUTO2_SOURCE_FILES tuto/main.cc)

add_library(shader_utils ${UTILS_HEADER_FILES} ${UTILS_SOURCE_FILES})
add_executable(shaders ${TUTO2_SOURCE_FILES} ${UTILS_HEADER_FILES} ${UTILS_SOURCE_FILES})

target_link_libraries(shaders; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
