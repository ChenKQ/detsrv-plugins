option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
find_package(CUDA REQUIRED)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

cuda_add_library(myplugins SHARED yololayer.cu)
target_link_libraries(myplugins nvinfer cudart)

add_library(trtyolov5 SHARED trtyolov5.cpp cuda_utils.h)
target_include_directories(trtyolov5 PRIVATE "../include" "/usr/local/cuda/include" "${OpenCV_INCLUDE_DIRS}")
target_link_libraries(trtyolov5 PUBLIC nvinfer)
target_link_libraries(trtyolov5 PUBLIC cudart)
target_link_libraries(trtyolov5 PUBLIC ${OpenCV_LIBS})
target_link_libraries(trtyolov5 PUBLIC myplugins)
set_property(TARGET trtyolov5 PROPERTY CXX_STANDARD 17)