#ifndef BACKGROUND_SUBTRACTION_INCLUDE_SVD_H
#define BACKGROUND_SUBTRACTION_INCLUDE_SVD_H

#include "VideoMat.h"

class SVD {
public:
    SVD(VideoMat& vm, int rank = 5);
    void QR(VideoMat &vm, VideoMat &q, VideoMat &r);
};
#endif // BACKGROUND_SUBTRACTION_INCLUDE_SVD_H
