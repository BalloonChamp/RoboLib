add_executable(AppFoo
  src/AppFoo.cpp
)

# Tell CMake where to find headers (if needed)
target_include_directories(AppFoo
  PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/include
    ${PROJECT_SOURCE_DIR}/components/ComponentA/include
    ${PROJECT_SOURCE_DIR}/components/ComponentB/include
)

# Link against the shared library and whichever components you need:
target_link_libraries(AppFoo
  PRIVATE
    libshared     # the .so from lib/
    ComponentA    # static lib for component A
    ComponentB    # static lib for component B
)
