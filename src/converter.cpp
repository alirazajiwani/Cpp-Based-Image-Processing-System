#include <iostream>
#include "converter.hpp"

FrameBuffer ColorConverter::rgbToGray(Pixel* rgbFrame, int width, int height){

	int i;
	int size = width*height;	

	GrayPixel* Gray = new GrayPixel[size];

	#ifdef DEBUG
	std::cout << "Converting RGB to Grayscale  (" << width << "," << height << ")\n";
	#endif

	for (i = 0 ; i < size ; i++){
		Pixel p = rgbFrame[i];
		
		// Grayscale Formula 
		Gray[i] = static_cast<uint8_t>(0.299*p.r + 0.587*p.g + 0.114*p.b);
	}	
	
	FrameBuffer result;
	result.data = Gray;
	result.width = width;
	result.height = height;
	
	return result;
}

