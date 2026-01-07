#include "convolution.hpp"
#include <algorithm>

#ifdef DEBUG
#include <iostream>
#endif

void ConvolutionEngine::setKernel(int k[3][3])
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            kernel[i][j] = k[i][j];
}

FrameBuffer ConvolutionEngine::apply(GrayPixel* in, int w, int h)
{
    GrayPixel* out = new GrayPixel[w * h];

    #ifdef DEBUG
    std::cout << "Kernel applied at (" << w << "," << h << ")\n";
    #endif

    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w - 1; x++) {

            int sum = 0;

            for (int ky = -1; ky <= 1; ky++) {
                for (int kx = -1; kx <= 1; kx++) {
                    int pixel = in[(y + ky) * w + (x + kx)];
                    sum += pixel * kernel[ky + 1][kx + 1];
                }
            }

            sum = std::clamp(sum, 0, 255);
            out[y*w + x] = static_cast<uint8_t>(sum);
        }
    }

    FrameBuffer result;
    result.data = out;
    result.width = w;
    result.height = h;
    
    return result;
}

