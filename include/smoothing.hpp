#pragma once
#include "framebuffer.hpp"
#include "filter.hpp"

class SmoothingFilter : public Filter {
public:
    FrameBuffer applyAverage3x3(GrayPixel* grayFrame, int width, int height);
    
    // Override base Filter interface - returns FrameBuffer to match base class
    FrameBuffer apply(GrayPixel* in, int w, int h) override {
        return applyAverage3x3(in, w, h);
    }
};