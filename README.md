# Trabajo Integrador Final 2026 — Grupo 06

**Juego aprobado:** Ahorcado  
**Interfaz / Modalidad:** Gráfica — 1 jugador  

## Integrantes y aportes
- Celeste Rocío Miltos (@celes976)
- Milagros López (@Miliii08)
- Valentina Laura Morando (GitHub no informado)

## Reglas y alcance
El juego permitirá identificar al jugador y seleccionar una dificultad: fácil, normal o difícil.

La palabra se elegirá desde un archivo de texto `palabras.txt`, donde las palabras estarán clasificadas por dificultad.

Durante la partida el jugador podrá ingresar letras o intentar adivinar la palabra completa. Se controlarán letras repetidas y habrá un máximo de 6 intentos.

Cada partida será medida mediante un cronómetro. Los resultados se almacenarán en `ranking.dat` y se organizarán considerando, en este orden:

1. dificultad;
2. tiempo;
3. cantidad de intentos.

La propuesta contempla una interfaz gráfica.

## Compilación y ejecución

Dependencias necesarias:
- GCC (compilador de C).
- Raylib (biblioteca gráfica utilizada para el juego).

Comando de compilación:
gcc main.c juego.c interfaz.c palabras.c ranking.c -o ahorcado.exe -lraylib -lopengl32 -lgdi32 -lwinmm

Comando de ejecución:
./ahorcado.exe

Para compilar y ejecutar el juego, es necesario tener GCC y Raylib instalados y configurados correctamente.

## Organización de datos y funciones

Estructuras y datos principales
En el archivo "estructuras.h" se encuentran las estructuras y enumeraciones que utilizan los distintos módulos:
- Dificultad: permite identificar los tres niveles del juego: fácil, medio y difícil.
- Tema: permite clasificar las palabras en animales, frutas y países.
- Palabra: almacena el número, la palabra, su dificultad y su tema.
- Partida: almacena los datos de cada partida, como el jugador, la palabra utilizada, la dificultad, los intentos realizados, el resultado, el tiempo y el puntaje obtenido.
- EstadoJuego: almacena la información necesaria durante una partida, como el nombre del jugador, la palabra elegida, el progreso, las letras utilizadas, los intentos restantes y el estado del juego.

Organización de los archivos y funciones
- main.c: contiene la función principal y se encarga de coordinar el funcionamiento del programa, los menús y las distintas pantallas.
- juego.c / juego.h: contienen la lógica del juego, el procesamiento de las letras ingresadas, la comprobación de letras repetidas y la verificación de la victoria.
- palabras.c / palabras.h: se encargan de cargar las palabras desde el archivo "palabras.txt" y seleccionar una según la dificultad elegida.
- ranking.c / ranking.h: se encargan de guardar las partidas ganadas, cargar los datos del ranking y ordenarlos para mostrarlos.
- interfaz.c / interfaz.h: contienen las funciones encargadas de dibujar los menús, las instrucciones, la pantalla de juego, los resultados y el ranking.

Flujo del programa
Al iniciar, el programa carga las palabras y los datos del ranking. Luego muestra el menú principal, desde donde el jugador puede ingresar su nombre, consultar las instrucciones o acceder al ranking.
Para comenzar una partida, el jugador selecciona una dificultad y el programa elige una palabra correspondiente a ese nivel. Durante el juego se procesan las letras ingresadas y se actualiza el progreso hasta que el jugador gana o pierde.
Al finalizar, se muestra el resultado de la partida. Si el jugador gana, sus datos se guardan en el ranking. Finalmente, puede volver a jugar o regresar al menú principal.

## Interfaz gráfica

La interfaz gráfica fue desarrollada utilizando la biblioteca Raylib. Se encarga de mostrar los menús, las instrucciones, la pantalla de juego, los resultados y el ranking.
El archivo "interfaz.c" contiene las funciones encargadas de dibujar los elementos visuales, mientras que "juego.c" contiene la lógica del juego.
Ambos módulos se conectan para que la interfaz pueda mostrar los cambios que se producen durante cada partida, como el progreso de la palabra, las letras utilizadas, los intentos restantes y el resultado final.
Para el desarrollo de la interfaz se utilizaron funciones de Raylib para dibujar textos, figuras y otros elementos gráficos.
Uso de inteligencia artificial: No se utilizaron herramientas de IA para generar imágenes o elementos gráficos. Sin embargo, se utilizó inteligencia artificial como herramienta de asistencia durante el desarrollo y la escritura del código.
