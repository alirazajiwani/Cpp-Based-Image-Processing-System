#pragma once
#include "pixel.hpp"
#include <string>

class FrameReader {
public:
    Pixel* readPPM(const std::string& filename, int& width, int& height);
};

