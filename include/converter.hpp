#pragma once
#include "framebuffer.hpp"

class ColorConverter {
public:
    FrameBuffer rgbToGray(Pixel* rgbFrame, int width, int height);
};

