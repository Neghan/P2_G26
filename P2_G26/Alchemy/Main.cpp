#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include<unordered_map>

template<>
struct std::hash<std::pair<std::string, std::string>> {
	size_t operator()(const std::pair<std::string, std::string>&p)const
	{
		return((hash<std::string>()(p.first)
			^ (hash<std::string>()(p.second) << 1)) >> 1);
	}
};

std::unordered_map<std::pair<std::string, std::string>, std::string>elementosFinales;

//GUARDA EN UN PAIR LOS ELEMENTOS QUE SE SUMADOS GENERARAN EL VALUE UN ELEMENTO EN FIRST Y OTRO EN SECOND
std::pair<std::string, std::string>GuardarKey(std::string l) {

	std::string aux;
	std::pair<std::string, std::string>elementos;

	aux = l.substr(l.find("=") + 2, l.find("+"));
	aux = l.substr(l.find("+") + 2, l.find("\n") - 1);
	
	
	
	return elementos;
}

//GUARDA COMO VALUE EL ELEMENTO RESULTANTE DE LA SUMA DE DOS ELEMENTOS
std::string GuardarValue(std::string l) {
	l = l.substr(0, l.find_first_of(" "));
	return l;
}

//LEE EL ARCHIVO
void leerArchivo(char lineas[]) {
	
	std::ifstream fentrada("elements.dat");

	while (!fentrada.eof()) {
		fentrada.getline(lineas, 1280);
		elementosFinales[GuardarKey(lineas)] = GuardarValue(lineas);
		} 
	fentrada.close();
}

//PRINTEAR ELEMENTOS 
void printElementos() {
	for (auto i : elementosFinales)
	{
		std::cout << i.first.first << "/////" << i.first.second << "/////" << i.second <<std::endl;
	}
}



void main() {
	/*
	//PRINT DE LA INFORMACION
	std::cout << "-----------" << std::endl;
	std::cout << "ALCHEMY BOY" << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "Enter two numbers of your elements list to combine them." << std::endl;
	std::cout << "Enter the word 'add' and the number of an element to add a new instance of that element." << std::endl;
	std::cout << "Enter 'add basics' to add new instances of the 4 basic elements" << std::endl;
	std::cout << "Enter the word 'delete' and the number of an element to erase it from your list" << std::endl;
	std::cout << "Enter the word 'info' and the number of an element to get information about it in the explorer." << std::endl;
	std::cout << "Enter the word 'sort' to sort by alphabetical order the elements in the list" << std::endl;
	std::cout << "Enter the word 'clean' to delete all the instances of repeated elements." << std::endl;
	std::cout << "-Enter the word 'help' to show this tutorial." << std::endl;*/
	

	char lineas[1280];
	leerArchivo(lineas);

	printElementos();

	//std::cin.clear();
	//std::cin.ignore(std::cin.rdbuf()->in_avail());
	//auto url = "https://en.wikipedia.org/wiki/fire";
	//ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);
}