cmake_minimum_required(VERSION 3.10)
project(detsrv-plugins LANGUAGES C CXX)

set(LIBRARY_OUTPUT_PATH    ${PROJECT_SOURCE_DIR}/build)

set(PluginName "minic")

add_subdirectory(${PluginName})

add_executable(run main.cpp)
target_include_directories(run PRIVATE "include/")
target_link_libraries(run ${PluginName})