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

# Tell autodiff to use the Eigen3 package installed by libigl
## I wish I could use something automated like this to get EIGEN3_INCLUDE_DIR
##get_target_property(Eigen3_INCLUDE_DIR Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)
set(EIGEN3_INCLUDE_DIR "${FETCHCONTENT_BASE_DIR}/eigen-src/")
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
