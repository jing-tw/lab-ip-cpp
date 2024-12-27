cmake_minimum_required(VERSION 3.11)
project(MyProject)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

# 使用 FetchContent 下載 nlohmann/json
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3 # 可以替換為最新版本
)

FetchContent_MakeAvailable(json)

add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE nlohmann_json::nlohmann_json)