#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "raylib.h"
#include "juego.h"

// Esta función comprueba si la letra ingresada por el jugador está en la palabra
int comprobarLetra(char palabra[], char progreso[], char letra) {
  int coincidencia = 0; // Indica si se encontró la letra en el arreglo
  
  // Recorre palabra carácter por carácter
  for(int i = 0; palabra[i] != '\0'; i++) {
    
    // Compara letra con palabra[i]
    if(letra == palabra[i]) {
      progreso[i] = letra; // Modifica el progreso del jugador
      coincidencia = 1; // Si está indica 1 (verdadero)
    }
  }
  
  return coincidencia; // Devuelve 1 si hubo coincidencia o 0 sino
}

// Esta función verifica si el jugador ya ingresó todas las letras de la palabra
int verificarVictoria(char progreso[]) {
  // Recorre cada letra del progreso del jugador
  for(int i = 0; progreso[i] != '\0'; i++) {
    // Verifica si queda letra por adivinar
    if(progreso[i] == '_') {
      return 0; // Si quedan, entonces todavía no ganó
    }
  }
  return 1; // Si no quedan, ya ganó
}

// Esta función verifica que la letra que ingresó el jugador no este repetida
int letraYaUsada(char letrasUsadas[], int cantidad, char letra) {
  
  // Recorre las letras que ya ingresó el jugador
  for(int i = 0; i < cantidad; i++) {
    
    // Comprueba si la letra ingresada ya está guardada
    if(letra == letrasUsadas[i]) {
      return 1; // La letra ya se usó
    }
  }
  
  return 0; // La letra todavía no se usó
}

// Inicializa el estado del juego con la palabra elegida
void iniciarJuego(EstadoJuego *juego, Palabra palabraElegida, char nombreJugador[]) {
  // Guarda la palabra elegida dentro de la estructura del juego
  juego->palabraElegida = palabraElegida;
  strcpy(juego->jugador, nombreJugador);

  int longitudPalabra = strlen(palabraElegida.palabra); // Calcula la longitud de la palabra sin contar el caracter nulo

  // Recorre cada posición de la palabra
  for(int i = 0; i < longitudPalabra; i++) {
    juego->progreso[i] = '_'; // Coloca un guion bajo en cada posición
  }

  juego->progreso[longitudPalabra] = '\0'; // Agrega el caracteer nulo a la palabra
  
  juego->cantidadLetrasUsadas = 0; // Contador de letras usadas
  juego->intentosRestantes = 6; // Cantidad de intentos que quedan
  juego->intentosUsados = 0; // Contador de intentos usados
  juego->gano = 0; // Indica que el jugador todavia no gano
  juego->terminado = 0;  // Indica que la partida todavia no gano
  juego->tiempoInicio = GetTime(); // Registra el inicio del juego para calcular el tiempo (pertenece a raylib)
}

// Procesa la letra ingresada por el jugador
void procesarLetra(EstadoJuego *juego, char letra) {
  // Comprueba si la partida ya termino
  if(juego->terminado) {
    return; // Si termino sale de la función sin procesar la letra
  }

  letra = toupper((unsigned char)letra); // Convierte la letra en mayuscula para trabajar con un formato uniforme, unsigned char evita problemas con ciertos valores de char

  // Comprueba si el carácter ingresado es una letra del alfabeto
  if(!isalpha((unsigned char)letra)) {
    return; // Si no lo es, termina la función sin procesarla
  }

  // Comprueba si la letra ingresada no fue ingresada anteriormente
  if(letraYaUsada(juego->letrasUsadas, juego->cantidadLetrasUsadas, letra)) {
    return; // Si lo fue, termina la función sin procesarla
  }

  juego->letrasUsadas[juego->cantidadLetrasUsadas] = letra; //  Guarda la letra ingresada
  juego->cantidadLetrasUsadas++; // Incrementa la cantidad de letras usadas para registrar la letra
  juego->intentosUsados++;

  // Comprueba si la letra aparece en la palabra elegida
  if(comprobarLetra(juego->palabraElegida.palabra, juego->progreso, letra)) {
    
    // Comprueba si ya se descubrieron todas las letras de la palabra
    if(verificarVictoria(juego->progreso)) {
      juego->gano = 1; // Si ya se descubrieron todas, indica que el jugador ganó la partida
      juego->terminado = 1; // Indica que se terminó la partida
    }

  } else {
    juego->intentosRestantes--; // Si la letra no esta en la palabra, se descuenta un intento

    // Comprueba si el jugador se quedo sin intentos
    if(juego->intentosRestantes == 0) {
      juego->terminado = 1; // Si se quedó sin intentos, indica que la partida terminó
    }
  }
}