#ifndef BACKGROUND_SUBTRACTION_INCLUDE_VIDEOMAT_H
#define BACKGROUND_SUBTRACTION_INCLUDE_VIDEOMAT_H

#include <initializer_list>
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
    VideoMat(std::initializer_list<std::initializer_list<double>> elements);
    void Resize(std::size_t rows, std::size_t cols);
    double& operator()(std::size_t row, std::size_t col);
    std::unique_ptr<VideoFrame> operator()(std::size_t col);
    void VMult(VideoFrame& in, VideoFrame& out);
    void MMult(VideoMat& in, VideoMat& out);
    size_t GetRows();
    size_t GetCols();
    void Randomize();
    void RawPrint();
};

#endif // BACKGROUND_SUBTRACTION_INCLUDE_VIDEOMAT_H

