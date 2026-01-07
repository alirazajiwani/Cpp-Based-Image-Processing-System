#pragma once
#include "reader.hpp"
#include "converter.hpp"
#include "smoothing.hpp"
#include "convolution.hpp"
#include "sobel.hpp"
#include "writer.hpp"
#include "hardware_regs.hpp"

class Pipeline {
private:
    ControlRegs regs;  // Hardware control registers
    
public:
    // Configure pipeline via register writes
    void setControlRegs(const ControlRegs& newRegs) {
        regs = newRegs;
    }
    
    // Read current register state
    ControlRegs getControlRegs() const {
        return regs;
    }
    
    // Main processing function
    void run(const std::string& inputFile, const std::string& outputFile);
    
    // Polymorphic filter execution (TASK 4)
    void runWithFilters(const std::string& inputFile, const std::string& outputFile);
};