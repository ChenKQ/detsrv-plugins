#ifndef _DETSVR_DETECTION_MINIC_
#define _DETSVR_DETECTION_MINIC_

#include "detsvr/IDetect.h"
#include "detsvr/detectionresult.h"

namespace detsvr
{

class DetectionMinic final : public IDetect 
{
public:
    DetectionMinic();
    virtual ~DetectionMinic() override = default;

    DetectionResult detect(const char* data, size_t length) override; 

private:
    const int deviceID = 0;
    // const double nmsThresh = 0.4;
    // const double confidenceThresh = 0.5;
    // const int batchSize = 1;
    const std::string engineName = "trtyolov5.trt";
};


} // namespace detsvr

#endif