#include "defendiendo_torres.h"
#include "utiles.h"
#include "funcionalidades.h"
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//
/******************************************************************************************** Constantes *********************************************************************************************/

#define BLANCO "\033[0m"
#define AMARILLO "\033[1;33m"
#define ROJO "\033[0;31m"
#define L_ROJO "\033[1;31m"
#define VERDE "\033[1;32m"
#define L_VERDE "\033[0;32m"
#define MARRON "\033[0;33m"
#define NEGRO "\033[0;30m"
#define NIVEL_1 1
#define NIVEL_2 2
#define NIVEL_3 3
#define NIVEL_4 4
#define MAX_VELOCIDAD 5
#define MAX_CANTIDAD 5
#define CANTIDAD_CAMINOS 6
#define FORMATO_CAMINO "%i;%i\n"
#define JUEGO_PERDIDO -1
#define JUEGO_GANADO 1
#define POR_DEFECTO -1
#define CAM_POR_DEFECTO "-1"
#define MAX_NOMBRE_PORCENTAJE 10
#define MAX_PARAMETRO 50
#define RANKING "ranking"
#define CSV ".csv"
#define FORMATO_RANKING "%[^;];%i\n"
#define MAX_NOMBRE 50
#define STR_POR_DEFECTO "-1"
#define TAMANIO_TABLERO_1 15
#define TAMANIO_TABLERO_2 15
#define TAMANIO_TABLERO_3 20
#define TAMANIO_TABLERO_4 20
static const char ARRIBA_MAY = 'W';
static const char ARRIBA_MIN = 'w';
static const char ABAJO_MAY = 'S';
static const char ABAJO_MIN = 's';
static const char IZQUIERDA_MAY = 'A';
static const char IZQUIERDA_MIN = 'a';
static const char DERECHA_MAY = 'D';
static const char DERECHA_MIN = 'd';
static const char BARRA_ESPAC = ' ';
static const char LETRA_F_MAX = 'F';
static const char LETRA_F_MIN = 'f';
static const int POS_MIN = 0;
static const int POS_MAX_1_2 = 14;
static const int POS_MAX_3_4 = 19;
static const char PASTO = '~';
static const char CAMINO = 'C';
const char BACKSPACE = 127;
const int PRIMER_CAMINO = 0;
const int SEGUNDO_CAMINO = 1;
const int TERCER_CAMINO = 2;
const int CUARTO_CAMINO = 3;
const int QUINTO_CAMINO = 4;
const int SEXTO_CAMINO = 5;
const int CAMINO_1 = 1;
const int CAMINO_2 = 2;
const int MAXIMO_RESIST_TORRE = 9999;
const int MIN_RESIST_TORRE = 1;
const int MAX_DEFENSORES_CONFIG = 99;
const int MIN_DEFENSORES_CONFIG = 0;
const int MIN_COSTO = 1;
const int MIN_PORCENTAJE = 1;
const int MAX_PORCENTAJE = 100;

/*
* Precondiciones: Debe recibir un nombre que no supere el maximo.
* Postcondiciones: Pondra una cantidad de espacios segun la longitud del nombre.
*/
void poner_espacios_segun_nombre(char nombre[MAX_NOMBRE]){
	int largo_nombre = (int)strlen(nombre);
	for(int i = 0; i < (MAX_NOMBRE - largo_nombre); i++){
		printf(" ");
	}
	printf(AMARILLO"║\n");
}


/**************************************************************************************** Detectar tecla pulsada *************************************************************************************/

/*
*	Postcondiciones: Devolvera la tecla pulsada por el usuario.
*/
static int getch(void){
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

/***************************************************************************************** Eliminar indicador ****************************************************************************************/

void eliminar_indicador(char dato[MAX_DATO], char argumento[],int primera_letra){
	int tope = (int)strlen(argumento);
	for(int i = primera_letra; i < tope; i++){
		dato[i - primera_letra] = argumento[i];
	}
	dato[tope - primera_letra] = '\0';
}

/******************************************************************************************* Pasar repeticion ****************************************************************************************/

/*
* Postcondiciones: Mostrara por pantalla una presentacion de la repeticion.
*/
void mostrar_introduccion_repeticion(){

	srand ((unsigned)time(NULL));
	int n = rand() % 2;
	if(n == 0){
		system("clear");
		printf("\n\n\n\n");
		printf(AMARILLO"                                      \\\n");
		printf("\t\t\t           A ver                       \\\n");
		printf("\t\t\t        poneme la repe                     __ _\n");
		printf("\t\t\t             /                            / _` \\\n");
		printf("\t\t\t            /                            (_( \\_ \\\n");
		printf("\t\t\t       ___________                        \\o^o-)/___\n");
		printf("\t\t\t      |___ ___  | |                     __(_/_/_ _)_)\n");
		printf("\t\t\t     |::::|   | | |                    /_/      \\/  |\n");
		printf("\t\t\t     |::::|   | | |                 __(/    ___> )  |\n");
		printf("\t\t\t     |oo__|   | | |                (_)_\\_`_/_,---'  |\n");
		printf("\t\t\t      \\____\\__|_|_|                (     > /        |\n");
		printf("\t\t\t       _||_____||_     ____      __/  __(  )________|\n");
		printf("\t\t\t      |oo____|_||_|    \\   \\    _\\___/__/__\\________)   \n");
		printf("\t\t\t      __||_____||__   __\\___\\  (___/|_/ (__)|_/  \\_|\n");
		printf("\t\t\t     |_______|_____| |___)___)\n");
		detener_el_tiempo(2);
		system("clear");
	}else{
		system("clear");
		printf("\n\n\n\n");
		printf(AMARILLO"\t\t\t               @-_________________-@\n");
		printf("\t\t\t         @-_____| HOY PRESENTAMOS |_____-@\n");
		printf("\t\t\t          |   Defendiendo las torres    |\n");
		printf("\t\t\t   _______|_____________________________|__________\n");
		printf("\t\t\t  |________________________________________________|\n");
		printf("\t\t\t  |               -                -               |\n");
		printf("\t\t\t  |   -       -             -                    - |\n");
		printf("\t\t\t  |        ____    ______________-   ____          |\n");
		printf("\t\t\t  | -  -  |    |   |  TICKETS   |   |    | -       |\n");
		printf("\t\t\t  |       |    |   |            |   |    |         |\n");
		printf("\t\t\t  |  --   |____| - |_o___oo___o_| - |____|     -   |\n");
		printf("\t\t\t  | -     |    |  |     --       |  |    |         |\n");
		printf("\t\t\t  |    -  |    |- | -      -     |  |    | --      |\n");
		printf("\t\t\t  |_______|====|__|______________|__|====|_________|\n");
		printf("\t\t\t /                                                  \\\n");
		printf("\t\t\t/____________________________________________________\\\n");
		detener_el_tiempo(2);
		system("clear");
	}

	printf(";i11tttttttttttttttttttttttttffffffffffffffffffffLLfLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLff1\n");
	printf("itfffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCLCCCCCCLLLffffLLfffLLLCCGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLCCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLLLCCLfttfffffffLLLLCCLLLLLLLfLLfffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLCCLttfffffLLCCCCCCCGGCCGGGGCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffLCCCCCCCCCCCGGCGCCCCGGGGGCLfLCftCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLCf1fLtfLCCCCCCCCGGCLLLLfLCGGGCGGGGGGCLfLCtfGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffLLLLLLLLLLLLLLLLLLLLLLCt1CttLCCCCCCCCCL.             GGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");//
	printf("1tffffLLLLLLLLLLLLLLLLLLLLC11C1fCCLCCCCCCCt.   ,iiiiiiiiiiGGGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLCt1C1fCLCCCCCCCCCC:   tCGGGGGGGGGGGCGGGGGGGGC1GftGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLiCttCLCCCCCCCCCCC:   t000000GGGGGGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCL   .Lft11tfLCGCCGCGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffffLLLLLLLLLLLLLLLLLiLttCLLCLLLLCCCCCi           .,1CGGGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1ffLLLLLLLLLLLLLLLLLLLLCLiG1fCCCCCCCCCCCCC.    :i1t1;.   .fGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfLLLLLLLLLLLLLLLLLLLLLLiG1fCCCCCCCCCCCCCCCCGCGGGGGGC;    LGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLiCttCLLLLLCCCCCCCCGLGCCCCCCCCC.   iGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCii1GCCCCCCCC.   1GGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLiCttCLLCCCCCCCCL    fGGGGGGCi   .GGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLCt1C1fCLLCCCCCCCC;    ;tffti,   :LCGGGGGGGGGC10ftGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLC11C1tCCLLLCCCCCCt:.        .:tGGCGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLCt1CttLCCLCCCCCCCCCCCCGGCGGGGGGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLCf1fLttLCCCCCCCCCCCCCCGCCCCCCCCCCGGGCLfCCtLGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itfffffffLLLLLLLLLLLLLLLLLLLLCLttfftfLLCCCCCCCCCCCGCCCCCCCGGGCCffLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffffLCCCCCCCGGCGGCCCCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLLLLLLCLfttffffffffLLLLCLLLLLfffLLLffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itffffffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCCCLLLLfffffLfffLLLCCCGGCCCCCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	detener_el_tiempo(1);
	system("clear");
	printf(";i11tttttttttttttttttttttttttffffffffffffffffffffLLfLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLff1\n");
	printf("itfffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCLCCCCCCLLLffffLLfffLLLCCGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLCCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLLLCCLfttfffffffLLLLCCLLLLLLLfLLfffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLCCLttfffffLLCCCCCCCGGCCGGGGCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffLCCCCCCCCCCCGGCGCCCCGGGGGCLfLCftCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLCf1fLtfLCCCCCCCCGGCLLLLfLCGGGCGGGGGGCLfLCtfGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffLLLLLLLLLLLLLLLLLLLLLLCt1CttLCCCCCCCCCLCCCCCGL:   1LGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLC11C1fCCLCCCCCCCCCCCCCC1.    1GCGGGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLCt1C1fCLCCCCCCCCCCCCCGL:      1GCGGCGGGGGGGGC1GftGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLiCttCLCCCCCCCCCCCCCC1.  :,   1GCGGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCCL:   1G:   1GCGGCGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffffLLLLLLLLLLLLLLLLLiLttCLLCLLLLCCCCCCC.  ,fGG:   1GCGGGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1ffLLLLLLLLLLLLLLLLLLLLCLiG1fCCCCCCCCCCCCL:  .1GGG0:   10GGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfLLLLLLLLLLLLLLLLLLLLLLiG1fCCCCCCCCCCCC.  .1CLLLC,   iGGGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLiCttCLLLLLCCCCL                  .CGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCL:::::::::::.   ,::;CGGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLiCttCLLCCCCCCCCCCCCCCCCG0:   10fLGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLCt1C1fCLLCCCCCCCCCCCCCCCCG,   1GCCCGGGGGGGGGC10ftGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLC11C1tCCLLLCCCCCCCCCCCCGGi:::tGCCCGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLCt1CttLCCLCCCCCCCCCCCCGGCGGGGGGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLCf1fLttLCCCCCCCCCCCCCCGCCCCCCCCCCGGGCLfCCtLGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itfffffffLLLLLLLLLLLLLLLLLLLLCLttfftfLLCCCCCCCCCCCGCCCCCCCGGGCCffLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffffLCCCCCCCGGCGGCCCCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLLLLLLCLfttffffffffLLLLCLLLLLfffLLLffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itffffffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCCCLLLLfffffLfffLLLCCCGGCCCCCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	detener_el_tiempo(1);
	system("clear");
	printf(";i11tttttttttttttttttttttttttffffffffffffffffffffLLfLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLff1\n");
	printf("itfffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCLCCCCCCLLLffffLLfffLLLCCGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLCCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLLLCCLfttfffffffLLLLCCLLLLLLLfLLfffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLCCLttfffffLLCCCCCCCGGCCGGGGCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffLCCCCCCCCCCCGGCGCCCCGGGGGCLfLCftCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLCf1fLtfLCCCCCCCCGGCLLLLfLCGGGCGGGGGGCLfLCtfGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffLLLLLLLLLLLLLLLLLLLLLLCt1CttLCCCCCCCCCL1:.      ,:iLGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLC11C1fCCLCCCCCCCt,   ,;ii;.   :iGGGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLCt1C1fCLCCCCCCCCt    1GGGGGC;   :GGCGGGGGGGGC1GftGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLiCttCLCCCCCCCCCfi;:iGCCCGC01   .GGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCCLCCCCCGfi.  .tGGCGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffffLLLLLLLLLLLLLLLLLiLttCLLCLLLLCCCCCCCCCCf       ,L0GGGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1ffLLLLLLLLLLLLLLLLLLLLCLiG1fCCCCCCCCCCCCCCCCCCG,:;:,   ,GGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfLLLLLLLLLLLLLLLLLLLLLLiG1fCCCCCCCCCCCCCCCCGCCGG0GCf,   :GGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLiCttCLLLLLCCCCCCCCGL1CCCCGCCGf    fGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCC:   ;GCCCGCGG1    LGGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLiCttCLLCCCCCCCCf.   ;LCGGCLi    1GGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLCt1C1fCLLCCCCCCCCf:    .,,.    :fGCGGGGGGGGGC10ftGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLC11C1tCCLLLCCCCCCCL1;,....,;1LGGCCGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLCt1CttLCCLCCCCCCCCCCCCGGCGGGGGGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLCf1fLttLCCCCCCCCCCCCCCGCCCCCCCCCCGGGCLfCCtLGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itfffffffLLLLLLLLLLLLLLLLLLLLCLttfftfLLCCCCCCCCCCCGCCCCCCCGGGCCffLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffffLCCCCCCCGGCGGCCCCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLLLLLLCLfttffffffffLLLLCLLLLLfffLLLffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itffffffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCCCLLLLfffffLfffLLLCCCGGCCCCCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	detener_el_tiempo(1);
	system("clear");
	printf(";i11tttttttttttttttttttttttttffffffffffffffffffffLLfLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLff1\n");
	printf("itfffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCLCCCCCCLLLffffLLfffLLLCCGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLCCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLLLCCLfttfffffffLLLLCCLLLLLLLfLLfffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLCCLttfffffLLCCCCCCCGGCCGGGGCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffLCCCCCCCCCCCGGCGCCCCGGGGGCLfLCftCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLCf1fLtfLCCCCCCCCGGCLLLLfLCGGGCGGGGGGCLfLCtfGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffLLLLLLLLLLLLLLLLLLLLLLCt1CttLCCCCCCCCCL1:,      .:iLGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLC11C1fCCLCCCCCCCt.   ,;ii;,    iGGGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLCt1C1fCLCCCCCCCCt   .tCGGGGGL,   iGCGGGGGGGGC1GftGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLiCttCLCCCCCCCCC;...;GCCCCCC01   ,GGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCCLCCCCCGCGL,   iGCGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffffLLLLLLLLLLLLLLLLLiLttCLLCLLLLCCCCCCCCCCCCGGC1.   ;GGGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1ffLLLLLLLLLLLLLLLLLLLLCLiG1fCCCCCCCCCCCCCCCCCCGGC1.   ,tGGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfLLLLLLLLLLLLLLLLLLLLLLiG1fCCCCCCCCCCCCCCCCGCf;.   :tGGGGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLiCttCLLLLLCCCCCCCCGL1,   .;fGGCCCCCGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCi.   :tCGGGGGGGGGGGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLiCttCLLCCCCCCCCL,   .ifLLfffffffLGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLCt1C1fCLLCCCCCCL                 .CGGGGGGGGGC10ftGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLC11C1tCCLLLCCCf:::::::::::::::::;CGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLCt1CttLCCLCCCCCCCCCCCCGGCGGGGGGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLCf1fLttLCCCCCCCCCCCCCCGCCCCCCCCCCGGGCLfCCtLGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itfffffffLLLLLLLLLLLLLLLLLLLLCLttfftfLLCCCCCCCCCCCGCCCCCCCGGGCCffLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffffLCCCCCCCGGCGGCCCCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLLLLLLCLfttffffffffLLLLCLLLLLfffLLLffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itffffffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCCCLLLLfffffLfffLLLCCCGGCCCCCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	detener_el_tiempo(1);
	system("clear");
	printf(";i11tttttttttttttttttttttttttffffffffffffffffffffLLfLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLff1\n");
	printf("itfffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCLCCCCCCLLLffffLLfffLLLCCGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLCCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLLLCCLfttfffffffLLLLCCLLLLLLLfLLfffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLCCLttfffffLLCCCCCCCGGCCGGGGCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffLCCCCCCCCCCCGGCGCCCCGGGGGCLfLCftCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLCf1fLtfLCCCCCCCCGGCLLLLfLCGGGCGGGGGGCLfLCtfGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffLLLLLLLLLLLLLLLLLLLLLLCt1CttLCCCCCCCCCL1CCGGC;  .CGLGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLC11C1fCCLCCCCCCCCCCGCLi.   .CGCGGGGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLCt1C1fCLCCCCCCCCCCCfi:      .CGCGGGCGGGGGGGGC1GftGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLiCttCLCCCCCCCCCCG;    :;   .CGCGGGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCCLCCCCC   .CGCGGGCGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffffLLLLLLLLLLLLLLLLLiLttCLLCLLLLCCCCCCCCCCCCG   .CCCCGGGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1ffLLLLLLLLLLLLLLLLLLLLCLiG1fCCCCCCCCCCCCCCCCCCGGf   .CGGGGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfLLLLLLLLLLLLLLLLLLLLLLiG1fCCCCCCCCCCCCCCCCGCCGf   .CGGGGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLiCttCLLLLLCCCCCCCCGCCCCCf   .GCCCCCGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCCCCCCCf   .CGGGGGGGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLiCttCLLCCCCCCCCCCCCCCCCf   .CCCCCGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLCt1C1fCLLCCCCCCCCCCCCCCCf    CCCCCCGGGGGGGGGC10ftGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLC11C1tCCLLLCCCCCCCCCCCCL::::CCCCCCGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLCt1CttLCCLCCCCCCCCCCCCGGCGGGGGGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLCf1fLttLCCCCCCCCCCCCCCGCCCCCCCCCCGGGCLfCCtLGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itfffffffLLLLLLLLLLLLLLLLLLLLCLttfftfLLCCCCCCCCCCCGCCCCCCCGGGCCffLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffffLCCCCCCCGGCGGCCCCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLLLLLLCLfttffffffffLLLLCLLLLLfffLLLffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itffffffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCCCLLLLfffffLfffLLLCCCGGCCCCCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	detener_el_tiempo(1);
	system("clear");
	printf(";i11tttttttttttttttttttttttttffffffffffffffffffffLLfLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLff1\n");
	printf("itfffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCLCCCCCCLLLffffLLfffLLLCCGGGGCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLCCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLLLCCLfttfffffffLLLLCCLLLLLLLfLLfffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLLCCLttfffffLLCCCCCCCGGCCGGGGCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffLCCCCCCCCCCCGGCGCCCCGGGGGCLfLCftCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLLLCf1fLtfLCCCCCCCCCCCCCCCCCCCCCCGGGGGGCLfLCtfGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffLLLLLLLLLLLLLLLLLLLLLLCt1CttLCCCCCCCCCL1CCCCCCCCCCiLGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLC11C1fCCLCCCCCCCCCCCGCCCGGCCCCCCGGGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLCt1C1fCLCCCCCCCCCCCCCCCCGCCCGGCCCCGCGGGGGGGGC1GftGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLLLiCttCLCCCCCCCCCCCCCCGCCCCCCCGCCCCGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tffffLLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCCLCGGCCGCGLGGCCiGCGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("itffffffLLLLLLLLLLLLLLLLLiLttCLLCLLLLCCCCCCCCCCCCGGC1CCGCCGGGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1ffLLLLLLLLLLLLLLLLLLLLCLiG1fCCCCCCCCCCCCCCCCCCGGC1GGGCCtGGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfLLLLLLLLLLLLLLLLLLLLLLiG1fCCCCCCCCCCCCCCCCGCfCCCCCCtGGGGGGGGGGGGGGGGCt01LGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLiCttCLLLLLCCCCCCCCGL1CCGCGCfGGCCCCCGGGGGGGGGGGLt01CGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffLLLLLLLLLLLLLLLLLC1tLiCLLCCCCCCCCCCCiCGCCCCCGGGGGGGGGGGGGGGGGGGGtCC1GGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLiCttCLLCCCCCCCCLCCCCCCfLLfffffffLGGGGGGGGGGGLt01LGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLCt1C1fCLLCCCCCCCCCCCCCCGGGCCCCGGCCCGGGGGGGGGC10ftGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLC11C1tCCLLLCCCCCCCCCCCCCCCGGCCGCCCGGGGGGGGLtGftGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLCt1CttLCCLCCCCCCCCCCCCGGCGGGGGGGGGGGGGGGffGftGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLCf1fLttLCCCCCCCCCCCCCCGCCCCCCCCCCGGGCLfCCtLGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itfffffffLLLLLLLLLLLLLLLLLLLLCLttfftfLLCCCCCCCCCCCGCCCCCCCGGGCCffLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tffffffLLLLLLLLLLLLLLLLLLLLLLLCLttffffffLCCCCCCCGGCGGCCCCCLLfLLLffCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCf\n");
	printf("1tfffffffLLLLLLLLLLLLLLLLLLLLLLLLCLfttffffffffLLLLCLLLLLfffLLLffLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("itffffffffLLLLLLLLLLLLLLLLLLLLLLLLLCCLLfffffffffffLfffffffffLLCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	printf("1tfffffffffLLLLLLLLLLLLLLLLLLLLLLLLLLLCCCLLLLfffffLfffLLLCCCGGCCCCCGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGCCf\n");
	detener_el_tiempo(0.25);
	system("clear");
}

/*
*	Precondiciones: Debe recibir un nivel_actual valido (1,2,3,4).
*	Postcondiciones: Mostrara la introduccion del nivel que se haya ingresado.
*/
void mostrar_introduccion_nivel_rep(int nivel_actual){
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
*	Postcondiciones: Mostrara la pantalla final con el mensaje de que se ganó el juego.
*/
static void mostrar_que_gano(){
	system("clear");
	printf("   "MARRON"***\n");
	printf("  "MARRON"*****\n");
	printf("  "MARRON"*****\n");
	printf("   "MARRON"***\n");
	printf("   "MARRON":::"AMARILLO"\\  .,,,,,,,..\n");
	printf("   "MARRON":::"AMARILLO" \\;;;;;;;;;;;;;;,.            ..,,;;;;;;;;;;;,.         .   \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,      ,;,   \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,,,,;;;'   \n");
	printf("   "MARRON":::  "AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;"BLANCO"####"AMARILLO";;;;;;;;;;;;;;;"BLANCO"#####"AMARILLO";;"BLANCO"#"AMARILLO";;;;;;;;;;;;;;;;'   \n");
	printf("   "MARRON":::  "AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#####"AMARILLO";:"BLANCO"####"AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;"BLANCO"##"AMARILLO":;;;;;;;;;'    \n");
	printf("   "MARRON":::  "AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;;;;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";;;;;;;;'     \n");
	printf("   "MARRON":::  "AMARILLO";;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;;;;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#####"AMARILLO";;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";;;;;;'      \n");
	printf("   "MARRON":::  "AMARILLO";;;"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;"BLANCO"#"AMARILLO";"BLANCO"######"AMARILLO";;;;;'       \n");
	printf("   "MARRON":::  "AMARILLO";;;;"BLANCO"##"AMARILLO";;;"BLANCO"#"AMARILLO";;"BLANCO"####"AMARILLO";;;;"BLANCO"#"AMARILLO";;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";;;;'        \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;"BLANCO"#"AMARILLO";;;;"BLANCO"####"AMARILLO";;;;;;;;;;;"BLANCO"#"AMARILLO";;;;"BLANCO"#"AMARILLO";;;'         \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'          \n");
	printf("   "MARRON":::  "AMARILLO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'           \n");
	printf("   "MARRON":::"AMARILLO" /''';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            \n");
	printf("   "MARRON":::"AMARILLO"/        '''::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            \n");
	printf("   "MARRON":::                 "AMARILLO"'\"\"\"\"\"\";;;;;;;;;;;;;;\"\"\"\"\"\"';;;;            \n");
	printf("   "MARRON":::                                             "AMARILLO":;;'\n");
	printf("   "MARRON":::                                             "AMARILLO";;'\n");
	printf("   "MARRON":::                                             "AMARILLO";'\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf(" "MARRON"/:::::\\\n");
	printf(" "MARRON":::::::\n");
	printf(" "MARRON"=======\n");
}

/*
*	Postcondiciones: Mostrara la pantalla final con el mensaje de que se perdió el juego.
*/
static void mostrar_que_perdio(){
	system("clear");
	printf("   "MARRON"***\n");
	printf("  "MARRON"*****\n");
	printf("  "MARRON"*****\n");
	printf("   "MARRON"***\n");
	printf("   "MARRON":::"BLANCO"\\  .,,,,,,,..\n");
	printf("   "MARRON":::"BLANCO" \\;;;;;;;;;;;;;;,.            ..,,;;;;;;;;;;;,.         .   \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,      ,;,   \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,,,,;;;'   \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#####"BLANCO";;"AMARILLO"######"BLANCO";;;;;;;;;;;;;;;;"AMARILLO"####"BLANCO";;"AMARILLO"#####"BLANCO";;;;;;;;;;;;;;'   \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;;;"AMARILLO"#####"BLANCO";;"AMARILLO"#####"BLANCO";;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;;;"AMARILLO"##"BLANCO";;;;;;;;'    \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#####"BLANCO";;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;"AMARILLO"#"BLANCO":;;;;;'     \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;;'      \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;;;"AMARILLO"#####"BLANCO";;"AMARILLO"#####"BLANCO";;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;"AMARILLO"######"BLANCO";;;'       \n");
	printf("   "MARRON":::  "BLANCO";"AMARILLO"#####"BLANCO";;"AMARILLO"######"BLANCO" "AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;"AMARILLO"####"BLANCO";;;;"AMARILLO"#"BLANCO";;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;'        \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";;;;;;;;;;;;;;"AMARILLO"#"BLANCO";;;;"AMARILLO"#"BLANCO";'         \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'          \n");
	printf("   "MARRON":::  "BLANCO";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;'           \n");
	printf("   "MARRON":::"BLANCO" /''';;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            \n");
	printf("   "MARRON":::"BLANCO"/        '''::;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;            \n");
	printf("   "MARRON":::                 "BLANCO"'\"\"\"\"\"\";;;;;;;;;;;;;;\"\"\"\"\"\"';;;;            \n");
	printf("   "MARRON":::                                             "BLANCO":;;'\n");
	printf("   "MARRON":::                                             "BLANCO";;'\n");
	printf("   "MARRON":::                                             "BLANCO";'\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf("   "MARRON":::\n");
	printf(" "MARRON"/:::::\\\n");
	printf(" "MARRON":::::::\n");
	printf(" "MARRON"=======\n");
}

/*
*	Precondiciones: Debe recibir un juego con todas sus estructuras validas.
*	Postcondiciones: Mostrara si la pantalla final de victoria o derrota segun el caso.
*/
void finalizar_repeticion(juego_t repeticion){
	if(estado_juego(repeticion) == JUEGO_GANADO){
		mostrar_que_gano();
	}else if(estado_juego(repeticion) == JUEGO_PERDIDO){
		mostrar_que_perdio();
	}
}

/*
* Precondiciones: Debe recibir una repeticion con todas sus estructuras validas.
* Postcondiciones: Devolvera true si acaba de comenzar el nivel y false si no.
*/
bool comenzo_nuevo_nivel(juego_t repeticion){
	bool comenzo = false;
	if((repeticion.nivel_actual == NIVEL_1 || repeticion.nivel_actual == NIVEL_2) && (repeticion.nivel.tope_enemigos == 1)){
		comenzo = true;
	}else if((repeticion.nivel_actual == NIVEL_3 || repeticion.nivel_actual == NIVEL_4) && (repeticion.nivel.tope_enemigos == 2)){
		comenzo = true;
	}
	return comenzo;
}

void pasar_repeticion(float velocidad, char ruta_grabacion[MAX_RUTA]){
	juego_t repeticion;

	if(strcmp(ruta_grabacion, STR_POR_DEFECTO) == 0){
		printf("ERROR -> NO se especificó ruta de grabacion\n");
	}
	FILE* arch_repeticion = fopen(ruta_grabacion, "r");
	if(!(arch_repeticion)){
		printf("ERROR -> NO se encontró esa repetición\n");
		return;
	}
	mostrar_introduccion_repeticion();
	fread(&repeticion, sizeof(juego_t), 1, arch_repeticion);
	torres_t maximos = repeticion.torres;
	while(!feof(arch_repeticion)){
		if(comenzo_nuevo_nivel(repeticion)){
			mostrar_introduccion_nivel_rep(repeticion.nivel_actual);
		}
		mostrar_juego(repeticion, maximos);
		detener_el_tiempo(velocidad);
		fread(&repeticion, sizeof(juego_t), 1, arch_repeticion);
  	}
	finalizar_repeticion(repeticion);
	fclose(arch_repeticion);
}

/********************************************************************************************* Crear camino ******************************************************************************************/

/*
*	Precondiciones: Debera recibir un movmiento valido (Izquierda, Derecha, Arriba o Abajo) y una posicion valida.
*	Postcondiciones: Devolvera true si es posible realizar el movimiento y false en el caso contrario.
*/
static bool es_posible_moverse(coordenada_t posicion, int movimiento, int tope_mov){
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
* Precondiciones: Debe recibir un numero de camino valido (0,1,2,3,4,5) y una posicion actual valida comprendida entre los maximos del tablero.
* Postcondiciones: Devolvera true si la posicion actual esta en el lado contrario a la entrada.
*/
bool es_pos_torre_valida(int n_camino, coordenada_t pos_actual){
	bool es_valida = false;
	if(n_camino == PRIMER_CAMINO && pos_actual.col == POS_MIN){
		es_valida = true;
	}else if(n_camino == SEGUNDO_CAMINO && pos_actual.col == POS_MAX_1_2){
		es_valida = true;
	}else if((n_camino == TERCER_CAMINO || n_camino == CUARTO_CAMINO) && pos_actual.fil == POS_MAX_3_4){
		es_valida = true;
	}else if((n_camino == QUINTO_CAMINO || n_camino == SEXTO_CAMINO) && pos_actual.fil == POS_MIN){
		es_valida = true;
	}
	return es_valida;
}

/*
* Precondiciones: Debe recibir un camino valido con sus topes, y una posicion actual comprendida entre los maximos del tablero.
* Postcondiciones: Devolvera true si la posicion_actual ya pertenece a algun camino, y false si no.
*/
bool pertenece_al_camino(coordenada_t camino[MAX_LONGITUD_CAMINO],int tope_camino, coordenada_t pos_actual){
	bool pertenece = false;
	for(int i = 0; i < tope_camino; i++){
		if(camino[i].fil == pos_actual.fil && camino[i].col == pos_actual.col){
			pertenece = true;
		}
	}
	return pertenece;
}

/*
* Precondiciones: Debe recibir una matriz de creador y su tope valido menor a los maximos de dicha matriz.
* Postcondiciones: Inicializara el creador con los valores de fondo (PASTO).
*/
void inicializar_creador(char creador[MAX_FILAS][MAX_COLUMNAS], int tope){
	for(int i = 0; i < tope; i++){
		for(int j = 0; j < tope; j++){
			creador[i][j] = PASTO;
		}
	}
}

/*
* Precondiciones: Debe recibir una matriz de creador valido, su respectivo tope y un numero de camino valido (0,1,2,3,4,5).
* Postcondiciones: Mostrara por pantalla el creador.
*/
void mostrar_creador(char creador[MAX_FILAS][MAX_COLUMNAS], int tope, int n_camino){
	system("clear");
	int nivel;
	int camino;
	if(n_camino == PRIMER_CAMINO){
		nivel = NIVEL_1;
		camino = CAMINO_1;
	}else if(n_camino == SEGUNDO_CAMINO){
		nivel = NIVEL_2;
		camino = CAMINO_2;
	}else if(n_camino == TERCER_CAMINO){
		nivel = NIVEL_3;
		camino = CAMINO_1;
	}else if(n_camino == CUARTO_CAMINO){
		nivel = NIVEL_3;
		camino = CAMINO_2;
	}else if(n_camino == QUINTO_CAMINO){
		nivel = NIVEL_4;
		camino = CAMINO_1;
	}else{
		nivel = NIVEL_4;
		camino = CAMINO_2;
	}


	if(tope == TAMANIO_TABLERO_1 || tope == TAMANIO_TABLERO_2){
		printf(AMARILLO"╔═════════════════════════════════════════════════════════╗"BLANCO"\n");
		printf(AMARILLO"║                                                         ║"BLANCO"\n");
		printf(AMARILLO"║       0  1  2  3  4  5  6  7  8  9  10 11 12 13 14      ║"BLANCO"\n");
		printf(AMARILLO"║     ╔═════════════════════════════════════════════╗     ║"BLANCO"\n");

	}else if(tope == TAMANIO_TABLERO_3 || tope == TAMANIO_TABLERO_4){
		printf(AMARILLO"╔════════════════════════════════════════════════════════════════════════╗"BLANCO"\n");
		printf(AMARILLO"║                                                                        ║"BLANCO"\n");
		printf(AMARILLO"║       0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19      ║"BLANCO"\n");
		printf(AMARILLO"║     ╔════════════════════════════════════════════════════════════╗     ║"BLANCO"\n");
	}

	for (int i = 0; i < tope; i++){
		printf(AMARILLO"║   %2d║"BLANCO"",i);
		for(int j = 0; j < tope; j++){
			if(creador[i][j] == CAMINO){
				printf (MARRON" ■ ");
			}else{
				printf(VERDE" %c ",creador[i][j]);
			}
		}
	printf(AMARILLO"║%-2d   ║"BLANCO"\n",i);
	}
	if(tope == TAMANIO_TABLERO_1 || tope == TAMANIO_TABLERO_2){
		printf(AMARILLO"║     ╚═════════════════════════════════════════════╝     ║"BLANCO"\n");
		printf(AMARILLO"║       0  1  2  3  4  5  6  7  8  9  10 11 12 13 14      ║"BLANCO"\n");
		printf(AMARILLO"║                                                         ║"BLANCO"\n");
		printf(AMARILLO"╠═════════════════════════════════════════════════════════╣"BLANCO"\n");
		printf(AMARILLO"║ Movimiento con WASD                                     ║"BLANCO"\n");
		printf(AMARILLO"║ Puedes borrar si con BACKSPACE                          ║"BLANCO"\n");
		printf(AMARILLO"║ Para finalizar el camino pulsa ESPACIO                  ║"BLANCO"\n");
		printf(AMARILLO"║ (Recorda que los caminos van de lado a lado)            ║"BLANCO"\n");
		printf(AMARILLO"╠═════════════════════════════════════════════════════════╣"BLANCO"\n");
		printf(AMARILLO"║   Nivel = %i                                Camino = %i   ║"BLANCO"\n",nivel, camino);
		printf(AMARILLO"╚═════════════════════════════════════════════════════════╝"BLANCO"\n");
	}else if(tope == TAMANIO_TABLERO_3 || tope == TAMANIO_TABLERO_4){
		printf(AMARILLO"║     ╚════════════════════════════════════════════════════════════╝     ║"BLANCO"\n");
		printf(AMARILLO"║       0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19      ║"BLANCO"\n");
		printf(AMARILLO"║                                                                        ║"BLANCO"\n");
		printf(AMARILLO"╠════════════════════════════════════════════════════════════════════════╣"BLANCO"\n");
		printf(AMARILLO"║ Movimiento con WASD                                                    ║"BLANCO"\n");
		printf(AMARILLO"║ Puedes borrar si con BACKSPACE                                         ║"BLANCO"\n");
		printf(AMARILLO"║ Para finalizar el camino pulsa ESPACIO                                 ║"BLANCO"\n");
		printf(AMARILLO"║ (Recorda que los caminos van de lado a lado)                           ║"BLANCO"\n");
		printf(AMARILLO"╠════════════════════════════════════════════════════════════════════════╣"BLANCO"\n");
		printf(AMARILLO"║   Nivel = %i                                               Camino = %i   ║"BLANCO"\n",nivel, camino);
		printf(AMARILLO"╚════════════════════════════════════════════════════════════════════════╝"BLANCO"\n");
	}

}

/*
* Precondiciones: Debe recibir un creador inicializado, un numero de camino valido (0,1,2,3,4,5), un tope de movimiento valido y el camino_1 con su respectivo tope, ambos validos.
* Postcondiciones: Determinara la entrada (primera posicion del camino) segun decida el usuario entre las posibilidades posibles segun el numero de camino.
*/
void determinar_entrada(char creador[MAX_FILAS][MAX_COLUMNAS], int n_camino, coordenada_t* pos_actual, int tope_mov, coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_camino_1){
	int tecla_pulsada;
	bool eligio_entrada = false;
	if(n_camino == PRIMER_CAMINO){
		pos_actual -> fil = 0;
		pos_actual -> col = 14;
	}else if(n_camino == SEGUNDO_CAMINO){
		pos_actual -> fil = 0;
		pos_actual -> col = 0;
	}else if(n_camino == TERCER_CAMINO || n_camino == CUARTO_CAMINO){
		pos_actual -> fil = 0;
		pos_actual -> col = 0;
	}else{
		pos_actual -> fil = 19;
		pos_actual -> col = 0;
	}
	creador[pos_actual -> fil][pos_actual -> col] = CAMINO;
	mostrar_creador(creador,tope_mov + 1, n_camino);
	printf(AMARILLO"  Primero selecciona la posicion donde se \n  Encontrara tu entrada (ESPACIO)\n");
	if(n_camino == PRIMER_CAMINO || n_camino == SEGUNDO_CAMINO){
		creador[pos_actual -> fil][pos_actual -> col] = CAMINO;
		while(!eligio_entrada){
			tecla_pulsada = getch();
			if(tecla_pulsada == ARRIBA_MAY || tecla_pulsada == ARRIBA_MIN){
				if(es_posible_moverse(*pos_actual, tecla_pulsada, tope_mov)){
					creador[pos_actual -> fil][pos_actual -> col] = PASTO;
					pos_actual -> fil --;
					creador[pos_actual -> fil][pos_actual -> col] = CAMINO;
				}
				mostrar_creador(creador,tope_mov + 1, n_camino);
				printf(AMARILLO"  Primero selecciona la posicion donde se \n  Encontrara tu entrada (ESPACIO)\n");
			}else if(tecla_pulsada == ABAJO_MAY || tecla_pulsada == ABAJO_MIN){
				if(es_posible_moverse(*pos_actual, tecla_pulsada, tope_mov)){
					creador[pos_actual -> fil][pos_actual -> col] = PASTO;
					pos_actual -> fil ++;
					creador[pos_actual -> fil][pos_actual -> col] = CAMINO;
				}
				mostrar_creador(creador,tope_mov + 1, n_camino);
				printf(AMARILLO"  Primero selecciona la posicion donde se \n  Encontrara tu entrada (ESPACIO)\n");
			}else if(tecla_pulsada == BARRA_ESPAC){
				eligio_entrada = true;
			}
		}
	}else{
		while(!eligio_entrada){
			tecla_pulsada = getch();
			if(tecla_pulsada == IZQUIERDA_MAY || tecla_pulsada == IZQUIERDA_MIN){
				if(es_posible_moverse(*pos_actual, tecla_pulsada, tope_mov)){
					if(!(pertenece_al_camino(camino_1, tope_camino_1, *pos_actual))){
						creador[pos_actual -> fil][pos_actual -> col] = PASTO;
					}
					pos_actual -> col --;
					creador[pos_actual -> fil][pos_actual -> col] = CAMINO;
				}
				mostrar_creador(creador,tope_mov + 1, n_camino);
				printf(AMARILLO"  Primero selecciona la posicion donde se \n  Encontrara tu entrada (ESPACIO)\n");
			}else if(tecla_pulsada == DERECHA_MAY || tecla_pulsada == DERECHA_MIN){
				if(es_posible_moverse(*pos_actual, tecla_pulsada, tope_mov)){
					if(!(pertenece_al_camino(camino_1, tope_camino_1, *pos_actual))){
						creador[pos_actual -> fil][pos_actual -> col] = PASTO;
					}
					pos_actual -> col ++;
					creador[pos_actual -> fil][pos_actual -> col] = CAMINO;
				}
				mostrar_creador(creador,tope_mov + 1, n_camino);
				printf(AMARILLO"  Primero selecciona la posicion donde se \n  Encontrara tu entrada (ESPACIO)\n");
			}else if(tecla_pulsada == BARRA_ESPAC){
				eligio_entrada = true;
			}
		}
	}
}

/*
* Precondiciones: Debe recibir un camino valido con su tope valido.
* Postcondiciones: Llenara el camino solicitado y su tope con el camino recibido y su tope.
*/
void llenar_camino(coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino, coordenada_t camino_a_llenar[MAX_LONGITUD_CAMINO], int *tope_camino_a_llenar){
	for(int i = 0; i < tope_camino; i++){
		camino_a_llenar[i] = camino[i];
	}
	*tope_camino_a_llenar = tope_camino;
}

/*
* Precondiciones: Debe recibir un creador valido, un camino valido y su respectivo tope menor al MAX_LONGITUD_CAMINO.
* Postcondiciones: Dibujara, en caso de ser necesario, el otro camino del nivel.
*/
void dibujar_otro_camino(char creador[MAX_FILAS][MAX_COLUMNAS], coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
	for(int i = 0; i < tope_camino; i++){
		creador[camino[i].fil][camino[i].col] = CAMINO;
	}
}

/*
* Precondiciones: Debe recibir 2 caminos validos, sus respectivos topes y un numero de camino valido (0,1,2,3,4,5).
* Postcondiciones: Creara un camino valido segun decida el usuario.
*/
void crear_camino_wasd(coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int *tope_camino_1, int *tope_camino_2 ,int n_camino){
	coordenada_t camino[MAX_LONGITUD_CAMINO];
	int tope_camino = 0;
	char creador[MAX_FILAS][MAX_COLUMNAS];
	int tope_mov;
	bool eligio_camino = false;
	if(n_camino == PRIMER_CAMINO || n_camino == SEGUNDO_CAMINO){
		tope_mov = POS_MAX_1_2;
	}else{
		tope_mov = POS_MAX_3_4;
	}
	inicializar_creador(creador, tope_mov + 1);
	dibujar_otro_camino(creador, camino_1, *tope_camino_1);
	mostrar_creador(creador,tope_mov + 1, n_camino);
	int tecla_pulsada;
	coordenada_t pos_actual;
	while(!eligio_camino){
		tecla_pulsada = getch();
		if(tope_camino == 0){
			determinar_entrada(creador, n_camino, &pos_actual, tope_mov,camino_1, *tope_camino_1);
			camino[tope_camino] = pos_actual;
			(tope_camino) ++;
			creador[pos_actual.fil][pos_actual.col] = CAMINO;
			mostrar_creador(creador,tope_mov + 1, n_camino);
		}else{
			if(tecla_pulsada == ARRIBA_MAY || tecla_pulsada == ARRIBA_MIN){
				if(es_posible_moverse(pos_actual, tecla_pulsada, tope_mov) && pos_actual.fil -1 != camino[tope_camino - 2].fil && tope_camino < MAX_LONGITUD_CAMINO){
					pos_actual.fil --;
					camino[tope_camino] = pos_actual;
					creador[pos_actual.fil][pos_actual.col] = CAMINO;
					(tope_camino) ++;
				}
				mostrar_creador(creador,tope_mov + 1, n_camino);
			}else if(tecla_pulsada == ABAJO_MAY || tecla_pulsada == ABAJO_MIN){
				if(es_posible_moverse(pos_actual, tecla_pulsada, tope_mov) && pos_actual.fil +1 != camino[tope_camino - 2].fil && tope_camino < MAX_LONGITUD_CAMINO){
					pos_actual.fil ++;
					camino[tope_camino] = pos_actual;
					creador[pos_actual.fil][pos_actual.col] = CAMINO;
					(tope_camino) ++;
				}
				mostrar_creador(creador,tope_mov + 1, n_camino);
			}else if(tecla_pulsada == IZQUIERDA_MAY || tecla_pulsada == IZQUIERDA_MIN){
				if(es_posible_moverse(pos_actual, tecla_pulsada, tope_mov) && pos_actual.col -1 != camino[tope_camino - 2].col && tope_camino < MAX_LONGITUD_CAMINO){
					pos_actual.col --;
					camino[tope_camino] = pos_actual;
					creador[pos_actual.fil][pos_actual.col] = CAMINO;
					(tope_camino) ++;
				}
				mostrar_creador(creador,tope_mov + 1, n_camino);
			}else if(tecla_pulsada == DERECHA_MAY || tecla_pulsada == DERECHA_MIN){
				if(es_posible_moverse(pos_actual, tecla_pulsada, tope_mov) && pos_actual.col +1 != camino[tope_camino - 2].col && tope_camino < MAX_LONGITUD_CAMINO){
					pos_actual.col ++;
					camino[tope_camino] = pos_actual;
					creador[pos_actual.fil][pos_actual.col] = CAMINO;
					(tope_camino) ++;
				}
				mostrar_creador(creador,tope_mov + 1, n_camino);
			}else if(tecla_pulsada == BACKSPACE){
				(tope_camino) --;
				if(pertenece_al_camino(camino_1, *tope_camino_1, pos_actual) || pertenece_al_camino(camino, tope_camino, pos_actual)){
					creador[camino[tope_camino].fil][camino[tope_camino].col] = CAMINO;
				}else{
					creador[camino[tope_camino].fil][camino[tope_camino].col] = PASTO;
				}
				pos_actual.col = camino[tope_camino - 1].col;
				pos_actual.fil = camino[tope_camino - 1].fil;
				mostrar_creador(creador,tope_mov + 1, n_camino);
			}else if(tecla_pulsada == BARRA_ESPAC){
				if(es_pos_torre_valida(n_camino, pos_actual)){
					if(n_camino == 0 || n_camino == 2 || n_camino == 4){
						llenar_camino(camino, tope_camino, camino_1, tope_camino_1);
					}else{
						llenar_camino(camino, tope_camino, camino_2, tope_camino_2);
					}
					eligio_camino = true;
				}else{
					printf(AMARILLO"  NO podes terminar tu camino aqui\n");
				}
			}
		}
	}
}

/*
* Precondiciones: Debe recibir un numero de camino valido (0,1,2,3,4,5).
* Postcondiciones: Reiniciara a 0 los topes de caminos que sean necesarios.
*/
void reiniciar_caminos(int *tope_camino_1, int *tope_camino_2 ,int n_camino){
	if(n_camino == PRIMER_CAMINO){
		*tope_camino_1 = 0;
	}else if(n_camino == SEGUNDO_CAMINO){
		*tope_camino_2 = 0;
	}else if(n_camino == CUARTO_CAMINO){
		*tope_camino_1 = 0;
		*tope_camino_2 = 0;
	}
}

/*
* Precondiciones: Debe recibir un archivo abierto para escritura, un camino valido y su respectivo tope tambien valido.
* Postcondiciones: Escribira el camino dentro del archivo con el formato dado.
*/
void escribir_camino(FILE** archivo_caminos, coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
	for(int i = 0; i < tope_camino; i++){
		fprintf(*archivo_caminos, FORMATO_CAMINO,camino[i].fil, camino[i].col);
	}
}

/*
* Precondiciones: Debe recibir un archivo valido abierto para escritura, dos caminos validos, sus respectivos topes validos, y un numero de camino valido (0,1,2,3,4,5).
* Postcondiciones: Escribira el archivo con el formato dado, escribiendo el nivel, el numero de camino y el respectivo camino.
*/
void escribir_archivo_con_caminos(FILE** archivo_caminos, coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_1, int tope_camino_2, int n_camino){
	if(n_camino == PRIMER_CAMINO){
		fprintf(*archivo_caminos, "NIVEL=1\n");
		fprintf(*archivo_caminos, "CAMINO=1\n");
		escribir_camino(archivo_caminos, camino_1, tope_camino_1);
	}else if(n_camino == SEGUNDO_CAMINO){
		fprintf(*archivo_caminos, "NIVEL=2\n");
		fprintf(*archivo_caminos, "CAMINO=2\n");
		escribir_camino(archivo_caminos, camino_2, tope_camino_2);
	}else if(n_camino == TERCER_CAMINO){
		fprintf(*archivo_caminos, "NIVEL=3\n");
		fprintf(*archivo_caminos, "CAMINO=1\n");
		escribir_camino(archivo_caminos, camino_1, tope_camino_1);
	}else if(n_camino == CUARTO_CAMINO){
		fprintf(*archivo_caminos, "CAMINO=2\n");
		escribir_camino(archivo_caminos, camino_2, tope_camino_2);
	}else if(n_camino == QUINTO_CAMINO){
		fprintf(*archivo_caminos, "NIVEL=4\n");
		fprintf(*archivo_caminos, "CAMINO=1\n");
		escribir_camino(archivo_caminos, camino_1, tope_camino_1);
	}else{
		fprintf(*archivo_caminos, "CAMINO=2\n");
		escribir_camino(archivo_caminos, camino_2, tope_camino_2);
	}
}

void crear_caminos_personalizados(char ruta[MAX_RUTA]){
	FILE* archivo_caminos = fopen(ruta,"w");
	if(!archivo_caminos){
		printf("ERROR -> NO puedo abrir este archivo\n");
		return;
	}
	coordenada_t camino_1[MAX_LONGITUD_CAMINO];
	int tope_camino_1 = 0;
	coordenada_t camino_2[MAX_LONGITUD_CAMINO];
	int tope_camino_2 = 0;
	for(int i = 0; i < CANTIDAD_CAMINOS; i++){
		crear_camino_wasd(camino_1,camino_2, &tope_camino_1, &tope_camino_2, i);
		escribir_archivo_con_caminos(&archivo_caminos,camino_1, camino_2, tope_camino_1, tope_camino_2, i);
		reiniciar_caminos(&tope_camino_1, &tope_camino_2, i);
	}
	fclose(archivo_caminos);
}

/***************************************************************************************** Crear configuracion ****************************************************************************************/

/*
* Postcondiciones: Inicializara la configuracion con todos valores por defecto.
*/
void cargar_config_defecto(configuracion_t *config){
	config -> resistencia_torres[0] = POR_DEFECTO;
	config -> resistencia_torres[1] = POR_DEFECTO;
	config -> enanos_inicio[0] = POR_DEFECTO;
	config -> enanos_inicio[1] = POR_DEFECTO;
	config -> enanos_inicio[2] = POR_DEFECTO;
	config -> enanos_inicio[3] = POR_DEFECTO;
	config -> elfos_inicio[0] = POR_DEFECTO;
	config -> elfos_inicio[1] = POR_DEFECTO;
	config -> elfos_inicio[2] = POR_DEFECTO;
	config -> elfos_inicio[3] = POR_DEFECTO;
	config -> enanos_extra[0] = POR_DEFECTO;
	config -> enanos_extra[1] = POR_DEFECTO;
	config -> enanos_extra[2] = POR_DEFECTO;
	config -> elfos_extra[0] = POR_DEFECTO;
	config -> elfos_extra[1] = POR_DEFECTO;
	config -> elfos_extra[2] = POR_DEFECTO;
	config -> animo_enanos[0] = POR_DEFECTO;
	config -> animo_enanos[1] = POR_DEFECTO;
	config -> animo_elfos[0] = POR_DEFECTO;
	config -> animo_elfos[1] = POR_DEFECTO;
	config -> velocidad_de_juego = POR_DEFECTO;
	strcpy(config -> caminos, CAM_POR_DEFECTO);
}

/*
*	Precondiciones: Debe recibir una configuracion con todos sus elementos validos y una posicion actual valida.
*	Postcondiciones: Mostrara el menu para modificar la configuracion.
*/
void actualizar_config_menu(configuracion_t config, int *opcion_actual){
	system("clear");
	if (*opcion_actual == -1){
		*opcion_actual = 21;
	}else if (*opcion_actual == 22){
		*opcion_actual = 0;
	}
	printf(AMARILLO"\n\n           ╔════════════════════════════════════════════════════════════════╗"BLANCO"\n");
	if(*opcion_actual == 0 || *opcion_actual == 1){
		printf(AMARILLO"           ║ -> Resistencia Torres                                          "AMARILLO"║\n");
	}else{
		printf(AMARILLO"           ║    Resistencia Torres                                          "AMARILLO"║\n");
	}
	if(*opcion_actual == 0){
		printf(AMARILLO"           ║    -> Resistencia Torre 1 = "VERDE"%-4d", config.resistencia_torres[0]);
	}else{
		printf(AMARILLO"           ║       Resistencia Torre 1 = "VERDE"%-4d", config.resistencia_torres[0]);
	}
	poner_espacios_segun_nombre("Resistencia Torre 1");
	if(*opcion_actual == 1){
		printf(AMARILLO"           ║    -> Resistencia Torre 2 = "VERDE"%-4d", config.resistencia_torres[1]);
	}else{
		printf(AMARILLO"           ║       Resistencia Torre 2 = "VERDE"%-4d", config.resistencia_torres[1]);
	}
	poner_espacios_segun_nombre("Resistencia Torre 2");
	if(*opcion_actual == 2 || *opcion_actual == 3 || *opcion_actual == 4 || *opcion_actual == 5){
		printf(AMARILLO"           ║ -> Enanos Inicio                                               "AMARILLO"║\n");
	}else{
		printf(AMARILLO"           ║    Enanos Inicio                                               "AMARILLO"║\n");
	}
	if(*opcion_actual == 2){
		printf(AMARILLO"           ║    -> Nivel 1 = "VERDE"%-4d", config.enanos_inicio[0]);
	}else{
		printf(AMARILLO"           ║       Nivel 1 = "VERDE"%-4d", config.enanos_inicio[0]);
	}
	poner_espacios_segun_nombre("Nivel 1");
	if(*opcion_actual == 3){
		printf(AMARILLO"           ║    -> Nivel 2 = "VERDE"%-4d", config.enanos_inicio[1]);
	}else{
		printf(AMARILLO"           ║       Nivel 2 = "VERDE"%-4d", config.enanos_inicio[1]);
	}
	poner_espacios_segun_nombre("Nivel 2");
	if(*opcion_actual == 4){
		printf(AMARILLO"           ║    -> Nivel 3 = "VERDE"%-4d", config.enanos_inicio[2]);
	}else{
		printf(AMARILLO"           ║       Nivel 3 = "VERDE"%-4d", config.enanos_inicio[2]);
	}
	poner_espacios_segun_nombre("Nivel 3");
	if(*opcion_actual == 5){
		printf(AMARILLO"           ║    -> Nivel 4 = "VERDE"%-4d", config.enanos_inicio[3]);
	}else{
		printf(AMARILLO"           ║       Nivel 4 = "VERDE"%-4d", config.enanos_inicio[3]);
	}
	poner_espacios_segun_nombre("Nivel 4");
	if(*opcion_actual == 6 || *opcion_actual == 7 || *opcion_actual == 8 || *opcion_actual == 9){
		printf(AMARILLO"           ║ -> Elfos Inicio                                                "AMARILLO"║\n");
	}else{
		printf(AMARILLO"           ║    Elfos Inicio                                                "AMARILLO"║\n");
	}
	if(*opcion_actual == 6){
		printf(AMARILLO"           ║    -> Nivel 1 = "VERDE"%-4d", config.elfos_inicio[0]);
	}else{
		printf(AMARILLO"           ║       Nivel 1 = "VERDE"%-4d", config.elfos_inicio[0]);
	}
	poner_espacios_segun_nombre("Nivel 1");
	if(*opcion_actual == 7){
		printf(AMARILLO"           ║    -> Nivel 2 = "VERDE"%-4d", config.elfos_inicio[1]);
	}else{
		printf(AMARILLO"           ║       Nivel 2 = "VERDE"%-4d", config.elfos_inicio[1]);
	}
	poner_espacios_segun_nombre("Nivel 2");
	if(*opcion_actual == 8){
		printf(AMARILLO"           ║    -> Nivel 3 = "VERDE"%-4d", config.elfos_inicio[2]);
	}else{
		printf(AMARILLO"           ║       Nivel 3 = "VERDE"%-4d", config.elfos_inicio[2]);
	}
	poner_espacios_segun_nombre("Nivel 3");
	if(*opcion_actual == 9){
		printf(AMARILLO"           ║    -> Nivel 4 = "VERDE"%-4d", config.elfos_inicio[3]);
	}else{
		printf(AMARILLO"           ║       Nivel 4 = "VERDE"%-4d", config.elfos_inicio[3]);
	}
	poner_espacios_segun_nombre("Nivel 4");
	if(*opcion_actual == 10 || *opcion_actual == 11 || *opcion_actual == 12){
		printf(AMARILLO"           ║ -> Enanos Extra                                                "AMARILLO"║\n");
	}else{
		printf(AMARILLO"           ║    Enanos Extra                                                "AMARILLO"║\n");
	}
	if(*opcion_actual == 10){
		printf(AMARILLO"           ║    -> Cantidad = "VERDE"%-4d", config.enanos_extra[0]);
	}else{
		printf(AMARILLO"           ║       Cantidad = "VERDE"%-4d", config.enanos_extra[0]);
	}
	poner_espacios_segun_nombre("Cantidad");
	if(*opcion_actual == 11){
		printf(AMARILLO"           ║    -> Costo Torre 1 = "VERDE"%-4d", config.enanos_extra[1]);
	}else{
	printf(AMARILLO"           ║       Costo Torre 1 = "VERDE"%-4d", config.enanos_extra[1]);
	}
	poner_espacios_segun_nombre("Costo Torre 1");
	if(*opcion_actual == 12){
		printf(AMARILLO"           ║    -> Costo Torre 2 = "VERDE"%-4d", config.enanos_extra[2]);
	}else{
		printf(AMARILLO"           ║       Costo Torre 2 = "VERDE"%-4d", config.enanos_extra[2]);
	}
	poner_espacios_segun_nombre("Costo Torre 2");
	if(*opcion_actual == 13 || *opcion_actual == 14 || *opcion_actual == 15){
		printf(AMARILLO"           ║ -> Elfos Extra                                                 "AMARILLO"║\n");
	}else{
		printf(AMARILLO"           ║    Elfos Extra                                                 "AMARILLO"║\n");
	}
	if(*opcion_actual == 13){
		printf(AMARILLO"           ║    -> Cantidad = "VERDE"%-4d", config.elfos_extra[0]);
	}else{
		printf(AMARILLO"           ║       Cantidad = "VERDE"%-4d", config.elfos_extra[0]);
	}
	poner_espacios_segun_nombre("Cantidad");
	if(*opcion_actual == 14){
		printf(AMARILLO"           ║    -> Costo Torre 1 = "VERDE"%-4d", config.elfos_extra[1]);
	}else{
		printf(AMARILLO"           ║       Costo Torre 1 = "VERDE"%-4d", config.elfos_extra[1]);
	}
	poner_espacios_segun_nombre("Costo Torre 1");
	if(*opcion_actual == 15){
		printf(AMARILLO"           ║    -> Costo Torre 2 = "VERDE"%-4d", config.elfos_extra[2]);
	}else{
		printf(AMARILLO"           ║       Costo Torre 2 = "VERDE"%-4d", config.elfos_extra[2]);
	}
	poner_espacios_segun_nombre("Costo Torre 2");
	if(*opcion_actual == 16 || *opcion_actual == 17){
		printf(AMARILLO"           ║ -> Animo Enanos                                                "AMARILLO"║\n");
	}else{
		printf(AMARILLO"           ║    Animo Enanos                                                "AMARILLO"║\n");
	}
	if(*opcion_actual == 16){
		printf(AMARILLO"           ║    -> Porcentaje Fallo = "VERDE"%-4d", config.animo_enanos[0]);
	}else{
		printf(AMARILLO"           ║       Porcentaje Fallo = "VERDE"%-4d", config.animo_enanos[0]);
	}
	poner_espacios_segun_nombre("Porcentaje Fallo");
	if(*opcion_actual == 17){
		printf(AMARILLO"           ║    -> Porcentaje Critico = "VERDE"%-4d", config.animo_enanos[1]);
	}else{
		printf(AMARILLO"           ║       Porcentaje Critico = "VERDE"%-4d", config.animo_enanos[1]);
	}
	poner_espacios_segun_nombre("Porcentaje Critico");
	if(*opcion_actual == 18 || *opcion_actual == 19){
		printf(AMARILLO"           ║ -> Animo Elfos                                                 "AMARILLO"║\n");
	}else{
		printf(AMARILLO"           ║    Animo Elfos                                                 "AMARILLO"║\n");
	}
	if(*opcion_actual == 18){
		printf(AMARILLO"           ║    -> Porcentaje Fallo = "VERDE"%-4d", config.animo_elfos[0]);
	}else{
		printf(AMARILLO"           ║       Porcentaje Fallo = "VERDE"%-4d", config.animo_elfos[0]);
	}
	poner_espacios_segun_nombre("Porcentaje Fallo");
	if(*opcion_actual == 19){
		printf(AMARILLO"           ║    -> Porcentaje Critico = "VERDE"%-4d", config.animo_elfos[1]);
	}else{
		printf(AMARILLO"           ║       Porcentaje Critico = "VERDE"%-4d", config.animo_elfos[1]);
	}
	poner_espacios_segun_nombre("Porcentaje Critico");
	if(*opcion_actual == 20){
		if(config.velocidad_de_juego == -1){
			printf(AMARILLO"           ║ -> Velocidad de Juego = "VERDE"-1                                     "AMARILLO"║\n");
		}else{
			printf(AMARILLO"           ║ -> Velocidad de Juego = "VERDE"%.3f                                  "AMARILLO"║\n", config.velocidad_de_juego);
		}
  	}else{
		if(config.velocidad_de_juego == -1){
			printf(AMARILLO"           ║    Velocidad de Juego = "VERDE"-1                                     "AMARILLO"║\n");
		}else{
			printf(AMARILLO"           ║    Velocidad de Juego = "VERDE"%.3f                                  "AMARILLO"║\n", config.velocidad_de_juego);
		}
	}
	if(*opcion_actual == 21){
		printf(AMARILLO"           ║ -> Camino = "VERDE"%s ", config.caminos);
	}else{
		printf(AMARILLO"           ║    Camino = "VERDE"%s ", config.caminos);
	}
	poner_espacios_segun_nombre(config.caminos);
	printf(AMARILLO"           ╠════════════════════════════════════════════════════════════════╣"BLANCO"\n");
	printf(AMARILLO"           ║ -> Para moverte por el menu : "VERDE"WASD                             "AMARILLO"║\n");
	printf(AMARILLO"           ║ -> Para modificar un valor: "VERDE"ESPACIO                            "AMARILLO"║\n");
	printf(AMARILLO"           ║ -> Para cerrar el configurador y guardar: "VERDE"F                    "AMARILLO"║\n");
	printf(AMARILLO"           ╚════════════════════════════════════════════════════════════════╝"BLANCO"\n");
}

/*
* Postcondiciones: Modificara el valor de la velocidad de juego por el ingresado por el usuario.
*/
void modificar_velocidad_juego(float *velocidad_de_juego){
	printf(AMARILLO"\n-> Inserta el valor de la velocidad que desees (Por defecto = -1): "VERDE);
	scanf("%f",velocidad_de_juego);
	while((*velocidad_de_juego < 0.125) && (*velocidad_de_juego != -1)){
		printf(AMARILLO"\n-> Ese valor no es valido (Por defecto = -1): "VERDE);
		scanf("%f",velocidad_de_juego);
	}
}

/*
* Postcondiciones: Modificara la ruta del camino por la ingresada por el usuario.
*/
void modificar_ruta_caminos(char ruta[MAX_RUTA]){
	printf(AMARILLO"\n-> Inserta la ruta donde se encuentra tu camino (Por defecto = -1): "VERDE);
	scanf("%s", ruta);
}

/*
* Postcondiciones: Modificara la resistencia de la torre por la ingresada por el usuario.
*/
void modificar_resistencia_torres(int *resistencia_torre){
	printf(AMARILLO"\n-> Inserta el valor de la resistencia que desees (Por defecto = -1): "VERDE);
	scanf("%i",resistencia_torre);
	while(((*resistencia_torre < MIN_RESIST_TORRE) || (*resistencia_torre > MAXIMO_RESIST_TORRE)) && (*resistencia_torre != -1)){
		printf(AMARILLO"\n-> Ese valor no es valido (Por defecto = -1): "VERDE);
		scanf("%i",resistencia_torre);
	}
}

/*
* Postcondiciones: Modificara la cantidad de defensores por la ingresada por el usuario.
*/
void modificar_cant_defensores(int *cant_defensores){
	printf(AMARILLO"\n-> Inserta el valor de la cantidad de defensores que desees (Por defecto = -1): "VERDE);
	scanf("%i",cant_defensores);
	while(((*cant_defensores < MIN_DEFENSORES_CONFIG) || (*cant_defensores > MAX_DEFENSORES_CONFIG)) && (*cant_defensores != -1)){
		printf(AMARILLO"\n-> Ese valor no es valido (Por defecto = -1): "VERDE);
		scanf("%i",cant_defensores);
	}
}

/*
* Postcondiciones: Modificara el costo que le cuesta a la torre un defensor extra por el ingresado por el usuario.
*/
void modificar_costo_a_torre(int *costo){
	printf(AMARILLO"\n-> Inserta el valor del costo a la torre que desees (Por defecto = -1): "VERDE);
	scanf("%i",costo);
	while((*costo < MIN_COSTO) && (*costo != -1)){
		printf(AMARILLO"\n-> Ese valor no es valido (Por defecto = -1): "VERDE);
		scanf("%i",costo);
	}
}

/*
* Precondiciones: Debe recibir un nombre de porcentaje valido (Critico o fallo).
* Postcondiciones: Modificara el porcentaje por el ingresado por el usuario.
*/
void modificar_porcentaje(int *porcentaje, char nombre[MAX_NOMBRE_PORCENTAJE]){
	printf(AMARILLO"\n-> Inserta el valor del porcentaje de %s que desees (Por defecto = -1): "VERDE, nombre);
	scanf("%i",porcentaje);
	while(((*porcentaje < MIN_PORCENTAJE) || (*porcentaje > MAX_PORCENTAJE)) && (*porcentaje != -1)){
		printf(AMARILLO"\n-> Ese valor no es valido (Por defecto = -1): "VERDE);
		scanf("%i",porcentaje);
	}
}

/*
*	Precondiciones: Debe recibir una opcion valida.
*	Postcondiciones: Dejara al usuario modificar la opcion elegida.
*/
void entrar_menu_config(configuracion_t *config, int opcion_actual){
	if(opcion_actual == 0){
		modificar_resistencia_torres(&(config -> resistencia_torres[0]));
	}else if(opcion_actual == 1){
		modificar_resistencia_torres(&(config -> resistencia_torres[1]));
	}else if(opcion_actual == 2){
		modificar_cant_defensores(&(config -> enanos_inicio[0]));
	}else if(opcion_actual == 3){
		modificar_cant_defensores(&(config -> enanos_inicio[1]));
	}else if(opcion_actual == 4){
		modificar_cant_defensores(&(config -> enanos_inicio[2]));
	}else if(opcion_actual == 5){
		modificar_cant_defensores(&(config -> enanos_inicio[3]));
	}else if(opcion_actual == 6){
		modificar_cant_defensores(&(config -> elfos_inicio[0]));
	}else if(opcion_actual == 7){
		modificar_cant_defensores(&(config -> elfos_inicio[1]));
	}else if(opcion_actual == 8){
		modificar_cant_defensores(&(config -> elfos_inicio[2]));
	}else if(opcion_actual == 9){
		modificar_cant_defensores(&(config -> elfos_inicio[3]));
	}else if(opcion_actual == 10){
		modificar_cant_defensores(&(config -> enanos_extra[0]));
	}else if(opcion_actual == 11){
		modificar_costo_a_torre(&(config -> enanos_extra[1]));
	}else if(opcion_actual == 12){
		modificar_costo_a_torre(&(config -> enanos_extra[2]));
	}else if(opcion_actual == 13){
		modificar_cant_defensores(&(config -> elfos_extra[0]));
	}else if(opcion_actual == 14){
		modificar_costo_a_torre(&(config -> elfos_extra[1]));
	}else if(opcion_actual == 15){
		modificar_costo_a_torre(&(config -> elfos_extra[2]));
	}else if(opcion_actual == 16){
		modificar_porcentaje(&(config -> animo_enanos[0]),"fallo");
	}else if(opcion_actual == 17){
		modificar_porcentaje(&(config -> animo_enanos[1]),"critico");
	}else if(opcion_actual == 18){
		modificar_porcentaje(&(config -> animo_elfos[0]),"fallo");
	}else if(opcion_actual == 19){
		modificar_porcentaje(&(config -> animo_elfos[1]),"critico");
	}else if(opcion_actual == 20){
		modificar_velocidad_juego(&(config -> velocidad_de_juego));
	}else if(opcion_actual == 21){
		modificar_ruta_caminos(config -> caminos);
  }
}

/*
* Precondiciones: Debe recibir un archivo abierto para escritura y una configuracion con todos sus elementos validos.
* Postcondiciones: Escribira en el archivo la configuracion ingresada por el usuario.
*/
void escribir_configuracion(FILE** archivo_config, configuracion_t config){
	fprintf(*archivo_config, "RESISTENCIA_TORRES=%i,%i\n", config.resistencia_torres[0], config.resistencia_torres[1]);
	fprintf(*archivo_config, "ENANOS_INICIO=%i,%i,%i,%i\n", config.enanos_inicio[0], config.enanos_inicio[1], config.enanos_inicio[2], config.enanos_inicio[3]);
	fprintf(*archivo_config, "ELFOS_INICIO=%i,%i,%i,%i\n", config.elfos_inicio[0], config.elfos_inicio[1], config.elfos_inicio[2], config.elfos_inicio[3]);
	fprintf(*archivo_config, "ENANOS_EXTRA=%i,%i,%i\n", config.enanos_extra[0], config.enanos_extra[1], config.enanos_extra[2]);
	fprintf(*archivo_config, "ELFOS_EXTRA=%i,%i,%i\n", config.elfos_extra[0], config.elfos_extra[1], config.elfos_extra[2]);
	fprintf(*archivo_config, "ENANOS_ANIMO=%i,%i\n", config.animo_enanos[0], config.animo_enanos[1]);
	fprintf(*archivo_config, "ELFOS_ANIMO=%i,%i\n", config.animo_elfos[0], config.animo_elfos[1]);
	fprintf(*archivo_config, "VELOCIDAD=%f\n", config.velocidad_de_juego);
	fprintf(*archivo_config, "CAMINOS=%s\n", config.caminos);
}

/*
* Postcondiones: Mostrara por pantalla la presentacion del editor de configuraciones.
*/
void presentacion_config_menu(){
	system("clear");
	printf(AMARILLO"\n\n           ╔════════════════════════════════════════════════════════════════╗"BLANCO"\n");
	printf(AMARILLO"           ║                                                                ║"BLANCO"\n");
	printf(AMARILLO"           ║                                                                ║"BLANCO"\n");
	printf(AMARILLO"           ║             Bienvenido al editor de configuraciones            ║"BLANCO"\n");
	printf(AMARILLO"           ║                                                                ║"BLANCO"\n");
	printf(AMARILLO"           ║                                                                ║"BLANCO"\n");
	printf(AMARILLO"           ╚════════════════════════════════════════════════════════════════╝"BLANCO"\n");
	detener_el_tiempo(2);
	system("clear");
}

/*
* Postcondiones: Mostrara por pantalla que se termino de configurar.
*/
void mostrar_fin_configuracion(){
	detener_el_tiempo(0.5);
	system("clear");
	printf(AMARILLO"\n\n           ╔════════════════════════════════════════════════════════════════╗"BLANCO"\n");
	printf(AMARILLO"           ║                                                                ║"BLANCO"\n");
	printf(AMARILLO"           ║                                                                ║"BLANCO"\n");
	printf(AMARILLO"           ║                    SE HA GUARDADO CON EXITO                    ║"BLANCO"\n");
	printf(AMARILLO"           ║                                                                ║"BLANCO"\n");
	printf(AMARILLO"           ║                                                                ║"BLANCO"\n");
	printf(AMARILLO"           ╚════════════════════════════════════════════════════════════════╝"BLANCO"\n");
	detener_el_tiempo(2);
	system("clear");
}

void crear_configuracion_personalizada(char ruta[MAX_RUTA]){
	FILE* arch_config = fopen(ruta, "w");
	if(!(arch_config)){
		printf("ERROR -> NO puedo escribir ese archivo\n");
		return;
	}
	configuracion_t config;
	int opcion_actual = 0;
	int tecla_pulsada;
	bool termino_de_configurar = false;
	cargar_config_defecto(&config);
	presentacion_config_menu();
	actualizar_config_menu(config, &opcion_actual);
	while(!termino_de_configurar){
		tecla_pulsada = getch();
		if(tecla_pulsada == ARRIBA_MAY || tecla_pulsada == ARRIBA_MIN){
			opcion_actual --;
			actualizar_config_menu(config, &opcion_actual);
		}else if(tecla_pulsada == ABAJO_MAY || tecla_pulsada == ABAJO_MIN){
			opcion_actual ++;
			actualizar_config_menu(config, &opcion_actual);
		}else if(tecla_pulsada == BARRA_ESPAC){
			entrar_menu_config(&config, opcion_actual);
			actualizar_config_menu(config, &opcion_actual);
		}else if(tecla_pulsada == LETRA_F_MAX || tecla_pulsada == LETRA_F_MIN){
			escribir_configuracion(&arch_config, config);
			termino_de_configurar = true;
			mostrar_fin_configuracion();
		}
	}
}

/******************************************************************************************* Mostrar ranking *****************************************************************************************/

/*
* Postcondiciones: Mostrara un mensaje de que no se pudo abrir el ranking personalizado.
*/
void mostrar_mensaje_error(){
	printf(AMARILLO"\n\n               ╔═══════════════════════════════════════════════════════════════╗"BLANCO"\n");
	printf(AMARILLO"               ║ NO existe ese ranking, se mostrara                            ║\n");
	printf(AMARILLO"               ║ el ranking con la configuracion DEFAULT                       ║\n");
	printf(AMARILLO"               ╚═══════════════════════════════════════════════════════════════╝"BLANCO"\n");
	detener_el_tiempo(2);
	system("clear");
}

void mostrar_ranking(int cantidad_rank, char ruta_ranking[MAX_RUTA]){
	system("clear");
	FILE* arch_ranking;
	arch_ranking = fopen(ruta_ranking, "r");
	if(!arch_ranking && (strcmp(ruta_ranking, "ranking.csv") != 0)){
		mostrar_mensaje_error();
		strcpy(ruta_ranking, "ranking.csv");
		arch_ranking = fopen(ruta_ranking, "r");
	}
	if(!arch_ranking){
		printf(AMARILLO"-> NO existe el ranking DEFAULT\n\n");
		return;
	}
	char nombre[MAX_NOMBRE];
	int puntaje;
	int cantidad_leidos = 0;
	int leidos = fscanf(arch_ranking, FORMATO_RANKING, nombre, &puntaje);
	printf(AMARILLO"\n\n               ╔═══════════════════════════════════════════════════════════════╗"BLANCO"\n");
	if(cantidad_rank == -1){
		while(leidos == 2){
			if(cantidad_leidos == 0){
				printf(AMARILLO"               ║ 1) ");
			}else if(cantidad_leidos == 1){
				printf(AMARILLO"               ║ 2) ");
			}else if(cantidad_leidos == 2){
				printf(AMARILLO"               ║ 3) ");
			}else{
				printf(AMARILLO"               ║ -> ");
			}
			printf(AMARILLO"%s : %-5d ", nombre, puntaje);
			poner_espacios_segun_nombre(nombre);
			leidos = fscanf(arch_ranking, FORMATO_RANKING, nombre, &puntaje);
			cantidad_leidos ++;
		}
	}else{
		while((leidos == 2) && (cantidad_leidos < cantidad_rank)){
			if(cantidad_leidos == 0){
				printf(AMARILLO"               ║ 1) ");
			}else if(cantidad_leidos == 1){
				printf(AMARILLO"               ║ 2) ");
			}else if(cantidad_leidos == 2){
				printf(AMARILLO"               ║ 3) ");
			}else{
				printf(AMARILLO"               ║ -> ");
			}
			printf(AMARILLO"%s : %-5d ", nombre, puntaje);
			poner_espacios_segun_nombre(nombre);
			leidos = fscanf(arch_ranking, FORMATO_RANKING, nombre, &puntaje);
			cantidad_leidos ++;
		}
	}
	printf(AMARILLO"               ╚═══════════════════════════════════════════════════════════════╝"BLANCO"\n\n\n");

}

/****************************************************************************************** Mostrar comandos *****************************************************************************************/

void mostrar_comandos(){
	printf(AMARILLO"\n -> No reconozco esta accion!\n\n");
	printf(" -> Comandos disponibles: \n\n");
	printf("    -> jugar *config=<archivo> *grabacion=<archivo>\n\n");
	printf("    -> ranking *listar=<cantidad> *config=<archivo>\n\n");
	printf("    -> crear_configuracion <archivo>\n\n");
	printf("    -> poneme_la_repe grabacion=<archivo> *velocidad=<velocidad>\n\n");
	printf("    -> crear_camino <archivo>\n\n");
	printf("    -> Aquellos parametros con un * son opcionales\n\n");
}

/*****************************************************************************************************************************************************************************************************/
