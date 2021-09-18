#ifndef _DETSVR_DETECTION_MINIC_
#define _DETSVR_DETECTION_MINIC_

#include "detcore/detection.h"

namespace detsvr
{

class DetectionMinic final : public IDetect 
{
public:
    virtual ~DetectionMinic() override = default;

    DetectionResult detect(const char* data, size_t length) override; 
};


} // namespace detsvr

#endif