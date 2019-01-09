#ifndef meni_h_
#define meni_h_
#include "bafer.h"
typedef struct player
{
    char ime[31];
    int brojOdigranihPartija;
    int ukupniDobijeniPoeni;
    int ukupniIzgubljeniPoeni;
} PLAYER;

// Igrac
void stvoriPlayera(PLAYER *pla);  
void pozdravPlayera(PLAYER *pla);  
void upisiPlayera(PLAYER *pla);   
int ucitajPlayera(PLAYER *pla);   
// Pomocne
void printajNaslov();
void dummyGame(int);
int obradibrojniUnos(int, void (*)()); // int je broj od 1 do int limita uljucujuci i limit
// ISPISI EKRANA TJ STATICNIH ELEMENATA
void screen0();
void screen1(); 
void screen2();
void screen3(); 
void screen4();
void Instrukcije();
// ZA OPCIJE MENIJA 1 i 2 SE KORISTE OVE 2 DA SE OSTAVI CISTA KONZOLA POSTO IMA PROMJENLJIVIH ELEMENATA, SAKATO I JEST
int obradiSpecijal1(int limit, void (*scr)(), PLAYER *pla);
int obradiSpecijal2(int limit, void (*scr)(), BAFERREZULTATA *, BAFERREZULTATA *, BAFERREZULTATA *);
#endif