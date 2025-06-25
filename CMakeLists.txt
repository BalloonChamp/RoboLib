cmake_minimum_required(VERSION 3.10)
project(RoboLib)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(lib)

file(GLOB LIB_SOURCES
    lib/networking/*.cpp
    lib/components/*.cpp
)

add_library(robolib STATIC ${LIB_SOURCES})

file(GLOB SRC_SOURCES src/*.cpp)
add_executable(robot ${SRC_SOURCES})

find_library(HIREDIS hiredis)
target_link_libraries(robot robolib pthread ${HIREDIS})
