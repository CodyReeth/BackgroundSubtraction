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

void VideoFrame::Dot(VideoFrame &in, VideoFrame &out) {

}
