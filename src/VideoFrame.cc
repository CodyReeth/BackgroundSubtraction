#include <iostream>
#include <initializer_list>
#include "VideoFrame.h"

VideoFrame::VideoFrame()  
    : data_(nullptr),
    size_(0)
{}

VideoFrame::VideoFrame(size_t size)  
    : data_(std::make_unique<double[]>(size)),
    size_(size)
{}

VideoFrame::VideoFrame(size_t size, int width, int height)  
    : data_(std::make_unique<double[]>(size)),
    size_(size),
    frame_dims_(std::make_pair(width,height))
{}

VideoFrame::VideoFrame(std::initializer_list<double> elements) :
    data_(std::make_unique<double[]>(elements.size())),
    size_(elements.size()) {
    std::copy(elements.begin(), elements.end(), &data_[0]);
}

void VideoFrame::Resize(size_t size, int width, int height) {
    data_ = std::make_unique<double[]>(size);
    size_ = size;
    frame_dims_ = std::make_pair(width, height);
}

std::pair<int,int> VideoFrame::GetFrameDims() {
    return frame_dims_;
}

double* VideoFrame::GetData() {
    return data_.get();
}

double& VideoFrame::operator[](std::size_t index) {
    return data_[index];
}
double& VideoFrame::operator()(std::size_t index) {
    return data_[index];
}

VideoFrame& VideoFrame::operator*=(double scale) {
    for (size_t i = 0; i < size_; i++) {
        data_[i] *= scale;
    }
    return *this;
}
VideoFrame& VideoFrame::operator+=(VideoFrame& f2) {
    if (f2.GetSize() != size_ || size_ == 0) throw std::invalid_argument("+=: Vector size error");
    for (size_t i = 0; i < size_; i++) {
        data_[i] += f2[i];
    }
    return *this;
}
VideoFrame& VideoFrame::operator-=(VideoFrame& f2) {
    if (f2.GetSize() != size_ || size_ == 0) throw std::invalid_argument("-=: Vector size error");
    for (size_t i = 0; i < size_; i++) {
        data_[i] -= f2[i];
    }
    return *this;
}
size_t VideoFrame::GetSize() {
    return size_;
}

double VideoFrame::Dot(VideoFrame &b) {
    if (size_ != b.size_ || size_ == 0) throw std::invalid_argument("Dot: Vector size error");

    double res = 0;
    for (int i = 0; i < b.size_; i++) {
        res += data_[i] * b(i);
    }

    return res;
}
