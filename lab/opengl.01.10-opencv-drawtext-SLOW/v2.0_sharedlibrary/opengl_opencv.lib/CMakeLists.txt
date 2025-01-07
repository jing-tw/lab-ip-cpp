cmake_minimum_required(VERSION 3.0)

project(myopengl_opencv)

add_definitions(-D__MYDEBUG__)

# Variable
# Usage; cmake -DUSER_DEFINED_BUILD_DIRECTORY=build
# if(NOT DEFINED USER_DEFINED_BUILD_DIRECTORY)
#     set(USER_DEFINED_BUILD_DIRECTORY "build")
# endif()
# message(STATUS "USER_DEFINED_BUILD_DIRECTORY: ${USER_DEFINED_BUILD_DIRECTORY}")

# Base
include_directories(${CMAKE_SOURCE_DIR}/include) 

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}
                    ${GLFW_INCLUDE_DIRS}
                   ) 

add_library(${PROJECT_NAME} SHARED 
            # OpenGL
            # ${CMAKE_SOURCE_DIR}/src/glad.c 

            # MyLib (OpenCV + OpenGL)
            ${CMAKE_SOURCE_DIR}/src/mylib/mylibopengl_opencv.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyPictureCV.cpp
            )

target_link_libraries(${PROJECT_NAME} 
            ${OPENGL_LIBRARIES} 
            ${OpenCV_LIBS} 
            ${CMAKE_SOURCE_DIR}/libmyopencv.so   # because DrawText in the lib myopencv.
            )

