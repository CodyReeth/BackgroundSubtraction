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
VideoFrame sigma;
omega_m.Resize(vm.GetCols(), rank);
omega_m.Randomize();
y_m.Resize(vm.GetRows(), rank);

vm.MMultFast(omega_m, y_m);

q_m.Resize(vm.GetRows(), rank);
r_m.Resize(rank,rank);
QR(y_m,q_m,r_m);

b_m.Resize(rank, vm.GetCols());
q_m.MMultFastTransposeLeft(vm, b_m);

bbt_m.Resize(rank,rank);
VideoMat b_m_copy(b_m);
b_m.MMultFastTransposeRight(b_m_copy, bbt_m);

//Eigendecomposition

u_tilde_m.Resize(rank,rank);
u_tilde_m.FillData(1);
sigma.Resize(rank, 0,0);


auto x = u_tilde_m(0);
//x->RawPrint();
VideoMat test_mat({{2,1,0},{0,3,0},{0,0,4}});

Diagonalize(test_mat, u_tilde_m, sigma, 1e-6);
sigma.RawPrint();
//Diagonalize(bbt_m, u_tilde_m, sigma, 1e-3);

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

void SVD::Diagonalize(VideoMat& vm, VideoMat& eigenvectors, VideoFrame& eigenvalues, double tol) {
    // \lambda = (x^T A x) / (x^T x)
    // x -= -(A - \lambda I)x

    for (int i = 0; i < eigenvectors.GetCols(); i++) {

        double lambda_prev = std::numeric_limits<double>::min();
        double lambda = std::numeric_limits<double>::max();

        while(std::abs(lambda - lambda_prev) > tol) {

            lambda_prev = lambda;
            auto x = eigenvectors(i);
            VideoFrame ax(eigenvalues.GetSize());
            vm.VMult(*x, ax);
            lambda = x->Dot(ax);
            VideoFrame descent_vec(*x);
            descent_vec *= -lambda;
            descent_vec += ax;
            descent_vec *= 1e-2;
            *x -= descent_vec;
            // Gram Schmidt
            for (int j = 0; j < i; j++) {
                auto y = eigenvectors(j);
                double overlap = y->Dot(*x);
                *y *= -overlap;
                *x += *y;
            }
            double scale = std::sqrt(1 / x->Dot(*x));
            *x *= scale;
            eigenvectors.SetColumn(i, *x);

        }
        eigenvalues[i] = lambda;
    }
}
