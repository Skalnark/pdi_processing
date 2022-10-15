#include "pixel.hpp"

Pixel::Pixel (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	this->r = red;
	this->g = green;
	this->b = blue;
	this->a = alpha;
};

Pixel::Pixel (unsigned char red, unsigned char green, unsigned char blue)
{
	this->r = red;
	this->g = green;
	this->b = blue;
	this->a = (unsigned char)255;
};

Pixel Pixel::Copy()
{
	return Pixel(r, g, b, a);
}