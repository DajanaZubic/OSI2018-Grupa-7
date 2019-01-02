#ifndef igra4_h_
#define igra4_h_

#include <stdio.h>
#define DUZINARIJECI 20   // Ne vise od 18 zbog \n i \0
#define DUZINASAVJETA 220 // max 218
#define MOVE -12
#define MEDIUMWORDS 25 // INDEKS GDJE SREDNJE TESKE RIJECI
#define HARDWORDS 50   // INDEKS GDJE POCINJU BAS TESKE RIJECI, ONO KRVAVO TESKE
#define TOTALWORDS 75  // TOTALAN BROJ RIJECI U FAJLU
typedef struct vjesalo
{
    char rijec[DUZINARIJECI];
    char hint[DUZINASAVJETA];
} VJESALO;
// Funkcije
void decWord(VJESALO *v);       // Pomocna za izvuci()
VJESALO *izvuci(FILE *fp);      // Izvlaci pitanje pomocna za igraj4() pomocu rnga i rezervise memoriju
int igrajInstancu4(VJESALO *v); // Bira se hint off/on i igra se, vraca 0 za loss i 1 za win
void igraj4();
#endif