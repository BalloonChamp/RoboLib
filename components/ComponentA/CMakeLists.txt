cmake_minimum_required(VERSION 3.15)
project(ComponentA LANGUAGES CXX)

set(CMAKE_CXX_STANDARD      17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ——— Auto‐include all .cpp under src/ ——————————————————————————————
file(GLOB COMPONENTA_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(ComponentA
    SHARED
    ${COMPONENTA_SRC}
)

target_include_directories(ComponentA
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(ComponentA
  PUBLIC
    shared
)

set_target_properties(ComponentA PROPERTIES
  VERSION   1.0.0
  SOVERSION 1
)

install(TARGETS ComponentA
        LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
