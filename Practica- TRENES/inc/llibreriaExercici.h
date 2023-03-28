#ifndef D8E5564E_A998_46E6_9A70_0B73488F1AF3
#define D8E5564E_A998_46E6_9A70_0B73488F1AF3
// incloure les llibreries que es necessiten
#include <stdbool.h>

#define MAXVECTOR 5
#define MAXCADENA 40
#define MAXESTACIO 40

typedef struct
{
     int x;
     int y;
}XY;

typedef struct
{
     char nom[MAXCADENA];
     XY coords;
}ESTACIO;

typedef struct
{
     char nom[MAXCADENA];
     int index[MAXESTACIO];
     int iqtt;
}RUTA;

enum OPCIOMENU
{
     ALTAESTACIO = 1,
     MOSTRAESTACIONS,
     INSERIRRUTA,
     MOSTRARUTA,
     MOSTRARUTESESTACIO,
     KMENTREESTACIONS,
     SORTIR
};

void continuar (void);
void altaEstacio (int *, ESTACIO []);
void mostraEstacions(int ,ESTACIO []);
bool validarNomE (char [], ESTACIO [], int *);
bool validarCoords(int , int , ESTACIO [], int *);
bool validarSinRuta(char []);
void inserirRuta(ESTACIO [], RUTA [], int , int *);
void separarNom(char [], char [], int *);
void dividirEstacions(char [], RUTA [], int , ESTACIO [], int );
bool allExists(char [][MAXESTACIO], ESTACIO [], int , int );
bool noRepit(int, RUTA);
bool repetirRuta(char [], RUTA [], int *);
int cercaPosicioEstacio(char [], ESTACIO [], int );
void mostrarRutas(int , RUTA [], ESTACIO []);
void mostrarRutaEspecifica(RUTA [], int , ESTACIO [], int );
void calculaDistanciaRutes(ESTACIO [], RUTA [], int );
void printarEstacionsKm(ESTACIO [], RUTA );
int posRuta(RUTA [], int , char []);
















#endif /* D8E5564E_A998_46E6_9A70_0B73488F1AF3 */
