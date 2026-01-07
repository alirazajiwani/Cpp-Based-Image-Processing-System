#pragma once
#include <cstdint>

// RGB pixel (24 bits)
struct Pixel {
    uint8_t r, g, b;
};

// Grayscale pixel (8 bits)
typedef uint8_t GrayPixel;

