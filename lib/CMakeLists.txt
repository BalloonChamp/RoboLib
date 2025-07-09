# Build a shared library called libshared
add_library(libshared
  src/libshared.cpp
)

# Install the public include directory for downstream
target_include_directories(libshared
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Set the library version (optional)
set_target_properties(libshared PROPERTIES
  VERSION 1.0.0
  SOVERSION 1
)