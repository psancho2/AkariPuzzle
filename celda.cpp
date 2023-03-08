#include "celda.h"
#include "colors.h"




const char CHAR_PARED_NO_RESTRINGIDA = 'X';        // Pared sin número
const char CHAR_NO_ILUMINADA = '.';                // LIBRE con 0 bombillas iluminandola
const char CHAR_BOMBILLA = '*';
// PAREDES CON RESTRICCION EN EL NUMERO DE BOMBILLAS
const char CHAR_PARED_RESTRINGIDA0 = '0';
const char CHAR_PARED_RESTRINGIDA1 = '1';
const char CHAR_PARED_RESTRINGIDA2 = '2';
const char CHAR_PARED_RESTRINGIDA3 = '3';
const char CHAR_PARED_RESTRINGIDA4 = '4';

using namespace celda;



void crearCeldaParedNoRestringida(tCelda& celda) {
    celda.tipo = PARED;
    celda.numBombillas = -1;
};

void crearCeldaLibre(tCelda& celda) {
    celda.tipo = LIBRE;
    celda.numBombillas = 0;
}

void crearCeldaParedRestringida(tCelda& celda, int n) {
    celda.tipo = PARED;
    celda.numBombillas = n;
}

void crearCeldaBombilla(tCelda& celda) {
    celda.tipo = BOMBILLA;
    celda.numBombillas = 0;
}


tCelda celda::charToCelda(char c) {
    using namespace celda;
    tCelda celda{};
    switch (c) {
    case CHAR_PARED_NO_RESTRINGIDA: crearCeldaParedNoRestringida(celda); break;
    case CHAR_NO_ILUMINADA: crearCeldaLibre(celda); break;
    case CHAR_PARED_RESTRINGIDA0:  crearCeldaParedRestringida(celda, 0); break;
    case CHAR_PARED_RESTRINGIDA1:  crearCeldaParedRestringida(celda, 1);; break;
    case CHAR_PARED_RESTRINGIDA2:  crearCeldaParedRestringida(celda, 2);; break;
    case CHAR_PARED_RESTRINGIDA3:  crearCeldaParedRestringida(celda, 3);; break;
    case CHAR_PARED_RESTRINGIDA4:  crearCeldaParedRestringida(celda, 4);; break;
    case CHAR_BOMBILLA:            crearCeldaBombilla(celda); break;
    }
    return celda;
}


int numBombillas(const tCelda& c) {
    return c.numBombillas;
}


char charNumPared(const celda::tCelda& celda) {
    return '0' + numBombillas(celda);
}

char celda::celdaToChar(const celda::tCelda& celda) {
    char c = ' ';
    if (celda::esBombilla(celda)) {
        c = CHAR_BOMBILLA;
    }
    else {
        if (celda::esParedRestringida(celda)) {
            c = charNumPared(celda);
        }
    }
    return c;
}


/* funcion privada */
tTipo tipoCelda(tCelda const& c) {
    return c.tipo;
}

/* comprueba si es pared */
bool celda::esPared(const tCelda& c) {
    return c.tipo == PARED;
}



/* pared con restricciones */
bool celda::esParedRestringida(tCelda const& c) {
    return esPared(c) && c.numBombillas != -1;
}


/* casilla libre y no iluminada */
bool celda::estaApagada(const tCelda& c) {
    return c.tipo == LIBRE && c.numBombillas == 0;
}


/* comprueba si es celda con bombilla */
bool celda:: esBombilla(const tCelda& c) {
    return c.tipo == BOMBILLA;
}

/* devuelve el numero de bombillas que requiere la pared */
int celda::numParedRestringida(const tCelda& c) {
    int num = -1;
    if (esParedRestringida(c)) num = c.numBombillas;
    return num;
}


/* comprueba si una celda esta iluminada*/
bool celda::estaIluminada(const tCelda&  c) {
    return c.tipo == LIBRE && c.numBombillas > 0;
}


/* apaga la celda poniendola libre */
void celda::apagaCelda(tCelda& c) {
    if (c.tipo == BOMBILLA) {
        c.tipo = LIBRE;
        c.numBombillas = 0;
    }
    else {
        if (c.numBombillas == 1) {
            c.tipo = LIBRE;
            c.numBombillas = 0;
        }
        else c.numBombillas--;
    }
}


/* ilumina una celda (no pone bombilla) */
void celda::iluminaCelda(tCelda& c) {
    c.tipo = LIBRE;
    c.numBombillas++;
    //c = C_ILUMINADA;
}

/* coloca una bombilla en la celda*/
void celda::ponBombilla(tCelda& c) {
    c = C_BOMBILLA;
}




