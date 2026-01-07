#pragma once
#include "pixel.hpp"

class Filter {
public:
    virtual FrameBuffer apply(GrayPixel* in, int w, int h) = 0;
    virtual ~Filter() {}
};

