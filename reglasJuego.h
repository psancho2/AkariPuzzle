#pragma once

#include "tablero.h"




// Comprueba que el juego está completamente iluminado y 
// cumple las restricciones numéricas de las paredes.
bool estaTerminado(tablero::tTablero const& juego);
// salir?
bool esPosQuit(int x, int y);
// ejecuta un paso del juego
void ejecutarPos(tablero::tTablero& tab, int x, int y);

// para la parte nueva
