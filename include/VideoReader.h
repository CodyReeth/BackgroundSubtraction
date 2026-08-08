#include <iostream>
#include "VideoMat.h"

class VideoReader {
public: 
    VideoReader(const std::string& path);
    bool ReadVideo(VideoMat& mat);
};
