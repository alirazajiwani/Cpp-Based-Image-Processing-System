#include "pipeline.hpp"
#include <iostream>

int main() {
    Pipeline p;
    
    // Demo 1: Standard pipeline with all stages enabled
    std::cout << "=== Demo 1: Full Pipeline ===\n";
    p.run("Images/SourceImage.ppm", "Images/OutputImage_Full.pgm");
    
    // Demo 2: Configure hardware registers to bypass smoothing
    std::cout << "\n=== Demo 2: No Smoothing ===\n";
    ControlRegs regs;
    regs.enableSmoothing = false;
    regs.enableSharpening = true;
    regs.enableSobel = true;
    regs.kernelType = ControlRegs::KERNEL_EDGE_DETECT;
    p.setControlRegs(regs);
    p.run("Images/SourceImage.ppm", "Images/OutputImage_NoSmooth.pgm");
    
    // Demo 3: Only edge detection (Sobel kernel)
    std::cout << "\n=== Demo 3: Edge Detect Only ===\n";
    regs.enableSmoothing = false;
    regs.enableSharpening = false;
    regs.enableSobel = true;
    p.setControlRegs(regs);
    p.run("Images/SourceImage.ppm", "Images/OutputImage_EdgesOnly.pgm");
    
    // Demo 4: Emboss effect
    std::cout << "\n=== Demo 4: Emboss Effect ===\n";
    regs.enableSmoothing = true;
    regs.enableSharpening = true;
    regs.enableSobel = false;
    regs.kernelType = ControlRegs::KERNEL_EMBOSS;
    p.setControlRegs(regs);
    p.run("Images/SourceImage.ppm", "Images/OutputImage_Emboss.pgm");
    
    // Demo 5: Polymorphic filter execution
    std::cout << "\n=== Demo 5: Polymorphic Filters ===\n";
    p.runWithFilters("Images/SourceImage.ppm", "Images/OutputImage_Poly.pgm");
    
    std::cout << "\nAll demos complete!\n";
    return 0;
}