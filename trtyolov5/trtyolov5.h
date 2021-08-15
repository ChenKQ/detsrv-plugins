#ifndef _DETSVR_DETECTION_MINIC_
#define _DETSVR_DETECTION_MINIC_

#include "detsvr/IDetect.h"
#include "detsvr/detectionresult.h"
#include "logging.h"
#include "yololayer.h"
#include "NvInfer.h"
#include "NvInferRuntime.h"
#include "common.hpp"
#include <opencv2/opencv.hpp>
#include <tuple>

namespace detsvr
{

class DetectionYoloV5 final : public IDetect 
{
public:
    DetectionYoloV5();
    virtual ~DetectionYoloV5();

    DetectionResult detect(const char* data, size_t length) override; 

private:
    void preprocessImg(cv::Mat& img);
    void doInference(float* input, float* output);

private:
    cudaStream_t stream;
    void* buffers[2];
    cv::Mat decodedImage;
    cv::Mat resizedImage;
    cv::Mat preprocessedImage;
    std::unique_ptr<float[]> data {nullptr};
    std::unique_ptr<float[]> prob {nullptr};

    IRuntime* runtime = nullptr;
    ICudaEngine* engine = nullptr;
    IExecutionContext* context = nullptr;

    const int deviceID = 0;
    const double nmsThresh = 0.4;
    const double confidenceThresh = 0.5;
    
    const std::string engineName = "trtyolov5.engine";
    const int batchSize = 1;
    const int inputWidth = Yolo::INPUT_W;
    const int inputHeight = Yolo::INPUT_H;
    const int maxOutputBBoxCount = Yolo::MAX_OUTPUT_BBOX_COUNT;
    const int classNumber = Yolo::CLASS_NUM;
    const int outputSize = Yolo::MAX_OUTPUT_BBOX_COUNT * sizeof(Yolo::Detection) / sizeof(float) + 1;

    const char* inputBlobName = "data";
    const char* outputBlobName = "prob";

    Logger gLogger;
};


} // namespace detsvr

#endif