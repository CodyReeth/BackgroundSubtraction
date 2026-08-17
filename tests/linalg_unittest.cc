#include "gtest/gtest.h"
#include "VideoFrame.h"
#include "VideoMat.h"

TEST(LINALGTest, SmallDotProduct) {
    VideoFrame a(5);
    VideoFrame b(5);
    for (int i = 0; i < 5; i++) {
        a(i) = 1;
        b(i) = 1;
    }
    EXPECT_DOUBLE_EQ(5, a.Dot(b));
}

TEST(LINALGTest, LargeDotProduct) {
    const size_t large_size = 1e5;
    VideoFrame a(large_size);
    VideoFrame b(large_size);
    for (int i = 0; i < large_size; i++) {
        a(i) = 1;
        b(i) = 1;
    }
    EXPECT_DOUBLE_EQ(large_size, a.Dot(b));
}

TEST(LINALGTest, IdentityMatrixVectorProduct) {
    VideoMat m(5,5);
    VideoFrame a(5);
    for (int i = 0; i < 5; i++) {
        a(i) = i;
        m(i,i) = i;
    }

    EXPECT_DOUBLE_EQ(256, a.Dot(a));
}

