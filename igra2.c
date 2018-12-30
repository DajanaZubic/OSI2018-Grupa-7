#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "igra2.h"
// FUNKCIJE
int hardQNumber(int izgubljeniBodoviIns) // Posto se u kvizu moze odredjen broj bodova izgubiti
{
    int gubljenjaBodova[] = {-150, -50, 0, 50, 100, 150};
    int minDif = abs(gubljenjaBodova[0] - izgubljeniBodoviIns);
    int indexTeskih = 0;
    for (int i = 1; i < 6; i++)
        if (minDif > abs(gubljenjaBodova[i] - izgubljeniBodoviIns))
        {
            minDif = abs(gubljenjaBodova[i] - izgubljeniBodoviIns);
            indexTeskih = i;
        }
    return indexTeskih;
}
void swapPitanja(KVIZPITANJE *a, KVIZPITANJE *b)
{
    KVIZPITANJE tmp;
    // tmp=a
    strcpy(tmp.pitanje, a->pitanje);
    strcpy(tmp.odgovorA, a->odgovorA);
    strcpy(tmp.odgovorB, a->odgovorB);
    strcpy(tmp.odgovorC, a->odgovorC);
    tmp.tacanOdg = a->tacanOdg;
    // a=b;
    strcpy(a->pitanje, b->pitanje);
    strcpy(a->odgovorA, b->odgovorA);
    strcpy(a->odgovorB, b->odgovorB);
    strcpy(a->odgovorC, b->odgovorC);
    a->tacanOdg = b->tacanOdg;
    // b=tmp
    strcpy(b->pitanje, tmp.pitanje);
    strcpy(b->odgovorA, tmp.odgovorA);
    strcpy(b->odgovorB, tmp.odgovorB);
    strcpy(b->odgovorC, tmp.odgovorC);
    b->tacanOdg = tmp.tacanOdg;
}
void shuffleQuestions(KVIZPITANJE *pitNiz)
{
    for (int i = 0; i < DUZINAKVIZA; i++)
    {
        int swapIndex = rand() % DUZINAKVIZA;
        if (swapIndex != i)
        {
            swapPitanja(&pitNiz[i], &pitNiz[swapIndex]);
        }
    }
}
void decPitanje(KVIZPITANJE *pit) // ascii pomjeraj
{
    for (int i = 0; i < DUZINAODGOVORA; i++)
        pit->odgovorA[i] = pit->odgovorA[i] - ENC;
    for (int i = 0; i < DUZINAODGOVORA; i++)
        pit->odgovorB[i] = pit->odgovorB[i] - ENC;
    for (int i = 0; i < DUZINAODGOVORA; i++)
        pit->odgovorC[i] = pit->odgovorC[i] - ENC;
    for (int i = 0; i < DUZINAPITANJA; i++)
        pit->pitanje[i] = pit->pitanje[i] - ENC;
    pit->tacanOdg = pit->tacanOdg - ENC;
}
void ucitajPitanja(FILE *fp, KVIZPITANJE *pitNiz, int izgubljeniBodoviIns)
{
    int teskaPitanja = hardQNumber(izgubljeniBodoviIns); // Dobijemo broj teskih pitanja nazad
    int popunjenost[] = {-1, -1, -1, -1, -1};            // Ako je -1 nije ucitano pitanje
    int j = 0;                                           // broji ucitana teska
    srand((unsigned)time(NULL));                         // seed RNG
    for (int i = 0; i < DUZINAKVIZA;)
    {
        if (j < teskaPitanja)
        {
            int mogucePitanje = rand() % (ENDPITANJA - HLIMIT) + HLIMIT;
            int duplicate = 0;
            for (int k = 0; k < j; k++)
                if (popunjenost[k] == mogucePitanje)
                    duplicate++;
            if (duplicate == 0)
            {
                popunjenost[i] = mogucePitanje;
                fseek(fp, mogucePitanje * sizeof(KVIZPITANJE), SEEK_SET);
                fread(&pitNiz[i], sizeof(KVIZPITANJE), 1, fp);
                decPitanje(&pitNiz[i]);
                //printf("VADI %d PITANJE\n", mogucePitanje); //Radi kontrole se koriste
                i++;
                j++;
            }
        }
        else
        {
            int mogucePitanje = rand() % HLIMIT;
            int duplicate = 0;
            for (int k = j; k < DUZINAKVIZA; k++)
                if (popunjenost[k] == mogucePitanje)
                    duplicate++;
            if (duplicate == 0)
            {
                popunjenost[i] = mogucePitanje;
                fseek(fp, mogucePitanje * sizeof(KVIZPITANJE), SEEK_SET);
                fread(&pitNiz[i], sizeof(KVIZPITANJE), 1, fp);
                decPitanje(&pitNiz[i]);
                // printf("VADI %d PITANJE\n", mogucePitanje);
                i++;
            }
        }
    }
    shuffleQuestions(pitNiz); // Kad ucita odrednjen odnos teskih i lakih, ide shuffle da ne budu teza stalno na pocetku
}
int igrajInstancu2(KVIZPITANJE *pitNiz)
{
    int bodovi = 0;
    int i = 0;
    int tolerisanjeDebilizma = 0; // Kad se ovo poveca na 1 onda ga kazni sa - 30 bodova
    while (i < 5)
    {
        char answer[100];
        printf("%d.) %sa)%sb)%sc)%s", i + 1, pitNiz[i].pitanje,
               pitNiz[i].odgovorA, pitNiz[i].odgovorB,
               pitNiz[i].odgovorC);
        printf("Vas odgovor: ");
        fgets(answer, 100, stdin); // Ako bude pogresno, povecaj tolerisanje debilizma na 1,
        if (strlen(answer) != 2 || (answer[0] != 'a' && answer[0] != 'b' && answer[0] != 'c'))
        {
            if (tolerisanjeDebilizma == 0)
            {
                printf("Mozete probati jos jednom.\n");
                tolerisanjeDebilizma++;
            }
            else
            {
                i++;
                tolerisanjeDebilizma = 0;
                printf("Oduzece vam se 30 bodova jer ste debilcina.\n");
                bodovi -= 30;
            }
        }
        else
        {
            tolerisanjeDebilizma = 0;
            if (answer[0] == pitNiz[i].tacanOdg)
            {

                printf("Tacno. Osvojili ste 20 bodova.\n");
                bodovi += 20;
            }
            else
            {
                printf("Pogresno. Izgubili ste 30 bodova.\n");
                bodovi -= 30;
            }
            i++;
        }
    }
    return bodovi;
}
int igrajIgru2(int izgubljeniBodoviIns) //Ovdje ce se slati (bafer) i (igrac) al za sada se samo salje broj bodova koji treba izgubiti
{
    FILE *fp = fopen("pitanja.txt", "rb"); // Otvaramo fajl
    int bodovi = 0;
    if (fp != NULL)
    {
        KVIZPITANJE pitNiz[5];
        ucitajPitanja(fp, pitNiz, izgubljeniBodoviIns);
        bodovi = igrajInstancu2(pitNiz);
    }
    else
        printf("Fajl sa pitanjima nije pronadjen\n.");
    return bodovi == 100 ? 150 : bodovi; // Za bonus poene
}
