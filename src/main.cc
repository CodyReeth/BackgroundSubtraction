#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[]) {

    std::cout << "OpenCV Version: " << CV_VERSION << std::endl;
    cv::VideoCapture cap("../videos/IMG_7857.MOV");
    std::cout << "CAP SIZE: " << cap.get(cv::CAP_PROP_FRAME_COUNT) << std::endl;
 
    bool printed_frame_stats = false;

     while (true) {

        cv::Mat frame;
        if (!cap.read(frame)) break;

        if (!printed_frame_stats) {
            std::cout << "Frame size: (" << frame.rows << ", " << frame.cols << ")\n";
            printed_frame_stats = true;
        }
        cv::imshow("Video Frame", frame);    
 
        char key = cv::waitKey(1);
        if (key == 'q') {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;

    //return 0;
}
