#include <iostream>
#include "VideoFrame.h"

VideoFrame::VideoFrame()  
    : data_(nullptr),
    size_(0)
{}

VideoFrame::VideoFrame(size_t size)  
    : data_(std::make_unique<double[]>(size)),
    size_(size)
{}

void VideoFrame::Resize(size_t size) {
    data_ = std::make_unique<double[]>(size);
    size_ = size;
}

double& VideoFrame::operator[](std::size_t index) {
    return data_[index];
}
double& VideoFrame::operator()(std::size_t index) {
    return data_[index];
}

size_t VideoFrame::GetSize() {
    return size_;
}

double VideoFrame::Dot(VideoFrame &b) {
    if (size_ != b.size_) std::cerr << "Dot product requires vectors of same length" << std::endl;

    double res = 0;
    for (int i = 0; i < b.size_; i++) {
        res += data_[i] * b(i);
    }

    return res;
}
