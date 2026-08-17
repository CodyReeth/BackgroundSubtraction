#ifndef BACKGROUND_SUBTRACTION_INCLUDE_VIDEOMAT_H
#define BACKGROUND_SUBTRACTION_INCLUDE_VIDEOMAT_H

#include <memory>
#include <VideoFrame.h>

class VideoMat {
private:
    std::unique_ptr<double[]> data_;
    std::size_t rows_;
    std::size_t cols_;
public:
    VideoMat();
    VideoMat(std::size_t rows, std::size_t cols);
    void Resize(std::size_t rows, std::size_t cols);
    double& operator()(std::size_t row, std::size_t col);
    void vmult(VideoFrame& in, VideoFrame& out);
};

#endif // BACKGROUND_SUBTRACTION_INCLUDE_VIDEOMAT_H

