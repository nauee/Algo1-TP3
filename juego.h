#ifndef __JUEGO_H__
#define __JUEGO_H__

/*
* Precondiciones: Debe recibir una ruta de configuracion y una de grabacion, o -1 en caso de no tener.
* Postcondiciones: Jugara el juego con la configuracion recibida (o con la por defecto en caso de no recibir)
* y grabara la partida en caso de que el usuario asi quiera.
*/
void jugar_juego(char ruta_config[MAX_RUTA], char ruta_grabacion[MAX_RUTA]);

#endif
