#include <stdio.h>
#include "loto.h"
#include <windows.h>
#include <limits.h>
int main()
{
    printf("Ovo je test igre loto. Unesite 7 brojeva u opsegu od 1 do 45. Nakon unosa svakog od njih pritisnite taster enter!\n");
    int ukIzg=0, ukDob=120, brBodova;
    brBodova=playLoto(INT_MAX, &ukIzg, &ukDob);
    //printf("\n\nBroj dobijenih: %d\nBroj ukupnih izgubljenih: %d\nBroj ukupnih dobijenih: %d\n", brBodova, ukIzg, ukDob); //testna provjera
    return 0;
}
