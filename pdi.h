#ifndef DECODE_H
#define DECODE_H
#include "lodepng.h"
#include "image.h"
#include "pixel.h"
#include "yiq.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void Save(const char* filename, Image source);

void Red(const char* filename, Image source);

void Green(const char* filename, Image source);

void Blue(const char* filename, Image source);

void RGB_to_YIQ_to_RGB_Again(Image source);

vector<YIQ>  RGB_to_YIQ(Image source);

vector<Pixel> YIQ_to_RGB(std::vector<YIQ> source);

void Negativo(Image source);

void BrilhoAditivo(Image source, int bright);

void BrilhoMultiplicativo(Image source, int bright);

#endif