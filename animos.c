#include <stdio.h>
#include <stdbool.h>
#include "animos.h"

#define BLANCO "\033[0m"
#define AMARILLO "\033[1;33m"
#define VERDE "\033[1;32m"
#define A_MODIFICAR -1
#define STR_A_MODIFICAR 'x'
const int MINIMO_DIAS = 1;
const int MAXIMO_DIAS = 30;
const int MINIMO_HORAS_SUENIO = 0;
const int MAXIMO_HORAS_SUENIO = 12;
const char MANIANA = 'M';
const char TARDE = 'T';
const char NOCHE = 'N';
const char PIE_DERECHO = 'D';
const char PIE_IZQUIERDO = 'I';
const char ENSALADA = 'E';
const char HAMBURGUESA = 'H';
const char PIZZA = 'P';
const char GUISO = 'G';
const int HUMEDAD_ALTA = 75;
const int HUMEDAD_MODERADA = 50;
const int HUMEDAD_BAJA = 25;
const int VIENTO_FUERTE = 75;
const int VIENTO_MODERADO = 50;
const int VIENTO_TRANQUILO = 25;
const int PRIMER_DIA = 1;
const int DECIMO_DIA = 10;
const int VIGESIMO_DIA = 20;
const int CINCO_HORAS_SUENIO = 5;
const int OCHO_HORAS_SUENIO = 8;
const int CINCO_PUNTOS = 5;
const int DIEZ_PUNTOS = 10;
const int QUINCE_PUNTOS = 15;
const int VEINTE_PUNTOS = 20;
const int TREINTA_Y_CINCO_PUNTOS = 35;
const char ANIMO_MALO = 'M';
const char ANIMO_REGULAR = 'R';
const char ANIMO_BUENO = 'B';

/*
*Postcondiciones: Devolvera true si el dia es igual a un dia del mes, y false si no lo es.
*/
bool es_dia_valido(int dia){
	return (dia >= MINIMO_DIAS && dia <= MAXIMO_DIAS);
}

/*
*Postcondiciones: Devolvera true si la hora del dia es igual a una de las opciones (Mañana, tarde, noche), y false si no lo es.
*/
bool es_hora_valida(char hora_del_dia){
	return (hora_del_dia == MANIANA || hora_del_dia == TARDE || hora_del_dia == NOCHE);
}

/*
*Postcondiciones: Devolvera true si el pie es igual a una de las dos opciones (izquierdo y derecho), y false si no lo es.
*/
bool es_pie_valido(char pie){
	return (pie == PIE_IZQUIERDO || pie == PIE_DERECHO);
}

/*
*Postcondiciones: Devolvera true si la cena es igual a una de las opciones(ensalada, hamburguesa, pizza, guiso), y false si no lo es.
*/
bool es_cena_valida(char cena){
	return (cena == ENSALADA || cena == HAMBURGUESA || cena == PIZZA || cena == GUISO);
}

/*
*Postcondiciones: Devolvera true si la cantidad de horas de sueño está en el rango preestablecido, y false si no lo está.
*/
bool son_horas_suenio_validas(int suenio){
	return (suenio >= MINIMO_HORAS_SUENIO && suenio <= MAXIMO_HORAS_SUENIO);
}

/*
*Postcondiciones: Devolvera el dia del mes.
*/
void preguntar_dia_del_mes (int *dia){
	printf(""AMARILLO" -> ¿Que dia es hoy? (1-30): "VERDE"");
	scanf("%i",dia);
	while (!es_dia_valido(*dia)){
		printf(""AMARILLO" -> Escribe un dia valido (1-30): "VERDE"");
		scanf("%i",dia);
	}
}

/*
*Postcondiciones: Devolvera la hora del dia.
*/
void preguntar_hora_del_dia(char *hora_del_dia){
	printf(""AMARILLO" -> ¿Que hora es? (Mañana(M), Tarde(T), Noche(N)): "VERDE"");
	scanf(" %c",hora_del_dia);
	while(!es_hora_valida(*hora_del_dia)){
		printf(""AMARILLO" -> Escribe una hora valida (Mañana(M), Tarde(T), Noche(N)): "VERDE"");
		scanf(" %c",hora_del_dia);
	}
	printf("\n");
}

/*
*Postcondiciones: Devolvera con que pie se levantó.
*/
void preguntar_pie_levanto(char *pie){
	printf(""AMARILLO" -> Hoy con que pie se levanto? (Izquierdo(I), Derecho(D)): "VERDE"");
	scanf(" %c", pie);
	while(!es_pie_valido(*pie)){
		printf(""AMARILLO" -> Escribe una opcion valida (Izquierdo(I), Derecho(D)): "VERDE"");
		scanf(" %c",pie);
	}
}

/*
*Postcondiciones: Devolvera lo que cenó la noche anterior
*/
void preguntar_cena_noche_anterior(char *cena){
	printf(""AMARILLO" -> ¿Qué cenó la noche anterior? (Ensalada(E), Hamburguesa(H), Pizza(P), Guiso(G)): "VERDE"");
	scanf(" %c", cena);
	while(!es_cena_valida(*cena)){
		printf(""AMARILLO" -> Escribe una opcion valida (Ensalada(E), Hamburguesa(H), Pizza(P), Guiso(G)): "VERDE"");
		scanf(" %c",cena);
	}
}

/*
* Postcondiones: Devolvera la cantidad de horas de sueño
*/
void pregunar_cuantas_horas_durmio(int *suenio){
	printf(""AMARILLO" -> ¿Cuantas horas durmió anoche? (0-12h): "VERDE"");
	scanf(" %i", suenio);
	while(!son_horas_suenio_validas(*suenio)){
		printf(""AMARILLO" -> Escribe una cantidad valida (0-12h): \n"VERDE"");
		scanf(" %i",suenio);
	}
	printf("\n");
}

/*
* Precondiciones: El dato del dia del mes debe ser un dia posible.
* Postcondiciones: Devolvera la velocidad del viento.
*/
int velocidad_viento_segun_dia(int dia){
		if(dia >= PRIMER_DIA && dia <= DECIMO_DIA){
			return VIENTO_FUERTE;
		}else if(dia > DECIMO_DIA && dia <= VIGESIMO_DIA){
			return VIENTO_MODERADO;
		}else{
			return VIENTO_TRANQUILO;
		}
}

/*
* Precondiones: El dato de la hora del dia debe corresponder a una de las opciones validas.
* Postcondiciones: Devolvera el porcentaje de humedad.
*/
int humedad_ambiente_segun_hora(int hora_del_dia){
	if (hora_del_dia == MANIANA){
		return HUMEDAD_ALTA;
	}else if(hora_del_dia == TARDE){
		return HUMEDAD_BAJA;
	}else{
		return HUMEDAD_MODERADA;
	}
}

/*
* Precondiciones: Los datos deben ser iguales a alguna de las opciones validas.
* Postcondiciones: Devolvera la cantidad de puntos obtenidos segun los datos que condicionan el animo.
*/
int puntos_animo(char pie, char cena, int horas_suenio){
	int puntos = 0;
	if(pie == PIE_DERECHO){
		puntos += DIEZ_PUNTOS;
	}
	if(cena == ENSALADA){
		puntos += VEINTE_PUNTOS;
	}else if(cena == HAMBURGUESA){
		puntos += QUINCE_PUNTOS;
	}else if(cena == PIZZA){
		puntos += DIEZ_PUNTOS;
	}else if(cena == GUISO){
		puntos += CINCO_PUNTOS;
	}
	if (horas_suenio >= CINCO_HORAS_SUENIO && horas_suenio <= OCHO_HORAS_SUENIO){
		puntos += DIEZ_PUNTOS;
	}else if(horas_suenio > OCHO_HORAS_SUENIO){
		puntos += VEINTE_PUNTOS;
	}
	return puntos;
}

/*
* Precondiciones: Los datos deben ser iguales a alguna de las opciones validas.
* Postcondiciones: Devolvera un estado de animo (M, R o B) segun los datos obtenidos.
*/
char animo_personaje(char pie, char cena, int horas_suenio){
	int puntos = puntos_animo(pie, cena, horas_suenio);
	if (puntos >= CINCO_PUNTOS && puntos <= VEINTE_PUNTOS){
		return ANIMO_MALO;
	}else if (puntos > VEINTE_PUNTOS && puntos <= TREINTA_Y_CINCO_PUNTOS){
		return ANIMO_REGULAR;
	}else{
		return ANIMO_BUENO;
	}
}

/*
* Precondiciones: Los datos de la velocidad del viento, humedad y animo de ambos deben ser valido.
* Postcondiciones: Mostrar el resultado el resultado obtenido con los datos.
*/
void mostrar_mensaje_final(int velocidad_del_viento, int humedad, char animo_legolas, char animo_gimli){

	if(velocidad_del_viento == VIENTO_FUERTE){
		printf(""AMARILLO" -> Un fuerte viento, ");
	}
	else if(velocidad_del_viento == VIENTO_MODERADO){
		printf(""AMARILLO" -> Un viento moderado, ");
	}
	else {
		printf(""AMARILLO" -> Un viento tranquilo, ");
	}

	if(humedad == HUMEDAD_ALTA) {
		printf("mucha humedad, ");
	}
	else if(humedad == HUMEDAD_MODERADA){
		printf("humedad moderada, ");
	}
	else {
		printf("muy poca humedad, ");
	}

	if(animo_legolas == ANIMO_BUENO){
		printf ("un gran dia para Legolas ");
	}
	else if(animo_legolas == ANIMO_REGULAR){
		printf("un dia normal para Legolas ");
	}
	else{
		printf("un mal dia para Legolas ");
	}

	if(animo_gimli == ANIMO_BUENO){
		printf("y un gran dia para Gimli.\n");
	}
	else if(animo_gimli == ANIMO_REGULAR){
		printf("y dia normal para Gimli.\n");
	}
	else{
		printf("y un mal dia para Gimli.\n");
	}
}

/*
* Precondiciones: Los datos de la velocidad del viento, humedad y animo de ambos debe ser valido.
* Postcondiciones: Mostrar el resultado el resultado obtenido con los datos, de forma resumida.
*/
void mostrar_resumen (int velocidad_del_viento, int humedad, char animo_legolas, char animo_gimli){
	printf(""AMARILLO" -> Resumen: %i %i %c %c.\n",velocidad_del_viento, humedad, animo_legolas, animo_gimli);
}

void mostrar_presentacion(){
	printf("\n"AMARILLO" -> Bienvenido a la epica batalla del Abismo de Helm, empecemos con las preguntas\n\n");
}

void presentar_animo_legolas(){
	printf(AMARILLO" -> Veamos como anda de animo Legolas\n");
}

void presentar_animo_gimli(){
	printf(AMARILLO" -> Ahora veamos como anda de animo Gimli\n");
}

void salto_de_linea(){
	printf("\n");
}

void animos(int *viento, int *humedad, char *animo_legolas, char *animo_gimli){
	int dia = 0;
	char hora_del_dia = '.';
	char pie_legolas = '.';
	char cena_legolas = '.';
	int horas_suenio_legolas = 0;
	char pie_gimli = '.';
	char cena_gimli = '.';
	int horas_suenio_gimli = 0;

	mostrar_presentacion();
	if(*viento == A_MODIFICAR){
		preguntar_dia_del_mes(&dia);
	}
	if(*humedad == A_MODIFICAR){
		preguntar_hora_del_dia(&hora_del_dia);
	}
	if(*animo_legolas == STR_A_MODIFICAR){
		presentar_animo_legolas();
		preguntar_pie_levanto(&pie_legolas);
		preguntar_cena_noche_anterior(&cena_legolas);
		pregunar_cuantas_horas_durmio(&horas_suenio_legolas);
	}
	if(*animo_gimli == STR_A_MODIFICAR){
		presentar_animo_gimli();
		preguntar_pie_levanto(&pie_gimli);
		preguntar_cena_noche_anterior(&cena_gimli);
		pregunar_cuantas_horas_durmio(&horas_suenio_gimli);
	}
	*viento = velocidad_viento_segun_dia(dia);
	*humedad =  humedad_ambiente_segun_hora(hora_del_dia);
	*animo_legolas = animo_personaje(pie_legolas, cena_legolas, horas_suenio_legolas);
	*animo_gimli = animo_personaje(pie_gimli, cena_gimli, horas_suenio_gimli);
	mostrar_mensaje_final(*viento, *humedad, *animo_legolas, *animo_gimli);
	mostrar_resumen(*viento, *humedad, *animo_legolas, *animo_gimli);
}
