cmake_minimum_required(VERSION 3.0)

project(MyDemo)

add_definitions(-D__MYDEBUG__)

# Base
include_directories(${CMAKE_SOURCE_DIR}/include) 

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(demo src/main.cpp)
target_link_libraries(demo 
                        ${OpenCV_LIBS} 
                        )
