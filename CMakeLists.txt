cmake_minimum_required(VERSION 3.10)
project(RoboLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(Threads REQUIRED)
find_package(nlohmann_json 3.11.3 REQUIRED)

add_library(robotlib
    src/redis.cpp
    src/redis_component.cpp
    src/config_loader.cpp
    src/database_component.cpp
    src/motor.cpp
    src/touch_sensor.cpp
    src/controller.cpp
)

add_executable(robot src/main.cpp)
target_link_libraries(robot robotlib hiredis nlohmann_json::nlohmann_json Threads::Threads)
