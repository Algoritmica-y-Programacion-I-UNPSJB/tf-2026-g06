#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include "ranking.h"

#define MAX_PARTIDAS 100


static int calcularPuntaje(Partida P){
    int puntajeDificultad = 0;
    int puntajeTiempo = 0;
    int puntajeIntentos = 0;
    
    //Para calcular los puntos segun la dificultad.
    switch (P.dificultad){
    case DIFICIL:
        puntajeDificultad = 40;
        break;
    case MEDIO:
        puntajeDificultad = 25;
        break;
    case FACIL:
        puntajeDificultad = 10;
        break;
    default:
        puntajeDificultad = 0;
        break;
    }
    
    //Para calcular los puntos segun el tiempo.
    if (P.tiempo >= 40){
        //tardo mucho.
        puntajeTiempo = 5;
    } else if (P.tiempo < 40 && P.tiempo >= 20){
        //tiempo normal.
        puntajeTiempo = 15;
    } else {
        //Adivino muy rapido.
        puntajeTiempo = 30;
    }

    //Para calcular los puntos segun los intentos usados.
    if (P.intentosUsados <= 2){
        puntajeIntentos = 30;
    } else if (P.intentosUsados > 2 && P.intentosUsados <= 4){
        puntajeIntentos = 15;
    } else {
        puntajeIntentos = 5;
    }

    return puntajeDificultad + puntajeTiempo + puntajeIntentos;
}

//funcion static porque solo se puede usar en este archivo.
//compara y mira entre dos partidas, cual se debe posicionar mas abajo.
static int debeIntercambiar(Partida a, Partida b){

    // Primero comparamos el puntaje.
    if (a.puntajeTotal < b.puntajeTotal){
        return 1;
    }

    // Si tienen el mismo puntaje, comparamos el tiempo.
    if (a.puntajeTotal == b.puntajeTotal){
        if (a.tiempo > b.tiempo){
            return 1;
        }
    }

    // Si también tienen el mismo tiempo, comparamos los intentos.
        if (a.puntajeTotal == b.puntajeTotal && a.tiempo == b.tiempo){
            if (a.intentosUsados > b.intentosUsados){
                return 1;
            }
        }

        return 0;
}

//Guarda las partidas en el archivo ranking.dat
void guardarPartida(Partida partidas){
    FILE *archivo = fopen("ranking.dat", "ab");
    if (archivo == NULL){
        printf ("Error al abrir ranking.dat para escribir.\n");
        return;
    }
    fwrite(&partidas, sizeof(Partida), 1, archivo);
    fclose(archivo);
    
}

/*Recibe un arreglo con todas las partidas anteriores
y segun los criterios de orden (dificultad, tiempo, intentos...)
utiliza burbujeo para acomodar las partidas*/   
void ordenarRanking(Partida partidas[], int cantidad){
    Partida auxiliar;
    for (int i = 0; i < cantidad - 1; i++){
        for (int j = 0; j < cantidad - 1 - i; j++){
            if (debeIntercambiar(partidas[j], partidas[j+1])){
                auxiliar = partidas[j];
                partidas[j] = partidas[j + 1];
                partidas[j + 1] = auxiliar;
            }
        }
    }
}


int cargarRanking(Partida ganadas[], int maximo){
    FILE *archivo = fopen("ranking.dat", "rb");
    if (archivo == NULL) return 0;
    
    int cantidad = 0;
    Partida temp;

    while (fread(&temp, sizeof(Partida), 1, archivo) == 1){
        if (temp.gano == 1 && cantidad < maximo){
            temp.puntajeTotal = calcularPuntaje(temp);
            ganadas[cantidad] = temp;
            cantidad++;
        }
    }
    fclose(archivo);

    if (cantidad > 0){
        ordenarRanking(ganadas, cantidad);
    }
    return cantidad;
}