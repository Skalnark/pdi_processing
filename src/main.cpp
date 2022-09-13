#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "pdi.hpp"
#include "image.hpp"

using namespace std;

int main()
{
	
	string sFilename = "lena.png";

	//string sFilename;
	//cout << "Arquivo: " << endl;
	//cin >> sFilename;

	const char* filename = sFilename.c_str();

	Image* image = new Image(filename);

	if(image->pixel_count == 0)
		return -1;


	FiltroDeMediaRGB(*image, 3, 3, false);
/*
	while(1)
	{
		int option;
		int bright;
		int limiar;

		int m, n;

		printf( "\n"
				"1 - Separacao das bandas de cores\n"
			    "2 - Negativo\n"
			    "3 - Controle de brilho aditivo\n"
			    "4 - Controle de brilho multiplicativo\n"
			    "5 - Limiarizacao\n" 
			    "6 - Filtro Media\n" 
			    "7 - Fltro Mediana\n" 
			    "8 - Filtro Sobel\n" 
				"\n"
				"0 - Sair\n");

		cout << endl << "Opcao: ";

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
			case 6:
				cout << "Altura da mascara: ";
				cin >> m;
				cout << "Largura da  mascara: ";
				cin >> n;

				FiltroDeMediaRGB(*image, m, n, true);
				FiltroDeMediaRGB(*image, m, n, false);

				break;
			case 0:
				return 0;
			default:
				break;
		}
	}
	*/
	return 0;
}