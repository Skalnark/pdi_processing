#include "image.h"

using namespace std;

Image::Image(const char* filename)
{
	unsigned w, h;
	vector<unsigned char> img;

	unsigned error = lodepng::decode(img, w, h, filename);

	if(error)
	{
		cout << "decode error " << error << ": " << lodepng_error_text(error) << endl;
		std::cout << "erro ao abrir o arquivo" << endl;
		this->pixel_count = 0;
	} 
	else
	{

		std::vector<Pixel> pixels;

		for(int i = 0; i < img.size(); i+=4)
		{
			Pixel* p = new Pixel(img[i], img[i+1], img[i+2], img[i+3]);
			pixels.push_back(*p);
		}

		this->pixel_count = pixels.size();
		this->width = w;
		this->height = h;
		this->pixels = pixels;
	}
};

Image::Image(std::vector<Pixel> pixels, unsigned width, unsigned height)
{

	this->pixel_count = pixels.size();
	this->width = width;
	this->height = height;
	this->pixels = pixels;

}

vector<unsigned char> Image::ByteList()
{
	vector<unsigned char> bytes;

	for(int i = 0; i < this->pixel_count; i++){
		bytes.push_back(pixels[i].r);
		bytes.push_back(pixels[i].g);
		bytes.push_back(pixels[i].b);
		bytes.push_back(pixels[i].a);
	}

	return bytes;
}

