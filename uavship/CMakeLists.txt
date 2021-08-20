option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
find_package(CUDA REQUIRED)

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

set(TensorRTXROOT "/home/nvidia/workspace/tensorrtx/yolov5")
set(EngineFile ${TensorRTXROOT}/build/uavship.engine)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wl,-rpath=./")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-rpath=./")

add_library(uavship SHARED trtyolov5.cpp)
target_include_directories(uavship PUBLIC ${TensorRTXROOT})
target_include_directories(uavship PRIVATE "../include" "/usr/local/cuda/include" "${OpenCV_INCLUDE_DIRS}")
target_link_libraries(uavship PUBLIC nvinfer)
target_link_libraries(uavship PUBLIC cudart)
target_link_libraries(uavship PUBLIC ${OpenCV_LIBS})
target_link_libraries(uavship PUBLIC ${TensorRTXROOT}/build/libmyplugins.so)
set_property(TARGET uavship PROPERTY CXX_STANDARD 17)

file(COPY ${TensorRTXROOT}/build/libmyplugins.so 
     DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../build)
file(COPY ${EngineFile}
    DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../build)