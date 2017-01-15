cmake_minimum_required(VERSION 3.5)
project(bump_mapping)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bump_mapping)

set(UTILS_SOURCE_FILES ../utils/file_reader.cc ../utils/file_reader.hh
        ../utils/shader_compiler.cc ../utils/shader_compiler.hh
        ../utils/shader.cc ../utils/shader.hh ../utils/camera.hh
        ../utils/camera.cc ../utils/model/model.hh ../utils/model/model.cc
        ../utils/model/mesh.hh ../utils/model/mesh.cc)
set(TUTO_SOURCE_FILES tuto/main.cc)

add_executable(bump_mapping ${TUTO_SOURCE_FILES} ${UTILS_SOURCE_FILES})

target_link_libraries(bump_mapping; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; ${SOIL_LIBRARIES}; ${ASSIMP_LIBRARIES} GL)
