#pragma once

#include "tablero.h"




// Comprueba que el juego est� completamente iluminado y 
// cumple las restricciones num�ricas de las paredes.
bool estaTerminado(tablero::tTablero const& juego);
// salir?
bool esPosQuit(int x, int y);
// ejecuta un paso del juego
void ejecutarPos(tablero::tTablero& tab, int x, int y);

// para la parte nueva
