#include "gtest/gtest.h"
#include "VideoFrame.h"
#include "VideoMat.h"

TEST(LINALGTest, ScalarMult) {
    VideoFrame a({1,2,3,4,5});
    VideoFrame b({2,4,6,8,10});
    a *= 2;
    for (int i = 0; i < 5; i++) {
    EXPECT_DOUBLE_EQ(a[i], b[i]);
    }
}

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

TEST(LINALGTest, DiagonalMatrixVectorProduct) {
    VideoMat m(5,5);
    VideoFrame a(5);
    VideoFrame b(5);
    for (int i = 0; i < 5; i++) {
        a(i) = i + 1;
        m(i,i) = i + 1;
    }
    m.VMult(a,b);
    EXPECT_DOUBLE_EQ(979, b.Dot(b));
}

TEST(LINALGTest, StandardMatrixVectorProduct) {
    VideoMat m({{1,3,4,5},{3,-4,17,8},{22,-7,41,2},{0,-1,4,18}});
    VideoFrame a({1,2,-1,3});
    VideoFrame b({-15,-1,9,73});
    VideoFrame c(4);
    m.VMult(a,c);
    for (size_t i = 0; i < 3; i++) {
        EXPECT_DOUBLE_EQ(c[i], b[i]);
    }
}



TEST(LINALGTest, MatrixMatrixMultiplication) {
    VideoMat a({{1,2,3},{8,5,2},{1,2,3}});
    VideoMat b({{5,2,1},{2,3,4},{2,1,4}});
    VideoMat c({{22,22,22},{30,27,24},{14,17,20}});
    VideoMat d(3,3);
    a.MMult(b,d);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(c(i,j), d(i,j));
        }
    }
}
