#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include<vector>
#include<unordered_map>



void printHelp() {
	std::cout << "-----------" << std::endl;
	std::cout << "ALCHEMY BOY" << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "- Enter two numbers of your elements list to combine them." << std::endl;
	std::cout << "- Enter the word 'add' and the number of an element to add a new instance of that element." << std::endl;
	std::cout << "- Enter 'add basics' to add new instances of the 4 basic elements" << std::endl;
	std::cout << "- Enter the word 'delete' and the number of an element to erase it from your list" << std::endl;
	std::cout << "- Enter the word 'info' and the number of an element to get information about it in the explorer." << std::endl;
	std::cout << "- Enter the word 'sort' to sort by alphabetical order the elements in the list" << std::endl;
	std::cout << "- Enter the word 'clean' to delete all the instances of repeated elements." << std::endl;
	std::cout << "- Enter the word 'help' to show this tutorial." << std::endl;
}

std::unordered_map<std::pair<std::string, std::string>, std::string>elementosFinales;

/* DEFINIR FUNCION HASH -------------------------------------------------------------------------------------/!\ */

std::pair<std::string, std::string>GuardarKey(std::string l) {
	std::pair<std::string, std::string>elementos;
	int pos1 = l.find('+');
	
	elementos.first = l.substr(l.find('='), pos1);
	elementos.second = l.substr(pos1, l.find('\n'));

	return elementos;
}

std::string GuardarValue(std::string l) {
	int primerElemento;
	primerElemento = l.find_first_of(" ");
	l = l.substr(0, primerElemento);
	return l;
}


void leerArchivo(char lineas[]) {
	
	std::ifstream fentrada("elements.dat");

	while (!fentrada.eof()) {
		fentrada.getline(lineas, 250);
		if (strlen(lineas) != 0) {
			elementosFinales[GuardarKey(lineas)] = GuardarValue(lineas);
		}
	}
	fentrada.close();
}




void main() {
	char lineas[250];
	leerArchivo(lineas);

	printHelp();
	std::cin.clear(); // clears all error state flags
					  // extracts characters from the input buffer and discards them
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	auto url= "https://en.wikipedia.org/wiki/fire";
	
	ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);

}