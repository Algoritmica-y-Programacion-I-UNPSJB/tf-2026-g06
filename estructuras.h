#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAX 51

// Dificultad que puede tener una palabra.
typedef enum {
    FACIL = 1,
    MEDIO,
    DIFICIL
} Dificultad;

// Tema que puede tener una palabra
typedef enum {
    ANIMALES = 1,
    FRUTAS,
    PAISES
} Tema;

// Representa una palabra que se puede elegir para jugar.
typedef struct {
    int numero;                 // Número identificador de la palabra.
    char palabra[MAX];         // Palabra que se va a utilizar.
    Dificultad dificultad;     // Dificultad de la palabra.
    Tema tema;                  // Tema de la palabra
} Palabra;

// Guarda la información de una partida que ya terminó.
typedef struct {
    char jugador[MAX];          // Nombre del jugador.
    char palabra[MAX];         // Palabra que le tocó.
    Dificultad dificultad;     // Dificultad de la partida.
    int intentosUsados;         // Cantidad de intentos que utilizó.
    int gano;                   // 1 si ganó, 0 si perdió.
    int tiempo;                 // Tiempo que tardó, en segundos.
    int puntajeTotal;
} Partida;

#endif