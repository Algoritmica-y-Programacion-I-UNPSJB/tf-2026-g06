#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "raylib.h"
#include "juego.h"
#include "interfaz.h"
#include "palabras.h"
#include "ranking.h"

#define MAX_PALABRAS 100
#define MAX_PARTIDAS 100

// Enumeracion que indica las distintas pantallas del juego
typedef enum {
    MENU,
    JUGAR,
    RANKING,
    INSTRUCCIONES,
    RESULTADO,
    INGRESAR_NOMBRE,
    SELECCION_DIFICULTAD
} Pantalla;

int main(void) {
    InitWindow(800, 600, "Ahorcado"); // Inicializa la ventana con 800 de ancho y 600 de alto
    Font fuente = LoadFont("help_me/HelpMe.ttf"); // Carga la fuente personalizada
    SetTargetFPS(60); // Establece que el juego se actualice a 60 cuadros por segundos

    EstadoJuego juego = {0}; // Crea e inicializa la estructura con los datos de la partida
    char nombreJugador[MAX] = ""; // Reserva espacio para almacenar el nombre del jugador
    

    Palabra palabras[MAX_PALABRAS]; // Arreglo donde se almacenarán las palabras cargadas del archivo

    Partida partidasGanadas[MAX_PARTIDAS]; // Almacena las partidas ganadas que forman parte del ranking
    
    // Carga las partidas guardadas en el archivo del ranking
    int cantidadPartidas = cargarRanking(partidasGanadas, MAX_PARTIDAS);
    
    // Carga las palabras del archivo y devuelve cuantas se cargaron
    int cantidadPalabras = cargarPalabras(palabras, MAX_PALABRAS);

    // Comprueba si se pudo cargar las palabras, si no se pudo cierra la ventana y finaliza el programa
    if(cantidadPalabras == 0) {
        CloseWindow();
        return 1;
    }

    Dificultad dificultadElegida = FACIL; // Almacena la dificultad seleccionada

    srand((unsigned int)time(NULL)); // Genera numeros aleatorios

    Pantalla pantallaActual = MENU; // Establece el menu como pantalla principal

    // Bucle principal, muestra el juego hasta que el usuario cierre la ventana
    while(!WindowShouldClose()) {

        // MENU PRINCIPAL
        // Detecta los clics solamente en el menú
        if(pantallaActual == MENU) {
            Vector2 mouse = GetMousePosition(); // Obtiene la posición actual del menú

            // Comprueba si se presiono el boton izquierdo del mouse
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                // Comprueba si el click fue en el boton jugar
                if(mouse.x >= 330 && mouse.x <= 500 && mouse.y >= 240 && mouse.y <= 275) {
                    nombreJugador[0] = '\0'; // Limpia el nombre anterior para permitir ingresar uno nuevo
                    pantallaActual = INGRESAR_NOMBRE; // Cambia la pantalla a ingresar nombre

                    // Comprueba si el click fue en el boton ranking
                } else if(mouse.x >= 300 && mouse.x <= 500 && mouse.y >= 285 && mouse.y <= 315) {
                    pantallaActual = RANKING; // Cambia la pantalla a ranking

                    // Comprueba si el click fue en el boton instrucciones
                } else if(mouse.x >= 270 && mouse.x <= 530 && mouse.y >= 320 && mouse.y <= 355) {
                    pantallaActual = INSTRUCCIONES; // Cambia la pantalla a instrucciones

                    // Comprueba si el click fue en el boton salir
                } else if(mouse.x >= 300 && mouse.x <= 500 && mouse.y >= 360 && mouse.y <= 395) {
                    break; // Finaliza el bucle principal
                }
            }
        }

        // SELECCION DE DIFICULTAD
        // Detecta los clicks solo en la pantalla dificultad
        if(pantallaActual == SELECCION_DIFICULTAD) {
            Vector2 mouse = GetMousePosition(); // Obtiene la posición actual del menú

            // Comprueba si se presiono el boton izquierdo del mouse
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                bool dificultadElegidaValida = true; // Supone que se slecciono un boton valido

                // Comprueba si se hizo click en facil
                if(mouse.x >= 350 && mouse.x <= 450 && mouse.y >= 250 && mouse.y <= 285) {
                    dificultadElegida = FACIL;

                    // Comprueba si se hizo click en medio
                } else if(mouse.x >= 350 && mouse.x <= 450 && mouse.y >= 310 && mouse.y <= 345) {
                    dificultadElegida = MEDIO;

                    // Comprueba si se hizo click en dificil
                } else if(mouse.x >= 350 && mouse.x <= 470 && mouse.y >= 370 && mouse.y <= 405) {
                    dificultadElegida = DIFICIL;

                    // si el click no corresponde a ningun boton, indica que la seleccion no es valida
                } else {
                    dificultadElegidaValida = false;
                }

                // Continua solamente si se selecciono una dificultad valida
                if(dificultadElegidaValida) {
                    // Solicita una palabra que corresponda con la dificultad elegida
                    Palabra palabraElegida = elegirPalabra(palabras, cantidadPalabras, dificultadElegida);

                    // Comprueba que se haya encontrado una palabra valida
                    if(palabraElegida.palabra[0] != '\0') {
                        // Inicializa la partida con la palabra y el nombre ingresado
                        iniciarJuego(&juego, palabraElegida, nombreJugador);
                        pantallaActual = JUGAR; // Cambia la pantalla a jugar
                    }
                }
                
            }
        }

        // Detecta los clicks solo en la pantalla instrucciones
        if(pantallaActual == INSTRUCCIONES) {
            Vector2 mouse = GetMousePosition(); // Obtiene la posición actual del menú

            // Comprueba si se presiono el boton izquierdo del mouse
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

                // Comprueba si se hizo click en volver al menu
                if(mouse.x >= 250 && mouse.x <= 550 && mouse.y >= 545 && mouse.y <= 585) {
                    pantallaActual = MENU; // Cambia la pantalla a menu
                }
            }
        }

        // Ingreso del nombre
        // Detecta los clicks solo en la pantalla ingresar nombre
        if(pantallaActual == INGRESAR_NOMBRE) {
            int caracter = GetCharPressed(); // Obtiene el primer caracter ingresado por teclado

            // Procesa todos los caracteres que esten pendientes de lectura
            while(caracter > 0) {
                int longitud = strlen(nombreJugador); // Calcula la longitud actual del nombre

                // Acepta caracteres imprimibles y comprueba que haya espacio
                if(caracter >= 32 && caracter <= 125 && longitud < MAX - 1) {
                    nombreJugador[longitud] = (char)caracter; // Guarda el caracter al final de la cadena
                    nombreJugador[longitud + 1] = '\0'; // Agrega el caracter nulo para finalizar la cadena
                }

                caracter = GetCharPressed(); // Obtiene el siguiente caracter pendiente
            }

            // Comprueba si se presiono la tecla backspace
            if(IsKeyPressed(KEY_BACKSPACE)) {
                int longitud = strlen(nombreJugador); // Calcula la longitud del nombre

                // Si hay caracteres elimina el ultimo
                if(longitud > 0) {
                    nombreJugador[longitud - 1] = '\0';
                }
            }

            // Permite continuar si selecciono enter y el nombre esta vacio
            if(IsKeyPressed(KEY_ENTER) && strlen(nombreJugador) > 0) {
                pantallaActual = SELECCION_DIFICULTAD;
            }
        }

        // Comprueba si el jugador está en la pantalla del ranking y si hizo click
        if(pantallaActual == RANKING && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mouse = GetMousePosition(); // Obtiene las coordenadas actuales del mouse

            Vector2 posicionVolver = {280, 550}; // Posición de volver al menu

            Rectangle botonVolver = {posicionVolver.x, posicionVolver.y, MeasureTextEx(fuente, "VOLVER AL MENU", 25, 2).x, 35}; // Rectangulo que representa el área de volver al menu

            // Comprueba si el curso del mouse está dentro del área del botón
            if(CheckCollisionPointRec(mouse, botonVolver)) {
                pantallaActual = MENU; // Cambia a la pantalla menu
            }
        }

        // Procesa el teclado solamente durante la partida
        if(pantallaActual == JUGAR && !juego.terminado) {
            int tecla = GetCharPressed(); // Obtiene el primer caracter ingresado por teclado

            // Procesa todos los caracteres pendientes de lectura
            while(tecla > 0) {
                procesarLetra(&juego, (char)tecla); // Envia la letra al modulo del juego para que la procese
                tecla = GetCharPressed();
            }
        }

        // Si la partida terminó, cambia a la pantalla de resultados
        if(pantallaActual == JUGAR && juego.terminado) {

            // Comprueba si el jugador ganó la partida
            if(juego.gano == 1) {
                Partida nuevaPartida = {0}; // Crea e iniciliaza partida con todos sus campos en 0

                strcpy(nuevaPartida.jugador, juego.jugador); // Copia el nombre del jugador
                strcpy(nuevaPartida.palabra, juego.palabraElegida.palabra); // Copia la palabra elegida

                // Guarda los datos de la partida terminada
                nuevaPartida.dificultad = juego.palabraElegida.dificultad;
                nuevaPartida.intentosUsados = juego.intentosUsados;
                nuevaPartida.gano = juego.gano;
                nuevaPartida.tiempo = (int)(GetTime() - juego.tiempoInicio);

                guardarPartida(nuevaPartida); // Guarda la partida en el archivo de ranking

                // Comprueba si hay espacio en el arreglo
                if(cantidadPartidas < MAX_PARTIDAS) {
                    partidasGanadas[cantidadPartidas] = nuevaPartida; // Agrega la partida en el final del arreglo
                    //Actualiza el arreglo y la cantidad de partidas
                    cantidadPartidas = cargarRanking(partidasGanadas, MAX_PARTIDAS);
                }
            }
            
            pantallaActual = RESULTADO; // Cambia la pantalla aresultados
        }

        // Resultado de la partida
        if(pantallaActual == RESULTADO) {

            // Comprueba si se presiono el boton izquierdo del mouse
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition(); // Obtiene la posición actual del menú

                // Comprueba si se hizo click en volver a jugar
                if(mouse.x >= 280 && mouse.x <= 500 && mouse.y >= 390 && mouse.y <= 435) {
                    pantallaActual = SELECCION_DIFICULTAD;
                    juego.terminado = 0; // Limpia el indicador de finalizacion para otra partida
                }

                // Comprueba si se clcik en volver al menu
                if(mouse.x >= 280 && mouse.x <= 500 && mouse.y >= 460 && mouse.y <= 505) {
                    juego.terminado = 0;
                    pantallaActual = MENU;
                }
            }
        }

        // Dibuja la pantalla correspondiente
        BeginDrawing();
        ClearBackground(BLACK); // Establece el fondo negro

        // Comprueba que pantalla debe dibujarse
        if(pantallaActual == MENU) {
            float tiempo = fmodf(GetTime(), 2.0f); // Calcula un tiempo que se repite cada dos segundos
            bool parpadeo = tiempo < 0.15f; // Activa el parpadeo durante los primeros 0.15 segundos del ciclo

            // Cambia el color de la pantalla en cada parpadeo
            if(parpadeo) {
                ClearBackground(DARKGRAY);
            }

            // Dibuja el menu principal
            dibujarMenu(fuente, parpadeo);

        } else if(pantallaActual == INGRESAR_NOMBRE) {
            dibujarIngresoNombre(nombreJugador, fuente);
            
        } else if(pantallaActual == SELECCION_DIFICULTAD) {
            dibujarSeleccionDificultad(fuente);
            
        } else if(pantallaActual == JUGAR) {
            dibujarJuego(&juego, fuente);

        } else if(pantallaActual == RANKING) {
            dibujarRanking(partidasGanadas, cantidadPartidas, fuente);
            
        } else if(pantallaActual == INSTRUCCIONES) {
            dibujarInstrucciones(fuente);
        
        } else if(pantallaActual == RESULTADO) {
            dibujarResultado(&juego, fuente);
        }

        EndDrawing(); // Termina de dibujar
    }

    UnloadFont(fuente); // Libera la memoria utilizada por la fuente
    CloseWindow(); // Cierra la ventana
    return 0;
}