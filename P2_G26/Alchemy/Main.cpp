#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <cstdlib>
#include<unordered_map>
#include<stdlib.h>

//HASH
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
//SCORE
int puntuacion = 0;

//GUARDA COMO VALUE EL ELEMENTO RESULTANTE DE LA SUMA DE DOS ELEMENTOS
std::string GuardarValue(std::string l) {
	l = l.substr(0, l.find_first_of(" "));
	return l;
};

//GUARDA EN UN PAIR LOS ELEMENTOS QUE SUMADOS GENERARAN EL VALUE, UN ELEMENTO EN FIRST Y OTRO EN SECOND
std::pair<std::string, std::string>GuardarKey(std::string l) {

	std::pair<std::string, std::string>key;
	auto pos = l.find("+");

	key.first = l.substr(l.find("=") + 2, pos - 1);
	key.first = key.first.substr(0, key.first.find("+") - 1);

	key.second  = l.substr(pos + 2, l.find("\n") - 1);

	return key;
};

//LEE EL ARCHIVO
void leerArchivo(char lineas[]) {

	std::ifstream fentrada("elements.dat");
	/*	if () {
		
		std::cout << "Cannot read combination of elements from file elements.dat." << std::endl;
		std::cout << "Check that it's placed in the same directory as Alchemy.exe!" << std::endl;
		system("pause");
	}*/


	while (!fentrada.eof()) {
		fentrada.getline(lineas, 300);
		elementosFinales[GuardarKey(lineas)] = GuardarValue(lineas);
	}
	fentrada.close();
};

//PRINTEAR ELEMENTOS 
void printElementos() {
	std::cout << "Your current score: " << puntuacion << std::endl;
	std::cout << "You have these elements: " << std::endl;
	for (int i = 0; i < elementos.size(); ++i)
	{
		std::cout << i + 1 << ":" << elementos[i] << std::endl;
	}
};

void printHelp() {
	//PRINT DE LA INFORMACION
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
};

//1 2 = OTRO ELEMENTO
void combineElements(int myIndex1, int myIndex2) {
	for (auto &it : elementosFinales) {
		if (elementos[myIndex1] == it.first.first && 
			elementos[myIndex2] == it.first.second) {
			elementos.push_back(it.second);
			puntuacion++;
			std::cout << "New element found: " << elementos[elementos.size()] << std::endl;
		}
		else {
			std::cout << "Combination failure, try again!" << std::endl;
		}
	}
};

//add 1 SE COPIA ESE ELEMENTO EN LA LISTA
void addElement(int index) {
	if (index <= elementos.size()) {
		elementos.push_back(elementos[index]);
	}
	else {
		std::cout << "You don't have this element!" << std::endl;
	}
};

//A�ADE LOS 4 PRIMEROS ELEMENTOS
//"Air", "Earth", "Fire", "Water"
void addBasics() {
	elementos.push_back("Air");
	elementos.push_back("Earth");
	elementos.push_back("Fire");
	elementos.push_back("Water");
};

//ELIMINA ELEMENTO SELECCIONADO
void deleteElement(int myIndex) {
	elementos.erase(elementos.begin() + myIndex);
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
	for (int i = 0; i < elementos.size() - 1; ++i) {
		for (int j = 1; j < elementos.size() - 1; ++j) {
			if (elementos[i] == elementos[j]) {
				elementos.erase(elementos.begin() + i);
			}
		}
	}
};

//LEE EL INPUT DEL JUGADOR
void leerInputJugador() {
	std::string aux;
	std::cin >> aux;

	auto index1 = aux.substr(0, aux.find_first_of(" ") - 1);
	auto index2 = index1.substr(0, index1.find("\n") - 1);

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
		
		if (aux == "add " + index2) {
			addElement(std::stoi(index2));
		}

		if (aux == "delete " + index2) {
			deleteElement(std::stoi(index1));
		}

		if (aux == "info " + index2) {
			info();
		}
	
		if (aux == index1 + " " + index2){
			combineElements(std::stoi(index1),std::stoi(index2));
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
	printElementos();
	leerInputJugador();
};