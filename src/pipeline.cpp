#include "pipeline.hpp"
#include "reader.hpp"
#include "converter.hpp"
#include "smoothing.hpp"
#include "convolution.hpp"
#include "sobel.hpp"
#include "writer.hpp"
#include "filter.hpp"

#ifdef DEBUG
#include <iostream>
#endif

void Pipeline::run(const std::string& input, const std::string& output)
{
    regs.pipelineReady = false;
    regs.processingComplete = false;
    
    #ifdef DEBUG
    std::cout << "Starting image processing pipeline...\n";
    std::cout << "Input: " << input << "\n";
    std::cout << "Output: " << output << "\n";
    std::cout << "Control Register State:\n";
    std::cout << "  Smoothing: " << (regs.enableSmoothing ? "ON" : "OFF") << "\n";
    std::cout << "  Sharpening: " << (regs.enableSharpening ? "ON" : "OFF") << "\n";
    std::cout << "  Sobel: " << (regs.enableSobel ? "ON" : "OFF") << "\n";
    std::cout << "  Kernel Type: " << (int)regs.kernelType << "\n";
    #endif

    FrameReader reader;
    ColorConverter converter;
    SmoothingFilter smooth;
    ConvolutionEngine conv;
    SobelEdgeDetector sobel;
    OutputWriter writer;

    int w, h;

    Pixel* rgb = reader.readPPM(input, w, h);
    
    // Update status registers
    regs.imageWidth = w;
    regs.imageHeight = h;
    regs.pipelineReady = true;
    
    FrameBuffer grayBuf = converter.rgbToGray(rgb, w, h);
    FrameBuffer currentBuf = grayBuf;
    
    // Stage 1: Smoothing (conditional based on register)
    FrameBuffer smoothedBuf;
    if (regs.enableSmoothing) {
        smoothedBuf = smooth.applyAverage3x3(currentBuf.data, w, h);
        currentBuf = smoothedBuf;
    } else {
        #ifdef DEBUG
        std::cout << "Smoothing stage BYPASSED by control register\n";
        #endif
    }

    // Stage 2: Sharpening/Convolution (conditional based on register)
    FrameBuffer filteredBuf;
    if (regs.enableSharpening) {
        // Select kernel based on register
        int selectedKernel[3][3];
        
        switch(regs.kernelType) {
            case ControlRegs::KERNEL_SHARPEN:
                #ifdef DEBUG
                std::cout << "Using SHARPEN kernel\n";
                #endif
                for(int i = 0; i < 3; i++)
                    for(int j = 0; j < 3; j++)
                        selectedKernel[i][j] = KernelBank::SHARPEN[i][j];
                break;
                
            case ControlRegs::KERNEL_EDGE_DETECT:
                #ifdef DEBUG
                std::cout << "Using EDGE_DETECT kernel\n";
                #endif
                for(int i = 0; i < 3; i++)
                    for(int j = 0; j < 3; j++)
                        selectedKernel[i][j] = KernelBank::EDGE_DETECT[i][j];
                break;
                
            case ControlRegs::KERNEL_EMBOSS:
                #ifdef DEBUG
                std::cout << "Using EMBOSS kernel\n";
                #endif
                for(int i = 0; i < 3; i++)
                    for(int j = 0; j < 3; j++)
                        selectedKernel[i][j] = KernelBank::EMBOSS[i][j];
                break;
                
            case ControlRegs::KERNEL_BLUR:
                #ifdef DEBUG
                std::cout << "Using BLUR kernel\n";
                #endif
                for(int i = 0; i < 3; i++)
                    for(int j = 0; j < 3; j++)
                        selectedKernel[i][j] = KernelBank::BLUR[i][j];
                break;
        }

        conv.setKernel(selectedKernel);
        filteredBuf = conv.apply(currentBuf.data, w, h);
        currentBuf = filteredBuf;
    } else {
        #ifdef DEBUG
        std::cout << "Sharpening stage BYPASSED by control register\n";
        #endif
    }

    // Stage 3: Sobel Edge Detection (conditional based on register)
    FrameBuffer edgesBuf;
    if (regs.enableSobel) {
        edgesBuf = sobel.applySobel(currentBuf.data, w, h);
        currentBuf = edgesBuf;
    } else {
        #ifdef DEBUG
        std::cout << "Sobel stage BYPASSED by control register\n";
        #endif
    }

    writer.saveGray(output, currentBuf.data, w, h);

    #ifdef DEBUG
    std::cout << "Pipeline complete. Cleaning up memory...\n";
    #endif

    // Memory cleanup
    delete[] rgb;
    delete[] grayBuf.data;
    if (regs.enableSmoothing && smoothedBuf.data != nullptr)
        delete[] smoothedBuf.data;
    if (regs.enableSharpening && filteredBuf.data != nullptr)
        delete[] filteredBuf.data;
    if (regs.enableSobel && edgesBuf.data != nullptr)
        delete[] edgesBuf.data;

    regs.processingComplete = true;
    
    #ifdef DEBUG
    std::cout << "Done!\n";
    #endif
}

void Pipeline::runWithFilters(const std::string& input, const std::string& output)
{
    #ifdef DEBUG
    std::cout << "Starting POLYMORPHIC pipeline...\n";
    #endif

    FrameReader reader;
    ColorConverter converter;
    OutputWriter writer;

    int w, h;
    Pixel* rgb = reader.readPPM(input, w, h);
    FrameBuffer grayBuf = converter.rgbToGray(rgb, w, h);

    // Create filters polymorphically
    Filter* f1 = new SmoothingFilter();
    Filter* f2 = new SobelEdgeDetector();

    #ifdef DEBUG
    std::cout << "Applying Filter 1 (Smoothing)...\n";
    #endif
    FrameBuffer out1 = f1->apply(grayBuf.data, w, h);

    #ifdef DEBUG
    std::cout << "Applying Filter 2 (Sobel)...\n";
    #endif
    FrameBuffer out2 = f2->apply(out1.data, w, h);

    writer.saveGray(output, out2.data, w, h);

    // Cleanup
    delete[] rgb;
    delete[] grayBuf.data;
    delete[] out1.data;
    delete[] out2.data;
    delete f1;
    delete f2;

    #ifdef DEBUG
    std::cout << "Polymorphic pipeline complete!\n";
    #endif
}