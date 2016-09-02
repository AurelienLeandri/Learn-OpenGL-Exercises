cmake_minimum_required(VERSION 3.5)
project(5_coordinate_systems)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/7_colors)

set(UTILS_SOURCE_FILES ../utils/file_reader.cc ../utils/file_reader.hh
        ../utils/shader_compiler.cc ../utils/shader_compiler.hh ../utils/shader.cc ../utils/shader.hh ../utils/camera.hh ../utils/camera.cc)
set(TUTO_SOURCE_FILES tuto/main.cc)

add_executable(colors ${TUTO_SOURCE_FILES} ${UTILS_SOURCE_FILES})

target_link_libraries(colors; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; ${SOIL_LIBRARIES}; GL)
