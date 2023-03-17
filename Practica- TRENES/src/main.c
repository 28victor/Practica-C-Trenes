#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "rlutil.h"
#include <windows.h>
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"

int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	srand(time(NULL));

	enum OPCIOMENU opcio;

	ESTACIO est[MAXESTACIO];
	int maxEstacions=0;

	do
	{
		pintaMenu();
		printf("\n\nIntrodueix quina opcio vols? [1..%d]\n",SORTIR);
		opcio=demanaNumeroEntreDosValors(1,SORTIR);
	
		// printf("\nL'opcio %d es: ",opcio);
		switch (opcio)
		{
			case SORTIR: printf("Adeu");break;
			case ALTAESTACIO: altaEstacio(&maxEstacions, est);break;
			case MOSTRAESTACIONS: mostraEstacions(&maxEstacions, est);break;
			case INSERIRRUTA: printf("inserir ruta");break;
			case MOSTRARUTA: printf("mostrar ruta");break;
			case MOSTRARUTESESTACIO: printf("Mostrar rutes estacion");break;
			case KMENTREESTACIONS: printf("KM entre estacions");break;
			case MOSTRARGRAFIC: printf("Mostrar grafic rutes");break;
		}
		printf("\n");
	}while (opcio!=SORTIR);


	acabament();
	return 0;
}
