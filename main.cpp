#include "detsvr/IDetect.h"
#include "detsvr/detectionresult.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <opencv2/opencv.hpp>

int main(int argc, const char* argv[])
{
    const char* imgFile = argv[1];
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
    // const unsigned char* pData = (const unsigned char*)str.c_str();
    // std::vector<unsigned char> imgVec(pData, pData+str.length());

    // cv::Mat img = cv::imdecode(imgVec, cv::ImreadModes::IMREAD_UNCHANGED );

    // cv::imwrite("save.jpg", img);
    

    auto pDetector = detsvr::createInstance();
    // warmup
    for(int i = 0; i<5; ++i)
    {
        detsvr::DetectionResult result = pDetector->detect(str.c_str(), str.length());

        std::cout   << "{img_width: " << result.img_width 
                    << ", img_height: " << result.img_height
                    << ", pre_time: " << result.pre_time
                    << ", inf_time: " << result.inf_time
                    << ", list: " << result.list.size() << "}\n";
    }
    const size_t testRepeat = 10;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<testRepeat; ++i)
    {
        detsvr::DetectionResult result = pDetector->detect(str.c_str(), str.length());

        // std::cout   << "{img_width: " << result.img_width 
        //             << ", img_height: " << result.img_height
        //             << ", pre_time: " << result.pre_time
        //             << ", inf_time: " << result.inf_time
        //             << ", list: " << result.list.size() << "}\n";
    }
    auto end = std::chrono::high_resolution_clock::now();
    int total = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    std::cout << "total time: " << total << "; mean: " << total/testRepeat << std::endl;
    return 0;
}