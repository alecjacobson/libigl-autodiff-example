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

# Fetch Eigen3 provided by libigl
get_target_property(Eigen3_INCLUDE_DIR Eigen3::Eigen INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "Eigen3_INCLUDE_DIR: ${Eigen3_INCLUDE_DIR}")
set(Eigen3_DIR "${Eigen3_INCLUDE_DIR}/cmake")
message(STATUS "Eigen3_DIR : ${Eigen3_DIR}")
# why doesn't this work?
list(APPEND CMAKE_MODULE_PATH ${Eigen3_DIR})


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
