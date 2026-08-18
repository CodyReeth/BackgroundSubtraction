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

    VideoMat vm;

    if (!reader.ReadVideo(vm)) {
        std::cout << "Failed to read video\n";
        return 0;
    }

    //----------------------------------

    VideoMat vm3({{1,2,-1,3,0},{8,12,-5,-5,-18},{23,1,0,-1,3},{2,9,14,8,5},{3,-4,-28,15,2}});
    VideoMat q(5,5);
    VideoMat r(5,5);
    SVD svd2(vm3,1);
    svd2.QR(vm3, q, r);
    VideoMat vm2(5,5);
    q.MMult(r, vm2);
    for (size_t i = 0; i < vm3.GetCols(); i++) {
        for (size_t j = 0; j < vm3.GetCols(); j++) {
            std::cout << vm3(j,i) << " ";
        }
            std::cout << std::endl;
    }
    std::cout << std::endl;
    for (size_t i = 0; i < vm3.GetCols(); i++) {
        for (size_t j = 0; j < vm3.GetCols(); j++) {
            std::cout << vm2(j,i) << " ";
        }
            std::cout << std::endl;
    }
    //----------------------------------
    int approx_order = 5;
    SVD svd(vm, approx_order);

    LowRankMask lrm(svd);
    lrm.Apply(vm);

    writer.Write(vm);
}
