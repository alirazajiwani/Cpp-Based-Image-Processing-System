#include "writer.hpp"
#include <fstream>
#ifdef DEBUG
#include <iostream>
#endif

void OutputWriter::saveGray(const std::string& filename, GrayPixel* buf, int w, int h)
{
    #ifdef DEBUG
    std::cout << "Writing grayscale image to " << filename << ": (" << w << "x" << h << ")\n";
    #endif

    std::ofstream file(filename, std::ios::binary);

    // PGM Header (P5 format)
    file << "P5\n" << w << " " << h << "\n255\n";

    file.write(reinterpret_cast<char*>(buf), w * h);
    file.close();
}

