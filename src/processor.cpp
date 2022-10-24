#include "lodepng.hpp"
#include "image.hpp"
#include "yiq.hpp"
#include "processor.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

Processor::Processor(Image *source)
{
	this->source = source;
}

void Processor::Save(std::string suffix, Image *output)
{
	std::cout << "Saving ";
	std::string fileName = (output->fileName.insert(output->fileName.find_last_of('.'), suffix));

	if (fileName.find('/') == std::string::npos)
	{
		fileName = "output/" + fileName;
	}
	std::cout << fileName << std::endl;

	auto error = lodepng::encode(fileName.c_str(), output->ByteList(), output->Width(), output->Height());

	if (error)
	{
		std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		std::cout << "error saving file" << std::endl;
	}
}

void Processor::Red()
{
	Image *output = new Image(*source);
	for (unsigned int i = 0; i < source->PixelCount(); i++)
	{
		output->pixels[i].g = (unsigned)0;
		output->pixels[i].b = (unsigned)0;
	}

	Processor::Save("_red", output);
}

void Processor::Green()
{

	Image *output = new Image(*source);

	for (unsigned int i = 0; i < output->PixelCount(); i++)
	{
		output->pixels[i].b = (unsigned)0;
		output->pixels[i].r = (unsigned)0;
	}

	Save("_green", output);
}

void Processor::Blue()
{

	Image *output = new Image(*source);

	for (unsigned int i = 0; i < output->PixelCount(); i++)
	{
		output->pixels[i].r = (unsigned)0;
		output->pixels[i].g = (unsigned)0;
	}

	Save("_blue", output);
}

std::vector<YIQ> Processor::RGB_to_YIQ()
{
	std::vector<YIQ> output;

	for (unsigned int i = 0; i < source->PixelCount(); i++)
	{
		float _y = ((0.299 * source->pixels[i].r) +
					(0.587 * source->pixels[i].g) +
					(0.114 * source->pixels[i].b));

		float _i = ((0.596 * source->pixels[i].r) -
					(0.274 * source->pixels[i].g) -
					(0.322 * source->pixels[i].b));

		float _q = ((0.211 * source->pixels[i].r) -
					(0.523 * source->pixels[i].g) +
					(0.312 * source->pixels[i].b));

		YIQ *p = new YIQ(_y, _i, _q);

		output.push_back(*p);
	}

	return output;
}

std::vector<Pixel> Processor::YIQ_to_RGB(std::vector<YIQ> vPixels)
{
	std::vector<Pixel> output;

	for (unsigned int k = 0; k < vPixels.size(); k++)
	{
		unsigned char r, g, b;

		float R = vPixels[k].y + (0.956 * vPixels[k].i) + (0.621 * vPixels[k].q);
		float G = vPixels[k].y - (0.272 * vPixels[k].i) - (0.647 * vPixels[k].q);
		float B = vPixels[k].y - (1.106 * vPixels[k].i) + (1.703 * vPixels[k].q);

		if (R <= 0)
			r = 0;
		else if (R > 255)
			r = 255;
		else
			r = R;

		if (G <= 0)
			g = 0;
		else if (G > 255)
			g = 255;
		else
			g = G;

		if (B <= 0)
			b = 0;
		else if (B > 255)
			b = 255;
		else
			b = B;

		Pixel *p = new Pixel(r, g, b);

		output.push_back(*p);
	}

	return output;
}

void Processor::RGB_to_YIQ_to_RGB_Again()
{
	std::vector<YIQ> yiq = RGB_to_YIQ();

	std::vector<Pixel> pixels = YIQ_to_RGB(yiq);

	Image *output = new Image(*source);

	Save("_rgb_yiq_test", output);
}

void Processor::NegativoRGB()
{
	Image *output = new Image(*source);

	for (unsigned int k = 0; k < output->PixelCount(); k++)
	{
		output->pixels[k].r = abs(output->pixels[k].r - 255);
		output->pixels[k].g = abs(output->pixels[k].g - 255);
		output->pixels[k].b = abs(output->pixels[k].b - 255);
	}

	Save("_negativo_RGB", output);
}

// WIP
void Processor::NegativoYIQ()
{
	std::vector<YIQ> yiq = RGB_to_YIQ();

	for (unsigned int k = 0; k < yiq.size(); k++)
	{
		yiq[k].y = abs(yiq[k].y - 255);
	}

	Image *output = new Image(source, YIQ_to_RGB(yiq));
	Save("_negativo_Y", output);
}

void Processor::BrilhoAditivoYIQ(int bright)
{
	std::vector<YIQ> yiq = RGB_to_YIQ();

	for (unsigned int k = 0; k < yiq.size(); k++)
	{
		yiq[k].y += bright;
	}

	Image *output = new Image(source, YIQ_to_RGB(yiq));

	Save("_brilho_add_YIQ", output);
}

void Processor::BrilhoMultiplicativoYIQ(int bright)
{
	std::vector<YIQ> yiq = RGB_to_YIQ();

	for (unsigned int k = 0; k < yiq.size(); k++)
	{
		yiq[k].y *= bright;
	}

	Image *output = new Image(source, YIQ_to_RGB(yiq));

	Save("_brilho_mult_YIQ", output);
}

void Processor::BrilhoAditivoRGB(int bright)
{
	Image *output = new Image(*source);
	for (unsigned int i = 0; i < output->PixelCount(); i++)
	{
		if (output->pixels[i].r + bright > 255)
			output->pixels[i].r = 255;
		else if (output->pixels[i].r + bright < 0)
			output->pixels[i].r = 0;
		else
			output->pixels[i].r += bright;

		if (output->pixels[i].g + bright > 255)
			output->pixels[i].g = 255;
		else if (output->pixels[i].g + bright < 0)
			output->pixels[i].g = 0;
		else
			output->pixels[i].g += bright;

		if (output->pixels[i].b + bright > 255)
			output->pixels[i].b = 255;
		else if (output->pixels[i].b + bright < 0)
			output->pixels[i].b = 0;
		else
			output->pixels[i].b += bright;
	}

	Save("_brilho_add_rgb", output);
}

void Processor::BrilhoMultiplicativoRGB(int bright)
{
	Image *output = new Image(*source);

	for (unsigned int i = 0; i < output->PixelCount(); i++)
	{
		if (output->pixels[i].r * bright > 255)
			output->pixels[i].r = 255;
		else if (output->pixels[i].r * bright < 0)
			output->pixels[i].r = 0;
		else
			output->pixels[i].r *= bright;

		if (output->pixels[i].g * bright > 255)
			output->pixels[i].g = 255;
		else if (output->pixels[i].g * bright < 0)
			output->pixels[i].g = 0;
		else
			output->pixels[i].g *= bright;

		if (output->pixels[i].b * bright > 255)
			output->pixels[i].b = 255;
		else if (output->pixels[i].b * bright < 0)
			output->pixels[i].b = 0;
		else
			output->pixels[i].b *= bright;
	}

	Save("_brilho_mult_RGB", output);
}

void Processor::LimiarizacaoRGB(int limiar)
{

	Image *output = new Image(*source);

	for (unsigned int i = 0; i < output->PixelCount(); i++)
	{
		float media = (output->pixels[i].r + output->pixels[i].g + output->pixels[i].b) / 3.0;
		if (media > limiar)
		{
			output->pixels[i].r = 255;
			output->pixels[i].g = 255;
			output->pixels[i].b = 255;
		}
		else
		{
			output->pixels[i].r = 0;
			output->pixels[i].g = 0;
			output->pixels[i].b = 0;
		}
	}

	Save("_limiar_RGB", output);
}

void Processor::LimiarizacaoYIQ(int limiar)
{
	std::vector<YIQ> yiq = RGB_to_YIQ();

	for (unsigned int k = 0; k < source->PixelCount(); k++)
	{
		if (yiq[k].y > limiar)
			yiq[k].y = 255;
		else
			yiq[k].y = 0;
	}

	Image *output = new Image(source, YIQ_to_RGB(yiq));

	Save("_limiarizacao_YIQ", output);
}

std::vector<std::vector<Pixel>> Processor::ToMatrix()
{
	std::vector<std::vector<Pixel>> output;
	int count = 0;

	for (unsigned int i = 0; i < source->Height(); ++i)
	{
		std::vector<Pixel> aux;
		for (unsigned int j = 0; j < source->Width(); ++j)
		{
			aux.push_back(source->pixels[i + count]);
			count++;
		}
		output.push_back(aux);
		count--;
		// std::cout << (int)output[1][0].r << std::endl;
	}

	return output;
}

Pixel Processor::MedianaRGB(std::vector<std::vector<Pixel>> frame)
{

	std::vector<unsigned char> auxR;
	std::vector<unsigned char> auxG;
	std::vector<unsigned char> auxB;

	for (long unsigned int i = 0; i < frame.size(); ++i)
	{
		for (long unsigned int j = 0; j < frame[i].size(); ++j)
		{
			auxR.push_back(frame[i][j].r);
			auxG.push_back(frame[i][j].g);
			auxB.push_back(frame[i][j].b);
		}
	}

	sort(auxR.begin(), auxR.end());
	sort(auxG.begin(), auxG.end());
	sort(auxB.begin(), auxB.end());

	int pivot = (auxR.size() / 2) + 1;

	return Pixel(auxR[pivot], auxG[pivot], auxB[pivot]);
}

Pixel Processor::MedianaGray(std::vector<std::vector<Pixel>> frame)
{

	std::vector<unsigned int> aux;

	for (long unsigned int i = 0; i < frame.size(); ++i)
	{
		for (long unsigned int j = 0; j < frame[i].size(); ++j)
		{
			aux.push_back(frame[i][j].ToGray().r);
		}
	}

	std::sort(aux.begin(), aux.end());

	int pivot = (aux.size() / 2);

	return Pixel(aux[pivot], aux[pivot], aux[pivot]);
}

std::vector<std::vector<Pixel>> Processor::MakeFrame(int width, int height, int pVertical, int pHorizontal, std::vector<std::vector<Pixel>> matrix)
{
	std::vector<std::vector<Pixel>> output;

	for (int i = pVertical - (height / 2); i < pVertical + (height / 2); ++i)
	{
		std::vector<Pixel> row;
		for (int j = pHorizontal - (width / 2); j < pHorizontal + (width / 2); ++j)
		{
			if (i < 0 || j < 0 || i > (int)matrix.size() - 1 || j > (int)matrix[i].size() - 1)
			{
				row.push_back(Pixel(0, 0, 0));
			}
			else
			{
				row.push_back(matrix[i][j]);
			}
		}
		output.push_back(row);
	}

	return output;
}

void Processor::FiltroMedianaRGB(unsigned int w, unsigned int h)
{
	if (w > source->Width() || h > source->Height() || w % 2 == 0 || h % 2 == 0)
	{
		throw std::invalid_argument("width and height must be valid odd numbers");
	}

	std::vector<Pixel> newImage;
	auto matrix = ToMatrix();

	for (unsigned int i = 0; i < source->Height(); ++i)
	{
		for (unsigned int j = 0; j < source->Width(); ++j)
		{
			auto frame = MakeFrame(w, h, i, j, matrix);

			newImage.push_back(MedianaRGB(frame));
		}
	}

	Image output = Image(newImage, source->Width(), source->Height(), source->fileName);

	Save("_mediana_rgb", &output);
}

void Processor::FiltroMedianaGray(unsigned int w, unsigned int h)
{
	if (w > source->Width() || h > source->Height() || w % 2 == 0 || h % 2 == 0)
	{
		throw std::invalid_argument("width and height must be valid odd numbers");
	}

	std::vector<Pixel> newImage;
	auto matrix = ToMatrix();

	for (unsigned int i = 0; i < source->Height(); ++i)
	{
		for (unsigned int j = 0; j < source->Width(); ++j)
		{
			auto frame = MakeFrame(w, h, i, j, matrix);

			newImage.push_back(MedianaGray(frame));
		}
	}

	Image output = Image(source, newImage);

	Save("_mediana_gray", &output);
}
