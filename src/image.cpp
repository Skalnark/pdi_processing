#include "image.hpp"
#include "lodepng.hpp"

using namespace std;

Image::Image(const char *fileName)
{
	unsigned w, h;
	vector<unsigned char> img;

	unsigned error = lodepng::decode(img, w, h, fileName);

	if (error)
	{
		cout << "decode error " << error << ": " << lodepng_error_text(error) << endl;
		std::cout << "error opening file" << endl;
		this->_pixel_count = 0;
	}
	else
	{
		std::vector<Pixel> pixels;

		for (unsigned int i = 0; i < img.size(); i += 4)
		{
			Pixel *p = new Pixel(img[i], img[i + 1], img[i + 2], img[i + 3]);
			pixels.push_back(*p);
		}

		this->_pixel_count = pixels.size();
		this->_width = w;
		this->_height = h;
		this->pixels = pixels;
		this->fileName = fileName;
	}
};

Image::Image(std::vector<Pixel> pixels, unsigned int width, unsigned int height, std::string fileName)
{
	this->pixels = pixels;
	this->_width = width;
	this->_height = height;
	this-> fileName = fileName;
	this->_pixel_count = width * height;
}

unsigned int Image::Width()
{
	return _width;
}

unsigned int Image::Height()
{
	return _height;
}

unsigned int Image::PixelCount()
{
	return _pixel_count;
}

Image::Image(Image *image, std::vector<Pixel> pixels)
{
	this->_pixel_count = pixels.size();
	this->_width = image->Width();
	this->_height = image->Height();
	this->fileName = image->fileName;
	this->pixels = pixels;
}

vector<unsigned char> Image::ByteList()
{
	vector<unsigned char> bytes;

	for (unsigned int i = 0; i < this->_pixel_count; i++)
	{
		bytes.push_back(pixels[i].r);
		bytes.push_back(pixels[i].g);
		bytes.push_back(pixels[i].b);
		bytes.push_back(pixels[i].a);
	}

	return bytes;
}
void Image::ToGrayScale()
{
	std::vector<Pixel> aux;

	for (unsigned int i = 0; i < _pixel_count; ++i)
	{
		aux.push_back(pixels[i].ToGray());
	}
	pixels = aux;
}
