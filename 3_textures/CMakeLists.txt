cmake_minimum_required(VERSION 3.5)
project(3_textures)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/3_textures)

set(UTILS_SOURCE_FILES ../utils/file_reader.cc ../utils/file_reader.hh
        ../utils/shader_compiler.cc ../utils/shader_compiler.hh ../utils/shader.cc ../utils/shader.hh)
set(TUTO_SOURCE_FILES tuto/main.cc)

add_executable(textures ${TUTO_SOURCE_FILES} ${UTILS_SOURCE_FILES})

target_link_libraries(textures; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
