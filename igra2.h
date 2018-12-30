#ifndef igra2_h_
#define igra2_h_
// MAKROI
#include <stdio.h>
#define DUZINAODGOVORA 50
#define DUZINAPITANJA 200 // Ne dirati ovo nikako
#define ENC -13           // Ni ovo
#define HLIMIT 35         // Odavde pocinju teska pitanja
#define ENDPITANJA 76     // Kraj pitanja
#define DUZINAKVIZA 5     //Broj pitanja koja se ucitavaju
// Definicija pitanja
typedef struct kvizPitanje
{
    char pitanje[DUZINAPITANJA];
    char odgovorA[DUZINAODGOVORA];
    char odgovorB[DUZINAODGOVORA];
    char odgovorC[DUZINAODGOVORA];
    char tacanOdg; /// moze biti a,b,c (STROGO MALO) u kvizu
} KVIZPITANJE;
// Prototipovi
int hardQNumber(int izgubljeniBodoviIns); // Pomocno za odredjivanje kako i sta se radi
void decPitanje(KVIZPITANJE *pit);  // Pomjera sve karaktere nazad na prave vrijednosti
void shuffleQuestions(KVIZPITANJE *pitNiz);// Mijesa niz pitanja nakon uctavanja
void ucitajPitanja(FILE *fp, KVIZPITANJE *pitNiz, int izgubljeniBodoviIns); // Ucitava niz pitanja
void swapPitanja(KVIZPITANJE *a, KVIZPITANJE *b); // Pomocna za Shuffle
int igrajInstancu2(KVIZPITANJE *pitNiz);// Pomocna za igrajIgru2, ovjde se zapravo igra
int igrajIgru2(int izgubljeniBodoviIns); // Funkcija koja se poziva za igranje (dodati uticaj na playera i buffer!)
// za igrajIgru2() je potrebno napraviti jos bocne efekte

#endif