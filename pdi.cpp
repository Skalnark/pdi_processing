#include "lodepng.h"
#include "image.h"
#include "yiq.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

void Save(const char* filename, Image source)
{
	unsigned error = lodepng::encode(filename, source.ByteList(), source.width, source.height);

	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void Red(const char* filename, Image source){
	
	for(int i = 0; i < source.pixel_count; i++){
		source.pixels[i].g = (unsigned)0;
		source.pixels[i].b = (unsigned)0;
	}

	Save(filename, source);
}

void Green(const char* filename, Image source){
	
	for(int i = 0; i < source.pixel_count; i++){
		source.pixels[i].b = (unsigned)0;
		source.pixels[i].r = (unsigned)0;
	}

	Save(filename, source);
}

void Blue(const char* filename, Image source){
	
	for(int i = 0; i < source.pixel_count; i++){
		source.pixels[i].r = (unsigned)0;
		source.pixels[i].g = (unsigned)0;
	}

	Save(filename, source);
}

vector<YIQ> RGB_to_YIQ(Image source)
{
	std::vector<YIQ> output;

	for (int i = 0; i < source.pixel_count; i++)
	{
		float _y = (
			(0.299 * source.pixels[i].r) +
			(0.587 * source.pixels[i].g) +
			(0.114 * source.pixels[i].b)
			);

		float _i = (
			(0.596 * source.pixels[i].r) -
			(0.274 * source.pixels[i].g) -
			(0.322 * source.pixels[i].b)
			);

		float _q = (
			(0.211 * source.pixels[i].r) -
			(0.523 * source.pixels[i].g) +
			(0.312 * source.pixels[i].b)
			);

		YIQ* p = new YIQ(_y, _i, _q);

		output.push_back(*p);
	}

	return output;
}

std::vector<Pixel> YIQ_to_RGB(std::vector<YIQ> source)
{
	std::vector<Pixel> output;

	for (int k = 0; k < source.size(); k++)
	{
		unsigned char r, g, b;

		float R = source[k].y + (0.956 * source[k].i) + (0.621 * source[k].q);
		float G = source[k].y - (0.272 * source[k].i) - (0.647 * source[k].q);
		float B = source[k].y - (1.106 * source[k].i) + (1.703 * source[k].q);

		if(R <= 0) 
			r = 0;
		else if (R > 255)
			r = 255;
		else 
			r = R;

		if(G <= 0) 
			g = 0;
		else if (G > 255) 
			g = 255;
		else 
			g = G;

		if(B <= 0) 
			b = 0;
		else if (B > 255) 
			b = 255;
		else 
			b = B;

		Pixel* p = new Pixel(r, g, b);

		output.push_back(*p);
	}

	return output;
}

void RGB_to_YIQ_to_RGB_Again(Image source)
{
	vector<YIQ> yiq = RGB_to_YIQ(source);

	vector<Pixel> pixels = YIQ_to_RGB(yiq);

	Image* image2 = new Image(pixels, source.width, source.height);

	string s = "output/rgb_to_yiq_to_rgb_file.png";
	const char* filename2 = s.c_str();

	Save(filename2, *image2);
}

void Negativo(Image source)
{
	for (int k = 0; k < source.pixel_count; k++)
	{
		source.pixels[k].r = abs(source.pixels[k].r - 255);
		source.pixels[k].g = abs(source.pixels[k].g - 255);
		source.pixels[k].b = abs(source.pixels[k].b - 255);
	}

	string s = "output/negativo.png";
	const char* filename = s.c_str();

	Save(filename, source);
}

void BrilhoAditivo(Image source, int bright)
{
	vector<YIQ> yiq = RGB_to_YIQ(source);

	for (int k = 0; k < yiq.size(); k++)
	{
		yiq[k].y += bright;
	}

	Image* image = new Image(YIQ_to_RGB(yiq), source.width, source.height);

	string s = "output/brilho_aditivo.png";
	const char* filename = s.c_str();

	Save(filename, *image);
}

void BrilhoMultiplicativo(Image source, int bright)
{
	vector<YIQ> yiq = RGB_to_YIQ(source);

	for (int k = 0; k < yiq.size(); k++)
	{
		yiq[k].y *= bright;
	}

	Image* image = new Image(YIQ_to_RGB(yiq), source.width, source.height);

	string s = "output/brilho_multiplicativo.png";
	const char* filename = s.c_str();

	Save(filename, *image);
}