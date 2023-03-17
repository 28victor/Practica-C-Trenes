#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rlutil.h"
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"

// void afegirPacient(PACIENT p[],int maxPacient,int *totalPacients)
// {
//     if (*totalPacients==maxPacient)
//     {
//         printf("\nHospital Ple");
//     }
//     else
//     {
//         PACIENT nouPacient;
//         nouPacient=demanarPacient();
//         //demanarPacient2(&nouPacient);

//         if (cercaPacient(p,*totalPacients,nouPacient.nom))
//         {
//             printf("\nEsperi si us plau, vost� ja est� a la cua d'espera");
//         }
//         else
//         {
//             int posInserir=cercaPosicioInserir(p,*totalPacients,nouPacient.prioritat);
//             desplacarPacients(p,*totalPacients,posInserir);
//             p[posInserir]=nouPacient;
//             (*totalPacients)++;
//         }
//     }
// }

// ESTACIO demanarPacient()
// {
//     ESTACIO unPacient;

//     printf("\nIntrodueix el nom: ");
//     entrarCadena(unPacient.nom,sizeof(unPacient.nom));

//     printf("\nIntrodueix la prioritat: [1..3] ");
//     unPacient.prioritat=demanaNumeroEntreDosValors(1,3);

//     return unPacient;
// }

// // void demanarPacient2(PACIENT *unPacient)
// // {
// //     printf("\nIntrodueix el nom: ");
// //     entrarCadena((*unPacient).nom,sizeof((*unPacient).nom));
// //     entrarCadena(unPacient->nom,sizeof(unPacient->nom));

// //     printf("\nIntrodueix la prioritat: [1..3] ");
// //     (*unPacient).prioritat=demanaNumeroEntreDosValors(1,3);
// //     unPacient->prioritat=demanaNumeroEntreDosValors(1,3);
// // }

// int cercaPosicioInserir(PACIENT p[],int totalPacients,int prioritatCerca)
// {
//     int i=0;
//     while (i<totalPacients && p[i].prioritat<=prioritatCerca)
//     {
//         i++;
//     }
//     return i;
// }
// void desplacarPacients(PACIENT p[],int totalPacients,int posInserir)
// {
//     for (int i=totalPacients-1;i>=posInserir;i--)
//     {
//         p[i+1]=p[i];
//     }
// }
// void pintaPacient(PACIENT p[],int totalPacients)
// {
//     if (totalPacients==0)
//     {
//         printf("\nNo hi ha pacients a la cua");
//     }
//     else
//     {
//         for (int i=0;i<totalPacients;i++)
//         {
//             pintaUnPacient(p[i]);
//         }
//     }
// }
// void pintaUnPacient(PACIENT unPacient)
// {
//     printf("\n%-15s%d",unPacient.nom,unPacient.prioritat);
// }
// void atendrePacients(PACIENT p[],int *totalPacients)
// {
//     if (*totalPacients==0)
//     {
//         printf("\nNo hi ha pacients a la cua");
//     }
//     else
//     {
//         printf("\nPacient ates:");
//         pintaUnPacient(p[0]);

//         mourePacients(p,&*totalPacients);
//     }
// }
// void mourePacients(PACIENT p[],int *totalPacients)
// {
//     for (int i=0;i<*totalPacients-1;i++)
//     {
//         p[i]=p[i+1];
//     }
//     (*totalPacients)--;
// }
// bool cercaPacient(PACIENT p[],int totalPacients,char nomCerca[])
// {
//     int i=0;
//     bool trobat=false;
//     while (i<totalPacients && !trobat)
//     {
//         if (strcmpi(p[i].nom,nomCerca)==0)
//         {
//             trobat=true;
//         }
//         else i++;
//     }

//     return trobat;
// }

void altaEstacio(int *index, ESTACIO novaEstacio[MAXESTACIO])
{
    char nomEstacio[MAXESTACIO];
    int xCoord;
    int yCoord;
    bool existeixNom = false;
    bool existeixCoords = false;

    if (*index == 40)
    {
        printf("\nNo hi ha m�s espai per afegir m�s estacions\n");
    }

    else
    {
        // Introduir i validar nom
        printf("Introdueix el nom de l'estaci�:");
        // entrarCadena(novaEstacio[*index].nom, sizeof(novaEstacio[*index].nom));
        entrarCadena(nomEstacio, sizeof(novaEstacio[*index].nom));
        if (*index > 0)
            existeixNom = validarNomE(nomEstacio, novaEstacio, index);

        // ----------------------------------------------------------------------------

        // Introduir i validar coord X

        printf("Introdueix la Coordenada X: (1..80)");
        xCoord = demanaNumeroEntreDosValors(1, 80);
        printf("Introdueix la Coordenada Y: (1..30)");
        yCoord = demanaNumeroEntreDosValors(1, 30);

        if (*index > 0)
            existeixCoords = validarCoords(xCoord, yCoord, novaEstacio, index);

        // Si es compleixen totes les regles, s'introdueix l'informaci� a l'estructura del element del vector real.
        // Coloquem primer la condicio "existeix" ja que aix� l'hi dona prioritat ja que es repetira m�s que index == 0.
        if (existeixNom == false && existeixCoords == false || *index == 0)
        {
            strcpy(novaEstacio[*index].nom, nomEstacio);
            novaEstacio[*index].coords.x = xCoord;
            novaEstacio[*index].coords.y = yCoord;
            *index = *index + 1;
        }
    }
}

bool validarNomE(char consulta[MAXESTACIO], ESTACIO ref[MAXESTACIO], int *qtt)
{
    bool res = false;

    for (int i = 0; i < *qtt; i++)
    {
        if (strcmp(consulta, ref[i].nom) == 0)
        {
            printf("\nAquesta estacio ja esta donada d'alta\n");
            res = true;
        }
    }

    return res;
}

bool validarCoords(int Coord1, int Coord2, ESTACIO ref[MAXESTACIO], int *qtt)
{
    bool res = false;

    for (int i = 0; i < *qtt; i++)
    {
        if (Coord1 == ref[i].coords.x)
        {
            if (Coord2 == ref[i].coords.y)
            {
                printf("\nNo es poden posar dues estacions en la mateixa coordenada\n");
                res = true;
            }
        }
    }
    return res;
}

void mostraEstacions(int *qtt, ESTACIO estacions[MAXESTACIO])
{
    for (int i = 0; i < *qtt; i++)
    {
        printf("%s\n\n", estacions[i].nom);
    }
}