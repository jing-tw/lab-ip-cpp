cmake_minimum_required(VERSION 3.0)

project(MyDemo)

add_definitions(-D__MYDEBUG__)
include_directories(
                    ${CMAKE_SOURCE_DIR}/include) 

# Mylib (algo: eigen)
include(FetchContent)

# Eigen
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0 
)
FetchContent_MakeAvailable(eigen)
unset(BUILD_TESTING CACHE)

# for the path of #include <Eigen/Dense>
set(EIGEN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/bin/_deps/eigen-src)
if(NOT EXISTS "${EIGEN_INCLUDE_DIR}")
    message(FATAL_ERROR "Please point EIGEN_INCLUDE_DIR to the include directory of your Eigen installation.")
endif()
include_directories(${EIGEN_INCLUDE_DIR})

add_library(mylib STATIC 
            # MyLib (algo)
            ${CMAKE_SOURCE_DIR}/src/mylib/hungarian.cpp
            ${CMAKE_SOURCE_DIR}/src/mylib/kalman.cpp
            )

add_executable(demo src/main.cpp)
target_link_libraries(demo 
                      Eigen3::Eigen
                      mylib)
