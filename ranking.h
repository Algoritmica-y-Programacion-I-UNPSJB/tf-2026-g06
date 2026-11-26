#ifndef RANKING_H
#define RANKING_H
#include "estructuras.h"

void guardarPartida (Partida partida);
void ordenarRanking (Partida partidas[], int cantidad);
int cargarRanking(Partida ganadas[], int maximo);

#endif