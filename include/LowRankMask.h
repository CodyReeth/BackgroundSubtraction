#ifndef BACKGROUND_SUBTRACTION_INCLUDE_LOWRANKMASK_H
#define BACKGROUND_SUBTRACTION_INCLUDE_LOWRANKMASK_H

#include "VideoMat.h"
#include "SVD.h"

class LowRankMask {
public:
    LowRankMask(SVD& svd);
    void Apply(VideoMat& vm);
};
#endif // BACKGROUND_SUBTRACTION_INCLUDE_LOWRANKMASK_H
