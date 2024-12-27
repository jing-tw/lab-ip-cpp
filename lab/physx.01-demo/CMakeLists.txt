cmake_minimum_required(VERSION 3.10)
project(PhysXDemo)

# option(USE_CUDA "Use CUDA acceleration" OFF) 
# option(PHYSX_USE_GPU "Enable GPU acceleration" OFF)
add_definitions(-DDISABLE_CUDA_PHYSX)
# unset(PX_SUPPORT_GPU_PHYSX CACHE)


# Set the path to your PhysX installation
set(PHYSX_PATH "/home/jing/PhysX/physx/install/linux/PhysX")

# Include directories for PhysX
include_directories(${PHYSX_PATH}/include)

# Link directories for PhysX libraries
link_directories(/home/jing/PhysX/physx/install/linux/PhysX/bin/linux.x86_64/checked)

# Add the executable
add_executable(PhysXDemo src/main.cpp)

# Link against PhysX libraries
# target_link_libraries(PhysXDemo 
#     physx 
#     physxfoundation 
#     physxextensions 
#     physxvehicle 
# )


target_link_libraries(PhysXDemo 
    PhysX_static_64
    PhysXPvdSDK_static_64
    PhysXExtensions_static_64
    PhysXCooking_static_64
    PhysXCommon_static_64
    PhysXFoundation_static_64 
    PhysXVehicle_static_64 
)