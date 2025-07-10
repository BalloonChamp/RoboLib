cmake_minimum_required(VERSION 3.15)
project(AppFoo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD      17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ——— Auto‐include all .cpp under src/ ——————————————————————————————
file(GLOB APPFOO_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(AppFoo
    ${APPFOO_SRC}
)

target_include_directories(AppFoo
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/include
    ${PROJECT_SOURCE_DIR}/components/ComponentA/include
)

target_link_libraries(AppFoo
  PRIVATE
    shared
    ComponentA
)

set_target_properties(AppFoo PROPERTIES
  SKIP_BUILD_RPATH         TRUE
  BUILD_WITH_INSTALL_RPATH TRUE
  INSTALL_RPATH            "/opt/robolib/lib"
)
