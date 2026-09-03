#include <iostream>
#include <cmath>
#include <memory>

#include "SVD.h"

SVD::SVD(VideoMat& vm, int rank) { // Y = A Omega
// QR = Y
// B = Q^TA
// BB^T = U^~Sigma^2U^~^T
// U = QU^~
// V = BU^~Sigma^-1
VideoMat omega_m, y_m, q_m, r_m, b_m, bbt_m, u_tilde_m, u_m, v_m;
omega_m.Resize(vm.GetCols(), rank);
omega_m.Randomize();
y_m.Resize(vm.GetRows(), rank);

vm.MMultFast(omega_m, y_m);

q_m.Resize(vm.GetRows(), rank);
r_m.Resize(rank,rank);
QR(vm,q_m,r_m);

b_m.Resize(rank, vm.GetCols());
q_m.MMultFastTransposeLeft(vm, b_m);

bbt_m.Resize(rank,rank);
VideoMat b_m_copy(b_m);
b_m.MMultFastTransposeRight(b_m_copy, bbt_m);

//Eigendecomposition
// symmetry test
for (int i = 0; i < bbt_m.GetRows(); i++) {
        if (bbt_m(i,i) - bbt_m(bbt_m.GetRows() - i,bbt_m.GetRows() - i) > 1e-5) std::cout << "MISMATCH\n";
    }

}

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

