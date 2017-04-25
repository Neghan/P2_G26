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

void GuardarKey(std::string &l) {
	int primerElemento;
	primerElemento = l.find_first_of(" ");
	l = l.substr(0, primerElemento);
}

void MostrarKeys(char lineas[]) {
	std::vector<std::string>elementosFinales(0);

	std::ifstream fentrada("elements.dat");

	while (!fentrada.eof()) {
		fentrada.getline(lineas, 250);
		if (strlen(lineas) != 0) {
			std::string primerElemento = lineas;
			GuardarKey(primerElemento);
			elementosFinales.push_back(primerElemento);
		}
	}
	fentrada.close();

	for (int i = 0; i < elementosFinales.size(); ++i) {
	std::cout << elementosFinales[i] << std::endl;
	}
}




void main() {
	char lineas[250];
	MostrarKeys(lineas);

	printHelp();
	std::cin.clear(); // clears all error state flags
					  // extracts characters from the input buffer and discards them
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	auto url= "https://en.wikipedia.org/wiki/fire";
	
	ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);

}