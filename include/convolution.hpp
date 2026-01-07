#pragma once
#include "framebuffer.hpp"
#include "filter.hpp"

class ConvolutionEngine : public Filter {
public:
    int kernel[3][3];

    void setKernel(int k[3][3]);
    FrameBuffer apply(GrayPixel* input, int width, int height);
    
    // Note: apply() already matches Filter interface signature
    // but returns FrameBuffer. For polymorphic use:
    GrayPixel* applyPoly(GrayPixel* in, int w, int h) {
        FrameBuffer result = apply(in, w, h);
        return result.data;
    }
};