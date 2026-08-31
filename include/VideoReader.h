#ifndef BACKGROUND_SUBTRACTION_INCLUDE_VIDEOREADER_H
#define BACKGROUND_SUBTRACTION_INCLUDE_VIDEOREADER_H

#include <iostream>
#include "VideoMat.h"

class VideoReader {
public: 
    VideoReader(const std::string& path);
    void ReadVideo(VideoMat& mat);

private:
    std::string path_;
};
#endif // BACKGROUND_SUBTRACTION_INCLUDE_VIDEOREADER_H
