cmake_minimum_required(VERSION 3.0)

project(myopengl VERSION 1.0.0 LANGUAGES CXX)

add_definitions(-D__MYDEBUG__)

# Variable
# Usage; cmake -DUSER_DEFINED_BUILD_DIRECTORY=build
# if(NOT DEFINED USER_DEFINED_BUILD_DIRECTORY)
#     set(USER_DEFINED_BUILD_DIRECTORY "build")
# endif()
# message(STATUS "USER_DEFINED_BUILD_DIRECTORY: ${USER_DEFINED_BUILD_DIRECTORY}")


message(STATUS "Project Version: ${PROJECT_VERSION}")

# Base
include_directories(${CMAKE_SOURCE_DIR}/include) 

# OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS}
                    ${GLFW_INCLUDE_DIRS}
) 

add_library(${PROJECT_NAME} SHARED 
            # MyLib (OpenGL)
            ${CMAKE_SOURCE_DIR}/src/mylib/mylibopengl.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyCordXYZ.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyFPS.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/MyPicture.cpp
            )

target_link_libraries(${PROJECT_NAME} 
            ${OPENGL_LIBRARIES} 
            )

# Set the version for the library
set_target_properties(${PROJECT_NAME}  PROPERTIES 
                        VERSION ${PROJECT_VERSION}
                        SOVERSION ${PROJECT_VERSION_MAJOR}
                        )
