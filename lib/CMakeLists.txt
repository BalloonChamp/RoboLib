cmake_minimum_required(VERSION 3.15)
project(libshared VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD      17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS     OFF)

# ——— Automatically grab all .cpp under src/ ——————————————————————————
file(GLOB LIB_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(shared
    SHARED
    ${LIB_SRC}
)

target_include_directories(shared
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(shared PROPERTIES
  VERSION   ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
)

install(TARGETS shared
        LIBRARY DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
