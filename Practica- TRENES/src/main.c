#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "rlutil.h"
#include <windows.h>
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"
#include <math.h>

int main()
{
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
	srand(time(NULL));

	enum OPCIOMENU opcio;

	ESTACIO est[MAXESTACIO];
	RUTA rut[MAXESTACIO];
	int qttEstacions = 0;
	int qttRutas = 0;

	do
	{
		pintaMenu();
		printf("\n\nIntrodueix quina opcio vols? [1..%d] ", SORTIR);
		opcio = demanaNumeroEntreDosValors(1, SORTIR);

		switch (opcio)
		{
		case SORTIR:
			printf("Bye!");
			break;
		case ALTAESTACIO:
			altaEstacio(&qttEstacions, est);
			premCont();
			break;
		case MOSTRAESTACIONS:
			mostraEstacions(qttEstacions, est);
			premCont();
			break;
		case INSERIRRUTA:
			inserirRuta(est, rut, qttEstacions, &qttRutas);
			premCont();
			break;
		case MOSTRARUTA:
			mostrarRutas(qttRutas, rut, est);
			premCont();
			break;
		case MOSTRARUTESESTACIO:
			mostrarRutas(qttRutas, rut, est);
			mostrarRutaEspecifica(rut, qttRutas, est, qttEstacions);
			premCont();
			break;
		case KMENTREESTACIONS:
			mostrarRutas(qttRutas, rut, est);
			calculaDistanciaRutes(est, rut, qttRutas);
			premCont();
			break;
		// case MOSTRARGRAFIC:
		// 	printf("Mostrar grafic rutes");
		// 	break;
		}
		printf("\n");
	} while (opcio != SORTIR);

	acabament();
	return 0;
}
