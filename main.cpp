#include <fstream>
#include <iostream>
#include <string>
#include "reglasJuego.h"
#include "colors.h"
#include <iomanip>

//version modificada por PST para pruebas
const int HUECOS = 2; // huecos a dejar en el formato de las celdas.


using namespace std;

/*
const char CHAR_PARED_NO_RESTRINGIDA = 'X';        // Pared sin número
const char CHAR_NO_ILUMINADA = '.';                // LIBRE con 0 bombillas iluminandola
const char CHAR_BOMBILLA = '*';
// PAREDES CON RESTRICCION EN EL NUMERO DE BOMBILLAS
const char CHAR_PARED_RESTRINGIDA0 = '0';
const char CHAR_PARED_RESTRINGIDA1 = '1';
const char CHAR_PARED_RESTRINGIDA2 = '2';
const char CHAR_PARED_RESTRINGIDA3 = '3';
const char CHAR_PARED_RESTRINGIDA4 = '4';
*/

void pedirPosConsola(int& x, int& y);
void cargaTablero(tablero::tTablero& tablero);
void leeBombillas(ifstream& archivo, tablero::tTablero& tablero);


int main() {
	using namespace tablero;
	tablero::tTablero tab = TABLERO_1;
	ifstream archivo;
	cargaTablero(tab);
	//-------------------------------
	cout << tab;
	int x = 0;
	int y = 0;
	int nIt = 0;
	while (!estaTerminado(tab) && !esPosQuit(x, y)) {
		pedirPosConsola(x, y);
		ejecutarPos(tab, x, y);
		nIt++;
		cout << tab;
	}
	cout << endl;
	if (esPosQuit(x, y))
		cout << ROSE << nIt - 1 << " intentos! " << BLUE << "Adios, adios!" << RESET << endl;
	else cout << BLUE << "Enhorabuena conseguido en " << nIt << " pasos." << RESET << endl;
	return 0;
}

/* se pide la posicion por consola */
void pedirPosConsola(int& x, int & y) {
	bool fallo = true;
	do {
		cout << "Pos: ";
		cin >> x >> y;
		fallo = cin.fail();
		if (fallo) {
			cout << ROSE << "ERROR: Posición desconocida (Dos enteros separados por blanco)." << RESET << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n'); // string basura; getLine(cin, basura);
		}
	} while (fallo);
}



void cargaTablero(tablero::tTablero& tab) {
	cout << "Dame el nombre del fichero que contiene el tablero: ";
	string nombre;
	getline(cin, nombre);
	ifstream archivo;
	archivo.open(nombre);
	if (archivo.is_open()) {
		archivo >> tab;
		leeBombillas(archivo, tab);
	}	
	archivo.close();
}

void leeBombillas(ifstream& archivo, tablero::tTablero& tab) {
	int nBombillas;
	archivo >> nBombillas;
	int f, c;
	for (int i = 0; i < nBombillas; i++) {
		archivo >> f >> c;
		ejecutarPos(tab, f, c);
	}
}

