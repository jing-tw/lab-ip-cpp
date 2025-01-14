cmake_minimum_required(VERSION 3.0)

project(demo)
option(BUILD_EXAMPLE "Build Example." ON)

add_definitions(-D__MYDEBUG__)

# Base
include_directories(
                    ${CMAKE_SOURCE_DIR}/include) 

# # OpenCV
# find_package(OpenCV REQUIRED)
# include_directories(${OpenCV_INCLUDE_DIRS})

# # OpenGL
# find_package(OpenGL REQUIRED)
# find_package(glfw3 REQUIRED)
# find_package(glm REQUIRED)

include_directories(
#                     ${OPENGL_INCLUDE_DIRS}
#                     ${GLFW_INCLUDE_DIRS}
                    ) 

# Build Example
if (BUILD_EXAMPLE)
    add_executable(${PROJECT_NAME}  
                example/main.cpp 
                src/wgs_conversions.cpp
                # src/glad.c
                )
endif (BUILD_EXAMPLE)

target_link_libraries(${PROJECT_NAME}  
                    # ${OPENGL_LIBRARIES} 
                    # glfw   
                    # ${OpenCV_LIBS}   
                    # ${CMAKE_SOURCE_DIR}/libmyopengl.so
                    # ${CMAKE_SOURCE_DIR}/libmyopencv.so
                    # ${CMAKE_SOURCE_DIR}/libmyopengl_opencv.so
                    )
