#include "Input.h"
#include "Lectura.h"
#include "Print.h"

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
std::unordered_map<std::pair<std::string, std::string>, std::string>elementosFinales; //Guardaremos -> Key: {elemento,elemento} Value: {elemento resultante}.

//VECTOR
std::vector<std::string>elementos({"Air","Earth","Fire","Water"}); //En este vector se guardan los elementos que vaya creando el jugador.

//SET
std::set<std::string>combinaciones; //Guardaremos en este set combinaciones ya hechas.

//SCORE
int puntuacion = 0; //Puntuacion del jugador.
int puntuacionMaxima = 395; //Es el numero maximo de elementos que se pueden combinar, asi controlaremos que una vez la puntuacion maxima del jugador llegue a ser 395 se termine el juego.

//COMBINE
bool errorCombining = false; //Cuando sea true (una combinacion que no existe) imprimira por pantalla que la combinacion no ha resultado efecto.
bool successCombining = false;//Cuando sea true (una combinacion que existe) imprimira por pantalla que la combinacion ha resultado efecto y diga tambien que elemento es el que ha conseguido.

//GUARDAR VALUE
std::string GuardarValue(std::string l) {
	l = l.substr(0, l.find_first_of(" ")); //Ej:"1up = Life + Mushroom", guardamos "1up" (elemento resultante), sera el value de nuestro map.
	return l;
};

//GUARDAR KEY
std::pair<std::string, std::string>GuardarKey(std::string l) {

	std::pair<std::string, std::string>key;
	auto pos = l.find("+");

	key.first = l.substr(l.find("=") + 2, pos - 1); 
	key.first = key.first.substr(0, key.first.find("+") - 1);  //Ej:"1up = Life + Mushroom", guardamos "Life"(elemento), sera el primer elemento de la key de nuestro map.

	key.second  = l.substr(pos + 2, l.find("\n") - 1); //Ej:"1up = Life + Mushroom", guardamos "Mushroom"(elemento), sera el segundo elemento de la key de nuestro map.

	return key;
};

//LEE EL ARCHIVO
void leerArchivo(char lineas[]) {

	std::ifstream fentrada("elements.dat"); //Abrimos el archivo con las combinaciones de  elementos.
	
	if (!fentrada.is_open()) { //Si no se ha abiert el archivo, imprimiremos un mensaje reportandolo.
		std::cout << "Cannot read combination of elements from file elements.dat." << std::endl;
		std::cout << "Check that it's placed in the same directory as Alchemy.exe!" << std::endl;
		system("pause");
	}
		while (!fentrada.eof()) { //Mientras haya elementos en el archivo leemos lineas.
			fentrada.getline(lineas, 300);
			elementosFinales[GuardarKey(lineas)] = GuardarValue(lineas); //Guardamos en nuestro map como value los elementos que sumados generan otro y como key el elemento resultante de la suma de dos elementos.
		}
		fentrada.close(); //Cerramos el archivo.
};

//PRINTEAR ELEMENTOS 
void printElementos() {

	if (errorCombining == true) { std::cout << "Combination Failure, try again!" << std::endl; } //En caso de una combinacion fallida, lo imprime.
	if (successCombining == true) { std::cout << "New element found: " << elementos[elementos.size() - 1]<< std::endl; }//En caso de una combinacion existente, muestra que elemento encontrado es.

	std::cout << "Your current score: " << puntuacion << std::endl; //Muestra la puntuacion del jugador.
	std::cout << "You have these elements: " << std::endl; 

	for (int i = 0; i < elementos.size(); ++i) { //Muestra los elementos de los que dispone el jugador.
		std::cout << i + 1 << ":" << elementos[i] << std::endl;
	}
	std::cout << std::endl;
};

//PRINT HELP
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
	std::cout << std::endl;
};

//COMBINE ELEMENTS
void combineElements(int myIndex1, int myIndex2) {
	
	std::pair<std::string, std::string>aux1 = {elementos[myIndex1 - 1], elementos[myIndex2 - 1]}; //Declaramos un pair que contendra una posible combinacion.
	std::pair<std::string, std::string>aux2 = { elementos[myIndex2 - 1], elementos[myIndex1 - 1]};//Este pair es por si el jugador introduce lo que seria una key invertida. "Earth Air" en vez de "Air Earth".

	auto findKey1 = elementosFinales.find(aux1); //Miramos si el pair que se ha entrado coincide con la key de nuestro map que contiene los elementos.
	auto findKey2 = elementosFinales.find(aux2);

	if (findKey1 != elementosFinales.end()) { //Si coincide entra.

		std::string value1 = findKey1->second; //Guardamos el value de la key encontrada.

		if (myIndex1 > myIndex2) { //Esta condicion sirve para saber que elemento debe borrarse primero ya que al usar begin() y despues borrar un elemento se recalcula la posicion begin() y puede acabar eliminando un elemento no deaseado.
			elementos.erase(elementos.begin() + myIndex1 - 1);
			elementos.erase(elementos.begin() + myIndex2 - 1);
		}
		else {
			elementos.erase(elementos.begin() + myIndex2 - 1);
			elementos.erase(elementos.begin() + myIndex1 - 1);
		}
		successCombining = true;//Combinacion valida.
		elementos.push_back(value1);//El nuevo elemento se inserta al final del vector.

		auto it1 = combinaciones.find(value1);
		

		if (it1 == combinaciones.end()) {
			puntuacion++;//Aumentamos la puntuacion.
			combinaciones.insert(value1);
		}
	}
	
	else if (findKey2 != elementosFinales.end()) { //El mismo condicional que el anterior per trabajando sobre el vector que tiene la key invertida

		std::string value2 = findKey2->second;

		if (myIndex1 > myIndex2) {
			elementos.erase(elementos.begin() + myIndex1 - 1);
			elementos.erase(elementos.begin() + myIndex2 - 1);
		}
		else {
			elementos.erase(elementos.begin() + myIndex2 - 1);
			elementos.erase(elementos.begin() + myIndex1 - 1);
		}
		successCombining = true;
		elementos.push_back(value2);

		auto it2 = combinaciones.find(value2);
		

		if (it2 == combinaciones.end()) {
			puntuacion++;//Aumentamos la puntuacion.
			combinaciones.insert(value2);
		}
	}
	else{
		errorCombining = true;  //Combinacion no valida.
	}		
};

//ADD ELEMENT
void addElement(int myIndex) {
	if (myIndex <= elementos.size() && myIndex != 0) {//El input (parte numerica) del usuario debe estar en el rango de el vector y no debe ser 0.
		elementos.push_back(elementos[myIndex - 1]);//Se envia ese elemento a la ultima posicion del vector
	}
};

//ADD BASICS
void addBasics() {//Añade los elementos con los que empieza el jugador "Air", "Earth", "Fire", "Water".
	elementos.push_back("Air");
	elementos.push_back("Earth");
	elementos.push_back("Fire");
	elementos.push_back("Water");
};

//DELETE ELEMENT
void deleteElement(int myIndex) {
	if (myIndex <= elementos.size() && myIndex != 0) {
		elementos.erase(elementos.begin() + myIndex - 1);
	}
};

//INFO
void info(int myIndex) {
	std::string url = "https://en.wikipedia.org/wiki/";
	std::string direccion = elementos[myIndex - 1]; //Guardamos el elemento seleccionado.
	
	std::string  urlDef = url + direccion; //Juntamos los string para que sea una url valida.
	
	ShellExecuteA(nullptr, "open", urlDef.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
};

//SORT
void sortElements() {
	std::sort(elementos.begin(), elementos.end()); //Funcion sort para ordenar alfabeticamente los elementos de los que dispone el jugador.
};

//CLEAN
void cleanRepeatedElements() {

	std::set<std::string>mySet; //Set no puede tener un mismo valor varias veces.

	for (auto it = elementos.begin(); it != elementos.end(); ++it) {//Se llena el set con todos los elementos, los que estan repetidos los elimina.
		mySet.insert(*it);
	}

	elementos.erase(elementos.begin(), elementos.end()); //Se borran todos los elementos en vector.

	for (auto it = mySet.begin(); it != mySet.end(); ++it) {//Se rellena el vector con los elementos del set, que habra eliminado los elementos repetidos.
		elementos.push_back(*it);
	}
};

//LEE EL INPUT DEL JUGADOR
void leerInputJugador() {

	std::string aux;
	std::getline(std::cin,aux); //Tomamos el input del jugador.

	auto index1 = aux.substr(0, aux.find_first_of(" "));
	auto index2 = aux.substr(aux.find_first_of(" ") + 1, aux.find("\n")); //Ej: index1 = "add" , index2= "1". 
		

	//Segun el input del jugador, si se cumplen las condiciones, se llamaran a las funciones.

		//COMBINE ELEMENTS
		if (std::atoi(aux.c_str())!=0 && 
			std::atoi(index1.c_str()) <= elementos.size() &&
			std::atoi(index2.c_str()) <= elementos.size() &&
			std::atoi(index1.c_str()) != std::atoi(index2.c_str())) { //El input debe ser formado por dos numeros, ambos comprendidos entre el rango del vector y que sean distintos entre ellos.

			combineElements(std::atoi(index1.c_str()), std::atoi(index2.c_str())); 
		}
		
		//ADD ELEMENT
		if (index1 == "add" && std::atoi(index2.c_str()) != 0 && std::atoi(index2.c_str()) <= elementos.size()) {//El input debe estar formado por "add" y una parte numerica comprendida entre el rango del vector.
			addElement(std::atoi(index2.c_str()));
		}


		//DELETE ELEMENT
		if (index1 == "delete" && std::atoi(index2.c_str()) != 0 && std::atoi(index2.c_str()) <= elementos.size()) {//El input debe estar formado por "delete" y una parte numerica comprendida entre el rango del vector.
			deleteElement(std::atoi(index2.c_str()));
		}
		

		//INFO ABOUT ELEMENT
		if (index1 == "info" && std::atoi(index2.c_str()) != 0 && std::atoi(index2.c_str()) <= elementos.size()) {//El input debe estar formado por "info" y una parte numerica comprendida entre el rango del vector.
			info(std::atoi(index2.c_str()));
		}
		

		//ADDS BASICS
		if(aux == "add basics"){//El input debe estar formado por "add basics".
			addBasics();
		}

		//SORT
		if (aux == "sort") {//El input debe estar formado por "sort".
			sortElements();
		}

		//CLEAN
		if (aux == "clean") {//El input debe estar formado por "clean".
			cleanRepeatedElements();
		}

		//PRINTS HELP
		if (aux == "help") {//El input debe estar formado por "help".
			printHelp();
		}

		//Borra los inputs incorrectos.
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
};



void main() {
		char lineas[300];
		leerArchivo(lineas);//Llamamos a la funcion para leer el archivo con las combinaciones de los elementos.
		printHelp();//Printeamos la informacion al jugador de como jugar.
		printElementos();//Printeamos los elementos con los que empieza asi como su puntuacion.

	do {//mantendremos la lectura del input de usuario y el printeo de elementos y puntuacion mientras la puntuacion no sea la maxima;
		errorCombining = false;
		successCombining = false;
		leerInputJugador();
		system("cls");
		printElementos();
	} while (puntuacion != puntuacionMaxima);
};