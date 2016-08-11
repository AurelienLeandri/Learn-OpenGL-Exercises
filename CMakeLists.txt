cmake_minimum_required(VERSION 3.5)
project(tuto1)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY /home/leo/Projects/opengl_tutorials/tuto1)
# Detect and add GLEW
find_package(GLEW REQUIRED)
if (!GLEW_FOUND)
    MESSAGE("GLEW NOT FOUND")
endif()
include_directories(${GLEW_INCLUDE_DIRS})

# Detect and add SFML
find_package(SFML 2 REQUIRED system window graphics network audio)
if (!SFML_FOUND)
    MESSAGE("SFML NOT FOUND")
endif()
include_directories(${SFML_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
if (!OPENGL_FOUND)
    MESSAGE("OPENGL NOT FOUND")
endif()
include_directories(${GLEW_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(UTILS_SOURCE_FILES utils/file_reader.cc utils/file_reader.hh utils/shader_compiler.cc utils/shader_compiler.hh)
set(TUTO_SOURCE_FILES main.cpp)
set(EX1_SOURCE_FILES exo1/main.cc)
add_executable(tuto ${TUTO_SOURCE_FILES} ${UTILS_SOURCE_FILES})
add_executable(ex1 ${EX1_SOURCE_FILES} ${UTILS_SOURCE_FILES})
target_link_libraries(tuto; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
target_link_libraries(ex1; ${SFML_LIBRARIES}; ${GLEW_LIBRARIES}; GL)
