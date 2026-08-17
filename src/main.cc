#include <iostream>
#include "VideoReader.h"
#include "VideoWriter.h"
#include "VideoMat.h"
#include "SVD.h"
#include "LowRankMask.h"

int main() {
    std::string input_path = "videos/videos.mov";
    std::string output_path = "videos/result.mov";

    VideoReader reader(input_path);
    VideoWriter writer(output_path);

    VideoMat vm(2,2);

    if (!reader.ReadVideo(vm)) {
        std::cout << "Failed to read video\n";
        return 0;
    }

    int approx_order = 5;
    SVD svd(vm, approx_order);

    LowRankMask lrm(svd);
    lrm.Apply(vm);

    writer.Write(vm);
}
