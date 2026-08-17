#include <memory>
#include <iostream>

#include "VideoMat.h"

VideoMat::VideoMat() 
    : data_(nullptr),
    rows_(0),
    cols_(0)
{}

VideoMat::VideoMat(std::size_t rows, std::size_t cols) 
    : data_(std::make_unique<double[]>(rows * cols)),
    rows_(rows),
    cols_(cols)
{}

void VideoMat::Resize(std::size_t rows, std::size_t cols) {
    data_ = std::make_unique<double[]>(rows * cols);
    rows_ = rows;
    cols_ = cols;
}

double& VideoMat::operator()(std::size_t row, std::size_t col) {
    return data_[row + col * rows_];
}

void VideoMat::vmult(VideoFrame& in, VideoFrame& out) {

    if(rows_ != in.GetSize()) std::cerr << "Matrix dimension must match vector dimension." << std::endl;
    if(cols_ != out.GetSize()) std::cerr << "Input and output vectors must have same number of elements." << std::endl;

    for (int i = 0; i < rows_; i++) {
        out[i] = 0;
        for (int j = 0; j < cols_; j++) {
            out[i] += in[j] * data_[j + i * rows_];
        }
    }
}
