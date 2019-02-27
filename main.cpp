#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "pdi.h"

using namespace std;

int main()
{
	string sFilename;
	cout << "File' path: " << endl;
	cin >> sFilename;

	const char* filename = sFilename.c_str();

	BlackAndRed(filename);
	/*while(true){
		int option;
		cout << "Insira qual a operação: ";
		cin >> option;

		switch(option){
			case 1:
				//foo
				break;
			default:
				break;
		}
	}*/

	return 0;
}