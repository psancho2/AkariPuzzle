#include <iomanip>

#include "tablero.h"
#include "colors.h"
#include "celda.h"



int tablero::getNumFilas(const tTablero& tab) {
    return tab.nFils;
}
int tablero::getNumCols(const tTablero& tab) {
    return tab.nCols;
}

celda::tCelda tablero::celdaEnPos(const tTablero& tablero, int x, int y) {
   return tablero.datos[x][y];
}
void tablero::ponCeldaEnPos(tTablero& tablero, int x, int y, const tCelda& c) {
    tablero.datos[x][y] = c;
}

void iniciaTablero(tablero::tTablero& tab, int f, int c) {
    tab.nFils = f;
    tab.nCols = c;
}

ifstream& tablero::operator>>(ifstream& archivo, tTablero& tab) {
	using namespace celda;
	int col, fil;
	archivo >> fil >> col;
	iniciaTablero(tab, fil, col);
	celda::tCelda celda;
	for (int i = 0; i < fil; i++) {
		for (int j = 0; j < col; j++) {
			char c;
			archivo >> c;
			celda = celda::charToCelda(c);
			ponCeldaEnPos(tab, i, j, celda);
		}
	}
	return archivo;
}

const int HUECOS = 2; // huecos a dejar en el formato de las celdas.

void mostrarCoutSeparadorMat(const tablero::tTablero& tab, ostream& out) {
	out << "\t -+";
	for (int col = 0; col < tablero::getNumCols(tab); ++col) {
		out << setw(HUECOS + 2) << setfill('-') << '+' << setfill(' ');
	}
	out << endl;
}

void ponColorCelda(const celda::tCelda& celda, ostream& out) {
	char c = ' ';
	if (celda::esBombilla(celda)) out << BG_YELLOW << BLACK;
	else {
		if (celda::esParedRestringida(celda)) out << BG_BLACK << WHITE;
		else if (celda::estaApagada(celda)) out << BG_WHITE << WHITE;
		else if (celda::estaIluminada(celda)) out << BG_YELLOW << WHITE;
	}
}


ostream& tablero::operator<<(ostream& out, const tTablero& tab) {
	using namespace celda;
	out << "\t  |";

	for (int col = 0; col < getNumCols(tab); ++col) {
		out << LBLUE << setw(HUECOS) << col << " " << RESET << '|';
	}
	cout << endl;

	// mostrar separador
	mostrarCoutSeparadorMat(tab,out);
	// mostrar tablero

	for (int f = 0; f < getNumFilas(tab); f++) {
		out << "\t" << LBLUE << setw(HUECOS) << f << RESET << '|';
		for (int c = 0; c < getNumCols(tab); c++) {
			ponColorCelda(celdaEnPos(tab, f, c), out);
			out << setw(HUECOS) << setfill(' ') <<
				celda::celdaToChar(tablero::celdaEnPos(tab, f, c)) << " " << RESET;
			out << '|';
		}
		out << endl;

		mostrarCoutSeparadorMat(tab,out);
	}

	out << endl;
	return out;
}


