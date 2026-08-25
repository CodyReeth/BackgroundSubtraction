#include "gtest/gtest.h"
#include <stdexcept>
#include "VideoFrame.h"
#include "VideoMat.h"

// Dot product
//---------------------------
TEST(DotProductTest, KnownValueDistinctInputs) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({-11,2,3,4});
    EXPECT_EQ(a.Dot(b), -46);
}
TEST(DotProductTest, ZeroVector) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({0,0,0,0});
    EXPECT_EQ(a.Dot(b), 0);
}
TEST(DotProductTest, KnownOrthogonalVectors) {
    VideoFrame a({1,1,0, 0});
    VideoFrame b({1,-1,1,1});
    EXPECT_EQ(a.Dot(b), 0);
}
TEST(DotProductTest, SelfMagnitude) {
    VideoFrame a({1,3,5,-14});
    EXPECT_EQ(a.Dot(a), 231);
}
TEST(DotProductTest, Commutativity) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({-11,2,3,4});
    EXPECT_EQ(a.Dot(b), b.Dot(a));
}
TEST(DotProductTest, SizeOneVector) {
    VideoFrame a({5});
    VideoFrame b({-12});
    EXPECT_EQ(a.Dot(b), -60);
}
TEST(DotProductTest, EmptyVector) {
    VideoFrame a;
    VideoFrame b;
    EXPECT_THROW(a.Dot(b), std::invalid_argument);
}
TEST(DotProductTest, LargeVectorAccumulation) {
    VideoFrame a(1e6);
    for (size_t i = 0; i < 1e6; i++) {
        a[i] = 1;
    }
    EXPECT_NEAR(a.Dot(a), 1e6, 1e-5);
}
TEST(DotProductTest, SizeMismatch) {
    VideoFrame a(5);
    VideoFrame b(2);
    EXPECT_THROW(a.Dot(b), std::invalid_argument);
}

// Scalar mult
//---------------------------
TEST(ScalarMultTest, KnownValueScale) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({3,9,15,-42});
    a *= 3;
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(a[i], b[i]);
    }

}
TEST(ScalarMultTest, NegativeScale) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({-1,-3,-5,14});
    a *= -1;
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(a[i], b[i]);
    }

}
TEST(ScalarMultTest, IdentityScale) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({1,3,5,-14});
    a *= 1;
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(a[i], b[i]);
    }
}
TEST(ScalarMultTest, ZeroScale) {
    VideoFrame a({1,3,5,-14});
    a *= 0;
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(a[i], 0);
    }
}
TEST(ScalarMultTest, DistributiveProperty) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({-1,-3,-5,14});
    VideoFrame c({0,0,0,0});
    c += a;
    c += b;
    c *= 3;
    a *= 3;
    b *= 3;
    a += b;
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(a[i], c[i]);
    }
}

// Matrix vector product
//---------------------------
TEST(MatrixVectorProductTest, IdentityMatrixVector) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b(4);
    VideoMat m({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}});
    m.VMult(a, b);
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(a[i], b[i]);
    }
}
TEST(MatrixVectorProductTest, ZeroMatrixVector) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b(4);
    VideoMat m({{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}});
    m.VMult(a, b);
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(b[i], 0);
    }
}
TEST(MatrixVectorProductTest, DiagonalMatrixVector) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({1,6,15,-56});
    VideoFrame c(4);
    VideoMat m({{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4}});
    m.VMult(a, c);
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(c[i], b[i]);
    }
}
TEST(MatrixVectorProductTest, KnownMatrixVector) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({63,117,-179,22});
    VideoFrame c(4);
    VideoMat m({{1,18,-6,3},{3,2,0,9},{5,41,-1,4},{-2,8,12,2}});
    m.VMult(a, c);
    for (size_t i = 0; i < 4; i++) {
        EXPECT_EQ(c[i], b[i]);
    }
}
TEST(MatrixVectorProductTest, NonSquareMatrixVector) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b({63,117,-179});
    VideoFrame c(3);
    VideoMat m({{1,18,-6},{3,2,0},{5,41,-1},{-2,8,12}});
    m.VMult(a, c);
    for (size_t i = 0; i < 3; i++) {
        EXPECT_EQ(c[i], b[i]);
    }
}
TEST(MatrixVectorProductTest, DimensionMismatchMatrixVector) {
    VideoFrame a({1,3,5,-14});
    VideoFrame b(4);
    VideoFrame c(5);
    VideoMat m1({{1,18,-6},{3,2,0},{5,41,-1}});
    VideoMat m({{1,18,-6},{3,2,0},{5,41,-1},{-2,8,12}});
    
    EXPECT_THROW(m1.VMult(a, b), std::invalid_argument);
    EXPECT_THROW(m.VMult(a, c), std::invalid_argument);

}

// Matrix matrix product
//---------------------------
TEST(MatrixMatrixProductTest, IdentityMatrixMatrix) {
    VideoMat a({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}});
    VideoMat b({{1,18,-6, 2},{3,2,0,2},{5,41,-1,3},{-2,8,12, 14}});
    VideoMat c(4,4);
    a.MMult(b, c);
    for (size_t i = 0; i < a.GetCols(); i++) {
        for (size_t j = 0; j < a.GetRows(); j++) {
            EXPECT_EQ(b(i,j),c(i,j));
        }
    }
}
TEST(MatrixMatrixProductTest, ZeroMatrixMatrix) {
    VideoMat a({{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}});
    VideoMat b({{1,18,-6, 2},{3,2,0,2},{5,41,-1,3},{-2,8,12, 14}});
    VideoMat c(4,4);
    a.MMult(b, c);
    for (size_t i = 0; i < a.GetCols(); i++) {
        for (size_t j = 0; j < a.GetRows(); j++) {
            EXPECT_EQ(a(i,j),c(i,j));
        }
    }
}
TEST(MatrixMatrixProductTest, KnownMatrixMatrix) {
    VideoMat a({{1,3,-1,9},{8,1,5,2},{15,-4,7,-3},{1,2,3,1}});
    VideoMat b({{1,18,-6, 2},{3,2,0,2},{5,41,-1,3},{-2,8,12, 14}});
    VideoMat c({{57,49,53,65},{21,15,13,33},{321,66,202,133},{256,-18,168,-24}});
    VideoMat d(4,4);
    a.MMult(b, d);
    for (size_t i = 0; i < a.GetCols(); i++) {
        for (size_t j = 0; j < a.GetRows(); j++) {
            EXPECT_EQ(d(i,j),c(i,j));
        }
    }

}
TEST(MatrixMatrixProductTest, NonSquareMatrixMatrix) {
    VideoMat a({{1,3,-1},{8,1,5},{15,-4,7},{1,2,3}});
    VideoMat b({{1,18,-6, 2},{3,2,0,2},{5,41,-1,3},{-2,8,12, 14}});
    VideoMat c({{57,49,53},{21,15,13},{321,66,202},{256,-18,168}});
    VideoMat d(3,4);
    a.MMult(b, d);
    for (size_t i = 0; i < d.GetRows(); i++) {
        for (size_t j = 0; j < d.GetCols(); j++) {
            EXPECT_EQ(d(i,j),c(i,j));
        }
    }
}
TEST(MatrixMatrixProductTest, NonCommutativeMatrixMatrix) {
    VideoMat a({{1,3,-1, 2},{8,1,5, 1},{15,-4,7, -3},{1,2,3,8}});
    VideoMat b({{1,18,-6, 2},{3,2,0,2},{5,41,-1,3},{-2,8,12, 14}});
    VideoMat c(4,4);
    VideoMat d(4,4);
    a.MMult(b, c);
    b.MMult(a, d);
    bool equal = true;
    for (size_t i = 0; i < c.GetCols(); i++) {
        for (size_t j = 0; j < c.GetRows(); j++) {
            if (c(i,j) != d(i,j)) equal = false;
        }
    }
    EXPECT_EQ(equal,false);
}
TEST(MatrixMatrixProductTest, AssociativeMatrixMatrix) {
    VideoMat a({{1,3,-1,4},{8,1,5,-3},{15,-4,7,2},{1,2,3,14}});
    VideoMat b({{1,18,-6, 2},{3,2,0,2},{5,41,-1,3},{-2,8,12, 14}});
    VideoMat c({{57,49,53,-34},{21,15,13,34},{321,66,202,-63},{256,-18,168,188}});
    VideoMat d(4,4);
    VideoMat e(4,4);
    VideoMat f(4,4);
    a.MMult(b, d);
    c.MMult(d,e);
    c.MMult(a,d);
    d.MMult(b,f);


    for (size_t i = 0; i < e.GetRows(); i++) {
        for (size_t j = 0; j < e.GetCols(); j++) {
            EXPECT_EQ(e(i,j),f(i,j));
        }
    }

}
TEST(MatrixMatrixProductTest, DimensionMismatchMatrixMatrix) {
    VideoMat a({{1,3,-1},{8,1,5},{15,-4,},{1,2,3}}); // 3x4
    VideoMat b({{1,3,-1,8},{8,1,5,-2},{15,-4,11,15}}); // 4x3
    VideoMat c(3,4); // 4x3
    VideoMat d(4,4); // 4x4
    VideoMat e(3,3); // 3x3
    VideoMat f(3,3); // 3x3

    EXPECT_THROW(a.MMult(b,c), std::invalid_argument);
    EXPECT_THROW(a.MMult(e,f), std::invalid_argument);
    EXPECT_THROW(b.MMult(d,e), std::invalid_argument);
    EXPECT_NO_THROW(a.MMult(b, e));
}
