cmake_minimum_required(VERSION 3.0)

project(MyDemo)

add_definitions(-D__MYDEBUG__)

# Variable
# cmake -DUSER_DEFINED_BUILD_DIRECTORY=build
if(NOT DEFINED USER_DEFINED_BUILD_DIRECTORY)
    set(USER_DEFINED_BUILD_DIRECTORY "build")
endif()
message(STATUS "USER_DEFINED_BUILD_DIRECTORY: ${USER_DEFINED_BUILD_DIRECTORY}")

# Base
include_directories(${CMAKE_SOURCE_DIR}/include) 

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


# # ByteTrack
# include_directories(${CMAKE_SOURCE_DIR}/include) 


# Eigen
include(FetchContent)
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0 
)
FetchContent_MakeAvailable(eigen)
unset(BUILD_TESTING CACHE)

set(EIGEN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/${USER_DEFINED_BUILD_DIRECTORY}/_deps/eigen-src)
if(NOT EXISTS "${EIGEN_INCLUDE_DIR}")
    message(FATAL_ERROR "Please point EIGEN_INCLUDE_DIR to the include directory of your Eigen installation.")
endif()
include_directories(${EIGEN_INCLUDE_DIR})
# end

add_executable(demo src/main.cpp)

target_link_libraries(demo 
                        ${OpenCV_LIBS}
                 
                        )
