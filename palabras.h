#ifndef PALABRAS_H
#define PALABRAS_H

#include "estructuras.h"

int cargarPalabras(Palabra palabras[], int capacidad);

Palabra elegirPalabra(Palabra palabras[], int cantidad, Dificultad dificultad);

Tema obtenerPista(Palabra palabra);

#endif