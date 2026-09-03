#ifndef BACKGROUND_SUBTRACTION_INCLUDE_VIDEOFRAME_H
#define BACKGROUND_SUBTRACTION_INCLUDE_VIDEOFRAME_H
#include <memory>
#include <initializer_list>

class VideoFrame {
private:
    std::unique_ptr<double[]> data_;
    size_t size_;
    std::pair<int,int> frame_dims_;
public:
    VideoFrame();
    VideoFrame(size_t size);
    VideoFrame(size_t size, int width, int height);
    VideoFrame(std::initializer_list<double> elements);
    void Resize(size_t size, int width, int height);
    double Dot(VideoFrame& b);
    double& operator[](std::size_t index);
    double& operator()(std::size_t index);
    size_t GetSize();
    VideoFrame& operator*=(double scale);
    VideoFrame& operator+=(VideoFrame& f2);
    VideoFrame& operator-=(VideoFrame& f2);
    double* GetData();
    std::pair<int,int> GetFrameDims();
    
};

#endif // BACKGROUND_SUBTRACTION_INCLUDE_VIDEOFRAME_H

