#include <iostream>

#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

#include "VideoWriter.h"
#include "VideoMat.h"
#include "VideoFrame.h"

VideoWriter::VideoWriter(const std::string& path) 
    : path_(path) 
{}

void VideoWriter::WriteVideo(VideoMat& vm) {
    std::pair<int,int> frame_dims = vm.GetFrameDims();
    cv::VideoWriter output_video;
    output_video.open(path_, cv::VideoWriter::fourcc('m','p','4','v'), 30,
                      cv::Size(frame_dims.first,frame_dims.second), /*color =*/ false);
    if (!output_video.isOpened()) throw std::invalid_argument("VideoWriter: could not open file for writing");

    for (size_t frame_counter = 0; frame_counter < vm.GetCols(); frame_counter++) {
        double* frame_buffer = vm.GetData() + (frame_counter * vm.GetRows());
        cv::Mat cv_frame(frame_dims.second,frame_dims.first, CV_64F, frame_buffer);
        cv::Mat cv_frame_uchar;
        cv_frame.convertTo(cv_frame_uchar, CV_8UC1);
        output_video.write(cv_frame_uchar);
    }
    output_video.release();
}

void VideoWriter::WriteFrame(VideoFrame& f, std::string& path) {

    cv::Mat cv_frame(f.GetFrameDims().second, f.GetFrameDims().first, CV_64F, f.GetData());
    cv::Mat cv_frame_uchar;
    cv_frame.convertTo(cv_frame_uchar, CV_8UC1);
    cv::imwrite(path, cv_frame_uchar);


    /*
    std::pair<int,int> frame_dims = vm.GetFrameDims();
    cv::VideoWriter output_video;
    if (!output_video.isOpened()) throw std::invalid_argument("VideoWriter: could not open file for writing");

    for (size_t frame_counter = 0; frame_counter < vm.GetCols(); frame_counter++) {
        double* frame_buffer = vm.GetData() + (frame_counter * vm.GetRows());
        cv::Mat cv_frame(frame_dims.second,frame_dims.first, CV_64F, frame_buffer);
        cv::Mat cv_frame_uchar;
        cv_frame.convertTo(cv_frame_uchar, CV_8UC1);
        output_video.write(cv_frame_uchar);
    }
    output_video.release();
    */
}
