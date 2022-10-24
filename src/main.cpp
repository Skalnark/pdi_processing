#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "processor.hpp"
#include "image.hpp"

int main(int argc, char **argv)
{

	if (argc < 2)
	{
		std::cout << "missing arguments" << std::endl;
		std::cout << "./pdi filepath medianM medianN";
		return -1;
	}
	int m = 3;
	int n = 3;

	if (argc >= 4)
	{
		m = std::stoi(argv[2]);
		n = std::stoi(argv[3]);
	}

	std::string sFilename = argv[1];

	const char *filename = sFilename.c_str();

	Image *image = new Image(filename);

	if (image->PixelCount() == 0)
		return -1;

	Processor p = Processor(image);

	// p.Blue();
	// p.Red();
	// p.Green();
	p.NegativoRGB();
	p.NegativoYIQ();
	p.RGB_to_YIQ_to_RGB_Again();
	// p.BrilhoAditivoRGB(brightnessA);
	// p.BrilhoMultiplicativoRGB(brightnessM);
	// p.BrilhoAditivoYIQ(brightnessA);
	// p.BrilhoMultiplicativoYIQ(brightnessM);
	// p.LimiarizacaoRGB(limiar);
	// p.LimiarizacaoYIQ(limiar);
	// p.FiltroMedianaGray(3, 3);
	p.FiltroMedianaRGB(m, n);

	return 0;
}