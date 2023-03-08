#pragma once

#include <fstream>
#include <iostream>
#include "celda.h"

using namespace std;

namespace tablero {
    const int MAX_FILS = 20;
    const int MAX_COLS = 20;
    

    using namespace celda;

    typedef tCelda tTableroDatos[MAX_FILS][MAX_COLS];

    typedef struct {
        int nFils, nCols;
        tTableroDatos datos;
    } tTablero;

    // Tablero inicial utilizado para depuración y otras opciones, tiene bombillas que se pegan entre si
    const tTablero TABLERO_0 = { 4, 4, { {C_PARED0,   C_PARED1,    C_LIBRE,     C_PARED2},
                                         {C_PARED1,   C_ILUMINADA, C_PARED,     C_LIBRE},
                                         {C_BOMBILLA, C_ILUMINADA, C_BOMBILLA,  C_ILUMINADA},
                                         {C_PARED2,   C_BOMBILLA,  C_ILUMINADA, C_PARED} } };
    // Tablero vacío para inicializar y evitar carga sin fichero.
    const tTablero TABLERO_1 = { 5, 5, { {C_LIBRE,  C_PARED,  C_LIBRE,   C_PARED3,  C_LIBRE},
                                         {C_PARED2, C_LIBRE,  C_LIBRE,   C_LIBRE,   C_LIBRE},
                                         {C_LIBRE,  C_LIBRE,  C_LIBRE,   C_LIBRE,   C_LIBRE},
                                         {C_LIBRE,  C_LIBRE,  C_PARED,   C_PARED1,  C_LIBRE},
                                         {C_LIBRE,  C_LIBRE,  C_LIBRE,   C_LIBRE,   C_LIBRE} } };


   

    
    // constructoras
    //void iniciaTablero(tTablero& tab, int f, int c);

    // getters

    int getNumFilas(const tTablero& tab);
    int getNumCols(const tTablero& tab);
    tCelda celdaEnPos(const tTablero& tablero, int x, int y);
    
    // setters
    void ponCeldaEnPos(tTablero& tablero, int x, int y, const tCelda& c);

    // lectura
    ifstream& operator>>(ifstream& archivo, tTablero& tab);

    // escritura
    ostream& operator<<(ostream& out, const tTablero& tab);
    
}