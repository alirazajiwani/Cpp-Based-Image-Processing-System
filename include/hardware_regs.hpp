#pragma once
#include <cstdint>

// Hardware Control Registers - simulates FPGA register interface
struct ControlRegs {
    // Enable/Disable pipeline stages
    bool enableSmoothing;
    bool enableSharpening;
    bool enableSobel;
    
    // Kernel selection for convolution engine
    enum KernelType {
        KERNEL_SHARPEN = 0,
        KERNEL_EDGE_DETECT = 1,
        KERNEL_EMBOSS = 2,
        KERNEL_BLUR = 3
    };
    
    uint8_t kernelType;
    
    // Image dimensions (read-only status registers)
    uint16_t imageWidth;
    uint16_t imageHeight;
    
    // Pipeline status flags
    bool pipelineReady;
    bool processingComplete;
    
    // Constructor with defaults
    ControlRegs() 
        : enableSmoothing(true)
        , enableSharpening(true)
        , enableSobel(true)
        , kernelType(KERNEL_SHARPEN)
        , imageWidth(0)
        , imageHeight(0)
        , pipelineReady(false)
        , processingComplete(false)
    {}
};

// Kernel definitions for different filter types
namespace KernelBank {
    const int SHARPEN[3][3] = {
        { 0,-1, 0},
        {-1, 5,-1},
        { 0,-1, 0}
    };
    
    const int EDGE_DETECT[3][3] = {
        {-1,-1,-1},
        {-1, 8,-1},
        {-1,-1,-1}
    };
    
    const int EMBOSS[3][3] = {
        {-2,-1, 0},
        {-1, 1, 1},
        { 0, 1, 2}
    };
    
    const int BLUR[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
}