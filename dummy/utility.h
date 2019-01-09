#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#define KOEFICIJENT_RASTA_ODNOSA 0.1 // Da ne bude agresivan sistem
/*Funkcija calcNTLPoints radi na principu uporedjivanja trazenog odnosa ukupnog broja izgubljenih 
i dobijenih bodova sa trenutnim odnosom. 
Trazeni odnos raste linearno sa svakom igrom i iznosi KOEFICIJENT_RASTA_ODNOSA*brojIgre dok iznos ne bude 1.4*/
int calcNTLPoints(int, int, int);      //calculate Next Turn Loosing Points

#endif // UTILITY_H_INCLUDED
