#include <iostream>
#include "VideoReader.h"
#include "VideoWriter.h"
#include "VideoMat.h"
#include "SVD.h"
#include "LowRankMask.h"

int main() {
    std::string input_path = "../videos/forest2.mp4";
    std::string output_path = "../videos/test.mp4";

    VideoReader reader(input_path);
    VideoWriter writer(output_path);

    VideoMat vm;
    reader.ReadVideo(vm);

    int approx_order = 5;
    SVD svd(vm, approx_order);

    LowRankMask lrm(svd);
    lrm.Apply(vm);

    writer.Write(vm);
}
