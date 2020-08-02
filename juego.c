#include "defendiendo_torres.h"
#include "animos.h"
#include "utiles.h"
#include "juego.h"
#include "funcionalidades.h"
#include <time.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/******************************************************************************************** Constantes *********************************************************************************************/

#define BLANCO "\033[0m"
#define AMARILLO "\033[1;33m"
#define ROJO "\033[0;31m"
#define L_ROJO "\033[1;31m"
#define VERDE "\033[1;32m"
#define L_VERDE "\033[0;32m"
#define MARRON "\033[0;33m"
#define NEGRO "\033[0;30m"
#define POR_DEFECTO -1
#define STR_POR_DEFECTO "-1"
#define MAX_NOMBRE 50
#define RANKING "ranking"
#define CSV ".csv"
#define FORMATO_CAMINO "%i;%i\n"
#define FORMATO_R_RANKING "%[^;];%i\n"
#define FORMATO_W_RANKING "%s;%i\n"
#define FORMATO_R_INDICADOR "%[^=]="
const int NIVEL_1 = 1;
const int NIVEL_2 = 2;
const int NIVEL_3 = 3;
const int NIVEL_4 = 4;
const int CANT_DEFENSORES_1 = 5;
const int CANT_DEFENSORES_2 = 5;
const int CANT_DEFENSORES_3 = 6;
const int CANT_DEFENSORES_4 = 8;
const char ELFOS = 'L';
const char ENANOS ='G';
const int POS_MIN = 0;
const int POS_MAX_1_2 = 14;
const int POS_MAX_3_4 = 19;
const int ENEMIGOS_NV_1 = 100;
const int ENEMIGOS_NV_2 = 200;
const int ENEMIGOS_NV_3 = 300;
const int ENEMIGOS_NV_4 = 500;
const int COSTO_DEF_EXTRA = 50;
const int JUGAR = 0;
const int CAMBIAR_VEL = 1;
const int SALIR = 2;
const char ARRIBA_MAY = 'W';
const char ARRIBA_MIN = 'w';
const char ABAJO_MAY = 'S';
const char ABAJO_MIN = 's';
const char IZQUIERDA_MAY = 'A';
const char IZQUIERDA_MIN = 'a';
const char DERECHA_MAY = 'D';
const char DERECHA_MIN = 'd';
const char ENTER = '\n';
const char BARRA_ESPAC = ' ';
const int OP_VEL_M_LENTA = 0;
const int OP_VEL_LENTA = 1;
const int OP_VEL_NORMAL = 2;
const int OP_VEL_RAPIDA = 3;
const int OP_VEL_M_RAPIDA = 4;
const float VEL_M_LENTA = 1.25;
const float VEL_LENTA = 1;
const float VEL_NORMAL = 0.75;
const float VEL_RAPIDA = 0.5;
const float VEL_M_RAPIDA = 0.25;
const int PERIOD_ENEM_1 = 25;
const int PERIOD_ENEM_2_3_4 = 50;
const int OP_SI = 0;
const int OP_NO = 1;
const int OP_ENANOS = 0;
const int OP_ELFOS = 1;
const int JUEGO_JUGANDO = 0;
const int JUEGO_PERDIDO = -1;
const int JUEGO_GANADO = 1;
const int NIVEL_GANADO = 1;
const int NIVEL_JUGANDO = 0;
const int TOPE_TABLERO_1_2 = 15;
const int TOPE_TABLERO_3_4 = 20;
const int MINIMO_CAMINO = 50;
const int NINGUN_DEFENSOR = 0;
const int NINGUN_ENEMIGO = 0;
const int NINGUN_ENANO_EXTRA = 0;
const int NINGUN_ELFO_EXTRA = 0;
const int VIDA_INICIAL_TORRES = 600;
const int ELFOS_INICIALES_EXTRA = 10;
const int ENANOS_INICIALES_EXTRA = 10;
const int SIN_COSTO = 0;
const int ELFOS_EXTRA = 10;
const int ENANOS_EXTRA = 10;

/******************************************************************************************* Presentacion ********************************************************************************************/

/*
*	Postcondiciones: Mostrara la introduccion al juego.
*/
void mostrar_dibujo_portada (){
	for(int i = 0; i < 4; i++){
		system("clear");
		printf(AMARILLO"                                o\n");
		printf("                             .-'|\n");
		printf("                             |-'|\n");
		printf("                                |   _.-'`.\n");
		printf("                               _|-''_.-'|.`.\n");
		printf("                              |:^.-'_.-'`.;.`.\n");
		printf("                              | `.'.   ,-'_.-'|\n");
		printf("                              |   + '-'.-'   J\n");
		printf("           __.            .d88| +. `.-' _-.  |\n");
		printf("      _.--'_..`.    .d88888888| ||] |  | J] J8b.\n");
		printf("   +:'' ,--'_.|`.`.d88888888888|-' J |  | J|.|888b.\n");
		printf("   | \\ \\-'_.--'_.-+888888888+'  _-F F +:    `88888bo.                  ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("________  _______   ________ _______   ________   ________  ___  _______   ________   ________  ________      \n");
		}
		printf("    L \\ +'_.--'   |88888+''  _.' J J J  `.    +8888888b.              ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("|\\   ___ \\|\\  ___ \\ |\\  _____\\\\  ___ \\ |\\   ___  \\|\\   ___ \\|\\  \\|\\  ___ \\ |\\   ___  \\|\\   ___ \\|\\   __  \\     \n");
		}
		printf("    L \\ +'_.--'   |88888+''  _.' J J J  `.    +8888888b.              ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\ \\  \\_|\\ \\ \\   __/|\\ \\  \\__/\\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\ \\   __/|\\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\|\\  \\    \n");
		}
		printf("    |  `+'   __   |8+''  _.-'    | | |    +    `+8888888._-'.          ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\ \\  \\ \\\\ \\ \\  \\_|/_\\ \\   __\\\\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\ \\\\ \\ \\  \\ \\  \\_|/_\\ \\  \\\\ \\  \\ \\  \\ \\\\ \\ \\  \\\\\\  \\   \n");
		}
		printf("  .d8L  L   / \\\\  J' _.-'        | | |     `.,   `+888+'^.-|.`.         ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\ \\  \\_\\\\ \\ \\  \\_|\\ \\ \\  \\_| \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\_\\\\ \\ \\  \\ \\  \\_|\\ \\ \\  \\\\ \\  \\ \\  \\_\\\\ \\ \\  \\\\\\  \\  \n");
		}
		printf(" d888|  |   F  FL J-'            F F F      /`/  _.-'_.-'_.+.`.`.        ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\ \\_______\\ \\_______\\ \\__\\   \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\__\\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\ \n");
		}
		printf("d88888L  L  |  \\L  L            J J J      /`/ `|. +'_.-'    `_+ `;       ");
		if(i == 0){
			printf("\n");
		}
		else if(i > 0){
			printf("\\|_______|\\|_______|\\|__|    \\|_______|\\|__| \\|__|\\|_______|\\|__|\\|_______|\\|__| \\|__|\\|_______|\\|_______| \n");
		}
		fflush(stdout);
		printf("888888J  |  K    \\ L         _.-+.|.'.    /`/   F `.`.     .-'_.-'J\n");
		printf("8888888|  L L\\    \\|     _.-'     '   `. /`/   J  ,_`.`..-'.-'    |            ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("___       ________  ________\n");
		}else if(i == 3){
			printf("___       ________  ________           _________  ________  ________  ________  _______   ________      \n");
		}
		printf("8888888PL | | \\    `._.-'               /`/    | || \\ `..-'      J.b          ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("|\\  \\     |\\   __  \\|\\   ____\\\n");
		}else if(i == 3){
			printf("|\\  \\     |\\   __  \\|\\   ____\\         |\\___   ___\\\\   __  \\|\\   __  \\|\\   __  \\|\\  ___ \\ |\\   ____\\    \n");
		}
		printf("8888888 |  L L `.    \\     _.-+.       /`/`.   L+`'  |  |        F88b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\ \\  \\    \\ \\  \\|\\  \\ \\  \\___|_\n");
		}else if(i == 3){
			printf("\\ \\  \\    \\ \\  \\|\\  \\ \\  \\___|_        \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\   __/|\\ \\  \\___|_ \n");
		}
		printf("8888888  L | |   \\   _:.--'_.-|.`.    '`/   >-'     .J J        |8888b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\ \\  \\    \\ \\   __  \\ \\_____  \\\n");
		}else if(i == 3){
			printf("\\ \\  \\    \\ \\   __  \\ \\_____  \\            \\ \\  \\ \\ \\  \\\\\\  \\ \\   _  _\\ \\   _  _\\ \\  \\_|/_\\ \\_____  \\  \n");
		}
		printf("8888888  |  L L   +:' _.--'_.-'.`.`.    _.-'    :'|' | |       JY88888b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\ \\  \\____\\ \\  \\ \\  \\|____|\\  \\\n");
		}else if(i == 3){
			printf("\\ \\  \\____\\ \\  \\ \\  \\|____|\\  \\            \\ \\  \\ \\ \\  \\\\\\  \\ \\  \\\\  \\\\ \\  \\\\  \\\\ \\  \\_|\\ \\|____|\\  \\  \n");
		}
		printf("8888888   L | |   J \\ \\_.-'     `.`.`.-'    :'|-'   J J        F Y88888b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\ \\_______\\ \\__\\ \\__\\____\\_\\  \\\n");
		}else if(i == 3){
			printf("\\ \\_______\\ \\__\\ \\__\\____\\_\\  \\            \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\\\ \\__\\\\ _\\\\ \\_______\\____\\_\\  \\ \n");
		}
		printf("Y888888    \\ L L   L \\ `.      _.-'_.-+ :'|-'       | |       |   Y88888b         ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\|_______|\\|__|\\|__|\\_________\\\n");
		}else if(i == 3){
			printf("\\|_______|\\|__|\\|__|\\_________\\            \\|__|  \\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|\\_________\\ \n");
		}
		printf("`888888b    \\| |   |  `. \\ _.-'_.-'   |-'          J J       J     Y88888b                           ");
		if(i < 2){
			printf("\n");
		}else if(i == 2){
			printf("\\|_________|\n");
		}else if(i == 3){
			printf("\\|_________|                                                          \\|_________|\n");
		}
		printf(" Y888888     +'\\   J    \\ '_.-'       F    ,-T'\\   | |    .-'      )888888\n");
		printf("  Y88888b.      \\   L    +'          J    /  | J  J J  .-'        .d888888\n");
		printf("   Y888888b      \\  |    |           |    F  '.|.-'+|-'         .d88888888\n");
		printf("    Y888888b      \\ J    |           F   J    -:              .od88888888P\n");
		printf("     Y888888b      \\ L   |          J    | .' ` \\d8888888888888888888888P\n");
		printf("      Y888888b      \\|   |          |  .-'`.  `\\ `+88888888888888888888P\n");
		printf("       Y888888b.     J   |          F-'     \\ ` \\ \\88888888888888888P'\n");
		printf("        Y8888888b     L  |         J       d8+.`\\  \\`+8888888888888P'\n");
		printf("         Y8888888b    |  |        .+      d8888\\  ` .'  `Y888888P'\n");
		printf("         `88888888b   J  |     .-'     .od888888\\.-'\n");
		printf("          Y88888888b   \\ |  .-'     d888888888P'\n");
		printf("          `888888888b   \\|-'       d88888888'\n");
		printf("           `Y88888888b            d8888888P'\n");
		printf("             Y88888888bo.      .od88888888\n");
		printf("             `8888888888888888888888888888\n");
		printf("              Y88888888888888888888888888P\n");
		printf("               `Y8888888888888888888888P'\n");
		printf("                 `Y8888888888888P'\n");
		printf("                      `Y88888P'\n");
		detener_el_tiempo(1);
	}
}

/******************************************************************************************* Iniciar nivel *******************************************************************************************/

/*
*	Postcondiciones: Devolvera la tecla pulsada por el usuario.
*/
int getch(void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= (unsigned int) ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

/*
*	Postcondiciones: Mostrara un mensaje de cargando.
*/
void mostrar_mensaje_cargando_simple(){
	printf(AMARILLO" -> Cargando .");
	for(int i = 0; i < 10; i++){
		printf(".");
		fflush(stdout);
		detener_el_tiempo(0.25);
	}
}

/*
*	Precondiciones: Debe recibir un nivel_actual valido (1,2,3,4).
*	Postcondiciones: Mostrara la introduccion del nivel que se haya ingresado.
*/
void mostrar_introduccion_nivel(int nivel_actual){
	mostrar_mensaje_cargando_simple();
	system("clear");
	printf(""AMARILLO"╔═════════════════════════════════════════════════════════╗\n");
	printf("║ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ║\n");
	printf("║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n");
	printf("║ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ║\n");
	printf("║ ░░░░░ ╔══════════════════════════════════════════╗ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ║                                          ║ ▒▒▒▒ ║\n");
	printf("║ ░░░░░ ║  ██    █   █   █     █   █▀▀▀▀   █       ║ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ║  █ █   █   █   █     █   █       █       ║ ▒▒▒▒ ║\n");
	printf("║ ░░░░░ ║  █  █  █   █    █   █    █■■■■   █       ║ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ║  █   █ █   █     █ █     █       █       ║ ▒▒▒▒ ║\n");
	printf("║ ░░░░░ ║  █    ██   █      █      █▄▄▄▄   █▄▄▄▄▄  ║ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ║                                          ║ ▒▒▒▒ ║\n");
	printf("║ ░░░░░ ║                                          ║ ░░░░ ║\n");
	if(nivel_actual == NIVEL_1){
		printf("║ ▒▒▒▒▒ ║                 ▀▀█▀▀                    ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║                   █                      ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║                   █                      ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║                   █                      ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║                 ▄▄█▄▄                    ║ ▒▒▒▒ ║\n");
	}else if(nivel_actual == NIVEL_2){
		printf("║ ▒▒▒▒▒ ║                ▀▀█▀▀▀█▀▀                 ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║                  █   █                   ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║                  █   █                   ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║                  █   █                   ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║                ▄▄█▄▄▄█▄▄                 ║ ▒▒▒▒ ║\n");
	}else if(nivel_actual == NIVEL_3){
		printf("║ ▒▒▒▒▒ ║             ▀▀█▀▀▀█▀▀▀█▀▀                ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║               █   █   █                  ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║               █   █   █                  ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║               █   █   █                  ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║             ▄▄█▄▄▄█▄▄▄█▄▄                ║ ▒▒▒▒ ║\n");
	}else if(nivel_actual == NIVEL_4){
		printf("║ ▒▒▒▒▒ ║            ▀▀█▀▀▀█▀▀▀▀▀█▀▀               ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║              █   █     █                 ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║              █    █   █                  ║ ▒▒▒▒ ║\n");
		printf("║ ░░░░░ ║              █     █ █                   ║ ░░░░ ║\n");
		printf("║ ▒▒▒▒▒ ║            ▄▄█▄▄▄▄▄▄█▄▄▄▄                ║ ▒▒▒▒ ║\n");
	}
	printf("║ ░░░░░ ║                                          ║ ░░░░ ║\n");
	printf("║ ▒▒▒▒▒ ╚══════════════════════════════════════════╝ ▒▒▒▒ ║\n");
	printf("║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n");
	printf("║ ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ║\n");
	printf("║ ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░ ║\n");
	printf("╚═════════════════════════════════════════════════════════╝"BLANCO"\n");

	detener_el_tiempo(2);
	system("clear");
}

/*
*	Precondiciones: Debe recibir un juego con caminos creados.
*	Postcondiciones: Devolvera true si los caminos no se juntan, y false si lo hacen.
*/
bool son_caminos_separados(juego_t juego){

	bool caminos_separados = true;
	int i = 0;

	while(caminos_separados == true && i < juego.nivel.tope_camino_1){
		for(int j = 0; j < juego.nivel.tope_camino_2; j++){
			if((juego.nivel.camino_1[i].fil == juego.nivel.camino_2[j].fil) && (juego.nivel.camino_1[i].col == juego.nivel.camino_2[j].col)){
				caminos_separados = false;
			}
		}
		i++;
	}

	return caminos_separados;
}

/*
*	Precondiciones: Debe recibir un archivo abierto que contenga el camino a leer.
*	Postcondiciones: Leera del archivo el camino y lo guardara en el vector camino con su respectivo tope.
*/
void leer_camino(FILE** arch_camino, coordenada_t camino[MAX_LONGITUD_CAMINO], int *tope_camino){
  coordenada_t casillero_camino;
  int leidos = fscanf(*arch_camino, FORMATO_CAMINO, &(casillero_camino.fil), &(casillero_camino.col));
  while(leidos == 2){
    camino[*tope_camino].fil = casillero_camino.fil;
    camino[*tope_camino].col = casillero_camino.col;
    (*tope_camino) ++;
    leidos = fscanf(*arch_camino, FORMATO_CAMINO, &(casillero_camino.fil), &(casillero_camino.col));
  }
}

/*
*	Precondiciones: Debera recibir un juego con un nivel valido (1,2,3,4) y un archivo valido.
*	Postcondiciones: Creara el o los caminos validos segun el nivel correspondiente o leera los creados por el usuario.
*/
void crear_caminos(juego_t *juego, FILE** arch_camino){

	coordenada_t entrada1;
	coordenada_t torre1;
	coordenada_t entrada2;
	coordenada_t torre2;
  if(!(*arch_camino)){
    if(juego -> nivel_actual == NIVEL_1){
      entrada1.fil = rand() % TOPE_TABLERO_1_2;
      entrada1.col = POS_MAX_1_2;
      torre1.fil = rand() % TOPE_TABLERO_1_2;
      torre1.col = POS_MIN;
    }else if(juego -> nivel_actual == NIVEL_2){
      entrada2.fil = rand() % TOPE_TABLERO_1_2;
      entrada2.col = POS_MIN;
      torre2.fil = rand() % TOPE_TABLERO_1_2;
      torre2.col = POS_MAX_1_2;
    }else if(juego -> nivel_actual == NIVEL_3){
      entrada1.fil = POS_MIN;
      entrada1.col = rand() % TOPE_TABLERO_3_4 / 2;
      torre1.fil = POS_MAX_3_4;
      torre1.col = rand() % TOPE_TABLERO_3_4 / 2;
      entrada2.fil = POS_MIN;
      entrada2.col = rand() % (TOPE_TABLERO_3_4 / 2) + (TOPE_TABLERO_3_4 / 2);
      torre2.fil = POS_MAX_3_4;
      torre2.col = rand() % (TOPE_TABLERO_3_4 / 2) + (TOPE_TABLERO_3_4 / 2);
    }else if(juego -> nivel_actual == NIVEL_4){
      entrada1.fil = POS_MAX_3_4;
      entrada1.col = rand() % TOPE_TABLERO_3_4 / 2;
      torre1.fil = POS_MIN;
      torre1.col = rand() % TOPE_TABLERO_3_4 / 2;

      entrada2.fil = POS_MAX_3_4;
      entrada2.col = rand() % (TOPE_TABLERO_3_4 / 2) + (TOPE_TABLERO_3_4 / 2);
      torre2.fil = POS_MIN;
      torre2.col = rand() % (TOPE_TABLERO_3_4 / 2) + (TOPE_TABLERO_3_4 / 2);
    }

    if(juego -> nivel_actual == NIVEL_1){
      obtener_camino(juego -> nivel.camino_1,&(juego -> nivel.tope_camino_1), entrada1, torre1);
      while(juego -> nivel.tope_camino_1 < MINIMO_CAMINO){
        obtener_camino(juego -> nivel.camino_1,&(juego -> nivel.tope_camino_1), entrada1, torre1);
      }
      juego -> nivel.tope_camino_2 = 0;
    }else if(juego -> nivel_actual == NIVEL_2){
      obtener_camino(juego -> nivel.camino_2,&(juego -> nivel.tope_camino_2), entrada2, torre2);
      while(juego -> nivel.tope_camino_2 < MINIMO_CAMINO){
        obtener_camino(juego -> nivel.camino_2,&(juego -> nivel.tope_camino_2), entrada2, torre2);
      }
      juego -> nivel.tope_camino_1 = 0;
    }else if(juego -> nivel_actual == NIVEL_3 || juego -> nivel_actual == NIVEL_4){
      obtener_camino(juego -> nivel.camino_1, &(juego -> nivel.tope_camino_1), entrada1, torre1);
      while(juego -> nivel.tope_camino_1 < MINIMO_CAMINO){
        obtener_camino(juego -> nivel.camino_1,&(juego -> nivel.tope_camino_1), entrada1, torre1);
      }
      obtener_camino(juego -> nivel.camino_2, &(juego -> nivel.tope_camino_2), entrada2, torre2);
      while(juego -> nivel.tope_camino_1 < MINIMO_CAMINO){
        obtener_camino(juego -> nivel.camino_2,&(juego -> nivel.tope_camino_2), entrada2, torre2);
      }
      while(!son_caminos_separados(*juego)){
        obtener_camino(juego -> nivel.camino_1, &(juego -> nivel.tope_camino_1), entrada1, torre1);
        while(juego -> nivel.tope_camino_1 < MINIMO_CAMINO){
          obtener_camino(juego -> nivel.camino_1,&(juego -> nivel.tope_camino_1), entrada1, torre1);
        }
        obtener_camino(juego -> nivel.camino_2, &(juego -> nivel.tope_camino_2), entrada2, torre2);
        while(juego -> nivel.tope_camino_1 < MINIMO_CAMINO){
          obtener_camino(juego -> nivel.camino_2,&(juego -> nivel.tope_camino_2), entrada2, torre2);
        }
      }
    }
  }else{
    juego -> nivel.tope_camino_1 = 0;
    juego -> nivel.tope_camino_2 = 0;
		int nivel_leyendo;
		fscanf(*arch_camino, "NIVEL=%i\n", &nivel_leyendo);
    if(nivel_leyendo == 1){
      fscanf(*arch_camino, "CAMINO=1\n");
      leer_camino(arch_camino, juego -> nivel.camino_1, &(juego -> nivel.tope_camino_1));
    }else if(nivel_leyendo == 2){
      fscanf(*arch_camino, "CAMINO=2\n");
      leer_camino(arch_camino, juego -> nivel.camino_2, &(juego -> nivel.tope_camino_2));
    }else if(nivel_leyendo == 3){
      fscanf(*arch_camino, "CAMINO=1\n");
      leer_camino(arch_camino, juego -> nivel.camino_1, &(juego -> nivel.tope_camino_1));
      fscanf(*arch_camino, "CAMINO=2\n");
      leer_camino(arch_camino, juego -> nivel.camino_2, &(juego -> nivel.tope_camino_2));
    }else if(nivel_leyendo == 4){
      fscanf(*arch_camino, "CAMINO=1\n");
      leer_camino(arch_camino, juego -> nivel.camino_1, &(juego -> nivel.tope_camino_1));
      fscanf(*arch_camino, "CAMINO=2\n");
      leer_camino(arch_camino, juego -> nivel.camino_2, &(juego -> nivel.tope_camino_2));
    }
  }
}

/*
*	Precondiciones: Debera recibir un movmiento valido (Izquierda, Derecha, Arriba o Abajo) y una posicion valida.
*	Postcondiciones: Devolvera true si es posible realizar el movimiento y false en el caso contrario.
*/
bool es_posible_moverse(coordenada_t posicion, int movimiento, int tope_mov){
	bool es_posible = true;
	if(movimiento == ARRIBA_MAY || movimiento == ARRIBA_MIN){
		if(posicion.fil == POS_MIN){
			es_posible = false;
		}
	}else if(movimiento == ABAJO_MAY || movimiento == ABAJO_MIN){
		if(posicion.fil == tope_mov){
			es_posible = false;
		}
	}else if(movimiento == IZQUIERDA_MAY || movimiento == IZQUIERDA_MIN){
		if(posicion.col == POS_MIN){
			es_posible = false;
		}
	}else if(movimiento == DERECHA_MAY || movimiento == DERECHA_MIN){
		if(posicion.col == tope_mov){
			es_posible = false;
		}
	}

	return es_posible;
}

/*
*	Precondiciones: Debera recibir un nivel con todas sus estructuras validas.
*	Postcondiciones: En caso de que sea posible ubicara el defensor en la posicion deseada.
*/
void eligio_posicion(nivel_t *nivel, int n_def, bool *eligio_pos){

	if(agregar_defensor(nivel, (nivel -> defensores[n_def].posicion), nivel -> defensores[n_def].tipo) == 0){
		*eligio_pos = true;
	}else{
		printf(AMARILLO" -> No podemos poner un defensor aqui, elige otro lugar\n");
	}
}

/*
*	Precondiciones: Debera recibir un juego con todas sus estructuras validas y un torres_t con los valores maximos iniciales.
*	Postcondiciones: Mostrara por pantalla el juego mientras se esta ubicando al defensor.
*/
void mostrar_modificado(juego_t *juego, torres_t maximos){
	juego -> nivel.tope_defensores ++;
	mostrar_juego(*juego, maximos);
	printf(AMARILLO" -> Movimiento con WASD\n");
	printf(AMARILLO" -> Selecciona con ESPACIO\n");
	juego -> nivel.tope_defensores --;
}

/*
*	Precondiciones: Debera recibir un juego con todas sus estructuras validas y un torres_t con los valores maximos iniciales.
*	Postcondiciones: Creara un nuevo defensor en la posicion que eliga el usuario.
*/
void crear_defensor(juego_t *juego, int n_def, torres_t maximos){

	int tope_mov;
	if(juego -> nivel_actual == NIVEL_1 || juego -> nivel_actual == NIVEL_2){
		tope_mov = POS_MAX_1_2;
	}else{
		tope_mov = POS_MAX_3_4;
	}
	juego -> nivel.defensores[n_def].posicion.fil = POS_MIN;
	juego -> nivel.defensores[n_def].posicion.col = POS_MIN;
	int tecla_pulsada;
	bool eligio_pos = false;
	mostrar_modificado(juego, maximos);
	while(!eligio_pos){
		tecla_pulsada = getch();
		if(tecla_pulsada == ARRIBA_MAY || tecla_pulsada == ARRIBA_MIN){
			if(es_posible_moverse(juego -> nivel.defensores[n_def].posicion, tecla_pulsada, tope_mov)){
				(juego -> nivel.defensores[n_def].posicion.fil) --;
			}
			mostrar_modificado(juego, maximos);
		}else if(tecla_pulsada == ABAJO_MAY || tecla_pulsada == ABAJO_MIN){
			if(es_posible_moverse(juego -> nivel.defensores[n_def].posicion, tecla_pulsada, tope_mov)){
				(juego -> nivel.defensores[n_def].posicion.fil) ++;
			}
			mostrar_modificado(juego, maximos);
		}else if(tecla_pulsada == IZQUIERDA_MAY || tecla_pulsada == IZQUIERDA_MIN){
			if(es_posible_moverse(juego -> nivel.defensores[n_def].posicion, tecla_pulsada, tope_mov)){
				(juego -> nivel.defensores[n_def].posicion.col) --;
			}
			mostrar_modificado(juego, maximos);
		}else if(tecla_pulsada == DERECHA_MAY || tecla_pulsada == DERECHA_MIN){
			if(es_posible_moverse(juego -> nivel.defensores[n_def].posicion, tecla_pulsada, tope_mov)){
				(juego -> nivel.defensores[n_def].posicion.col) ++;
			}
			mostrar_modificado(juego, maximos);
		}else if(tecla_pulsada == BARRA_ESPAC){
			eligio_posicion(&(juego -> nivel), n_def, &eligio_pos);
		}
	}
}

/*
*	Precondiciones: Sea un nivel valido (1,2,3,4) y un camino valido y una configuracion valida.
*	Postcondiciones: Pondra los defensores en donde el usuario lo decida, siempre y cuando sea posible.
*/
void poner_defensores(juego_t *juego, configuracion_t config){
	system("clear");
	torres_t maximos;
	maximos.resistencia_torre_1 = config.resistencia_torres[0];
	maximos.resistencia_torre_2 = config.resistencia_torres[1];
	maximos.enanos_extra = config.enanos_extra[0];
	maximos.elfos_extra = config.elfos_extra[0];
	juego -> nivel.tope_defensores = NINGUN_DEFENSOR;
	if(juego -> nivel_actual == NIVEL_1){
		for(int i = 0; i < config.enanos_inicio[0]; i++){
			juego -> nivel.defensores[i].tipo = ENANOS;
			crear_defensor(juego, i, maximos);
		}
    for(int i = config.enanos_inicio[0]; i < config.enanos_inicio[0] + config.elfos_inicio[0]; i++){
      juego -> nivel.defensores[i].tipo = ELFOS;
			crear_defensor(juego, i, maximos);
    }
	}else if(juego -> nivel_actual == NIVEL_2){
    for(int i = 0; i < config.enanos_inicio[1]; i++){
			juego -> nivel.defensores[i].tipo = ENANOS;
			crear_defensor(juego, i, maximos);
		}
    for(int i = config.enanos_inicio[1]; i < config.enanos_inicio[1] + config.elfos_inicio[1]; i++){
      juego -> nivel.defensores[i].tipo = ELFOS;
			crear_defensor(juego, i, maximos);
    }
	}else if(juego -> nivel_actual == NIVEL_3){
    for(int i = 0; i < config.enanos_inicio[2]; i++){
			juego -> nivel.defensores[i].tipo = ENANOS;
			crear_defensor(juego, i, maximos);
		}
    for(int i = config.enanos_inicio[2]; i < config.enanos_inicio[2] + config.elfos_inicio[2]; i++){
      juego -> nivel.defensores[i].tipo = ELFOS;
			crear_defensor(juego, i, maximos);
    }
	}else{
    for(int i = 0; i < config.enanos_inicio[3]; i++){
			juego -> nivel.defensores[i].tipo = ENANOS;
			crear_defensor(juego, i, maximos);
		}
    for(int i = config.enanos_inicio[3]; i < config.enanos_inicio[3] + config.elfos_inicio[3]; i++){
      juego -> nivel.defensores[i].tipo = ELFOS;
			crear_defensor(juego, i, maximos);
    }
	}
}

/*
*	Precondiciones: Debe recibir un juego con un nivel valido (1,2,3,4).
*	Postcondiciones: Modificara el maximo de enemigos segun el nivel correspondiente e inicializara el tope de enemigos a 0.
*/
void inicializar_enemigos(juego_t *juego){
	if(juego -> nivel_actual == NIVEL_1){
		juego -> nivel.max_enemigos_nivel = ENEMIGOS_NV_1;
	}else if(juego -> nivel_actual == NIVEL_2){
		juego -> nivel.max_enemigos_nivel = ENEMIGOS_NV_2;
	}else if(juego -> nivel_actual == NIVEL_3){
		juego -> nivel.max_enemigos_nivel = ENEMIGOS_NV_3;
	}else if(juego -> nivel_actual == NIVEL_4){
		juego -> nivel.max_enemigos_nivel = ENEMIGOS_NV_4;
	}

	juego -> nivel.tope_enemigos = NINGUN_ENEMIGO;
}

/*
*	Precondiciones: Debe recibir un juego con un nivel valido (1,2,3,4), una configuracion valida y un archivo de caminos valido.
*	Postcondiciones: Iniciara el nivel correspondiente.
*/
void iniciar_nivel(juego_t *juego, configuracion_t config, FILE** arch_camino){
	mostrar_introduccion_nivel(juego -> nivel_actual);
	crear_caminos(juego, arch_camino);
  inicializar_enemigos(juego);
	poner_defensores(juego, config);
}

/*************************************************************************************** Poner nuevo defensor ****************************************************************************************/

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Devolvera true si se llegó a la cantidad indicada para poner un nuevo defensor, y false si no se llegó.
*/
bool es_posible_poner_nuevo_defensor(juego_t juego){
	bool es_posible = false;
	int cada_cuanto_def_extra = 0;
	if(juego.nivel_actual == NIVEL_1){
		cada_cuanto_def_extra = PERIOD_ENEM_1;
	}else{
		cada_cuanto_def_extra = PERIOD_ENEM_2_3_4;
	}

	if(((juego.nivel.tope_enemigos % cada_cuanto_def_extra) == 0) && (juego.nivel.tope_enemigos != 0) && (juego.nivel.tope_enemigos != juego.nivel.max_enemigos_nivel)
	 && (juego.torres.elfos_extra > 0 || juego.torres.enanos_extra > 0)){
			es_posible = true;
	}

	return es_posible;
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas, una configuracion y un tipo de defensor valido (ENANO o ELFO).
*	Postcondiciones: Devolvera true si el usuario costear un defensor extra del tipo especificado.
*/
bool puede_costear_defensor(juego_t juego, configuracion_t config, char tipo_defensor){
	bool puede_costear = false;
	if(tipo_defensor == ENANOS){
		if((juego.torres.resistencia_torre_1 > config.enanos_extra[1]) && (juego.torres.resistencia_torre_2 > config.enanos_extra[2])){
			puede_costear = true;
		}
	}else{
		if((juego.torres.resistencia_torre_1 > config.elfos_extra[1]) && (juego.torres.resistencia_torre_2 > config.elfos_extra[2])){
			puede_costear = true;
		}
	}
	return puede_costear;
}

/*
*	Precondiciones: Debe recibir una opcion valida (0 (Si) o 1 (No))
*	Postcondiciones: Confirmara la desicion del usuario sobre si quiere o no un nuevo defensor.
*/
void elegir_si_no(int opcion_actual, bool *entro_a_menu, bool *quiere_defensor){
	if(opcion_actual == OP_SI){
		*quiere_defensor = true;
		*entro_a_menu = true;
	}else if(opcion_actual == OP_NO){
		*quiere_defensor = false;
		*entro_a_menu = true;
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas, una configuracion valida y un torres_t con los valores maximos iniciales.
*	Postcondiciones: Mostrara el menu para elegir si o no.
*/
void actualizar_menu_si_no(juego_t juego, int *opcion_actual, torres_t maximos, configuracion_t config){
	if(*opcion_actual == OP_SI - 1){
		*opcion_actual = OP_NO;
	}else if(*opcion_actual == OP_NO + 1){
		*opcion_actual = OP_SI;
	}
	system("clear");

	mostrar_juego(juego, maximos);
	if(juego.torres.enanos_extra > NINGUN_DEFENSOR && juego.torres.elfos_extra > NINGUN_DEFENSOR && puede_costear_defensor(juego, config, ENANOS) && puede_costear_defensor(juego, config, ELFOS)){
			printf(""AMARILLO" -> Tenes disponible un enano o un elfo extra para ubicar"VERDE"\n");
			printf(""AMARILLO" -> Quieres poner un defensor extra?\n");
		}else if(juego.torres.enanos_extra > NINGUN_DEFENSOR && puede_costear_defensor(juego, config, ENANOS)){
			printf(""AMARILLO" -> Tenes disponible un enano extra para ubicar"VERDE"\n");
			printf(""AMARILLO" -> Quieres poner un enano extra? || Costo ( Torre 1 -> %i || Torre 2 -> %i )\n", config.enanos_extra[1], config.enanos_extra[2]);
		}else{
			printf(""AMARILLO" -> Tenes disponible un elfo extra para ubicar"VERDE"\n");
			printf(""AMARILLO" -> Quieres poner un elfo extra? || Costo ( Torre 1 -> %i || Torre 2 -> %i )\n", config.elfos_extra[1], config.elfos_extra[2]);
	}

	if(*opcion_actual == OP_SI){
		printf(AMARILLO" -> SI\n");
	}else{
		printf(AMARILLO"    SI\n");
	}
	if(*opcion_actual == 1){
		printf(AMARILLO" -> NO\n");
	}else{
		printf(AMARILLO"    NO\n");
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas, una configuracion valida y un torres_t con los valores maximos iniciales.
*	Postcondiciones: Modificara el valor de quiere_defensor segun si el usuario quiere o no (true si quiere, false si no).
*/
void preguntar_si_quiere_defensor(juego_t juego, bool *quiere_defensor, torres_t maximos, configuracion_t config){
	int opcion_actual = OP_SI;
	int tecla_pulsada;
	bool entro_a_menu = false;
	actualizar_menu_si_no(juego, &opcion_actual, maximos, config);
	while(!entro_a_menu){
		tecla_pulsada = getch();
		if(tecla_pulsada == ARRIBA_MAY || tecla_pulsada == ARRIBA_MIN){
			opcion_actual --;
			actualizar_menu_si_no(juego, &opcion_actual, maximos, config);
		}else if(tecla_pulsada == ABAJO_MAY || tecla_pulsada == ABAJO_MIN){
			opcion_actual ++;
			actualizar_menu_si_no(juego, &opcion_actual, maximos, config);
		}else if(tecla_pulsada == ENTER){
			elegir_si_no(opcion_actual,&entro_a_menu,quiere_defensor);
		}
	}
}

/*
*	Precondiciones: Debe recibir una opcion valida (0 (Enano) o 1 (Elfo)).
*	Postcondiciones: Confirmara el tipo de defensor elegido por el usuario.
*/
void confirmar_tipo(int opcion_actual, bool *entro_a_menu, char *tipo_defensor){
	if(opcion_actual == OP_ENANOS){
		*tipo_defensor = ENANOS;
		*entro_a_menu = true;
	}else if(opcion_actual == OP_ELFOS){
		*tipo_defensor = ELFOS;
		*entro_a_menu = true;
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas, una configuracion valida y un torres_t con los valores maximos iniciales.
*	Postcondiciones: Mostrara el menu de seleccion del tipo de defensor.
*/
void actualizar_menu_tipo(juego_t juego, int *opcion_actual, torres_t maximos, configuracion_t config){
	if(*opcion_actual == OP_ENANOS - 1){
		*opcion_actual = OP_ELFOS;
	}else if(*opcion_actual == OP_ELFOS + 1){
		*opcion_actual = OP_ENANOS;
	}
	system("clear");
	mostrar_juego(juego, maximos);
	printf(""AMARILLO" -> Quieres un enano o un elfo extra?\n");
	if(*opcion_actual == OP_ENANOS){
		printf(AMARILLO" -> Enano || Costo ( Torre 1 -> %i || Torre 2 -> %i )\n", config.enanos_extra[1], config.enanos_extra[2]);
	}else{
		printf(AMARILLO"    Enano || Costo ( Torre 1 -> %i || Torre 2 -> %i )\n", config.enanos_extra[1], config.enanos_extra[2]);
	}
	if(*opcion_actual == OP_ELFOS){
		printf(AMARILLO" -> Elfo  || Costo ( Torre 1 -> %i || Torre 2 -> %i )\n", config.elfos_extra[1], config.elfos_extra[2]);
	}else{
		printf(AMARILLO"    Elfo  || Costo ( Torre 1 -> %i || Torre 2 -> %i )\n", config.elfos_extra[1], config.elfos_extra[2]);
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas, una configuracion valida y un torres_t con los valores maximos iniciales.
*	Postcondiciones: Modificara el tipo de defensor por el elegido por el usuario.
*/
void obtener_tipo_defensor(juego_t juego, char *tipo_defensor, torres_t maximos, configuracion_t config){
	int opcion_actual = OP_ENANOS;
	int tecla_pulsada;
	bool entro_a_menu = false;
	if(juego.torres.enanos_extra > NINGUN_ENANO_EXTRA && juego.torres.elfos_extra > NINGUN_ELFO_EXTRA && puede_costear_defensor(juego, config, ENANOS) && puede_costear_defensor(juego, config, ELFOS)){
		actualizar_menu_tipo(juego, &opcion_actual, maximos, config);
		while(!entro_a_menu){
			tecla_pulsada = getch();
			if(tecla_pulsada == ARRIBA_MAY || tecla_pulsada == ARRIBA_MIN){
				opcion_actual --;
				actualizar_menu_tipo(juego, &opcion_actual, maximos, config);
			}else if(tecla_pulsada == ABAJO_MAY || tecla_pulsada == ABAJO_MIN){
				opcion_actual ++;
				actualizar_menu_tipo(juego, &opcion_actual, maximos, config);
			}else if(tecla_pulsada == ENTER){
				confirmar_tipo(opcion_actual,&entro_a_menu,tipo_defensor);
			}
		}
	}else if(juego.torres.enanos_extra > NINGUN_ENANO_EXTRA && puede_costear_defensor(juego, config, ENANOS)){
		*tipo_defensor = ENANOS;
	}else{
		*tipo_defensor = ELFOS;
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas y un tipo de defensor valido (Enano o Elfo) y una configuracion valida.
*	Postcondiciones: Descontara la resistencia que ocasiona crear un defensor nuevo a la torre 1 o 2 segun corresponda.
*/
void descontar_resistencia_torres(juego_t *juego, char tipo_defensor, configuracion_t config){
	if(tipo_defensor == ENANOS){
		juego -> torres.resistencia_torre_1 -= config.enanos_extra[1];
		juego -> torres.resistencia_torre_2 -= config.enanos_extra[2];
	}else{
		juego -> torres.resistencia_torre_1 -= config.elfos_extra[1];
		juego -> torres.resistencia_torre_2 -= config.elfos_extra[2];
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas y un tipo de defensor valido (Enano o Elfo).
*	Postcondiciones: Descontara en 1 a los enanos extra disponibles o a los enanos extra disponibles segun corresponda.
*/
void descontar_un_defensor_extra(juego_t *juego, char tipo_defensor){
	if(tipo_defensor == ENANOS){
		(juego -> torres.enanos_extra) --;
	}else{
		(juego -> torres.elfos_extra) --;
	}
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas y una configuracion valida.
*	Postcondiciones: Ubicara un nuevo defensor si el usuario lo quiere.
*/
void poner_nuevo_defensor(juego_t *juego, configuracion_t config){
	torres_t maximos;
	maximos.resistencia_torre_1 = config.resistencia_torres[0];
	maximos.resistencia_torre_2 = config.resistencia_torres[1];
	maximos.enanos_extra = config.enanos_extra[0];
	maximos.elfos_extra = config.elfos_extra[0];
	if(es_posible_poner_nuevo_defensor(*juego) && (puede_costear_defensor(*juego, config, ENANOS) || puede_costear_defensor(*juego, config, ELFOS))){
		bool quiere_defensor;
		char tipo_defensor;
		preguntar_si_quiere_defensor(*juego, &quiere_defensor, maximos, config);
		if(quiere_defensor){
			obtener_tipo_defensor(*juego, &tipo_defensor, maximos, config);
			juego -> nivel.defensores[juego -> nivel.tope_defensores].tipo = tipo_defensor;
			crear_defensor(juego, juego -> nivel.tope_defensores, maximos);
			descontar_resistencia_torres(juego, tipo_defensor, config);
			descontar_un_defensor_extra(juego, tipo_defensor);
		}
	}
}

/************************************************************************************* Pasar al siguiente nivel **************************************************************************************/

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas, una configuracion valida y un archivo de caminos valido.
*	Postcondiciones: Pasara al siguiente nivel con todos sus valores inicializados.
*/
void pasar_al_siguiente_nivel(juego_t *juego, configuracion_t config, FILE** arch_camino){
	torres_t maximos;
	maximos.resistencia_torre_1 = config.resistencia_torres[0];
	maximos.resistencia_torre_2 = config.resistencia_torres[1];
	maximos.enanos_extra = config.enanos_extra[0];
	maximos.elfos_extra = config.elfos_extra[0];
	(juego -> nivel_actual) ++;
	iniciar_nivel(juego, config, arch_camino);
	mostrar_juego(*juego, maximos);
}

/****************************************************************************************** Finalizar juego ******************************************************************************************/

/*
*	Postcondiciones: Mostrara la pantalla final con el mensaje de que se ganó el juego.
*/
void mostrar_que_gano(){
	system("clear");
	printf(AMARILLO"                                                                                        	 |>>>\n");
	printf(AMARILLO"	                                                                                         |\n");
	printf(AMARILLO"	                                                                                     _  _|_  _\n");
	printf(AMARILLO"	                                                                                    |;|_|;|_|;|\n");
	printf(AMARILLO"	                                                                                    \\\\.    .  /\n");
	printf(AMARILLO"	    ___      ___ ___  ________ _________  ________  ________  ___  ________          \\\\:  .  /\n");
	printf(AMARILLO"	   |\\  \\    /  /|\\  \\|\\   ____\\\\___   ___\\\\   __  \\|\\   __  \\|\\  \\|\\   __  \\          ||:   |\n");
	printf(AMARILLO"	   \\ \\  \\  /  / | \\  \\ \\  \\___\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\ \\  \\|\\  \\         ||:.  |\n");
	printf(AMARILLO"	    \\ \\  \\/  / / \\ \\  \\ \\  \\       \\ \\  \\ \\ \\  \\\\\\  \\ \\   _  _\\ \\  \\ \\   __  \\        ||:  .|\n");
	printf(AMARILLO"	     \\ \\    / /   \\ \\  \\ \\  \\____   \\ \\  \\ \\ \\  \\\\\\  \\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\       ||:   |       \\,/\n");
	printf(AMARILLO"	      \\ \\__/ /     \\ \\__\\ \\_______\\  \\ \\__\\ \\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\__\\      ||: , |            /`\\\n");
	printf(AMARILLO"	       \\|__|/       \\|__|\\|_______|   \\|__|  \\|_______|\\|__|\\|__|\\|__|\\|__|\\|__|      ||:   |\n");
	printf(AMARILLO"	                                                                                      ||: . |\n");
	printf(AMARILLO"	                                                       __                            _||_   |\n");
	printf(AMARILLO"	            ____---_      -~~__               ____--`~    '--~~__            __ ----~    ~`---,              ___\n");
	printf(AMARILLO"	   --~_--~--~       '--~~'       ~---__  -~--~                   ~---__ ,--~'                  ~~----_____-~'   `~----~~\n");
}

/*
*	Postcondiciones: Mostrara la pantalla final con el mensaje de que se perdió el juego.
*/
void mostrar_que_perdio(){
	system("clear");
	printf(AMARILLO"	                        ________  _______   ________  ________  ________  _________  ________\n");
	printf(AMARILLO"	                       |\\   ___ \\|\\  ___ \\ |\\   __  \\|\\   __  \\|\\   __  \\|\\___   ___\\\\   __  \\\n");
	printf(AMARILLO"	        _.---,._,'     \\ \\  \\_|\\ \\ \\   __/|\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\  \\|\\  \\\n");
	printf(AMARILLO"	       /' _.--.<        \\ \\  \\ \\\\ \\ \\  \\_|/_\\ \\   _  _\\ \\   _  _\\ \\  \\\\\\  \\   \\ \\  \\ \\ \\   __  \\\n");
	printf(AMARILLO"	         /'     `'       \\ \\  \\_\\\\ \\ \\  \\_|\\ \\ \\  \\\\  \\\\ \\  \\\\  \\\\ \\  \\\\\\  \\   \\ \\  \\ \\ \\  \\ \\  \\\n");
	printf(AMARILLO"	       /' _.---._____     \\ \\_______\\ \\_______\\ \\__\\\\ _\\\\ \\__\\\\ _\\\\ \\_______\\   \\ \\__\\ \\ \\__\\ \\__\\\n");
	printf(AMARILLO"	       \\.'   ___, .-'`     \\|_______|\\|_______|\\|__|\\|__|\\|__|\\|__|\\|_______|    \\|__|  \\|__|\\|__|\n");
	printf(AMARILLO"	           /'    \\\\\n");
	printf(AMARILLO"	         /'       `-.\n");
	printf(AMARILLO"	        |                                     _____\n");
	printf(AMARILLO"	        |                                    /~/~   ~\\\n");
	printf(AMARILLO"	        |                                   | |       \\\n");
	printf(AMARILLO"	        |                                   \\ \\        \\\n");
	printf(AMARILLO"	        |                                    \\ \\        \\\n");
	printf(AMARILLO"	        |                                   --\\ \\       .\\''                   />______________\n");
	printf(AMARILLO"	         \\                                 --==\\ \\        \\            [:]XXXX]| _____________/\\|\n");
	printf(AMARILLO"	   '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''\n");
}

/*
*	Precondiciones: Debe recibir una configuracion valida, y una cantidad de orcos muertos valida (Mayor a 0).
*	Postcondiciones: Devolvera el puntaje obtenido en el juego.
*/
int puntaje_segun_jugada(configuracion_t config, int orcos_muertos){
	int numerador = orcos_muertos * 1000;
	int denominador = config.resistencia_torres[0] + config.resistencia_torres[1] + config.enanos_inicio[0] + config.enanos_inicio[1] + config.enanos_inicio[2] + config.enanos_inicio[3] + config.elfos_inicio[0] + config.elfos_inicio[1] + config.elfos_inicio[2] + config.elfos_inicio[3] + config.enanos_extra[0] + config.elfos_extra[0];
	return (numerador / denominador);
}

/*
*	Precondiciones: Debe recibir un puntaje valido, una ruta valida y un nombre del jugador valido.
*	Postcondiciones: Escribira en el archivo encontrado en la ruta especificada el puntaje obtenido por el jugador.
*/
void escribir_archivo_puntaje(int puntaje, char ruta_ranking[MAX_RUTA], char nombre_jugador[MAX_NOMBRE]){

		FILE* ranking_viejo = fopen(ruta_ranking, "r");
		if(!ranking_viejo){
			FILE* ranking_act = fopen(ruta_ranking, "w");
			fprintf(ranking_act, FORMATO_W_RANKING, nombre_jugador, puntaje);
			fclose(ranking_act);
			return;
		}
		FILE* ranking_act = fopen("temp_ranking.csv", "w");
		if(!ranking_act){
			printf("ERROR -> No puedo escribir este archivo\n");
			return;
		}
		char nom_leyendo[MAX_NOMBRE];
		int punt_leyendo;
		int leidos = fscanf(ranking_viejo, FORMATO_R_RANKING, nom_leyendo, &punt_leyendo);
		while(leidos == 2 && punt_leyendo > puntaje){
			fprintf(ranking_act, FORMATO_W_RANKING, nom_leyendo, punt_leyendo);
			leidos = fscanf(ranking_viejo, FORMATO_R_RANKING, nom_leyendo, &punt_leyendo);
		}
		if(leidos != 2){
			fprintf(ranking_act, FORMATO_W_RANKING, nombre_jugador, puntaje);
		}else{
			if(punt_leyendo == puntaje){
				if(strcmp(nombre_jugador, nom_leyendo) < 0){
					fprintf(ranking_act, FORMATO_W_RANKING, nombre_jugador, puntaje);
					fprintf(ranking_act, FORMATO_W_RANKING, nom_leyendo, punt_leyendo);
				}else{
					fprintf(ranking_act, FORMATO_W_RANKING, nom_leyendo, punt_leyendo);
					fprintf(ranking_act, FORMATO_W_RANKING, nombre_jugador, puntaje);
				}
			}else{
				fprintf(ranking_act, FORMATO_W_RANKING, nombre_jugador, puntaje);
				fprintf(ranking_act, FORMATO_W_RANKING, nom_leyendo, punt_leyendo);
			}
			leidos = fscanf(ranking_viejo, FORMATO_R_RANKING, nom_leyendo, &punt_leyendo);
			while(leidos == 2){
				fprintf(ranking_act, FORMATO_W_RANKING, nom_leyendo, punt_leyendo);
				leidos = fscanf(ranking_viejo, FORMATO_R_RANKING, nom_leyendo, &punt_leyendo);
			}
		}
		fclose(ranking_viejo);
		rename("temp_ranking.csv", ruta_ranking);
		fclose(ranking_act);
}

/*
*	Precondiciones: Debe recibir un puntaje valido y un nombre de configuracion y de jugador validos.
*	Postcondiciones: Escribira en la ruta formada por el nombre de la configuracion, el puntaje del jugador.
*/
void escribir_puntaje(int puntaje, char nombre_config[MAX_NOMBRE], char nombre_jugador[MAX_NOMBRE]){
	char ruta_ranking[MAX_RUTA];
	strcpy(ruta_ranking, RANKING);
	if(strcmp(nombre_config, STR_POR_DEFECTO) == 0){
		strcat(ruta_ranking, CSV);
		escribir_archivo_puntaje(puntaje, ruta_ranking, nombre_jugador);
	}else{
		strcat(ruta_ranking, "_");
		strcat(ruta_ranking, nombre_config);
		strcat(ruta_ranking, CSV);
		escribir_archivo_puntaje(puntaje, ruta_ranking, nombre_jugador);
	}
}

/*
*	Postcondiciones: Modificara el nombre por el ingresado por el jugador.
*/
void pedir_nombre(char nombre_jugador[MAX_NOMBRE]){
	printf(AMARILLO"                                       ╔═══════════════════════════════════╗\n");
	printf(AMARILLO"                                       ║           FIN DEL JUEGO           ║\n");
	printf(AMARILLO"                                       ║         Di tu nombre para         ║\n");
	printf(AMARILLO"                                       ║        recordar tu hazaña!!       ║\n");
	printf(AMARILLO"                                       ╚═══════════════════════════════════╝\n");
	printf(AMARILLO"                                         -> "VERDE);
	scanf("%[^\n]",nombre_jugador);
	printf(AMARILLO"\n\n\n\n\n\n\n");
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Finalizara el juego, escribiendo el ranking y mostrando la pantalla final de victoria o derrota segun el caso.
*/
void finalizar_juego(juego_t juego, configuracion_t config, char nombre_config[MAX_NOMBRE]){
	if(estado_juego(juego) == JUEGO_GANADO){
		int orcos_muertos = ENEMIGOS_NV_1 + ENEMIGOS_NV_2 + ENEMIGOS_NV_3 + ENEMIGOS_NV_4;
		char nombre_jugador[MAX_NOMBRE];
		mostrar_que_gano();
		detener_el_tiempo(2);
		pedir_nombre(nombre_jugador);
		int puntaje = puntaje_segun_jugada(config, orcos_muertos);
		escribir_puntaje(puntaje, nombre_config, nombre_jugador);
	}else if(estado_juego(juego) == JUEGO_PERDIDO){
		int orcos_muertos;
		if(juego.nivel_actual == NIVEL_1){
			orcos_muertos = NINGUN_ENEMIGO;
		}else if(juego.nivel_actual == NIVEL_2){
			orcos_muertos = ENEMIGOS_NV_1;
		}else if(juego.nivel_actual == NIVEL_3){
			orcos_muertos = ENEMIGOS_NV_1 + ENEMIGOS_NV_2;
		}else{
			orcos_muertos = ENEMIGOS_NV_1 + ENEMIGOS_NV_2 + ENEMIGOS_NV_3;
		}
		for(int i = 0; i < juego.nivel.tope_enemigos; i++){
			if(juego.nivel.enemigos[i].vida <= 0){
				orcos_muertos ++;
			}
		}
		int puntaje = puntaje_segun_jugada(config, orcos_muertos);
		char nombre_jugador[MAX_NOMBRE];
		mostrar_que_perdio();
		pedir_nombre(nombre_jugador);
		escribir_puntaje(puntaje, nombre_config,nombre_jugador);
	}
}

/********************************************************************************************** Jugar juego ******************************************************************************************/

/*
* Postcondiciones: Llenara la configuracion con sus valores por defecto.
*/
void llenar_config_defecto(configuracion_t *config){
	config -> resistencia_torres[0] = VIDA_INICIAL_TORRES;
	config -> resistencia_torres[1] = VIDA_INICIAL_TORRES;
	config -> enanos_inicio[0] = CANT_DEFENSORES_1;
	config -> enanos_inicio[1] = NINGUN_DEFENSOR;
	config -> enanos_inicio[2] = CANT_DEFENSORES_3 / 2;
	config -> enanos_inicio[3] = CANT_DEFENSORES_4 / 2;
	config -> elfos_inicio[0] = NINGUN_DEFENSOR;
	config -> elfos_inicio[1] = CANT_DEFENSORES_2;
	config -> elfos_inicio[2] = CANT_DEFENSORES_3 / 2;
	config -> elfos_inicio[3] = CANT_DEFENSORES_4 / 2;
	config -> enanos_extra[0] = ENANOS_EXTRA;
	config -> enanos_extra[1] = COSTO_DEF_EXTRA;
	config -> enanos_extra[2] = SIN_COSTO;
	config -> elfos_extra[0] = ELFOS_EXTRA;
	config -> elfos_extra[1] = SIN_COSTO;
	config -> elfos_extra[2] = COSTO_DEF_EXTRA;
	config -> animo_enanos[0] =  POR_DEFECTO;
	config -> animo_enanos[1] =  POR_DEFECTO;
	config -> animo_elfos[0] =  POR_DEFECTO;
	config -> animo_elfos[1] =  POR_DEFECTO;
	config -> velocidad_de_juego = VEL_NORMAL;
	strcpy(config -> caminos, STR_POR_DEFECTO);
}

/*
*	Precondiciones: Debe recibir un archivo valido (en caso de estar abierto).
* Postcondiciones: Llenara la configuracion con la leida en el archivo o por la configuracion por defecto en caso de no poder abrirlo.
*/
void llenar_config(configuracion_t *config, FILE** arch_config){
  if(!(*arch_config)){
    llenar_config_defecto(config);
  }else{
		char indicador[MAX_NOMBRE];
		int leidos = fscanf(*arch_config,FORMATO_R_INDICADOR, indicador);
		while(leidos != EOF){
			if(strcmp(indicador, "RESISTENCIA_TORRES") == 0){
				fscanf(*arch_config,"%i,%i\n", &(config -> resistencia_torres[0]), &(config -> resistencia_torres[1]));
		    if(config -> resistencia_torres[0] == POR_DEFECTO){
		      config -> resistencia_torres[0] = VIDA_INICIAL_TORRES;
		    }
		    if(config -> resistencia_torres[1] == POR_DEFECTO){
		      config -> resistencia_torres[1] = VIDA_INICIAL_TORRES;
		    }
			}else if(strcmp(indicador, "ENANOS_INICIO") == 0){
				fscanf(*arch_config, "%i,%i,%i,%i\n", &(config -> enanos_inicio[0]), &(config -> enanos_inicio[1]), &(config -> enanos_inicio[2]), &(config -> enanos_inicio[3]));
		    if(config -> enanos_inicio[0] == POR_DEFECTO){
		      config -> enanos_inicio[0] = CANT_DEFENSORES_1;
		    }
		    if(config -> enanos_inicio[1] == POR_DEFECTO){
		      config -> enanos_inicio[1] = NINGUN_DEFENSOR;
		    }
		    if(config -> enanos_inicio[2] == POR_DEFECTO){
		      config -> enanos_inicio[2] = CANT_DEFENSORES_3 / 2;
		    }
		    if(config -> enanos_inicio[3] == POR_DEFECTO){
		      config -> enanos_inicio[3] = CANT_DEFENSORES_4 / 2;
		    }
			}else if(strcmp(indicador, "ELFOS_INICIO") == 0){
				fscanf(*arch_config, "%i,%i,%i,%i\n", &(config -> elfos_inicio[0]), &(config -> elfos_inicio[1]), &(config -> elfos_inicio[2]), &(config -> elfos_inicio[3]));
		    if(config -> elfos_inicio[0] == POR_DEFECTO){
		      config -> elfos_inicio[0] = NINGUN_DEFENSOR;
		    }
		    if(config -> elfos_inicio[1] == POR_DEFECTO){
		      config -> elfos_inicio[1] = CANT_DEFENSORES_2;
		    }
		    if(config -> elfos_inicio[2] == POR_DEFECTO){
		      config -> elfos_inicio[2] = CANT_DEFENSORES_3 / 2;
		    }
		    if(config -> elfos_inicio[3] == POR_DEFECTO){
		      config -> elfos_inicio[3] = CANT_DEFENSORES_4 / 2;
		    }
			}else if(strcmp(indicador, "ENANOS_EXTRA") == 0){
				fscanf(*arch_config, "%i,%i,%i\n", &(config -> enanos_extra[0]), &(config -> enanos_extra[1]), &(config -> enanos_extra[2]));
		    if(config -> enanos_extra[0] == POR_DEFECTO){
		      config -> enanos_extra[0] = ENANOS_EXTRA;
		    }
		    if(config -> enanos_extra[1] == POR_DEFECTO){
		      config -> enanos_extra[1] = COSTO_DEF_EXTRA;
		    }
		    if(config -> enanos_extra[2] == POR_DEFECTO){
		      config -> enanos_extra[2] = SIN_COSTO;
		    }
			}else if(strcmp(indicador, "ELFOS_EXTRA") == 0){
				fscanf(*arch_config, "%i,%i,%i\n", &(config -> elfos_extra[0]), &(config -> elfos_extra[1]), &(config -> elfos_extra[2]));
		    if(config -> elfos_extra[0] == POR_DEFECTO){
		      config -> elfos_extra[0] = ENANOS_EXTRA;
		    }
		    if(config -> elfos_extra[1] == POR_DEFECTO){
		      config -> elfos_extra[1] = SIN_COSTO;
		    }
		    if(config -> elfos_extra[2] == POR_DEFECTO){
		      config -> elfos_extra[2] = COSTO_DEF_EXTRA;
		    }
			}else if(strcmp(indicador, "ENANOS_ANIMO") == 0){
				fscanf(*arch_config, "%i,%i\n", &(config -> animo_enanos[0]), &(config -> animo_enanos[1]));
			}else if(strcmp(indicador, "ELFOS_ANIMO") == 0){
		    fscanf(*arch_config, "%i,%i\n", &(config -> animo_elfos[0]), &(config -> animo_elfos[1]));
			}else if(strcmp(indicador, "VELOCIDAD") == 0){
				fscanf(*arch_config, "%f\n", &(config -> velocidad_de_juego));
		    if(config -> velocidad_de_juego == POR_DEFECTO){
		      config -> velocidad_de_juego = VEL_NORMAL;
		    }
			}else if(strcmp(indicador, "CAMINOS") == 0){
				fscanf(*arch_config, "%[^\n]\n", config -> caminos);
			}
			leidos = fscanf(*arch_config,FORMATO_R_INDICADOR, indicador);
		}
  }
}

/*
*	Precondiciones: Debe recibir una ruta valida.
*	Postcondiciones: Modificara el nombre de la configuracion por el obtenido con la ruta.
*/
void copiar_nombre_config(char nombre_config[MAX_NOMBRE], char ruta[MAX_RUTA]){
	char *nombre;
	nombre = strtok(ruta,".");
	if(nombre == NULL){
		strcpy(nombre_config, ruta);
	}else{
		strcpy(nombre_config, nombre);
	}
}

/*
* Precondiciones: Debe recibir una configuracion valida.
*	Postcondiciones: Modificara los valores del viento, humedad y animos a -1 en caso de ser necesario que se modifiquen en animos().
*/
void cargar_animos_necesarios(int *viento, int *humedad, char *animo_legolas, char *animo_gimli, configuracion_t config){
	if(config.animo_enanos[0] == -1){
		*humedad = -1;
	}else{
		*humedad = 0;
	}
	if(config.animo_enanos[1] == -1){
		*animo_gimli = 'x';
	}else{
		*animo_gimli = ' ';
	}
	if(config.animo_elfos[0] == -1){
		*viento = -1;
	}else{
		*viento = 0;
	}
	if(config.animo_elfos[1] == -1){
		*animo_legolas = 'x';
	}else{
		*animo_legolas = ' ';
	}
}

/*
* Precondiciones: Debe recibir los argumentos del main.
* Postcondiciones: Jugara el juego con la configuracion ingresada o por defecto (si no se ingreso configuracion),
* y lo grabara en caso de que se ingrese una ruta de grabacion.
*/
void jugar_juego(char ruta_config[MAX_RUTA], char ruta_grabacion[MAX_RUTA]){
  configuracion_t config;
  FILE* arch_grabacion;
	FILE* arch_config;
	FILE* arch_camino;
	char nombre_config[MAX_NOMBRE];
	strcpy(nombre_config, STR_POR_DEFECTO);
	srand ((unsigned)time(NULL));
	int viento;
	int humedad;
	char animo_legolas;
	char animo_gimli;
	juego_t juego;
	torres_t maximos;
	if(strcmp(ruta_config, STR_POR_DEFECTO) != 0){
		arch_config = fopen(ruta_config, "r");
		if(arch_config){
			copiar_nombre_config(nombre_config, ruta_config);
		}
	}
  llenar_config(&config, &arch_config);
	if(arch_config){
		fclose(arch_config);
	}
	if(strcmp(ruta_grabacion, STR_POR_DEFECTO) != 0){
		arch_grabacion = fopen(ruta_grabacion, "w");
	}
  mostrar_dibujo_portada();
	cargar_animos_necesarios(&viento,&humedad,&animo_legolas,&animo_gimli,config);
  animos(&viento,&humedad,&animo_legolas,&animo_gimli);
  inicializar_juego(&juego, viento, humedad, animo_legolas,animo_gimli,config);
	maximos = juego.torres;
  if(strcmp(config.caminos, STR_POR_DEFECTO) != 0){
    arch_camino = fopen(config.caminos, "r");
  }
  iniciar_nivel(&juego, config, &arch_camino);
  mostrar_juego(juego, maximos);
  while (estado_juego(juego) == JUEGO_JUGANDO){
    if(estado_nivel(juego.nivel) == NIVEL_GANADO){
      pasar_al_siguiente_nivel(&juego, config, &arch_camino);
    }else if(estado_nivel(juego.nivel) == NIVEL_JUGANDO){
      jugar_turno(&juego);
      mostrar_juego(juego,maximos);
      poner_nuevo_defensor(&juego, config);
      if(arch_grabacion){
        fwrite(&juego,sizeof(juego_t),1,arch_grabacion);
      }
      detener_el_tiempo(config.velocidad_de_juego);
    }
  }
  if(arch_grabacion){
		fclose(arch_grabacion);
	}
	if(arch_camino){
		fclose(arch_camino);
	}
  finalizar_juego(juego,config,nombre_config);
  }

/*****************************************************************************************************************************************************************************************************/
