#pragma once
#include "pixel.hpp"

struct FrameBuffer {
    GrayPixel* data;
    int width;
    int height;	    
};

