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
    std::pair<int,int> frame_dims_; // (width,height)
public:
    VideoMat();
    VideoMat(VideoMat& vm);
    void SetColumn(int column, VideoFrame& f);
    VideoMat(std::size_t rows, std::size_t cols);
    VideoMat(std::initializer_list<std::initializer_list<double>> elements);
    void Resize(std::size_t rows, std::size_t cols);
    void Resize(std::size_t rows, std::size_t cols, int frame_width, int frame_height);
    double& operator()(std::size_t row, std::size_t col);
    std::unique_ptr<VideoFrame> operator()(std::size_t col);
    void VMult(VideoFrame& in, VideoFrame& out);
    void MMult(VideoMat& in, VideoMat& out);
    void MMultFast(VideoMat& in, VideoMat& out);
    void MMultFastTransposeLeft(VideoMat& in, VideoMat& out);
    void MMultFastTransposeRight(VideoMat& in, VideoMat& out);
    size_t GetRows();
    size_t GetCols();
    std::pair<int,int> GetFrameDims();
    void Randomize();
    void RawPrint();
    double* GetData();
    void LoadFrame(size_t index, VideoFrame& out);
    void FillData(double val);
};

#endif // BACKGROUND_SUBTRACTION_INCLUDE_VIDEOMAT_H

