#include "gtest/gtest.h"
#include "VideoMat.h"

TEST(SVDTest, VideoMatrixAllocation) {
    VideoMat m(5,5);
    EXPECT_EQ(m(0,0), 0);
}

TEST(SVDTest, NonIdentityMatrix) {
    VideoMat m;
}
