#ifndef IMAGE_H
#define IMAGE_H
	
#include <iostream>
#include <vector>
#include "lodepng.h"
#include "pixel.h"

class Image{

public:
	unsigned width;
	unsigned height;
	unsigned pixel_count;
	std::vector<Pixel> pixels;

	Image();

	Image(const char* filename);
	
	Image(std::vector<Pixel> pixels, unsigned width, unsigned height);

	std::vector<unsigned char> ByteList();
};

#endif