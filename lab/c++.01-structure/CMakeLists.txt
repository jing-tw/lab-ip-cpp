cmake_minimum_required(VERSION 2.8)
project(test)

# find_package(OpenCV REQUIRED)

# Directories
set(SRC_DIR src)
set(INC_DIR include)
# set(UTIL_INC_DIR ../utility/include)
# set(UTIL_SRC_DIR ../utility/src)

# Include
# include_directories(${UTIL_INC_DIR})
# include_directories(${OpenCV_INCLUDE_DIRS})

# Source files
include_directories(${INC_DIR})
file(GLOB SRC_FILES ${SRC_DIR}/main.cpp 
                    )

# Files to compile
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Libraries
# target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
