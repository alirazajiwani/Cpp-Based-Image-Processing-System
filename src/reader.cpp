#include "reader.hpp"
#include <fstream>
#include <iostream>

Pixel* FrameReader::readPPM(const std::string& filename, int& width, int& height)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << "\n";
        return nullptr;
    }

    // Read PPM header (P6 format)
    std::string format;
    file >> format;
    if (format != "P6") {
        std::cerr << "Error: Unsupported PPM format (use P6)\n";
        return nullptr;
    }

    // Read image size
    file >> width >> height;
    int maxValue;
    file >> maxValue;
    file.ignore(1); // Skip one whitespace

    #ifdef DEBUG
    std::cout << "Reading PPM: (" << width << "x" << height << ")\n";
    #endif


    // Allocate memory
    Pixel* buffer = new Pixel[width * height];

    // Read RGB data
    file.read(reinterpret_cast<char*>(buffer), width * height * 3);

    file.close();
    return buffer;
}

