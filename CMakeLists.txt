cmake_minimum_required(VERSION 3.16)
project(example)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# enable c++17
set(CMAKE_CXX_STANDARD 17)

# Libigl
include(libigl)

# Enable the target igl::glfw
igl_include(glfw)

# autodiff.github.io
include(FetchContent)

# Get the Eigen3 include directory from the Eigen3::Eigen target
get_target_property(EIGEN3_INCLUDE_DIR_TMP Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)

# Use file(GENERATE ...) to resolve the generator expression at build-system generation time
file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/eigen3_include_dir.txt" CONTENT "${EIGEN3_INCLUDE_DIR_TMP}")

# Execute process to force CMake to generate the file before continuing
execute_process(COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --cyan "Resolving Eigen3 include directory")

# Read the resolved path from the file
file(READ "${CMAKE_BINARY_DIR}/eigen3_include_dir.txt" EIGEN3_INCLUDE_DIR)

list(APPEND CMAKE_MODULE_PATH "${EIGEN3_INCLUDE_DIR}/cmake/")


set(AUTODIFF_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(AUTODIFF_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(AUTODIFF_BUILD_PYTHON OFF CACHE BOOL "" FORCE)
set(AUTODIFF_BUILD_DOCS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
  autodiff
  GIT_REPOSITORY https://github.com/autodiff/autodiff/
  GIT_TAG        v1.0.3
)
FetchContent_MakeAvailable(autodiff)

# Add your project files
file(GLOB SRC_FILES *.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link igl (and the glfw module) to your project
target_link_libraries(${PROJECT_NAME} PUBLIC 
  igl::glfw
  autodiff
  Eigen3::Eigen
  )
