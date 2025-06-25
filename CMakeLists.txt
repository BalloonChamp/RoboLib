cmake_minimum_required(VERSION 3.10)
project(RoboLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(lib)
include_directories(third_party)

file(GLOB LIB_SOURCES
    lib/components/*.cpp
    lib/networking/*.cpp
    sim/hooks/*.cpp
    sim/simcomponents/*.cpp
)

add_library(robolib ${LIB_SOURCES})

file(GLOB APP_SOURCES src/*.cpp)
add_executable(robot ${APP_SOURCES})
target_link_libraries(robot robolib pthread)
