#include <string.h>
#include <math.h>
#include "raylib.h"
#include "interfaz.h"
#include "palabras.h"

// Dibuja la horca
//Los dos primero valores (x, y) indican donde empieza la linea y los siguientes dos (x, y) donde termina, lo último es el color
// x aumenta hacia la derecha e y hacia abajo
void dibujarHorca(void) {
  DrawLine(100, 450, 300, 450, DARKBROWN); // Dibuja la base de la horca
  DrawLine(150, 450, 150, 100, DARKBROWN); // El poste vertical
  DrawLine(150, 100, 300, 100, DARKBROWN); // La parte horizontal superior
  DrawLine(300, 100, 300, 150, DARKBROWN); // La cuerda vertical
}

// Dibuja las partes del muñeco según la cantidad de errores cometidos
void dibujarMuneco(int errores) {
  if(errores >= 1) {
    // Posicion x, posicion y, radio y color
    DrawCircleLines(300, 180, 25, WHITE); // Cabeza
  }

  if(errores >=  2) {
    DrawLine(300, 205, 300, 290, WHITE); // Cuerpo
  }

  if(errores >= 3) {
    DrawLine(300, 225, 270, 255, WHITE); // Brazo izquierdo
  }

  if(errores >= 4) {
    DrawLine(300, 225, 330, 255, WHITE); // Brazo derecho
  }

  if(errores >= 5) {
    DrawLine(300, 290, 270, 330, WHITE); // Pierna izquierda
  }

  if(errores >= 6) {
    DrawLine(300, 290, 330, 330, WHITE); // Pierna derecha
  }
}

/* Dibuja los elementos visuales de la interfaz del juego, recibe un puntero a EstadoJuego para acceder a los datos de la partida y una fuente para dibujar los textos */
void dibujarJuego(EstadoJuego *juego, Font fuente) {
  
  dibujarHorca();

  // Calcula los errores cometidos restando los intentos que le quedan
  dibujarMuneco(6 - juego->intentosRestantes);

  float tamFuente = 50; // Tamaño de la fuente
  Vector2 tamTitulo = MeasureTextEx(fuente, "AHORCADO", tamFuente, 2); // Calcula el alto y el ancho del texto
  Vector2 posicionTitulo = {(800 - tamTitulo.x) / 2, 25}; // Calcula la posición del título para centrarlo
  
  DrawTextEx(fuente, "AHORCADO", posicionTitulo, tamFuente, 2, MAROON); // Titulo principal
  
  DrawTextEx(fuente, "PALABRA", (Vector2){430, 120}, 25, 2, MAROON);

  // Muestra el progreso de la palabra que tiene que adivinar (guiones bajos)
  DrawText(juego->progreso, 430, 160, 35, WHITE);

  int tiempoTranscurrido = (int)(GetTime() - juego->tiempoInicio);

  DrawTextEx(fuente, TextFormat("TIEMPO: %02d:%02d", tiempoTranscurrido / 60, tiempoTranscurrido % 60), (Vector2){590, 90}, 22, 2, WHITE);

  /* En dificultad facil la pista aparece en el principio y en medio cuando quedan dos intentos, en dificil no hay pista */
  if(juego->palabraElegida.dificultad == FACIL || (juego->palabraElegida.dificultad == MEDIO && juego->intentosRestantes <= 2)) {
    Tema tema = obtenerPista(juego->palabraElegida); // Recibe la palabra elegida y devuelve el tema

    if(tema == ANIMALES) {
      DrawText("Pista: Animales", 430, 210, 20, DARKGREEN);
    } else if(tema == FRUTAS) {
      DrawText("Pista: Frutas", 430, 210, 20, DARKGREEN);
    } else if(tema == PAISES) {
      DrawText("Pista: Paises", 430, 210, 20, DARKGREEN);
    }
  }

  DrawTextEx(fuente, "INTENTOS RESTANTES", (Vector2){430, 250}, 22, 2, MAROON);
  // Convierte el entero en texto para que se pueda mostrar en pantalla
  DrawText(TextFormat("%d", juego->intentosRestantes), 430, 285, 35, RED);

  DrawTextEx(fuente, "LETRAS USADAS", (Vector2){430, 330}, 22, 2, MAROON);

  char letras[MAX * 3]; // Permite almacenar las letras utilizadas
  letras[0] = '\0'; // Inicializa la cadena vacia

  // Recorre el arreglo de letras utilizadas
  for(int i = 0; i < juego->cantidadLetrasUsadas; i++) {
    char letra[2] = {juego->letrasUsadas[i], '\0'}; // Almacena la letra utilizada y el caracter nulo
    strcat(letras, letra); // Agrega la letra actual al final de la cadena
    strcat(letras, " "); // Agrega un espacio después de cada letra
  }

  DrawText(letras, 430, 365, 20, RED); // Muestra todas las letras utilizadas
}

// Pantalla de instrucciones
void dibujarInstrucciones(Font fuente) {

  // Guarda el texto del titulo en un puntero a constante, const char * indica que no se modifica el texto
  const char *titulo = "INSTRUCCIONES";
  float tamTitulo = 45; // Tamaño de la fuente del titulo

  Vector2 tam = MeasureTextEx(fuente, titulo, tamTitulo, 2); // Calcula el ancho y el alto del titulo
  Vector2 pos = {(800 - tam.x) / 2, 35}; // Calcula la posición del titulo para centrarlo

  // Título principal
  DrawTextEx(fuente, titulo, pos, tamTitulo, 2, MAROON);

  // Subtítulos
  DrawTextEx(fuente, "OBJETIVO", (Vector2){100, 115}, 27, 2, MAROON);

  DrawText("Descubri la palabra antes de quedarte", 100, 155, 18, WHITE);
  DrawText("sin intentos. Puede ser una fruta,", 100, 180, 18, WHITE);
  DrawText("un animal o un pais.", 100, 205, 18, WHITE);

  DrawTextEx(fuente, "COMO JUGAR", (Vector2){100, 240}, 27, 2, MAROON);

  DrawText("Ingresa una letra por vez e intenta", 100, 275, 18, WHITE);
  DrawText("adivinar la palabra completa.", 100, 300, 18, WHITE);
  DrawText("Las letras repetidas no descuentan", 100, 325, 18, WHITE);
  DrawText("intentos.", 100, 350, 18, WHITE);

  DrawTextEx(fuente, "DIFICULTADES", (Vector2){100, 385}, 27, 2, MAROON);

  DrawText("FACIL: Muestra el tema de la palabra", 100, 425, 18, WHITE);
  DrawText("MEDIO: Muestra una pista cuando quedan", 100, 455, 18, WHITE);
  DrawText("2 intentos", 100, 480, 18, WHITE);
  DrawText("DIFICIL: No muestra pistas", 100, 510, 18, WHITE);

  Vector2 mouse = GetMousePosition(); // Obtiene la posición actual del mouse

  Vector2 posicionVolver = {300, 550}; // Establece la posición inicial del texto "VOLVER AL MENU"

  // Crea un rectangulo que representa el área del botón
  Rectangle botonVolver = {posicionVolver.x, posicionVolver.y, MeasureTextEx(fuente, "VOLVER AL MENU", 24, 2).x, 35};

  /* Comprueba si la posición del mouse está dentro del rectángulo, si está dentro, significa que el mouse está sobre el botón */
  if(CheckCollisionPointRec(mouse, botonVolver)) {
      posicionVolver.x += sin(GetTime() * 40) *3; // Genera el movimiento del botón

      posicionVolver.y += cos(GetTime() * 45) *2; // Genera el movimiento del botón
    }

    DrawTextEx(fuente, "VOLVER AL MENU", posicionVolver, 24, 2, MAROON);
}

// Dibuja el menú principal
void dibujarMenu(Font fuente, bool parpadeo) {
  Vector2 mouse = GetMousePosition(); // Obtiene la posición del mouse
  
  Vector2 tamTitulo = MeasureTextEx(fuente, "AHORCADO", 75, 2); // Calcula las dimensiones del titulo
  Vector2 posicion = {(800 - tamTitulo.x) / 2, 100}; // Calcula la posici+on para centrarlo

  // Modifica la posición del titulo según el papardeo de la pantalla
  if(parpadeo) {
    posicion.x += GetRandomValue(-20, 20);
    posicion.y += GetRandomValue(-12, 12);
  }
  
  DrawTextEx(fuente, "AHORCADO", posicion, 75, 2, MAROON);

  // Boton JUGAR
  int anchoJugar = MeasureText("JUGAR", 25); // Calcula el ancho del texto
  // Calculas posiciones x,y para centrar el texto
  int xJugar = 400 - anchoJugar / 2;
  int yJugar = 250;

  Rectangle botonJugar = {xJugar - 5, yJugar - 5, anchoJugar + 10, 35}; // Define el rectangulo invisible

  // Comprueba si el mouse esta sobre el boton
  if(CheckCollisionPointRec(mouse, botonJugar)) {
    // Modifica las posiciones de x,y para generar el movimiento
    xJugar += (int)(sin(GetTime() * 40) * 3);
    yJugar += (int)(cos(GetTime() * 45) * 2);
  }

  DrawText("JUGAR", xJugar, yJugar, 25, WHITE);
  
  // Botón RANKING
  int anchoRanking = MeasureText("RANKING", 25); // Calcula el ancho del texto
  // Calculas posiciones x,y para centrar el texto
  int xRanking = 400 - anchoRanking / 2;
  int yRanking = 290;

  Rectangle botonRanking = { xRanking - 5, yRanking - 5, anchoRanking + 10, 35}; // Define el rectangulo invisible

  // Comprueba si el mouse esta sobre el boton
  if(CheckCollisionPointRec(mouse, botonRanking)) {
    // Modifica las posiciones de x,y para generar el movimiento
      xRanking += (int)(sin(GetTime() * 40) * 3);
      yRanking += (int)(cos(GetTime() * 45) * 2);
  }

  DrawText("RANKING", xRanking, yRanking, 25, WHITE);

  // Botón INSTRUCCIONES
  int anchoInstrucciones = MeasureText("INSTRUCCIONES", 25); // Calcula el ancho del texto
  // Calculas posiciones x,y para centrar el texto
  int xInstrucciones = 400 - anchoInstrucciones / 2;
  int yInstrucciones = 330;

  // Define el rectangulo invisible
  Rectangle botonInstrucciones = {xInstrucciones - 5, yInstrucciones - 5, anchoInstrucciones + 10, 35};
  
  // Comprueba si el mouse esta sobre el boton
  if (CheckCollisionPointRec(mouse, botonInstrucciones)) {
    // Modifica las posiciones de x,y para generar el movimiento
      xInstrucciones += (int)(sin(GetTime() * 40) * 3);
      yInstrucciones += (int)(cos(GetTime() * 45) * 2);
  }

  DrawText("INSTRUCCIONES", xInstrucciones, yInstrucciones, 25, WHITE);

  // Botón SALIR
  int anchoSalir = MeasureText("SALIR", 25); // Calcula el ancho del texto
  // Calculas posiciones x,y para centrar el texto
  int xSalir = 400 - anchoSalir / 2;
  int ySalir = 370;

  Rectangle botonSalir = {xSalir - 5, ySalir - 5, anchoSalir + 10, 35}; // Define el rectangulo invisible

  // Comprueba si el mouse esta sobre el boton
  if (CheckCollisionPointRec(mouse, botonSalir)) {
    // Modifica las posiciones de x,y para generar el movimiento
      xSalir += (int)(sin(GetTime() * 40) * 3);
      ySalir += (int)(cos(GetTime() * 45) * 2);
  }

  DrawText("SALIR", xSalir, ySalir, 25, RED);
}

// Dibuja la pantalla que aparece cuando termina la partida
void dibujarResultado(EstadoJuego *juego, Font fuente) {

  // Comprueba si el jugador ganó
  if(juego->gano) {
    DrawTextEx(fuente, "GANASTE!", (Vector2){280, 200}, 50, 3, GREEN);
  
  } else {
    DrawTextEx(fuente, "PERDISTE!", (Vector2){280, 200}, 50, 3, RED);

    /* TextFormat construye una cadena que incluye la palabra elegida, %s indica que se insertará una cadena de carcteres */
    const char *mensaje = TextFormat("La palabra era: %s", juego->palabraElegida.palabra);
    
    int anchoTexto = MeasureText(mensaje, 20); // Calcula el ancho del texto
    int posicionX = (800 - anchoTexto) / 2; // Calcula la posicion para centrarlo

    DrawText(mensaje, posicionX, 280, 20, WHITE);
  }

  Vector2 mouse = GetMousePosition(); // Obtiene la poscion del mouse

  Vector2 posicionVolver = {280, 470}; // Establece la posicion inicial del boton

  // Define el area de deteccion del boton
  Rectangle botonVolver = {posicionVolver.x, posicionVolver.y, MeasureTextEx(fuente, "VOLVER AL MENU", 25, 2).x, 35};

  // Verifica si el mouse esta dentro del boton
  if(CheckCollisionPointRec(mouse, botonVolver)) {
    // Modifica la posicion de x, y para generar movimiento
    posicionVolver.x += sin(GetTime() * 40) * 3;
    posicionVolver.y += cos(GetTime() * 45) * 2;
  }
  
  DrawTextEx(fuente, "VOLVER AL MENU", posicionVolver, 25, 2, MAROON);

  Vector2 posicionJugar = {280, 400}; // Establece la posicion inicial del boton

  // Define el area de deteccion del boton
  Rectangle botonJugar = {posicionJugar.x, posicionJugar.y, MeasureTextEx(fuente, "VOLVER A JUGAR", 25, 2).x, 35};

  // Verifica si el mouse esta dentro del boton
  if(CheckCollisionPointRec(mouse, botonJugar)) {
    // Modifica la posicion de x, y para generar movimiento
    posicionJugar.x += sin(GetTime() * 40) * 3;
    posicionJugar.y += cos(GetTime() * 45) * 2;
  }

  DrawTextEx(fuente, "VOLVER A JUGAR", posicionJugar, 25, 2, MAROON);
}

// Dibuja la pantalla donde se le pregunta el nombre al jugador
void dibujarIngresoNombre(char nombreJugador[], Font fuente) {
  // Guarda el texto del titulo en un puntero a constante, const char * indica que no se modifica el texto
  const char *titulo = "INGRESA TU NOMBRE";
  float tamTitulo = 40; // Tamaño de la fuente del titulo

  Vector2 tam = MeasureTextEx(fuente, titulo, tamTitulo, 2); // Calcula las dimensiones del titulo
  Vector2 posicion = {(800 - tam.x) / 2, 150}; // Calcula la posicion para centrarlo

  DrawTextEx(fuente, titulo, posicion, tamTitulo, 2, MAROON); // Dibuja el titulo

  int anchoNombre = MeasureText(nombreJugador, 30); // Calcula el ancho del nombre
  int posicionX = (800 - anchoNombre) / 2; // Calcula la posicion para centrarlo
  DrawText(nombreJugador, posicionX, 280, 30, WHITE); // Dibuja el nombre centrado
}

// Dibuja el nombre donde el jugador selecciona la dificultad
void dibujarSeleccionDificultad(Font fuente) {
  /* TextFormat construye una cadena que incluye la palabra elegida, %s indica que se insertará una cadena de carcteres */
  const char *titulo = "SELECCIONA LA DIFICULTAD";
  float tamTitulo = 35; // Tamaño de la fuente del titulo

  Vector2 tam = MeasureTextEx(fuente, titulo, tamTitulo, 2); // Calcula las dimensiones del titulo
  Vector2 posicion = {(800 - tam.x) / 2, 130}; // Calcula posicion para centrarlo

  DrawTextEx(fuente, titulo, posicion, tamTitulo, 2, MAROON);

  Vector2 mouse = GetMousePosition(); // Calcula la posicion del mouse
  
  // Calculas posiciones x,y para centrar el texto
  int xFacil = 350;
  int yFacil = 250;
  Rectangle botonFacil = {xFacil, yFacil, 100, 35}; // Define el area de deteccion del boton

  // Verifica si el mouse esta dentro del boton
  if(CheckCollisionPointRec(mouse, botonFacil)) {
    // Modifica la posicion de x, y para generar movimiento
    xFacil += (int)(sin(GetTime() * 40) * 3);
    yFacil += (int)(cos(GetTime() * 45) * 2);
  }

  DrawText("FACIL", xFacil, yFacil, 25, WHITE);

  // Calculas posiciones x,y para centrar el texto
  int xMedio = 350;
  int yMedio = 310;
  Rectangle botonMedio = {xMedio, yMedio, 100, 35}; // Define el area de deteccion del boton

  // Verifica si el mouse esta dentro del boton
  if(CheckCollisionPointRec(mouse, botonMedio)) {
    // Modifica la posicion de x, y para generar movimiento
    xMedio += (int)(sin(GetTime() * 40) * 3);
    yMedio += (int)(cos(GetTime() * 45) * 2);
  }
    
  DrawText("MEDIO", xMedio, yMedio, 25, WHITE);

  // Calculas posiciones x,y para centrar el texto
  int xDificil = 350;
  int yDificil = 370;
  Rectangle botonDificil = {xDificil, yDificil, 120, 35}; // Define el area de deteccion del boton

  // Verifica si el mouse esta dentro del boton
   if(CheckCollisionPointRec(mouse, botonDificil)) {
     // Modifica la posicion de x, y para generar movimiento
    xDificil += (int)(sin(GetTime() * 40) * 3);
    yDificil += (int)(cos(GetTime() * 45) * 2);
  }
    
  DrawText("DIFICIL", xDificil, yDificil, 25, RED);
}

// Dibuja la tabla en la ventana gráfica (se llama entre BeginDrawing y EndDrawing)
void dibujarRanking(const Partida ganadas[], int cantidadGanadas, Font fuente){
    // Título principal
    DrawTextEx(fuente, "TABLA DE CLASIFICACIONES", (Vector2){220, 40}, 28, 2, MAROON);

    if (cantidadGanadas == 0){
        DrawText("No hay partidas ganadas registradas aun.", 210, 220, 20, LIGHTGRAY);
    } else {

    // Cabecera de la tabla
    int posY = 100;
    DrawRectangle(50, posY - 5, 730, 32, DARKGRAY);
    DrawText("#",          65,  posY, 20, RAYWHITE);
    DrawText("Jugador",   100,  posY, 20, RAYWHITE);
    DrawText("Palabra",   205,  posY, 20, RAYWHITE);
    DrawText("Dificultad", 365,  posY, 20, RAYWHITE);
    DrawText("Tiempo",    490,  posY, 20, RAYWHITE);
    DrawText("Intentos", 585, posY, 20, RAYWHITE);  
    DrawText("Puntos",    700,  posY, 20, GOLD);

    // Mostramos hasta un máximo de 10 puestos para que no se desborde la pantalla
    int maxFilas = (cantidadGanadas > 10) ? 10 : cantidadGanadas;

    for (int i = 0; i < maxFilas; i++){
        posY += 36;

        // Fila alterna con fondo tenue para legibilidad
        if (i % 2 == 0) {
            DrawRectangle(50, posY - 4, 730, 30, (Color){ 40, 40, 40, 255 });
        }

        const char *difTexto = (ganadas[i].dificultad == FACIL) ? "FACIL" :
                               (ganadas[i].dificultad == MEDIO) ? "MEDIO" : "DIFICIL";

        // Posición y color destacado para el podio (1°, 2° y 3°)
        Color colorTexto = (i == 0) ? GOLD : (i == 1) ? LIGHTGRAY : (i == 2) ? (Color){ 205, 127, 50, 255 } : WHITE;

        DrawText(TextFormat("%d", i + 1),                      65,  posY, 18, colorTexto);
        DrawText(ganadas[i].jugador,                           100,  posY, 18, WHITE);
        DrawText(ganadas[i].palabra,                           205,  posY, 18, WHITE);
        DrawText(difTexto,                                     365,  posY, 18, SKYBLUE);
        DrawText(TextFormat("%ds", ganadas[i].tiempo),         490,  posY, 18, WHITE);
        DrawText(TextFormat("%d", ganadas[i].intentosUsados), 585, posY, 18, WHITE);
        DrawText(TextFormat("%d", ganadas[i].puntajeTotal),    700,  posY, 18, YELLOW);
    }
    }

    Vector2 mouse = GetMousePosition(); // Obtiene la poscion del mouse

      Vector2 posicionVolver = {280, 550}; // Establece la posicion inicial del boton

      // Define el area de deteccion del boton
      Rectangle botonVolver = {posicionVolver.x, posicionVolver.y, MeasureTextEx(fuente, "VOLVER AL MENU", 25, 2).x, 35};

      // Verifica si el mouse esta dentro del boton
      if(CheckCollisionPointRec(mouse, botonVolver)) {
        // Modifica la posicion de x, y para generar movimiento
        posicionVolver.x += sin(GetTime() * 40) * 3;
        posicionVolver.y += cos(GetTime() * 45) * 2;
      }

      DrawTextEx(fuente, "VOLVER AL MENU", posicionVolver, 25, 2, MAROON);
}