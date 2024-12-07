cmake_minimum_required(VERSION 3.0)

project(OpenGLProject)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

find_package(glm REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}
                    ${GLFW_INCLUDE_DIRS}
                    ${CMAKE_SOURCE_DIR}/include) 

add_library(glad 
            ${CMAKE_SOURCE_DIR}/src/glad.c 
            ${CMAKE_SOURCE_DIR}/src/mylib/mylib.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyFPS.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyPicture.cpp
            )

add_executable(OpenGLDemo src/main.cpp)

target_link_libraries(OpenGLDemo ${OPENGL_LIBRARIES} glfw glad dl)
target_include_directories(OpenGLDemo PRIVATE ${GLM_INCLUDE_DIRS})
