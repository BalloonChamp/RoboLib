cmake_minimum_required(VERSION 3.15)
project(MyProject LANGUAGES CXX)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# Where to put built libraries and executables
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   # for .a / .lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)   # for .so / .dll
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)   # for executables

# Make sure the compiler can find all our headers by default
include_directories(
  ${PROJECT_SOURCE_DIR}/lib/include
  ${PROJECT_SOURCE_DIR}/components/ComponentA/include
  ${PROJECT_SOURCE_DIR}/components/ComponentB/include
)

# Bring in subdirectories
add_subdirectory(lib)
add_subdirectory(components/ComponentA)
add_subdirectory(components/ComponentB)
add_subdirectory(apps/AppManager)
add_subdirectory(apps/AppFoo)
