#ifndef PIXEL_H
#define PIXEL_H

class Pixel{
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	Pixel (unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
	Pixel (unsigned char red, unsigned char green, unsigned char blue);
	Pixel Copy();
};
#endif	