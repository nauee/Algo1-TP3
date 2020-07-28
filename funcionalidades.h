#ifndef __FUNCIONALIDADES_H__
#define __FUNCIONALIDADES_H__

#define MAX_RUTA 100
#define MAX_DATO 50
#define MAX_RESISTENCIA_TORRES_C 2
#define MAX_DEFENSORES_C 4
#define MAX_EXTRA_C 3
#define MAX_ANIMOS_C 2

typedef struct configuracion {
  int resistencia_torres[MAX_RESISTENCIA_TORRES_C]; // [0] = Torre 1, [1] = Torre 2
  int enanos_inicio[MAX_DEFENSORES_C]; // [0] = Nivel 1, [1] = Nivel 2, [2] = Nivel 3, [3] = Nivel 4
  int elfos_inicio[MAX_DEFENSORES_C]; // [0] = Nivel 1, [1] = Nivel 2, [2] = Nivel 3, [3] = Nivel 4
  int enanos_extra[MAX_EXTRA_C]; // [0] = Cantidad, [1] = Costo Torre 1, [2] = Costo Torre 2
  int elfos_extra[MAX_EXTRA_C]; // [0] = Cantidad, [1] = Costo Torre 1, [2] = Costo Torre 2
  int animo_enanos[MAX_ANIMOS_C]; // [0] = %Fallo, [1] = %Criticos
  int animo_elfos[MAX_ANIMOS_C]; // [0] = %Fallo, [1] = %Criticos
  float velocidad_de_juego;
  char caminos[MAX_RUTA];
} configuracion_t;

/*
* Precondiciones: Debe recibir argumentos del main y su respectivo tope.
* Postcondiciones: Mostrara por pantalla la repeticion solicitada en caso de poder abrirla.
*/
void pasar_repeticion(int argc, char *argv[]);

/*
* Postcondiciones: Mostrara por pantalla los comandos disponibles para ejecutar el juego.
*/
void mostrar_comandos();

/*
* Precondiciones: Recibira un argumento ingresado en el main.
* Postcondiciones: Pondra en otra cadena el argumento sin la parte que señala que parametro se ingresó.
*/
void eliminar_indicador(char dato[MAX_DATO], char argumento[],int primera_letra);

/*
* Precondiciones: Debe recibir una ruta de archivo.
* Postcondiciones: Escribira, en caso de poder, el archivo ubicado en dicha ruta con los caminos creados por el usuario.
*/
void crear_caminos_personalizados(char ruta[MAX_RUTA]);

/*
* Precondiciones: Debe recibir una ruta de archivo.
* Postconidiones: Escribira, en caso de poder, el archivo ubicado en dicha ruta con las configuraciones creadas por el usuario.
*/
void crear_configuracion_personalizada(char ruta[MAX_RUTA]);

void mostrar_ranking(int argc, char *argv[]);

#endif
