#pragma once

#include <fstream>
#include <iostream>

using namespace std;

namespace celda {
	
	/*
	PARED: el numero de bombillas nos dice las bombillas que deben rodearla.
	BOMBILLA: indica que la celda tiene una bombilla
	LIBRE: si numBombillas es 0, la casilla está libre. En otro caso la casilla
	   está iluminada y no se puede colocar bombilla en ella
	*/

	typedef enum tTipo { PARED, BOMBILLA, LIBRE };
	typedef struct tCelda {
		tTipo tipo;
		int numBombillas;
	};


	
	const tCelda C_PARED = { tTipo::PARED, -1 };    // Pared sin número
	const tCelda C_PARED0 = { tTipo::PARED, 0 };
	const tCelda C_PARED1 = { tTipo::PARED, 1 };
	const tCelda C_PARED2 = { tTipo::PARED, 2 };
	const tCelda C_PARED3 = { tTipo::PARED, 3 };
	const tCelda C_PARED4 = { tTipo::PARED, 4 };
	const tCelda C_LIBRE = { tTipo::LIBRE, 0 };
	const tCelda C_ILUMINADA = { tTipo::LIBRE, 1 };
	const tCelda C_BOMBILLA = { tTipo::BOMBILLA, 0 };
	


	char celdaToChar(const tCelda& celda);
	tCelda charToCelda(char c);

	bool esPared(const tCelda& c);
	bool esParedRestringida(const tCelda& c);
	int numParedRestringida(const tCelda& c);
	

	bool esBombilla(const tCelda& c);
	

	bool estaApagada(const tCelda& c);
	bool estaIluminada(const tCelda& c);
	
	void apagaCelda(tCelda& c);
	void iluminaCelda(tCelda& c);

	void ponBombilla(tCelda& c);

	


}