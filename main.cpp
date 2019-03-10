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
	cout << "Arquivo: " << endl;
	cin >> sFilename;

	const char* filename = sFilename.c_str();

	Image* image = new Image(filename);

	if(image->pixel_count == 0)
		return -1;

	while(1)
	{
		string _option;
		string _bright;
		int option;
		int bright;

		printf( "\n"
				"1 - Separacao das bandas de cores\n"
			    "2 - Negativo\n"
			    "3 - Controle de brilho aditivo\n"
			    "4 - Controle de brilho multiplicativo\n"
			    "5 - Filtro Sobel\n" 
			    "6 - Filtro Media\n" 
			    "7 - Fltro Mediana\n" 
			    "8 - Limiarizacao\n" 
				"\n"
				"0 - Sair\n");

		cin >> option;

		switch(option)
		{
			case 1:
				Red(("output/Red " + sFilename).c_str(), *image);
				Green(("output/Green " + sFilename).c_str(), *image);
				Blue(("output/Blue " + sFilename).c_str(), *image);
				break;
			case 2:
				NegativoRGB(*image);
				NegativoYIQ(*image);
				break;
			case 3:
				cout << "brilho: " << endl;
				cin >> bright;

				BrilhoAditivoYIQ(*image, bright);
				BrilhoAditivoRGB(*image, bright);
				break;
			case 4:
				cout << "brilho: " << endl;
				cin >> bright;
				BrilhoMultiplicativoYIQ(*image, bright);
				BrilhoMultiplicativoRGB(*image, bright);
				break;
			case 0:
				return 0;
			default:
				break;
		}
	}

	return 0;
}