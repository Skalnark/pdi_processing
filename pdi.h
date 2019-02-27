#ifndef DECODE_H
#define DECODE_H
#include "lodepng.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void EncodePNG(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height);

void BlackAndWhite(const char* filename);

#endif