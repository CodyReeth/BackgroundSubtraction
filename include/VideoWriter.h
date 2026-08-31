#ifndef BACKGROUND_SUBTRACTION_INCLUDE_VIDEOWRITER_H
#define BACKGROUND_SUBTRACTION_INCLUDE_VIDEOWRITER_H

#include <iostream>
#include "VideoMat.h"

class VideoWriter {
public:
    VideoWriter(const std::string& path);
    void Write(VideoMat& vm);
private:
    std::string path_;
};
#endif // BACKGROUND_SUBTRACTION_INCLUDE_VIDEOWRITER_H
