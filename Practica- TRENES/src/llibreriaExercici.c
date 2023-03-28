#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "rlutil.h"
#include "llibreriaPropia.h"
#include "llibreriaExercici.h"
#include <math.h>

    // Donar d'alta una estaciÛ
void altaEstacio(int *index, ESTACIO estacions[])
{
    ESTACIO nEstacio;
    bool existeixNom = false;
    bool existeixCoords = false;

    if (*index == 40)
    {
        printf("\nNo hi ha mes espai per afegir mes estacions.\n");
    }

    else
    {
        // Introduir i validar nom
        printf("Introdueix el nom de l'estacio: ");
        entrarCadena(nEstacio.nom, sizeof(nEstacio.nom));
        existeixNom = validarNomE(nEstacio.nom, estacions, index);

        // ----------------------------------------------------------------------------

        // Introduir i validar coord X
        if (existeixNom == true)
        {
            printf("\nAquesta estacio ja esta donada d'alta.\n");
        }
        else
        {
            printf("\nIntrodueix la Coordenada X: (1..80) ");
            // xCoord = demanaNumeroEntreDosValors(1, 80);
            nEstacio.coords.x = demanaNumeroEntreDosValors(1, 80);
            printf("\nIntrodueix la Coordenada Y: (1..30) ");
            // yCoord = demanaNumeroEntreDosValors(1, 30);
            nEstacio.coords.y = demanaNumeroEntreDosValors(1, 30);

            // if (*index > 0)
            existeixCoords = validarCoords(nEstacio.coords.x, nEstacio.coords.y, estacions, index);
        }

        // Si es compleixen totes les regles, s'introdueix l'informaciù a l'estructura del element del vector real.
        // Coloquem primer la condicio "existeix" ja que aixù l'hi dona prioritat ja que es repetira mùs que index == 0.
        if ((existeixNom == false && existeixCoords == false) || *index == 0)
        {
            // strcpy(novaEstacio[*index].nom, nomEstacio);
            // novaEstacio[*index].coords.x = xCoord;
            // novaEstacio[*index].coords.y = yCoord;

            estacions[*index] = nEstacio;

            *index = *index + 1;
        }
    }
}

bool validarNomE(char consulta[], ESTACIO ref[], int *qtt)
{
    bool res = false;

    for (int i = 0; i < *qtt; i++)
    {
        if (strcmp(consulta, ref[i].nom) == 0)
        {
            res = true;
        }
    }

    return res;
}

bool validarCoords(int Coord1, int Coord2, ESTACIO ref[], int *qtt)
{
    bool res = false;

    for (int i = 0; i < *qtt; i++)
    {
        if (Coord1 == ref[i].coords.x)
        {
            if (Coord2 == ref[i].coords.y)
            {
                printf("\nNo es poden posar dues estacions en la mateixa coordenada.\n");
                res = true;
            }
        }
    }
    return res;
}

void mostraEstacions(int qtt, ESTACIO estacions[])
{
    printf("ESTACIONS:\n");
    printf("NOM\t\tCOORDENADES\n");
    for (int i = 0; i < qtt; i++)
    {
        printf("%s\t\t(%d-%d)\n", estacions[i].nom, estacions[i].coords.x, estacions[i].coords.y);
    }
}

void inserirRuta(ESTACIO est[], RUTA rutes[], int qttEstacions, int *qttRutas)
{
    char consultaAux[MAXCADENA];
    char nom[MAXCADENA];

    RUTA novaRuta;

    bool Sinok = true;
    bool nomRepetit = false;
    int ubiDosP;
    if (qttEstacions < 2)
    {
        printf("No existeixen suficients estacions per crear una ruta. (Mùnim 2)");
    }
    else
    {
        printf("Les estacions son:\n");
        mostraEstacions(qttEstacions, est);

        printf("\nIntrodueix la ruta amb el format:\n");
        printf("P.e: Ruta1:Estacio1,Estacio2,Estacio3:\n");
        entrarCadena(consultaAux, sizeof(consultaAux));
        Sinok = validarSinRuta(consultaAux);
        if (Sinok == true)
        {
            separarNom(consultaAux, nom, &ubiDosP);
            if (*qttRutas > 0)
            {
                nomRepetit = repetirRuta(nom, rutes, qttRutas);
            }

            if (nomRepetit == true)
            {
                printf("El nom de la ruta ja esta donada d'alta.");
            }
            else
            {
                strcpy(novaRuta.nom, nom);
                novaRuta.iqtt = 0;
                dividirEstacions(consultaAux, &novaRuta, ubiDosP, est, qttEstacions);
                rutes[*qttRutas] = novaRuta;
                (*qttRutas)++;
            }
        }
    }
}

bool validarSinRuta(char consultaAux[])
{
    bool valid = true;
    int i = 0;
    int cant = 0;
    while (i < (int)strlen(consultaAux))
    {
        if (consultaAux[i] == ':')
            cant++;
        if (consultaAux[i] == ':' && i < 1)
            valid = false;
        else if (cant > 1)
            valid = false;
        else if (consultaAux[i] == ':' && i == (int)strlen(consultaAux))
            valid = false;
        i++;
    }
    if (valid == false)
    {
        printf("\nEl format de la ruta Ès incorrecta.\n");
    }

    return valid;
}

bool repetirRuta(char nom[], RUTA rut[], int *qttRutas)
{
    bool res = false;
    for (int i = 0; i < *qttRutas; i++)
    {
        if (strcmpi(nom, rut[i].nom) == 0)
            res = true;

        // char matriz[2][MAXCADENA]
        // La Garriga
        // Granollers

        // matriz[0] // La Garriga
        // matriz[0][0] // L
    }

    return res;
}

void separarNom(char nomAux[], char nom[], int *pos)
{
    int i = 0;
    while (nomAux[i] != ':')
    {
        nom[i] = nomAux[i];
        i++;
    }
    nom[i] = '\0';
    i++;
    *pos = i;
    nom[i] = '\0';
}

void dividirEstacions(char nomAux[], RUTA *ruta, int dosPunts, ESTACIO estacions[], int qttEstacions)
{
    char estacionsInd[MAXESTACIO][MAXCADENA];
    int fila = 0, columna = 0;

    // [] [ ] [ ] [ ] [ ] [ ]
    // [ ] [ ] [ ] [ ] [ ] [ ]
    // [ ] [ ] [ ] [ ] [ ] [ ]
    // [ ] [ ] [ ] [ ] [ ] [ ]

    // R1:La Garriga,Granollers

    for (int i = dosPunts; i < (int)strlen(nomAux); ++i)
    {
        if (nomAux[i] != ',')
        {
            estacionsInd[fila][columna] = nomAux[i];
            columna++;
        }
        else
        {
            columna = 0;
            fila++;
        }
    }

    // [L] [a ] [ G] [ ] [ ] [ ]
    // [G ] [r ] [a ] [ ] [ ] [ ]
    // [ ] [ ] [ ] [ ] [ ] [ ]
    // [ ] [ ] [ ] [ ] [ ] [ ]

    int qttEstEsc = fila + 1;
    bool estacioNoExisteix = false;

    for (int i = 0; i < qttEstEsc && estacioNoExisteix == false; ++i)
    {
        int posEstacio = cercaPosicioEstacio(estacionsInd[i], estacions, qttEstacions);

        if (posEstacio == -1)
        {
            estacioNoExisteix = true;
            (*ruta).iqtt = 0;
        }
        else if (noRepit(posEstacio, *ruta) == true)
            printf("Hi ha una estacio repetida");
        else
        {
            // printf("%d\n", (*ruta).iqtt);
            (*ruta).index[(*ruta).iqtt] = posEstacio;
            (*ruta).iqtt++;
        }
    }

    if (estacioNoExisteix)
        printf("\nAlguna de les estacions no existeix.\n");

    // existenEst = allExists(estacionsInd, estacions, qttEstacions, qttEstEsc);
    // if (existenEst == false)
    // {
    //     printf("\nAlguna de les estacions no existeix.\n");
    // }
    // else
    // {
    //     noRepEst = noRepit(estacionsInd);
    //     printf("Hola");
    // }

    // int y = 0;
    // int escritura = 0;
    // int qttEstEsc = 0;
    // bool existenEst = true;
    // bool noRepEst = true;

    // while (i <= strlen(nomAux))
    // {
    //     while (nomAux[i] != ',' && i != strlen(nomAux))
    //     {
    //         estacionsInd[y][escritura] = nomAux[i];
    //         escritura++;
    //         i++;
    //     }
    //     escritura = 0;
    //     i++;
    //     y++;
    //     qttEstEsc++;
    // }

    // if (qttEstEsc < 2)
    // {
    //     printf("\nCom a mùnim una ruta ha de tenir dues estacions.\n");
    // }
    // else
    // {
    //     existenEst = allExists(estacionsInd, estacions, qttEstacions, qttEstEsc);
    //     if (existenEst == false)
    //     {
    //         printf("\nAlguna de les estacions no existeix.\n");
    //     }
    //     else
    //     {
    //         noRepEst = noRepit(estacionsInd);
    //         printf("Hola");
    //     }
    // }
}

int cercaPosicioEstacio(char nomEstacio[], ESTACIO estacions[], int qttEstacions)
{
    int pos = -1;
    for (int i = 0; i < qttEstacions; ++i)
    {
        if (strcmpi(estacions[i].nom, nomEstacio) == 0)
            pos = i;
    }
    return pos;
}

bool allExists(char listEs[][MAXESTACIO], ESTACIO listEx[], int qttEst, int qttEsc)
{
    bool si = true;
    for (int i = 0; i < qttEsc; i++)
    {
        bool igual = false;
        for (int y = 0; y < qttEst; y++)
        {
            if (strcmpi(listEx[y].nom, listEs[i]) == 0)
            {
                igual = true;
            }
        }
        if (igual == false)
        {
            si = false;
        }
    }

    return si;
}

// RUTA:
//     nom
//     estacionsRuta[]

bool noRepit(int posEstacioRuta, RUTA ruta)
{
    bool estacioRepetida = false;

    int numEstacionsRuta = ruta.iqtt;
    for (int i = 0; i < numEstacionsRuta && estacioRepetida == false; ++i)
    {
        if (ruta.index[i] == posEstacioRuta)
            estacioRepetida = true;
    }

    return estacioRepetida;
}

void mostrarRutas(int qttRutas, RUTA rut[], ESTACIO est[])
{
    printf("RUTES:\n");
    for (int i = 0; i < qttRutas; i++)
    {
        printf("\nNom Ruta:\t%s\n", rut[i].nom);
        for (int y = 0; y < rut[i].iqtt; y++)
        {
            printf("%s\t\t(%d-%d)\n", est[rut[i].index[y]].nom, est[rut[i].index[y]].coords.x, est[rut[i].index[y]].coords.y);
        }
    }
}

void mostrarRutaEspecifica(RUTA rutas[], int qttRutas, ESTACIO est[], int qttEstacions)
{
    char estacioConsulta[MAXCADENA];
    int cont = 0;
    printf("Introdueix el nom de l'estacio: ");
    entrarCadena(estacioConsulta, sizeof(estacioConsulta));
    bool estacioEx = validarNomE(estacioConsulta, est, &qttEstacions);
    if (estacioEx == true)
    {
        for (int i = 0; i < qttRutas; i++)
        {
            for (int y = 0; y < rutas[i].iqtt; y++)
            {
                if (strcmpi(estacioConsulta, est[rutas[i].index[y]].nom) == 0)
                {
                    printf("\n%s\n", rutas[i].nom);
                    cont++;
                }
            }
        }
        if (cont == 0)
        {
            printf("Existeix l'estacio pero no hi ha cap ruta que hi pari.");
        }
    }
    else
        printf("Aquesta estacio no esta donada d'alta.");
}

void calculaDistanciaRutes(ESTACIO e[], RUTA r[], int totalRutes)
{

    RUTA rutaACalcular;

    printf("\nIntrodueix el nom de la ruta: ");
    entrarCadena(rutaACalcular.nom, sizeof(rutaACalcular.nom));

    int pos = posRuta(r, totalRutes, rutaACalcular.nom);

    if (pos == -1)
    {
        printf("\nLa ruta seleccionada no s'ha donat d'alta");
    }
    else if (strlen(rutaACalcular.nom) == 0)
    {
        printf("\nHas d'introduir una ruta");
    }
    else
    {
        printf("\nESTACIO\t\t\tKM-ESTACIO-ANTERIOR\t\t\tTOTAL-KM");
        printarEstacionsKm(e, r[pos]);

        printf("\n");
    }
}

void printarEstacionsKm(ESTACIO e[], RUTA r)
{
    int posEstacio, posEstacioAnt;
    float kmEstacioAnterior = 0, totalKm = 0;
    int i = 0;

    while (i < r.iqtt)
    {
        posEstacio = r.index[i];
        posEstacioAnt = r.index[i - 1];

        if (i == 0)
        {
            printf("\n%s %30.2f %30.2f", e[posEstacio].nom, kmEstacioAnterior, totalKm);
        }
        else
        {

            float c1 = (e[posEstacio].coords.x) - (e[posEstacioAnt].coords.x);
            float c2 = (e[posEstacio].coords.y) - (e[posEstacioAnt].coords.y);

            kmEstacioAnterior = sqrt((c1 * c1) + (c2 * c2));
            totalKm = totalKm + kmEstacioAnterior;

            printf("\n%s %30.2f %30.2f", e[posEstacio].nom, kmEstacioAnterior, totalKm);
        }
        i++;
    }
}

int posRuta(RUTA rutas[], int qttRutas, char rutaConsulta[])
{
    int pos;
    for (int i = 0; i < qttRutas; i++)
    {
        if (strcmpi(rutaConsulta, rutas[i].nom) == 0)
        {
            pos = i;
        }
    }
    return pos;
}

// void mostrarKm(RUTA rutas[], int qttRutas, ESTACIO est[], int qttEstacions)
// {
//     char rutaConsulta[MAXCADENA];
//     int cont = 0;
//     float catetoX;
//     float catetoY;
//     float hipo;
//     int posRuta;

//     float totalKM = 0;

//     printf("Introdueix el nom de la ruta: ");
//     entrarCadena(rutaConsulta, sizeof(rutaConsulta));
//     bool rutaEx = repetirRuta(rutaConsulta, rutas, qttRutas);

//     if (qttRutas < 1)
//         printf("No hi ha cap ruta inserida");
//     else
//     {
//         for (int j = 0; j < qttRutas; j++)
//         {
//             if (strcmpi(rutaConsulta, rutas[j].nom) == 0)
//             {
//                 posRuta = j;
//             }
//         }

//         if (rutaEx == true)
//         {
//             printf("NOM DE LA RUTA: %s\n", rutaConsulta);
//             printf("ESTACIO\t\tKM-ESTACIO-ANTERIOR\t\tTOTAL-KM");
//             for (int i = 0; i < rutas[i].iqtt; i++)
//             {

//                 if (est[rutas[posRuta].index[i]].coords.x > est[rutas[posRuta + 1].index[i]].coords.x)
//                 {
//                     catetoX = (float)(est[rutas[posRuta].index[i]].coords.x) - (est[rutas[posRuta - 1].index[i]].coords.x);
//                 }
//                 else
//                 {
//                     catetoX = (float)(est[rutas[posRuta + 1].index[i]].coords.x) - (est[rutas[posRuta].index[i]].coords.x);
//                 }

//                 if (est[rutas[posRuta].index[i]].coords.y > est[rutas[posRuta + 1].index[i]].coords.y)
//                 {
//                     catetoY = (float)(est[rutas[posRuta].index[i]].coords.y) - (est[rutas[posRuta - 1].index[i]].coords.y);
//                 }
//                 else
//                 {
//                     catetoY = (float)(est[rutas[posRuta + 1].index[i]].coords.y) - (est[rutas[posRuta].index[i]].coords.y);
//                 }

//                 // Al cuadrado cada uno :)
//                 catetoX = pow(catetoX, 2);
//                 catetoY = pow(catetoY, 2);

//                 hipo = catetoX + catetoY;

//                 hipo = sqrt(hipo);

//                 totalKM += totalKM;

//                 printf("\n%s\t\t%.2f\t\t%.2f", est[rutas[posRuta].index[i]].nom, hipo, totalKM);
//             }
//         }
//         else
//             printf("Aquesta ruta no existeix.");
//     }
// }