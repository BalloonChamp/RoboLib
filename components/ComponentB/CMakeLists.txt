add_library(ComponentB STATIC
  src/ComponentB.cpp
)

target_include_directories(ComponentB
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(ComponentB
  PUBLIC
    libshared
)
