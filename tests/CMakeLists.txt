add_executable(test_svd test_svd.cc)
target_link_libraries(test_svd
    PRIVATE
    svd_lib
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(test_svd)
