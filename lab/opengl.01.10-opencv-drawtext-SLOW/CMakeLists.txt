cmake_minimum_required(VERSION 3.0)

project(OpenGLProject)

add_definitions(-D__MYDEBUG__)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}
                    ${GLFW_INCLUDE_DIRS}
                    ${CMAKE_SOURCE_DIR}/include) 

add_library(MyStaticLib STATIC 
            # OpenGL
            ${CMAKE_SOURCE_DIR}/src/glad.c 

            # MyLib (OpenGL)
            ${CMAKE_SOURCE_DIR}/src/mylib/mylibopengl.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyCordXYZ.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyFPS.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyPicture.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyPictureCV.cpp

            # MyLib (OpenCV)
            ${CMAKE_SOURCE_DIR}/src/mylib/mylibopencv.cpp
            )

add_executable(OpenGLDemo src/main.cpp)

target_link_libraries(OpenGLDemo 
                        ${OPENGL_LIBRARIES} 
                        ${OpenCV_LIBS} 
                        glfw MyStaticLib dl)
target_include_directories(OpenGLDemo PRIVATE ${GLM_INCLUDE_DIRS})
