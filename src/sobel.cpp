#include "sobel.hpp"
#include <cmath>
#include <algorithm>

#ifdef DEBUG
#include <iostream>
#endif

FrameBuffer SobelEdgeDetector::applySobel(GrayPixel* in, int w, int h)
{
    GrayPixel* out = new GrayPixel[w * h];

    #ifdef DEBUG
    std::cout << "Applying Sobel Edge Detection: (" << w << "x" << h << ")\n";
    #endif

    int sx[3][3] = {
        {-1,0,1},
        {-2,0,2},
        {-1,0,1}
    };

    int sy[3][3] = {
        {-1,-2,-1},
        { 0, 0, 0},
        { 1, 2, 1}
    };

    for (int y = 1; y < h-1; y++) {
        for (int x = 1; x < w-1; x++) {

            int gx = 0, gy = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {

                    int pixel = in[(y+ky)*w + (x+kx)];

                    gx += pixel * sx[ky+1][kx+1];
                    gy += pixel * sy[ky+1][kx+1];
                }
            }

            int mag = std::sqrt(gx*gx + gy*gy);
            mag = std::clamp(mag, 0, 255);

            out[y*w + x] = static_cast<uint8_t>(mag);
        }
    }

    FrameBuffer result;
    result.data = out;
    result.width = w;
    result.height = h;

    return result;
}

