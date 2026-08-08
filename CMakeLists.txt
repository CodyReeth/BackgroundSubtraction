cmake_minimum_required(VERSION 3.10)
project(SVD)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)

file(GLOB_RECURSE sources src/*.cc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(svd ${sources})

target_link_libraries(svd 
    PRIVATE 
    Eigen3::Eigen
    ${OpenCV_LIBS}
)
