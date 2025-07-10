cmake_minimum_required(VERSION 3.15)
project(AppManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD      17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ——— Auto‐include all .cpp under src/ ——————————————————————————————
file(GLOB APPMGR_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(AppManager
    ${APPMGR_SRC}
)

target_include_directories(AppManager
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/include
    ${PROJECT_SOURCE_DIR}/components/ComponentA/include
)

target_link_libraries(AppManager
  PRIVATE
    shared
    ComponentA
)

set_target_properties(AppManager PROPERTIES
  SKIP_BUILD_RPATH         TRUE
  BUILD_WITH_INSTALL_RPATH TRUE
  INSTALL_RPATH            "/opt/robolib/lib"
)
