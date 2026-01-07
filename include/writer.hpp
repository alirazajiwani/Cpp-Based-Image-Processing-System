#pragma once
#include "pixel.hpp"
#include <string>

class OutputWriter {
public:
    void saveGray(const std::string& filename, GrayPixel* buffer, int width, int height);
};

