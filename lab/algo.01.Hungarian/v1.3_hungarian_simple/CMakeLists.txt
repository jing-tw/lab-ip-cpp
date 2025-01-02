cmake_minimum_required(VERSION 3.0)

project(MyDemo)
add_definitions(-D__MYDEBUG__)
include_directories(
                    ${OPENGL_INCLUDE_DIRS}
                    ${GLFW_INCLUDE_DIRS}
                    ${CMAKE_SOURCE_DIR}/include) 
add_library(mylib STATIC 
            ${CMAKE_SOURCE_DIR}/src/mylib/hungarian.cpp
            )
add_executable(demo src/main.cpp)
target_link_libraries(demo 
                       mylib)
