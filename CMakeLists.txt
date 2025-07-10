cmake_minimum_required(VERSION 3.15)
project(MyProject VERSION 1.0 LANGUAGES CXX)

# ——— C++ standard ————————————————————————————————————————————————
set(CMAKE_CXX_STANDARD      17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS     OFF)

# ——— Build options ———————————————————————————————————————————————
option(BUILD_LIB         "Build the shared library (libshared)"    ON)
option(BUILD_COMPONENTA  "Build ComponentA library"                 ON)
option(BUILD_COMPONENTB  "Build ComponentB library"                 ON)
option(BUILD_APP_MANAGER "Build the AppManager executable"          ON)
option(BUILD_APP_FOO     "Build the AppFoo executable"              ON)

# ——— Output directories —————————————————————————————————————————————
# .a/.lib → lib/, .so/.dll → lib/, executables → bin/
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/bin)

# ——— RPATH settings: force runtime lookup to /opt/robolib/lib ————————
set(CMAKE_SKIP_BUILD_RPATH          TRUE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH  TRUE)
set(CMAKE_INSTALL_RPATH             "/opt/robolib/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# ——— Subdirectories —————————————————————————————————————————————————————
if(BUILD_LIB)
  add_subdirectory(lib)
endif()

if(BUILD_COMPONENTA)
  add_subdirectory(components/ComponentA)
endif()

if(BUILD_COMPONENTB)
  add_subdirectory(components/ComponentB)
endif()

if(BUILD_APP_MANAGER)
  add_subdirectory(apps/AppManager)
endif()

if(BUILD_APP_FOO)
  add_subdirectory(apps/AppFoo)
endif()
