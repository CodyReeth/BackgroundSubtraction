cmake_minimum_required(VERSION 3.10)
project(SVD)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
add_executable(svd src/main.cc)
target_link_libraries(svd PRIVATE ${OpenCV_LIBS})
