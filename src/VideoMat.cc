#include <memory>
#include <iostream>

#include "VideoMat.h"
#include "VideoFrame.h"

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
VideoMat::VideoMat(std::initializer_list<std::initializer_list<double>> elements) :
    data_(std::make_unique<double[]>(elements.size() * elements.begin()->size())),
    rows_(elements.begin()->size()),
    cols_(elements.size()) {
        int curr_row = 0;
        for (auto &row : elements) {
            std::copy(row.begin(), row.end(), &data_[curr_row * rows_]);
            curr_row++;
        }
}

void VideoMat::Resize(std::size_t rows, std::size_t cols) {
    data_ = std::make_unique<double[]>(rows * cols);
    rows_ = rows;
    cols_ = cols;
}

double& VideoMat::operator()(std::size_t row, std::size_t col) {
    return data_[row * cols_ + col];
}

std::unique_ptr<VideoFrame> VideoMat::operator()(std::size_t col) {
    std::unique_ptr<VideoFrame> vf = std::make_unique<VideoFrame>(rows_);
    for (size_t i = 0; i < rows_; i++) {
        (*vf)[i] = data_[rows_ * col + i];
    }
    return vf;
}

void VideoMat::VMult(VideoFrame& in, VideoFrame& out) {

    if(rows_ != in.GetSize()) std::cerr << "Matrix dimension must match vector dimension." << std::endl;
    if(cols_ != out.GetSize()) std::cerr << "Input and output vectors must have same number of elements." << std::endl;

    for (int i = 0; i < rows_; i++) {
        out[i] = 0;
        for (int j = 0; j < cols_; j++) {
            out[i] += in[j] * data_[i + j * rows_];
        }
    }
}

size_t VideoMat::GetRows() {
    return rows_; 
}

size_t VideoMat::GetCols() {
    return cols_; 
}

void VideoMat::MMult(VideoMat& in, VideoMat& out) {

    for (int i = 0; i < out.GetCols(); i++) {
        for (int j = 0; j < out.GetRows(); j++) {
            out(i,j) = 0;
        }
    }

    for (int i = 0; i < out.GetCols(); i++) {
        for (int j = 0; j < out.GetRows(); j++) {
            for (int k = 0; k < cols_; k++) {
                //data(:,j) * in(i, :)
                out(i,j) += data_[k * rows_ + j ] * in(i,k);

            }
        }
    }
}
