cmake_minimum_required(VERSION 3.5)
project(1_hello_triangle)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/leo/Projects/opengl_tutorials/1_hello_triangle)

set(UTILS_SOURCE_FILES utils/file_reader.cc utils/file_reader.hh utils/shader_compiler.cc utils/shader_compiler.hh)
set(TUTO_SOURCE_FILES main.cpp)
set(EX1_SOURCE_FILES exo1/main.cc)
set(EX2_SOURCE_FILES exo2/main.cc)
set(EX3_SOURCE_FILES exo3/main.cc)

add_executable(hello_triangle ${TUTO_SOURCE_FILES} ${UTILS_SOURCE_FILES})
add_executable(tuto1_ex1 ${EX1_SOURCE_FILES} ${UTILS_SOURCE_FILES})
add_executable(tuto1_ex2 ${EX2_SOURCE_FILES} ${UTILS_SOURCE_FILES})
add_executable(tuto1_ex3 ${EX3_SOURCE_FILES} ${UTILS_SOURCE_FILES})

target_link_libraries(hello_triangle; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
target_link_libraries(tuto1_ex1; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
target_link_libraries(tuto1_ex2; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
target_link_libraries(tuto1_ex3; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
