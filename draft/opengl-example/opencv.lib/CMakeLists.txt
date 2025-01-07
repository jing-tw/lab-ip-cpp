cmake_minimum_required(VERSION 3.0)

project(myopencv)
add_definitions(-D__MYDEBUG__)

# Base
include_directories(${CMAKE_SOURCE_DIR}/include) 

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED 
            # MyLib (OpenCV)
            ${CMAKE_SOURCE_DIR}/src/mylib/mylibopencv.cpp
            )
target_link_libraries(${PROJECT_NAME} 
            ${OpenCV_LIBS} 
            )

