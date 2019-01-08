#ifndef KEYS_H_INCLUDED
#define KEYS_H_INCLUDED
#define SAT 3600
#define DAN 86400
#define SEDAM_DANA 604800
#define NEOGRANICEN 2147483647
#define POMJERAJ -40
#include <time.h>
typedef struct key{
    int game;               //igra (1, 2, 3 ili 4)
    char id;                //identifikator aktivnosti (a-aktivan, n-novi, o-stari)
    char encrypted_key[20]; //20-znakovni char za kljuc
    int key_type;           //1 sat, 1 dan, 7 dana, neograniceno
    int time_spent;         //ukupno vrijeme provedeno u igri
} KEY;
int kontrolaKljuca(int);
void timeSpent(int, time_t, time_t);
char* unosKey();
int kontrolaUnosaKey(char*);
int pronadjiNedozvoljeni(char*);
void encrypt(KEY*);
char* decrypt(char*);
KEY* readKeys(int*);
int writeKeys(KEY*,int*);
#endif // KEYS_H_INCLUDED
