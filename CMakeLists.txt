cmake_minimum_required(VERSION 3.10)
project(RoboLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(robotlib
    src/tcp_server.cpp
    src/tcp_client.cpp
    src/component.cpp
    src/motor.cpp
    src/touch_sensor.cpp
    src/controller.cpp
    src/database_server.cpp
    src/database_client.cpp
    src/db_component.cpp
    src/db_motor.cpp
    src/db_touch_sensor.cpp
    src/data_packet.cpp
    src/scheduler.cpp
)

add_executable(robot src/main.cpp)
target_link_libraries(robot robotlib)
