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
		int option;
		int bright;
		int limiar;

		printf( "\n"
				"1 - Separacao das bandas de cores\n"
			    "2 - Negativo\n"
			    "3 - Controle de brilho aditivo\n"
			    "4 - Controle de brilho multiplicativo\n"
			    "5 - Limiarizacao\n" 
			    "6 - Filtro Sobel\n" 
			    "7 - Filtro Media\n" 
			    "8 - Fltro Mediana\n" 
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
				cout << "brilho: ";
				cin >> bright;

				BrilhoAditivoYIQ(*image, bright);
				BrilhoAditivoRGB(*image, bright);
				break;
			case 4:
				cout << "brilho: ";
				cin >> bright;
				BrilhoMultiplicativoYIQ(*image, bright);
				BrilhoMultiplicativoRGB(*image, bright);
				break;
			case 5:
				cout << "Limiar: ";
				cin >> limiar;

				LimiarizacaoRGB(*image, limiar);
				LimiarizacaoYIQ(*image, limiar);
				break;
			case 0:
				return 0;
			default:
				break;
		}
	}

	return 0;
}