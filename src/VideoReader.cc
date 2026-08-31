#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include "VideoReader.h"

VideoReader::VideoReader(const std::string& path) 
    : path_(path) 
{}

void VideoReader::ReadVideo(VideoMat& mat) {
    cv::VideoCapture vc(path_);
    if (!vc.isOpened()) throw std::invalid_argument("VideoReader: Could not read video");

    int frames = vc.get(cv::CAP_PROP_FRAME_COUNT);
    int width = vc.get(cv::CAP_PROP_FRAME_WIDTH);
    int height = vc.get(cv::CAP_PROP_FRAME_HEIGHT);

    int pixels_per_frame = width * height;

    cv::Mat frame, gray_frame, gray_frame_double;
    mat.Resize(pixels_per_frame, frames, width, height);

    int frame_counter = 0;
    while(vc.read(frame)) {
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        if (!gray_frame.isContinuous()) gray_frame = gray_frame.clone();
        gray_frame.convertTo(gray_frame_double, CV_64F);

        std::memcpy(mat.GetData() + (frame_counter * pixels_per_frame), gray_frame_double.data, pixels_per_frame * sizeof(double));
        frame_counter++;
    }
}

