#ifndef bafer_h_
#define bafer_h_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <windows.h>
// Limits koristimo da sa MIN_INT postavimo nevalidne vrijednosti bodova
#define SIZE 10 // Bufer treba da drzi 10 elemenata
/* Posto je ovo iskljucivo kruzni bafer iz koga se nikad nece brisati onda nije potrebno gledati pojmove punog i praznog, a 
ni brisanja.
Upis rezultata ce se vrsiti preko pomocnog niza pokazivaca koji se sortira i onda se vuce iz bafera, za rad u mainu
ce biti potrebno ucitati bafere u memoriju iz binarne datoteke koja ce sadrzati 3 bafera za igre i jos sta odlucimo.
Posto nismo odlucili jos, toga nema. Potrebno je deklarisati bafere i pozvati funkciju inicijalizujBafer() ako se ne ucitavaju
u fajlove, prilikom upisa je potrebno kreirati pomocni niz, potom ga sortirati, proslijediti u funkciju za upis u CSV i potom
osloboditi memoriju za pomocni niz sa pokazivacima. Prije gasenja aplikacije ce se morati updejtovati binarni fajl sa 
svim potrebnim podacima , 3 bafera, globalni structovi koji prate ostale statistike...
*/
// Sta sadrzi sve struct tm:
/*
int tm_sec	seconds after the minute – [0, 61](until C99) / [0, 60] (since C99)[note 1]
int tm_min	minutes after the hour – [0, 59]
int tm_hour	hours since midnight – [0, 23]
int tm_mday	day of the month – [1, 31]
int tm_mon	months since January – [0, 11]
int tm_year	years since 1900
int tm_wday	days since Sunday – [0, 6]
int tm_yday	days since January 1 – [0, 365]
int tm_isdst	Daylight Saving Time flag. The value is positive if DST is in effect, zero if not and negative if no information is available
*/
typedef struct rezultat
{
    int brojBodova;
    struct tm vrijemeDatum;
} REZULTAT;
typedef struct baferRezultata
{
    REZULTAT podaci[SIZE];
    int rear;
} BAFERREZULTATA;
// Protitipi za f-je
// OBAVEZNO pozvati poslije stvaranja bafera u mainu zbog nacina funkcionisanja
void inicijalizujBafer(BAFERREZULTATA *);
void dodajRezultat(BAFERREZULTATA *, int);
REZULTAT **kreirajPomocniNiz(BAFERREZULTATA *, int *); 
void kopirajVrijeme(struct tm *, struct tm *);         
void sortirajPomocniNiz(REZULTAT **, int);
// Ispis u CSV zvati
void pisiCSV(BAFERREZULTATA *, BAFERREZULTATA *, BAFERREZULTATA *);
// Za prikaz tabele
void prikaziTabeluStatistike(BAFERREZULTATA *, BAFERREZULTATA *, BAFERREZULTATA *);
// Ako ima ucitace ako nema nece, zato je bitno inicijalizuj... zvati prije 
void expBaferi(BAFERREZULTATA *, BAFERREZULTATA *, BAFERREZULTATA *);
// Obavezno iz ponovo izbaciti u fajl prije izlaza. Sad da li da se updejtuje poslije svake partije sva 3 
// Malo nema smisla al mozda Dujla proba zatvoriti konzolu unutar igre 
void impBaferi(BAFERREZULTATA *, BAFERREZULTATA *, BAFERREZULTATA *); 
#endif