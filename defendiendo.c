#include "funcionalidades.h"
#include "juego.h"
#include <string.h>

#define C_JUGAR "jugar"
#define C_REPETICION "poneme_la_repe"
#define C_CREAR_CAMINO "crear_camino"
#define C_CREAR_CONFIG "crear_configuracion"
#define C_RANKING "ranking"

/************************************************************************************************ Main ***********************************************************************************************/

int main(int argc, char *argv[]){
  if(argc == 1){
    mostrar_comandos();
  }else{
    if(strcmp(argv[1],C_JUGAR) == 0){
      jugar_juego(argc, argv);
    }else if(strcmp(argv[1],C_REPETICION) == 0){
      pasar_repeticion(argc, argv);
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
        mostrar_ranking(argc, argv);
    }else{
      mostrar_comandos();
    }
  }
}

/*****************************************************************************************************************************************************************************************************/
