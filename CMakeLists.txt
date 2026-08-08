cmake_minimum_required(VERSION 3.10)

project(SVD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

# Library

file(GLOB_RECURSE sources src/*.cc)
list(FILTER sources EXCLUDE REGEX ".*main\\.cc$")

add_library(svd_lib ${sources})

target_include_directories(svd_lib 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(svd_lib
    PRIVATE 
    Eigen3::Eigen
    ${OpenCV_LIBS}
)

# Executable

add_executable(svd src/main.cc)
target_link_libraries(svd
    PRIVATE
    svd_lib
)

# Tests
enable_testing()
add_subdirectory(tests)
