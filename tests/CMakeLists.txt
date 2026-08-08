add_executable(test_svd test_svd.cc)
target_link_libraries(test_svd
    PRIVATE
    svd_lib
)
add_test(
    NAME SVDTest
    COMMAND test_svd
)
