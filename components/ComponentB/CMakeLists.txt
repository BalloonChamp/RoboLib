cmake_minimum_required(VERSION 3.15)
project(ComponentB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD      17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ——— Auto‐include all .cpp under src/ ——————————————————————————————
file(GLOB COMPONENTB_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(ComponentB
    SHARED
    ${COMPONENTB_SRC}
)

target_include_directories(ComponentB
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(ComponentB
  PUBLIC
    shared
)

set_target_properties(ComponentB PROPERTIES
  VERSION   1.0.0
  SOVERSION 1
)

install(TARGETS ComponentB
        LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
