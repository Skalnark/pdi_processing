#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "pdi.h"
#include "image.h"

using namespace std;

int main()
{
	string sFilename;
	cout << "File' path: " << endl;
	cin >> sFilename;

	const char* filename = sFilename.c_str();

	Image* image = new Image(filename);

	if(image == nullptr)
		return -1;
/*
	Red(("output/Red " + sFilename).c_str(), *image);

	Green(("output/Green " + sFilename).c_str(), *image);

	Blue(("output/Blue " + sFilename).c_str(), *image);

	RGB_to_YIQ_to_RGB_Again(*image);
*/
	NegativoRGB(*image);

	NegativoYIQ(*image);

/*	string bright;

	cout << "Bright factor: " << endl;
	cin >> bright;

	BrilhoAditivoYIQ(*image, atoi(bright.c_str()));

	BrilhoMultiplicativoYIQ(*image, atoi(bright.c_str()));

	BrilhoAditivoRGB(*image, atoi(bright.c_str()));

	BrilhoMultiplicativoRGB(*image, atoi(bright.c_str()));
	*/

	return 0;
}