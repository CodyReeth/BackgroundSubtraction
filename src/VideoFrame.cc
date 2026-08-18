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
VideoFrame::VideoFrame(std::initializer_list<double> elements) :
    data_(std::make_unique<double[]>(elements.size())),
    size_(elements.size()) {
    std::copy(elements.begin(), elements.end(), &data_[0]);
}

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

VideoFrame& VideoFrame::operator*=(double scale) {
    for (size_t i = 0; i < size_; i++) {
        data_[i] *= scale;
    }
    return *this;
}
VideoFrame& VideoFrame::operator+=(VideoFrame& f2) {
    if (f2.GetSize() != size_) std::cerr << "Vectors must be the same size." << std::endl;
    for (size_t i = 0; i < size_; i++) {
        data_[i] += f2[i];
    }
    return *this;
}
VideoFrame& VideoFrame::operator-=(VideoFrame& f2) {
    if (f2.GetSize() != size_) std::cerr << "Vectors must be the same size." << std::endl;
    for (size_t i = 0; i < size_; i++) {
        data_[i] -= f2[i];
    }
    return *this;
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
