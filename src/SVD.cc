#include "SVD.h"
#include <cmath>
#include <memory>

SVD::SVD(VideoMat& vm, int rank)
{}

void SVD::QR(VideoMat &vm, VideoMat &q, VideoMat &r) {

    for (size_t i = 0; i < q.GetCols(); i++) {

        for (size_t j = 0; j < q.GetRows(); j++) {
            q(i,j) = 0;
        }
    }
    for (size_t i = 0; i < r.GetCols(); i++) {
        for (size_t j = 0; j < r.GetRows(); j++) {
            r(i,j) = 0;
        }
    }

    for (size_t i = 0; i < vm.GetCols(); i++) {
        std::unique_ptr<VideoFrame> vec_i = vm(i);
        for (size_t j = 0; j < i; j++) {
            std::unique_ptr<VideoFrame> vec_j = q(j);
            double dotp = vec_j->Dot(*vec_i);
            r(i,j) = dotp;
            *vec_j *= dotp;
            *vec_i -= *vec_j;
        }
        double norm = std::sqrt(vec_i->Dot(*vec_i));
        r(i,i) = norm;
        *vec_i *= 1/norm;
        for (size_t j = 0; j < q.GetRows(); j++) {
            q(i,j) = (*vec_i)(j);
        }
    }
}

// Y = A Omega
// QR = Y
// B = Q^TA
// BB^T = U^~Sigma^2U^~^T
// U = QU^~
// V = BU^~Sigma^-1
