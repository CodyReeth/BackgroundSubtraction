#include <memory>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <random>
#include <stdexcept>
#include <Accelerate/Accelerate.h>
#include <vecLib/vecLib.h>

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

VideoMat::VideoMat(VideoMat& vm) 
    : data_(std::make_unique<double[]>(vm.GetRows() * vm.GetCols())),
    rows_(vm.GetRows()),
    cols_(vm.GetCols()),
    frame_dims_(vm.GetFrameDims())
{
    std::memcpy(vm.GetData(), data_.get(), rows_ * cols_);
}

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

double* VideoMat::GetData() {
    return data_.get();
}

void VideoMat::LoadFrame(size_t index, VideoFrame& out) {
    if (out.GetSize() != rows_) throw std::invalid_argument("LoadFrame: incompatible sizes");

    std::memcpy(&data_[rows_ * index], out.GetData(), rows_);
}

void VideoMat::Resize(std::size_t rows, std::size_t cols, int frame_width, int frame_height) {

    data_ = std::make_unique<double[]>(rows * cols);
    rows_ = rows;
    cols_ = cols;
    frame_dims_ = std::make_pair(frame_width, frame_height);
}

double& VideoMat::operator()(std::size_t row, std::size_t col) {
    return data_[row * rows_ + col];
}

std::unique_ptr<VideoFrame> VideoMat::operator()(std::size_t col) {
    std::unique_ptr<VideoFrame> vf = std::make_unique<VideoFrame>(rows_,frame_dims_.first,frame_dims_.second);
    for (size_t i = 0; i < rows_; i++) {
        (*vf)[i] = data_[rows_ * col + i];
    }
    return vf;
}
void VideoMat::FillData(double val) {
    for (size_t i = 0; i < rows_ * cols_; i++) {
        data_[i] = val;
    }
}

void VideoMat::VMult(VideoFrame& in, VideoFrame& out) {

    if(rows_ == 0 || cols_ == 0 || in.GetSize() == 0 || out.GetSize() == 0) throw std::invalid_argument("VMult: Cannot multiply with dimension zero");

    if(cols_ != in.GetSize()) throw std::invalid_argument("VMult: Dimension mismatch");
    if(rows_!= out.GetSize()) throw std::invalid_argument("VMult: Dimension mismatch");

    for (int i = 0; i < rows_; i++) {
        out[i] = 0;
        for (int j = 0; j < cols_; j++) {
            out[i] += in[j] * data_[i + j * rows_];
        }
    }
}

void VideoMat::RawPrint() {
    for (size_t i = 0; i < rows_ * cols_; i++) {
        std::cout << data_[i] << " ";
    }
    std::cout << std::endl;
}

size_t VideoMat::GetRows() {
    return rows_; 
}

size_t VideoMat::GetCols() {
    return cols_; 
}

void VideoMat::MMult(VideoMat& in, VideoMat& out) {

    if(cols_ != in.GetRows()) throw std::invalid_argument("MMult: Dimension mismatch");
    if(rows_ != out.GetRows() || in.GetCols() != out.GetCols()) throw std::invalid_argument("MMult: Dimension mismatch");

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

void VideoMat::MMultFast(VideoMat& in, VideoMat& out) {

    if(cols_ != in.GetRows()) throw std::invalid_argument("MMult: Dimension mismatch");
    if(rows_ != out.GetRows() || in.GetCols() != out.GetCols()) throw std::invalid_argument("MMult: Dimension mismatch");

    // C = alpha * A * B + beta * C
    cblas_dgemm(
        CblasColMajor,
        CblasNoTrans,
        CblasNoTrans,
        rows_, in.GetCols(), cols_,
        /* alpha = */ 1.0,
        data_.get(), rows_,
        in.GetData(), cols_,
        /* beta = */ 0.0,
        out.GetData(), rows_
                );
}
void VideoMat::Randomize() {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::normal_distribution<double> dist(0, 1);

    for (size_t i = 0; i < cols_; i++) {
        for (size_t j = 0; j < cols_; j++) {
            data_[rows_ * i + j] = dist(gen);
        }
    }
}

std::pair<int,int> VideoMat::GetFrameDims() {
    return frame_dims_;
}
