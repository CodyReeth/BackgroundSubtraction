cmake_minimum_required(VERSION 3.10)

project(BackgroundSubtraction)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)

# Library

file(GLOB_RECURSE sources src/*.cc)
list(FILTER sources EXCLUDE REGEX ".*main\\.cc$")

add_library(background_subtraction_lib ${sources})
target_compile_definitions(background_subtraction_lib
    PUBLIC
    ACCELERATE_NEW_LAPACK
)

target_include_directories(background_subtraction_lib 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(background_subtraction_lib
    PUBLIC
    Eigen3::Eigen
    ${OpenCV_LIBS}
    "-framework Accelerate"
)

# Executable

add_executable(background_subtraction src/main.cc)
target_link_libraries(background_subtraction
    PRIVATE
    background_subtraction_lib
)

# Tests
enable_testing()
add_subdirectory(tests)
