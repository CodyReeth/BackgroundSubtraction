add_executable(svd_unittest svd_unittest.cc)
target_link_libraries(svd_unittest
    PRIVATE
    background_subtraction_lib
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(svd_unittest)
