#pragma once
#include "framebuffer.hpp"
#include "filter.hpp"

class SobelEdgeDetector : public Filter {
public:
    FrameBuffer applySobel(GrayPixel* input, int width, int height);
    
    // Override base Filter interface - returns FrameBuffer to match base class
    FrameBuffer apply(GrayPixel* in, int w, int h) override {
        return applySobel(in, w, h);
    }
};