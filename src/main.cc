#include <iostream>
#include "VideoReader.h"
#include "VideoWriter.h"
#include "VideoMat.h"
#include "SVD.h"
#include "LowRankMask.h"

int main() {
    std::string input_path = "../videos/forest.mp4";
    std::string output_path = "../videos/test2.mp4";

    VideoReader reader(input_path);
    VideoWriter writer(output_path);

    VideoMat vm;
    reader.ReadVideo(vm);

    /*
    VideoMat vm2;
    vm2.Resize(vm.GetCols(),vm.GetCols(),vm.GetFrameDims().first,vm.GetFrameDims().second);
    VideoMat vm3(vm);

    for (size_t i = 0; i < vm2.GetCols(); i++) {
        vm2(i,vm2.GetCols()-i) = 1;
    }
    //vm2.Randomize();
    vm.MMultFast(vm2,vm3);
    */

    int approx_order = 3;
    std::cout << "BEGIN RSVD\n";
    SVD svd(vm, approx_order);
    std::cout << "END RSVD\n";

    LowRankMask lrm(svd);
    lrm.Apply(vm);

    writer.WriteVideo(vm);
}
