cmake_minimum_required(VERSION 3.10)

project(BackgroundSubtraction)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(GTest REQUIRED)

# Debug / sanitizer configuration
add_library(sanitizers INTERFACE)

target_compile_options(sanitizers INTERFACE
    $<$<CONFIG:Debug>:-g -O0 -fno-omit-frame-pointer -fsanitize=address,undefined>
)

target_link_options(sanitizers INTERFACE
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>
)

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
    sanitizers
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
