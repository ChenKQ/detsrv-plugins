# <center> detsrv-plugin 目标检测插件开发 </center>

# 1. 插件开发要点：
- 插件必须编译为独立动态库
- 必须包含`include/IDetect.h`和`include/detectionresult.h`两个头文件，类必须public方式继承`IDetect`接口，实现`detect`方法；必须实现`createInstance()`函数


# 2. 基于tensorrtx开源项目的开发步骤（参考）
- 基于tensorrtx开源项目，得到动态库`libmyplugins.so`和tensorrt plain file：`xxx.engine`
- 拷贝uavship文件夹，并重命名为`“xxx”` 
- 修改`CMakeLists.txt`中的插件名称：
```
set(PluginName "xxx")
```
- 修改`uavship/CMakeLists.txt`文件中的动态库名称，将所有`uavship`修改为`"xxx"`
- 修改`uavship/CMakeLists.txt`文件中的TensorRTTOOT和EngineFile的值
```
set(TensorRTXROOT "/home/chenkq/workspace/tensorrtx/yolov5")
set(EngineFile ${TensorRTXROOT}/build/uavship.engine)
```
- 根据场景修改`xxx/xxx.h`和`xxx/xxx.cpp`文件内容
- 如有需要，修改`main.cpp`内容并进行动态库测试