#include "trtyolov5.h"
#include "detsvr/IDetect.h"
#include <fstream>
#include <

namespace detsvr
{

DetectionMinic::DetectionMinic()
{
    

}

DetectionResult DetectionMinic::detect(const char* data, size_t length)
{
    std::fstream saveFile("dump.jpg", std::ios::binary | std::ios::out);
    if(saveFile.is_open())
    {
        saveFile.write(data, length);
        saveFile.close();
    }

    BBox obj1 {1, "uav", 0.98, 100,200,300,400};
    BBox obj2 {2, "pedestrian", 0.88, 400,800,200,250};
    return
        {"defense", "2021-03-14 15:32:54", 1280, 1920, 20, 16, {obj1, obj2}};
}

std::shared_ptr<IDetect> createInstance()
{
    IDetect* ptr = new DetectionMinic();
    return std::shared_ptr<IDetect>(ptr);
}

} // namespace detsvr

