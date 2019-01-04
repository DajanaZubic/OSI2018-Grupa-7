#ifndef LOTO_H_INCLUDED
#define LOTO_H_INCLUDED

#define BUFFERSIZE 50
#define SLEEPTIME 2000

int normal3(int*);                     //normalan mod igre
int controlled3(int* ,int);            // kontrolisani mod igre, prima pokazivac na niz i broj pogodjenih brojeva u datoj instanci igre
int playLoto(int, int*, int*);         //glavna funkcija, prima vrijednost bodova koji trebaju biti izgubljeni u datoj instanci i bodove na nalogu
int pretraziNiz(int*, int, int);       //funkcija koja trazi cjelobrojnu vrijednost u cjelobrojnom nizu i vraca informaciju o tome da li je pronasao
void unos3(int*);                      //funkcija za unos niza od 7 brojeva
int kontrolaUnosa3(char*, int*, int*); //funkcija koja kontrolise ispravnost unosa
int isNumber(char);                    //da li je karakter broj
void printChar(int);                   //funkcija koja ispisuje izvuceni broj
#endif // LOTO_H_INCLUDED
