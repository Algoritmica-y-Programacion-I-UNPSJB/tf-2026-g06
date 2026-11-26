#ifndef INTERFAZ_H
#define INTERFAZ_H
#include "juego.h"
#include "raylib.h"

void dibujarJuego(EstadoJuego *juego, Font fuente);
void dibujarMenu(Font fuente, bool parpadeo);
void dibujarInstrucciones(Font fuente);
void dibujarResultado(EstadoJuego *juego, Font fuente);
void dibujarIngresoNombre(char nombreJugador[], Font Fuente);
void dibujarSeleccionDificultad(Font fuente);

void dibujarRanking(const Partida ganadas[], int cantidadGanadas, Font fuente);

#endif