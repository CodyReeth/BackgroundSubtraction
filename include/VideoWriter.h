#ifndef SVD_INCLUDE_VIDEOWRITER_H
#define SVD_INCLUDE_VIDEOWRITER_H

#include <iostream>
#include "VideoMat.h"

class VideoWriter {
public:
    VideoWriter(const std::string& path);
    void Write(VideoMat& vm);
};
#endif // SVD_INCLUDE_VIDEOWRITER_H
