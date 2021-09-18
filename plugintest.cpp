#include "detcore/detection.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

extern "C"
{
#include <dlfcn.h>
}

int main(int argc, char* argv[])
{
    std::cout << "test of plugin ...\n";
    char soFile[] = "./libminic.so";

    // load 
    void* m_handle = dlopen(soFile, RTLD_NOW);
    if(0 == m_handle)
    {
        m_handle==nullptr;
        const char* error= dlerror(); // clear any existing error
        std::string errorInfo = std::string{"cannot open the file: "} + soFile + ":\n" + error;
        std::cerr << errorInfo << '\n';
        // logger.Log(errorInfo);
        throw std::runtime_error(errorInfo);
    }
    std:: cout << "loaded the file: " << soFile << '\n';
    // logger.Log(std::string{"loaded the file: "} + m_filename );
    dlerror(); // clear any existing error

    // loop up
    std::string methodName = "createInstance";
    if(m_handle == nullptr)
    {
        return -1;
    }

    void* ptr = nullptr;
    char symbol[] = "createInstance";
    ptr = dlsym(m_handle, symbol);

    if(0 == ptr)
    {
        const char* error = dlerror(); // clear any existing errors
        std::string errorInfo = std::string{"cannot find the method: "} + symbol + ":\n" + error;
        std::cerr << errorInfo << '\n';
        // logger.Log(errorInfo);
        throw std::runtime_error(errorInfo);
    }
    std::cout << std::string{"found method: "} + symbol + '\n';
    // logger.Log(std::string{"found method: "} + symbol);
    dlerror(); // clear any existing error

    // get detector
    using func = std::shared_ptr<detsvr::IDetect> (*) ();
    func f = reinterpret_cast<func>(ptr);

    std::shared_ptr<detsvr::IDetect> pDetector = f();
    
    const char* imgFile = argv[1];
    std::ifstream fstrm(imgFile, std::ios::binary);
    std::stringstream sstrm;
    sstrm << fstrm.rdbuf();
    std::string str = sstrm.str();
    detsvr::DetectionResult result = 
            pDetector->detect(str.c_str(), str.length());
    std::cout   << "{img_width: " << result.img_width 
                << ", img_height: " << result.img_height
                << ", pre_time: " << result.pre_time
                << ", inf_time: " << result.inf_time
                << ", list: " << result.list.size() << "}\n";    
    return 0;
}