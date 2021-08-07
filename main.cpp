#include "detsvr/IDetect.h"
#include "detsvr/detectionresult.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

int main(int argc, const char* argv[])
{
    const char* imgFile = "dump.jpg";
    std::ifstream fstrm(imgFile, std::ios::binary);
    if(!fstrm.is_open())
    {
        std::cout << "fail to open the file " << imgFile << std::endl;
        return -1;
    }

    std::cout << "loading the image content..." << std::endl;
    std::stringstream sstrm;
    sstrm << fstrm.rdbuf();
    std::string str = sstrm.str();

    auto pDetector = detsvr::createInstance();
    detsvr::DetectionResult result = pDetector->detect(str.c_str(), str.length());

    std::cout   << "{img_width: " << result.img_width 
                << ", img_height: " << result.img_height
                << ", pre_time: " << result.pre_time
                << ", inf_time: " << result.inf_time
                << ", list: " << result.list.size() << "}\n";
    return 0;
}