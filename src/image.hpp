#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include "lodepng.hpp"
#include "pixel.hpp"

class Image
{
public:
	std::vector<Pixel> pixels;
	std::string fileName;

	Image();
	Image(const char *fileName);
	Image(Image* image, std::vector<Pixel> pixels);

	std::vector<unsigned char> ByteList();

	unsigned int Width();
	unsigned int Height();
	unsigned int PixelCount();

private:
	unsigned int _width;
	unsigned int _height;
	unsigned int _pixel_count;
};

#endif