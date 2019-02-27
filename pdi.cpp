#include "lodepng.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void EncodePNG(const char* filename, std::vector<unsigned char>& image, unsigned &width, unsigned &height)
{
	string name = "processed_";
	name += filename;
	const char* path = name.c_str();

	unsigned error = lodepng::encode(path, image, width, height);

	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void BlackAndRed(const char* filename)
{
	vector<unsigned char> image;
	
	unsigned width, height;

	// a partir daqui a imagem já pode ser manipulada
	unsigned error = lodepng::decode(image, width, height, filename);

	if(error)
		cout << "decode error " << error << ": " << lodepng_error_text(error) << endl;

	for (unsigned int i = 0; i < image.size(); i += 3)
	{
		image[i + 1] = (unsigned char)0;
		image[i + 2] = (unsigned char)0;
	}
	
	EncodePNG(filename, image, width, height);
}


