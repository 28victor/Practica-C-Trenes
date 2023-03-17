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

enum OPCIOMENU
{
     ALTAESTACIO = 1,
     MOSTRAESTACIONS,
     INSERIRRUTA,
     MOSTRARUTA,
     MOSTRARUTESESTACIO,
     KMENTREESTACIONS,
     MOSTRARGRAFIC,
     SORTIR
};


void altaEstacio (int *, ESTACIO []);
void mostraEstacions(int *,ESTACIO []);
bool validarNomE (char [], ESTACIO [], int *);
bool validarCoords(int , int , ESTACIO [], int *);








#endif /* D8E5564E_A998_46E6_9A70_0B73488F1AF3 */
