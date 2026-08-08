#ifndef SVD_INCLUDE_LOWRANKMASK_H
#define SVD_INCLUDE_LOWRANKMASK_H

#include "VideoMat.h"
#include "SVD.h"

class LowRankMask {
public:
    LowRankMask(SVD& svd);
    void Apply(VideoMat& vm);
};
#endif // SVD_INCLUDE_LOWRANKMASK_H
