#include "smoothing.hpp"

#ifdef DEBUG
#include <iostream>
#endif

FrameBuffer SmoothingFilter::applyAverage3x3(GrayPixel* in, int w, int h)
{
    GrayPixel* out = new GrayPixel[w * h];

    #ifdef DEBUG
    std::cout << "Applying 3x3 smoothing filter: (" << w << "x" << h << ")\n";
    #endif

    // Ignore border pixels for simplicity
    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w - 1; x++) {

            int sum = 0;
            sum += in[(y-1)*w + (x-1)];
            sum += in[(y-1)*w + (x)];
            sum += in[(y-1)*w + (x+1)];

            sum += in[(y)*w + (x-1)];
            sum += in[(y)*w + (x)];
            sum += in[(y)*w + (x+1)];

            sum += in[(y+1)*w + (x-1)];
            sum += in[(y+1)*w + (x)];
            sum += in[(y+1)*w + (x+1)];

            out[y*w + x] = static_cast<uint8_t>(sum / 9);
        }
    }
    FrameBuffer result;
    result.data = out;
    result.width = w;
    result.height = h;

    return result;
}

