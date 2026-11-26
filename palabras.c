#include <stdio.h>
#include <string.h>
#include "palabras.h"
#include <stdlib.h>
int cargarPalabras(Palabra palabras[], int capacidad) {
     FILE *archivo = fopen("palabras.txt", "r");
    if (archivo == NULL) {
        return 0;                                     //MAIN.C TENDRA QUE AVISAR CON LA INTERFAZ GRAFICA QUE NO SE PUDO ABRIR EL ARCHIVO solo si se kiere
    }
    int contadorPal = 0;                            // CONTADOR DE CUANTAS PALABRAS SE CARGAR
    char linea [100];                               // PARA LEER CADA LINEA DE PALABRAS.TXT
    while (contadorPal < capacidad && fgets(linea, 100, archivo) != NULL ) {  // SE LEE CADA LINEA DEL ARCHIVO HASTA QUE NO HAYAN MAS PALABRAS O SE LLENE EL ARREGLO
        linea[strcspn(linea, "\r\n")] = '\0';       // ELIMINA EL SALTO DE LINEA
        char *dato = strtok (linea , ";");          // SE UTILIZA UN PUNTERO PARA IR GUARDANDO CADA DATO
        if (dato == NULL) {
            continue;
        }
        if (sscanf(dato, "%d", &palabras[contadorPal].numero) != 1) { // GUARDA EL NUMERO DE LA PALABRA Y SI NO PUDO GUARDARLO (POR ESO !=1) SIGUE CON EL RESTO
            continue;
        }  
        dato = strtok (NULL , ";");
        if (dato == NULL) {
            continue;
        }
        strcpy (palabras[contadorPal].palabra, dato);  // GUARDA LA PALABRA
        dato = strtok (NULL , ";");
        if (dato == NULL) {
            continue;
        }
        if (strcmp (dato, "FACIL") == 0 ) {           // GUARDA LA DIFICULTAD
            palabras[contadorPal].dificultad = FACIL;
        } else if (strcmp (dato, "MEDIO") == 0 ) {
            palabras[contadorPal].dificultad = MEDIO;
        } else if (strcmp (dato, "DIFICIL") == 0 ) {
            palabras[contadorPal].dificultad = DIFICIL;
        } else {
            continue;
        }
        dato = strtok (NULL , ";");
        if (dato == NULL) {
            continue;
        }
        if (strcmp (dato, "ANIMALES") == 0 ) {        // GUARDA EL TEMA
            palabras[contadorPal].tema = ANIMALES;
        } else if (strcmp (dato, "FRUTAS") == 0 ) {
            palabras[contadorPal].tema = FRUTAS;
        } else if (strcmp (dato, "PAISES") == 0 ) {
            palabras[contadorPal].tema = PAISES;
        } else {
            continue;
        }
        contadorPal++;                                // AUMENTA EL CONTADOR DE PALABRAS CARGADAS
    }
    fclose (archivo);
    return contadorPal;                  
}
Palabra elegirPalabra(Palabra palabras[], int cantidad, Dificultad dificultad) { //SE ELIGE ALEATORIAMENTE UN TEMA Y UN NUMERO DE LA PALABRA
    Tema temaAleatorio = rand () % 3 + 1;
    int numeroAleatorio = rand () % 5 + 1;
    Palabra vacia = {0};     // SE CREA UNA PALABRA VACIA POR LAS DUDAS SI NO DEVUELVE NADA

    for (int i = 0; i < cantidad; i++) {
        if (palabras[i].numero == numeroAleatorio && palabras[i].dificultad == dificultad && palabras[i].tema == temaAleatorio) {
            return palabras[i]; // DEVUELVE LA PALABRA QUE TENGA LAS CARACTERISTICAS QUE SE ELIGIERON ALEATORIAMENTE
        }
    }
    return vacia;  // HAY QUE COMPROBAR DESPUES QUE DEVUELVE
}
Tema obtenerPista(Palabra palabra) {
    return palabra.tema;  // DEVUELVE EL TEMA DE LA PALABRA PARA UTLIZAR LA PISTA
}