#include "reglasJuego.h"
#include "celda.h"

// SALIR
const int PQX = -1;
const int PQY = 0;

// RESET
const int PRX = -1;
const int PRY = -1;

// direcciones
typedef enum tDir { NORTE, SUR, ESTE, OESTE };


/* funcion privada */
bool esPosReset(int x, int y) {
    return PRX == x && PRY == y;
}

/* funcion privada */
bool esPosValida(const tablero::tTablero& tablero, int x, int y) {
    return 0 <= x && x < tablero::getNumFilas(tablero) &&
        0 <= y && y < tablero::getNumCols(tablero);
}


/* funcion privada */
bool esPosApagada(const tablero::tTablero& tablero, int x, int y) {
    return esPosValida(tablero, x, y) &&
        celda::estaApagada(celdaEnPos(tablero, x, y));
}

/* funcion privada */
bool esPosParedNumerada(const tablero::tTablero& tablero, int x, int y) {
    return esPosValida(tablero, x, y) &&
        esParedRestringida(celdaEnPos(tablero, x, y));
}

/* funcion privada */
bool esPosBombilla(const tablero::tTablero& tab, int x, int y) {
    return esPosValida(tab, x, y) &&
        esBombilla(celdaEnPos(tab, x, y));
}

/* funcion privada */
bool iguales(int x, int y, int xx, int yy) {
    return (x == xx && y == yy);
}




/* funcion privada */
// Calcula cuantas bombillas vecinas tiene la posici�n pos	
int numBombillasVecinas(const tablero::tTablero& tab, int x, int y) {
    int nVec = 0;
    int xx, yy;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            xx = x + di;
            yy = y + dj;
            if (esPosBombilla(tab, xx, yy) && !iguales(x, y, xx, yy)) nVec++;
        }
    }
    return nVec;
}

/* funcion privada */
int numPared(const tablero::tTablero& tab, int x, int y) {
    return numParedRestringida(celdaEnPos(tab, x, y));
}

/* funcion privada */
// Devuelve falso cuando es una pared con restricci�n num�rica y
// no se cumple su restricci�n num�rica y cierto en el resto de casos.
// Es decir, es cierto cuando no es pared num�rica o se cumple su restricci�n
// de bombillas alrededor.
bool seCumpleRestriccion(const tablero::tTablero tab, int x, int y) {
    return !esPosParedNumerada(tab, x, y) ||
        (esPosParedNumerada(tab, x, y)
            && numBombillasVecinas(tab, x, y) == numPared(tab, x, y));
}

//--------------------------------------------------------------------

/* FUNCIONES PUBLICAS */
bool estaTerminado(tablero::tTablero const& tab) {
    int i = 0, j;
    bool completo = true;
    while (i < tablero::getNumFilas(tab) && completo) {
        j = 0;
        while (j < tablero::getNumCols(tab) && completo) {
            completo = !esPosApagada(tab, i, j) &&
                seCumpleRestriccion(tab, i, j);
            j++;
        }
        if (completo) i++;
    }
    return completo;
}


bool esPosQuit(int x, int y) {
    return PQX == x && PQY == y;
}

/* funcion privada*/
void cambiaCeldaAIluminada(tablero::tTablero& tab, celda::tCelda& laCelda) {
    celda::iluminaCelda(laCelda);
}

/* funcion privada */
void cambiaCeldaAApagada(tablero::tTablero& tab, celda::tCelda& laCelda) {
    celda::apagaCelda(laCelda);
}

// M�todos para el control de las bombillas que iluminan a una celda.
// Cambiar la iluminaci�n de la celda a�adiendo o quitando la posici�n de la bombilla.
// Si iluminar es true se a�ade la bombilla, sino se quita.

/* funcion privada */
void cambiarIluminacionCelda(celda::tCelda& celda, bool encender) {
    if (encender) iluminaCelda(celda);
    else apagaCelda(celda);
}

/* funcion privada */
// Avance de la posici�n pos en la direcci�n dir.
void avanzarPosDir(int& x, int& y, tDir dir) {
    switch (dir)
    {
    case NORTE: x--;
        break;
    case SUR:   x++;
        break;
    case ESTE:  y++;
        break;
    case OESTE: y--;
        break;
    }
};

// Considerando que en la posici�n pos se ha puesto/quitado una bombilla
// ilumina/reduce la iluminaci�n de las casillas en alcanzables en la direcci�n dir
// Iluminando o quitando la iluminaci�n dependiendo de iluminar
// La casilla pos no la cambia.

/* funcion privada */
void cambiarIluminacionDir(tablero::tTablero& tab, int x, int y, tDir dir, bool iluminar) {
    int newx = x;
    int newy = y;
    avanzarPosDir(newx, newy, dir);

    while (esPosValida(tab, newx, newy) &&
        !esBombilla(celdaEnPos(tab, newx, newy)) && // Innecesario no puede haber bombilla
        !esPared(celdaEnPos(tab, newx, newy))) {
        celda::tCelda c = celdaEnPos(tab, newx, newy);
        cambiarIluminacionCelda(c, iluminar);
        ponCeldaEnPos(tab, newx, newy, c);
        // pasar al siguiente
        avanzarPosDir(newx, newy, dir);
    }
}


void cambiarIluminacion(tablero::tTablero& tab, int x, int y, bool iluminar) {
    // Se puede programar con un for con array de direcciones, pero son 4 y queda m�s claro as�.
    cambiarIluminacionDir(tab, x, y, NORTE, iluminar);
    cambiarIluminacionDir(tab, x, y, SUR, iluminar);
    cambiarIluminacionDir(tab, x, y, ESTE, iluminar);
    cambiarIluminacionDir(tab, x, y, OESTE, iluminar);
}





/* funcion privada */
void resetearCelda(celda::tCelda& celda) {
    if (esBombilla(celda) || estaIluminada(celda))
        apagaCelda(celda);
}

/* funcion privada */
void resetearTablero(tablero::tTablero& tab) {
    for (int i = 0; i < tablero::getNumFilas(tab); i++) {
        for (int j = 0; j < tablero::getNumCols(tab); j++) {
            celda::tCelda c = celdaEnPos(tab, i, j);
            resetearCelda(c);
            tablero::ponCeldaEnPos(tab, i, j, c);
        }
    }

}


// Pone o quita la bombilla de la posici�n pos si se puede 
// y cambia la iluminaci�n de todos los alcanzables desde esa casilla.
void ejecutarPos(tablero::tTablero& tab, int x, int y) {
    if (esPosReset(x, y)) {
        resetearTablero(tab);
    }
    else if (esPosValida(tab, x, y)) {
        celda::tCelda celda = celdaEnPos(tab, x, y);
        if (celda::estaApagada(celda)) {
            celda::ponBombilla(celda);
            ponCeldaEnPos(tab, x, y, celda);
            cambiarIluminacion(tab, x, y, true);
        }
        else {
            if (celda::esBombilla(celda)) {
                cambiaCeldaAApagada(tab, celda);
                ponCeldaEnPos(tab, x, y, celda);
                cambiarIluminacion(tab, x, y, false);
            }
        }

    }
}









