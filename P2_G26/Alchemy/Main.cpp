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

//MAP
std::unordered_map<std::pair<std::string, std::string>, std::string>elementosFinales;

//VECTOR
std::vector<std::string>elementos({"Air","Earth","Fire","Water"});


//GUARDA COMO VALUE EL ELEMENTO RESULTANTE DE LA SUMA DE DOS ELEMENTOS
std::string GuardarValue(std::string l) {
	l = l.substr(0, l.find_first_of(" "));
	return l;
};

//GUARDA EN UN PAIR LOS ELEMENTOS QUE SUMADOS GENERARAN EL VALUE, UN ELEMENTO EN FIRST Y OTRO EN SECOND
std::pair<std::string, std::string>GuardarKey(std::string l) {

	std::pair<std::string, std::string>keys;
	auto pos = l.find("+");

	keys.first = l.substr(l.find("=") + 2, pos - 1);
	keys.first = keys.first.substr(0, keys.first.find("+") - 1);

	keys.second  = l.substr(pos + 2, l.find("\n") - 1);

	return keys;
};

//LEE EL ARCHIVO
void leerArchivo(char lineas[]) {

	std::ifstream fentrada("elements.dat");

	while (!fentrada.eof()) {
		fentrada.getline(lineas, 300);
		elementosFinales[GuardarKey(lineas)] = GuardarValue(lineas);
	}
	fentrada.close();
};

//PRINTEAR ELEMENTOS 
void printElementos() {
	for (auto &i : elementosFinales)
	{
		std::cout << "Elemento 1: " << i.first.first << " " << "Elemento 2: " << i.first.second << " " << "Elemento resultante: " << i.second <<std::endl;
	}
};

void printHelp() {
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
	std::cout << "-Enter the word 'help' to show this tutorial." << std::endl;
};

//1 2 = OTRO ELEMENTO
void combineElements() {

};

//add 1 SE COPIA ESE ELEMENTO EN LA LISTA
void addElement() {
	
};

//AÑADE LOS 4 PRIMEROS ELEMENTOS
//"Air", "Earth", "Fire", "Water"
void addBasics() {
	elementos.push_back("Air");
	elementos.push_back("Earth");
	elementos.push_back("Fire");
	elementos.push_back("Water");
};

//ELIMINA ELEMENTO SELECCIONADO
void deleteElement(std::vector<std::string> myVector,int myIndex) {
	myVector.erase(myVector.begin() + myIndex);
};

//ABRE WIKIPEDIA SOBRE ELEMENTO SELECCIONADO
void info() {
	auto url = "https://en.wikipedia.org/wiki/" /*+ */;
	ShellExecuteA(nullptr, "open", url, nullptr, nullptr, SW_SHOWNORMAL);
};

//LOS ORDENA ALFABETICAMENTE
void sortElements() {
	std::sort(elementos.begin(), elementos.end());
};

//ELIMINA ELEMENTOS REPETIDOS
void cleanRepeatedElements() {
	for (auto it = 0; it < elementos.size() - 1; ++it) {
		for (auto it = 1; it < elementos.size() - 1; ++it) {
			if (elementos[0] == elementos[1]) {
				elementos.erase(elementos.begin() + it);
			}
		}
	}
};

//LEE EL INPUT DEL JUGADOR
void leerInputJugador() {
	std::string aux;
	std::cin >> aux;

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());

	bool canCombine = false;
		
		combineElements();

		for (int i = 0; i < elementos.size() - 1; ++i) {

			if (aux == "add " + elementos[i]) {
				addElement();
			}

			if (aux == "delete " + elementos[i]) {
				deleteElement(elementos,i);
			}

			if (aux == "info " + elementos[i]) {
				info();
			}

			if (aux.substr(0, aux.find_first_of(" ")) == elementos[i]) {
				canCombine = true;
			}
		}
		for (int i = 0; i < elementos.size() - 1; ++i) {
			if (canCombine && aux.substr(aux.find_first_of(" "), aux.find("\n") - 1) == elementos[i]) {
				combineElements();
			}
		}
		
		if(aux == "add basics"){
			addBasics();
		}

		if (aux == "sort") {
			sortElements();
		}

		if (aux == "clean") {
			cleanRepeatedElements();
		}

		if (aux == "help") {
			printHelp();
		}
};



void main() {

	char lineas[300];
	leerArchivo(lineas);

	printHelp();
	leerInputJugador();
	printElementos();

};