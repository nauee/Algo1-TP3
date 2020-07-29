#include "funcionalidades.h"
#include "juego.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define C_JUGAR "jugar"
#define C_REPETICION "poneme_la_repe"
#define C_CREAR_CAMINO "crear_camino"
#define C_CREAR_CONFIG "crear_configuracion"
#define C_RANKING "ranking"
#define STR_POR_DEFECTO "-1"
#define RANKING "ranking"
#define CSV ".csv"

/************************************************************************************************Extra************************************************************************************************/

/*
*	Precondiciones: Debe recibir una ruta de configuracion valida.
*	Postcondiciones: Modificara la ruta eliminando su extension.
*/
void eliminar_extension(char config[MAX_RUTA]){
	char *nombre;
	nombre = strtok(config,".");
	if(nombre != NULL){
		strcpy(config, nombre);
	}
}

/*
*	Precondiciones: Debe recibir un vector de argumentos del main y su tope.
*	Postcondiciones: Modificara, en caso de encontrar, la ruta de configuracion y de grabacion.
*/
void encontrar_valores_jugar(char ruta_config[MAX_RUTA], char ruta_grabacion[MAX_RUTA], char *argv[], int argc){
  int pos_rec = -1;
  int pos_config = -1;
  for(int i = 2; i < argc; i++){
    if(strncmp(argv[i],"grabacion=",10) == 0){
      pos_rec = i;
    }else if(strncmp(argv[i],"config=",7) == 0){
      pos_config = i;
    }
  }
  if(pos_rec == -1){
    strcpy(ruta_grabacion, STR_POR_DEFECTO);
  }else{
    eliminar_indicador(ruta_grabacion, argv[pos_rec],10);
  }
  if(pos_config == -1){
    strcpy(ruta_config, STR_POR_DEFECTO);
  }else{
    eliminar_indicador(ruta_config, argv[pos_config],7);
  }
}

/*
*	Precondiciones: Debe recibir un vector de argumentos del main y su tope.
*	Postcondiciones: Modificara, en caso de encontrar, la ruta de grabacion y la velocidad.
*/
void encontrar_valores_repeticion(float *velocidad, char ruta_grabacion[MAX_RUTA], char *argv[], int argc){
  int pos_rec = -1;
  int pos_vel = -1;
  for(int i = 2; i < argc; i++){
    if(strncmp(argv[i],"grabacion=",strlen("grabacion=")) == 0){
      pos_rec = i;
    }else if(strncmp(argv[i],"velocidad=",strlen("velocidad=")) == 0){
      pos_vel = i;
    }
  }
  if(pos_rec == -1){
    strcpy(ruta_grabacion, STR_POR_DEFECTO);
  }else{
    eliminar_indicador(ruta_grabacion, argv[pos_rec],10);
  }
  if(pos_vel != -1){
    char velocidad_str[MAX_RUTA];
    eliminar_indicador(velocidad_str, argv[pos_vel],10);
    *velocidad = (float) atof(velocidad_str);
  }
}

/*
*	Precondiciones: Debe recibir un vector de argumentos del main y su tope.
*	Postcondiciones: Modificara, en caso de encontrar, la ruta del ranking y la cantidad a listar.
*/
void encontrar_valores_ranking(int *cantidad_rank, char ruta_ranking[MAX_RUTA], char *argv[], int argc){
  int pos_config = -1;
  int pos_cantidad = -1;
  strcpy(ruta_ranking, RANKING);
  for(int i = 2; i < argc; i++){
    if(strncmp(argv[i],"config=",strlen("config=")) == 0){
      pos_config = i;
    }else if(strncmp(argv[i],"listar=",strlen("listar=")) == 0){
      pos_cantidad = i;
    }
  }
  if(pos_config != -1){
    char nombre_config[MAX_RUTA];
    eliminar_indicador(nombre_config, argv[pos_config],7);
    eliminar_extension(nombre_config);
    strcat(ruta_ranking, "_");
    strcat(ruta_ranking, nombre_config);
	}
	strcat(ruta_ranking, CSV);
  if(pos_cantidad != -1){
    char cantidad_cadena[MAX_RUTA];
    eliminar_indicador(cantidad_cadena,argv[pos_cantidad],7);
    *cantidad_rank = atoi(cantidad_cadena);
    if(*cantidad_rank < 1){
      *cantidad_rank = -1;
    }
  }
}

/************************************************************************************************ Main ***********************************************************************************************/

int main(int argc, char *argv[]){
  if(argc == 1){
    mostrar_comandos();
  }else{
    if(strcmp(argv[1],C_JUGAR) == 0){
      char ruta_config[MAX_RUTA];
      char ruta_grabacion[MAX_RUTA];
      encontrar_valores_jugar(ruta_config, ruta_grabacion, argv, argc);
      jugar_juego(ruta_config, ruta_grabacion);
    }else if(strcmp(argv[1],C_REPETICION) == 0){
      float velocidad = 1;
      char ruta_grabacion[MAX_RUTA];
      encontrar_valores_repeticion(&velocidad, ruta_grabacion, argv, argc);
      pasar_repeticion(velocidad, ruta_grabacion);
    }else if(strcmp(argv[1],C_CREAR_CAMINO) == 0){
      if(argc >= 3){
        crear_caminos_personalizados(argv[2]);
      }else{
        mostrar_comandos();
      }
    }else if(strcmp(argv[1],C_CREAR_CONFIG) == 0){
      if(argc >= 3){
        crear_configuracion_personalizada(argv[2]);
      }
    }else if(strcmp(argv[1],C_RANKING) == 0){
        int cantidad_rank = -1;
        char ruta_ranking[MAX_RUTA];
        encontrar_valores_ranking(&cantidad_rank, ruta_ranking, argv, argc);
        mostrar_ranking(cantidad_rank, ruta_ranking);
    }else{
      mostrar_comandos();
    }
  }
}

/*****************************************************************************************************************************************************************************************************/
