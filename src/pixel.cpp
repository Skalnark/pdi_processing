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

Pixel Pixel::ToGray()
{
	float total = ((float)r + (float)g + (float)b)/3.0;

	if(total > 255.0)
	{
		total = 255.0;
	}
	else if(total < 0)
	{
		total = 0;
	}

	unsigned value = (unsigned char)total;

	return Pixel(value, value, value, (unsigned char)255); 
}