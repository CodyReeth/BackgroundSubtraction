#include <memory>
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
