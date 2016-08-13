cmake_minimum_required(VERSION 3.5)
project(2_shaders)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/2_shaders)

set(UTILS_SOURCE_FILES utils/file_reader.cc utils/file_reader.hh
        utils/shader_compiler.cc utils/shader_compiler.hh)
set(TUTO2_SOURCE_FILES tuto/main.cc)

add_executable(shaders ${TUTO2_SOURCE_FILES} ${UTILS_SOURCE_FILES})

target_link_libraries(shaders; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
