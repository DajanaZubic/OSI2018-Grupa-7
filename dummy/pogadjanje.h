#ifndef POGADJANJE_H_INCLUDED
#define POGADJANJE_H_INCLUDED
#define BUFFERSIZE1 50
int normal();     //normalni mod igre
int easy();       //laki mod igre
int impossible(); //nemoguci mod igre

int kontrolaUnosa(char *, int *);      //funkcija za kontrolisanje validnosti unosa
int unos(int, int (*)(char *, int *)); //funkcija za obradu i kontrolu unosa
int isNumber1(char);                   //da li je karakter broj
int playPogadjanje(int);               //GLAVNA FUNKCIJA ZA POZIV IGRE

#endif // POGADJANJE_H_INCLUDED
