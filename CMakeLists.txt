cmake_minimum_required(VERSION 3.10)
project(detsrv-plugins LANGUAGES C CXX)

set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

# find_package(OpenCV)
# include_directories(${OpenCV_INCLUDE_DIRS})

link_directories(/usr/local/cuda/lib64)
link_directories(/usr/lib/aarch64-linux-gnu)

set(PluginName "uavship")

add_subdirectory(${PluginName})

add_executable(run main.cpp)
target_include_directories(run PRIVATE "include/")
target_link_libraries(run ${PluginName} 
# ${OpenCV_LIBS}
)

add_executable(plugintest plugintest.cpp
)
target_include_directories(plugintest PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(plugintest PRIVATE "dl")
set_property(TARGET plugintest PROPERTY CXX_STANDARD 17)