# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

# project name
project(test1)

# target
add_executable( test1 test1.cpp )

# external libs
find_package(Ceres REQUIRED)
# Or find_package(Ceres REQUIRED PATHS "/path/to/install/dir") if the install directory is not in your PATH

target_include_directories(test1
  PRIVATE
    ${CERES_INCLUDE_DIRS}
)

target_link_libraries(test1
  PRIVATE
    ${CERES_LIBRARIES}
)
