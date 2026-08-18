#include "gtest/gtest.h"
#include <memory>
#include "VideoFrame.h"
#include "VideoMat.h"
#include "SVD.h"

TEST(SVDTest, VideoMatrixAllocation) {
    VideoMat m(5,5);
    EXPECT_EQ(m(0,0), 0);
}

TEST(SVDTest, NonIdentityMatrix) {
    VideoMat m;
}

TEST(QRDecomp, QOrthonormal) {
    VideoMat vm({{1,2,-1,3,0},{8,12,-5,-5,-18},{23,1,0,-1,3},{2,9,14,8,5},{3,-4,-28,15,2}});
    VideoMat q(5,5);
    VideoMat r(5,5);
    SVD svd(vm,1);
    svd.QR(vm, q, r);
    VideoMat vm2(5,5);

    for (int i = 0; i < 5; i++) {
        std::unique_ptr<VideoFrame> frame_i = q(i);
        for (int j = 0; j < 5; j++) {
            std::unique_ptr<VideoFrame> frame_j = q(j);
            double dotp = frame_i->Dot(*frame_j);
            if (i == j) {
                EXPECT_NEAR(dotp, 1, 1e-9);
            } else EXPECT_NEAR(dotp, 0, 1e-9);
        }
    }
}

TEST(QRDecomp, Reconstruction) {
    VideoMat vm({{1,2,-1,3,0},{8,12,-5,-5,-18},{23,1,0,-1,3},{2,9,14,8,5},{3,-4,-28,15,2}});
    VideoMat q(5,5);
    VideoMat r(5,5);
    SVD svd(vm,1);
    svd.QR(vm, q, r);
    VideoMat vm2(5,5);
    q.MMult(r, vm2);
    for (size_t i = 0; i < vm.GetCols(); i++) {
        for (size_t j = 0; j < vm.GetRows(); j++) {
            EXPECT_DOUBLE_EQ(vm(i,j), vm2(i,j));
        }
    }
}
