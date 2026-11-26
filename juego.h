#ifndef JUEGO_H
#define JUEGO_H
#include "estructuras.h"

// Reune toda la información necesaria para controlar una partida
typedef struct {
  char jugador[MAX];
  Palabra palabraElegida;
  char progreso[MAX];
  char letrasUsadas[MAX];
  int cantidadLetrasUsadas;
  int intentosRestantes;
  int intentosUsados;
  int gano;
  int terminado;
  double tiempoInicio;
} EstadoJuego;

void iniciarJuego(EstadoJuego *juego, Palabra palabraElegida, char nombreJugador[]);
void procesarLetra(EstadoJuego *juego, char letra);
int comprobarLetra(char palabra[], char progreso[], char letra);
int verificarVictoria(char progreso[]);
int letraYaUsada(char letrasUsadas[], int cantidad, char letra);

#endif