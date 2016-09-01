cmake_minimum_required(VERSION 3.5)
project(6_camera)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/6_camera)

set(UTILS_SOURCE_FILES ../utils/file_reader.cc ../utils/file_reader.hh
        ../utils/shader_compiler.cc ../utils/shader_compiler.hh ../utils/shader.cc ../utils/shader.hh)
set(TUTO_SOURCE_FILES tuto/main.cc ../utils/camera.hh)

add_executable(camera ${TUTO_SOURCE_FILES} ${UTILS_SOURCE_FILES})

target_link_libraries(camera; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; ${SOIL_LIBRARIES}; GL)
