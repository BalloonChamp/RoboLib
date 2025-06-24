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
)

add_executable(main src/main.cpp)
target_link_libraries(main robotlib)
target_compile_definitions(main PRIVATE MOTOR1_PORT=5001 MOTOR2_PORT=5002 SENSOR_PORT=5003)

add_executable(motor1 src/motor_main.cpp)
target_link_libraries(motor1 robotlib)
target_compile_definitions(motor1 PRIVATE MOTOR_ID=1 MOTOR_PORT=5001)

add_executable(motor2 src/motor_main.cpp)
target_link_libraries(motor2 robotlib)
target_compile_definitions(motor2 PRIVATE MOTOR_ID=2 MOTOR_PORT=5002)

add_executable(touch_sensor src/touch_sensor_main.cpp)
target_link_libraries(touch_sensor robotlib)
target_compile_definitions(touch_sensor PRIVATE SENSOR_PORT=5003)

