cmake_minimum_required(VERSION 3.16)
project(learnopengl)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external/glfw-3.3.2)
include_directories(external/glfw-3.3.2/include)
include_directories(external/glad/include)
include_directories(external)
add_library(gladc external/glad/src/glad.c)

add_executable(learnopengl main.cpp shaders/shader.h shaders/shader.cpp)
target_link_libraries(learnopengl gladc glfw ${GLFW_LIBRARIES})