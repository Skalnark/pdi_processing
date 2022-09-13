#include "lodepng.h"
#include "image.hpp"
#include "yiq.hpp"
#include "pdi.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

void Save(const char* filename, Image source)
{
	unsigned error = lodepng::encode(filename, source.ByteList(), source.width, source.height);

	if(error)
	{
		std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
		std::cout << "erro ao salvar o arquivo" << endl;
	}
}

void Red(const char* filename, Image source)
{
	
	for(unsigned int i = 0; i < source.pixel_count; i++){
		source.pixels[i].g = (unsigned)0;
		source.pixels[i].b = (unsigned)0;
	}

	Save(filename, source);
}

void Green(const char* filename, Image source){
	
	for(unsigned int i = 0; i < source.pixel_count; i++){
		source.pixels[i].b = (unsigned)0;
		source.pixels[i].r = (unsigned)0;
	}

	Save(filename, source);
}

void Blue(const char* filename, Image source){
	
	for(unsigned int i = 0; i < source.pixel_count; i++){
		source.pixels[i].r = (unsigned)0;
		source.pixels[i].g = (unsigned)0;
	}

	Save(filename, source);
}

vector<YIQ> RGB_to_YIQ(Image source)
{
	std::vector<YIQ> output;

	for (unsigned int i = 0; i < source.pixel_count; i++)
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

	for (unsigned int k = 0; k < source.size(); k++)
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

void NegativoRGB(Image source)
{
	for (unsigned int k = 0; k < source.pixel_count; k++)
	{
		source.pixels[k].r = abs(source.pixels[k].r - 255);
		source.pixels[k].g = abs(source.pixels[k].g - 255);
		source.pixels[k].b = abs(source.pixels[k].b - 255);
	}

	string s = "output/negativoRGB.png";
	const char* filename = s.c_str();

	Save(filename, source);
}


//WIP
void NegativoYIQ(Image source)
{
	vector<YIQ> yiq = RGB_to_YIQ(source);

	for(unsigned int k = 0; k < source.pixel_count; k++)
	{
		yiq[k].y = abs(yiq[k].y - 255);
	}

	Image* image = new Image(YIQ_to_RGB(yiq), source.width, source.height);

	string s = "output/negativoY.png";
	const char* filename = s.c_str();

	Save(filename, *image);
}

void BrilhoAditivoYIQ(Image source, int bright)
{
	vector<YIQ> yiq = RGB_to_YIQ(source);

	for (unsigned int k = 0; k < yiq.size(); k++)
	{
		yiq[k].y += bright;
	}

	Image* image = new Image(YIQ_to_RGB(yiq), source.width, source.height);

	string s = "output/brilho_aditivoYIQ.png";
	const char* filename = s.c_str();

	Save(filename, *image);
}

void BrilhoMultiplicativoYIQ(Image source, int bright)
{
	vector<YIQ> yiq = RGB_to_YIQ(source);

	for (unsigned int k = 0; k < yiq.size(); k++)
	{
		yiq[k].y *= bright;
	}

	Image* image = new Image(YIQ_to_RGB(yiq), source.width, source.height);

	string s = "output/brilho_multiplicativoYIQ.png";
	const char* filename = s.c_str();

	Save(filename, *image);
}

void BrilhoAditivoRGB(Image source, int bright)
{
	for (unsigned int i = 0; i < source.pixel_count; i++)
	{
		if(source.pixels[i].r + bright > 255)
			source.pixels[i].r = 255;
		else if(source.pixels[i].r + bright < 0)
			source.pixels[i].r = 0;
		else
			source.pixels[i].r += bright;

		if(source.pixels[i].g + bright > 255)
			source.pixels[i].g = 255;
		else if(source.pixels[i].g + bright < 0)
			source.pixels[i].g = 0;
		else
			source.pixels[i].g += bright;

		if(source.pixels[i].b + bright > 255)
			source.pixels[i].b = 255;
		else if(source.pixels[i].b + bright < 0)
			source.pixels[i].b = 0;
		else
			source.pixels[i].b += bright;
	}

	string s = "output/brilho_aditivoRGB.png";
	const char* filename = s.c_str();

	Save(filename, source);
}


void BrilhoMultiplicativoRGB(Image source, int bright)
{
	for (unsigned int i = 0; i < source.pixel_count; i++)
	{
		if(source.pixels[i].r * bright > 255)
			source.pixels[i].r = 255;
		else if(source.pixels[i].r * bright < 0)
			source.pixels[i].r = 0;
		else
			source.pixels[i].r *= bright;

		if(source.pixels[i].g * bright > 255)
			source.pixels[i].g = 255;
		else if(source.pixels[i].g * bright < 0)
			source.pixels[i].g = 0;
		else
			source.pixels[i].g *= bright;

		if(source.pixels[i].b * bright > 255)
			source.pixels[i].b = 255;
		else if(source.pixels[i].b * bright < 0)
			source.pixels[i].b = 0;
		else
			source.pixels[i].b *= bright;
	}

	string s = "output/brilho_multiplicativoRGB.png";
	const char* filename = s.c_str();

	Save(filename, source);
}

void LimiarizacaoRGB(Image source, int limiar)
{
	for (unsigned int i = 0; i < source.pixel_count; i++)
	{
		float media = (source.pixels[i].r +source.pixels[i].g +source.pixels[i].b) / 3.0;
		if(media > limiar)
		{
			source.pixels[i].r = 255;
			source.pixels[i].g = 255;
			source.pixels[i].b = 255;
		}
		else
		{
			source.pixels[i].r = 0;
			source.pixels[i].g = 0;
			source.pixels[i].b = 0;
		}
	}

	string s = "output/Limiar_RGB.png";
	const char* filename = s.c_str();

	Save(filename, source);
}

void LimiarizacaoYIQ(Image source, int limiar)
{
	vector<YIQ> yiq = RGB_to_YIQ(source);

	for(unsigned int k = 0; k < source.pixel_count; k++)
	{
		if(yiq[k].y > limiar)
			yiq[k].y = 255;
		else
			yiq[k].y = 0;
	}

	Image* image = new Image(YIQ_to_RGB(yiq), source.width, source.height);

	string s = "output/Limiar_YIQ.png";
	const char* filename = s.c_str();

	Save(filename, *image);
}

Image Convolucao(Image source)
{
	int len = source.pixel_count;
	auto aux = source.pixels;

	for (unsigned int i = 0; i < source.pixel_count; i++)
	{
		source.pixels[i] = aux[len - (i + 1)];
	}

	return source;
}

	void FiltroDeMediaRGB(Image source, unsigned w, unsigned h, bool convol)
	{

		vector<vector<Pixel>> matrix = ToMatrix(source);
		std::vector<Pixel> output;
		int range = (w * h);
		
		if(convol)
		{
			source = Convolucao(source);
		}



		for (unsigned int i = 0; i < source.width; i++){
			for(unsigned int j = 0; j < source.height; j++)
			{

				float mediaR = 0;
				float mediaG = 0;
				float mediaB = 0;

				for(unsigned int m = (w/(-2)); m < w/2; m++)
				{
					for(unsigned int n = (h/(-2)); n < h/2; n++)
					{
						if( (i + m >= 0 && i + m < source.width) &&
							(j + n >= 0 && j + n < source.height))
						{

							mediaR += matrix[i + m][j + n].r;
							mediaG += matrix[i + m][j + n].g;
							mediaB += matrix[i + m][j + n].b;
						}
					}
				}

				Pixel* p = new Pixel(
					(unsigned)(mediaR/range), 
					(unsigned)(mediaG/range), 
					(unsigned)(mediaB/range));

				output.push_back(*p);
			}
		}
		string s;

		if(convol)
		{
			s = "output/MediaRGBconvol.png";
			source = Convolucao(source);
		}
		else
			s = "output/MediaRGBnormal.png";

		const char* filename = s.c_str();

		Image *image = new Image(output, source.width, source.height);

		Save(filename, *image);
	}


vector<vector<Pixel>> ToMatrix(Image source)
{
	vector<vector<Pixel>> output;

	for (unsigned int i = 0; i < source.width; i++)
	{
		vector<Pixel> aux;
		for (unsigned int j = 0; j < source.height; j++)
		{
			aux.push_back(source.pixels[i + j]);
		}

		output.push_back(aux);
	}

	return output;
}