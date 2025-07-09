add_library(ComponentA STATIC
  src/ComponentA.cpp
)

target_include_directories(ComponentA
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# If ComponentA depends on libshared:
target_link_libraries(ComponentA
  PUBLIC
    libshared
)
