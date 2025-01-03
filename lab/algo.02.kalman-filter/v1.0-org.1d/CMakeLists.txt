cmake_minimum_required(VERSION 3.0)

project(MyDemo)

add_definitions(-D__MYDEBUG__)

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
                    ${CMAKE_SOURCE_DIR}/include) 

# Mylib (algo)
include(FetchContent)

# Eigen
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0  # You can specify the version you need
)
FetchContent_MakeAvailable(eigen)
unset(BUILD_TESTING CACHE)

# add_library(mylib STATIC 
#             # OpenGL
#             ${CMAKE_SOURCE_DIR}/src/glad.c 

#             # MyLib (OpenGL)
#             ${CMAKE_SOURCE_DIR}/src/mylib/mylibopengl.cpp
#             ${CMAKE_SOURCE_DIR}/src/mylib/MyCordXYZ.cpp
#             ${CMAKE_SOURCE_DIR}/src/mylib/MyFPS.cpp
#             ${CMAKE_SOURCE_DIR}/src/mylib/MyPicture.cpp
#             ${CMAKE_SOURCE_DIR}/src/mylib/MyPictureCV.cpp

#             # MyLib (OpenCV)
#             ${CMAKE_SOURCE_DIR}/src/mylib/mylibopencv.cpp

#             # MyLib (algo)
#             ${CMAKE_SOURCE_DIR}/src/mylib/hungarian.cpp
#             )

add_executable(demo src/main.cpp)
target_link_libraries(demo 
                      Eigen3::Eigen)

# target_link_libraries(demo 
#                         ${OPENGL_LIBRARIES} 
#                         ${OpenCV_LIBS} 
#                         glfw mylib dl Eigen3::Eigen)
# target_include_directories(demo PRIVATE ${GLM_INCLUDE_DIRS})
