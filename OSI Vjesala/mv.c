#include <stdio.h>
#include <string.h>
#define DUZINARIJECI 20   // Unositi max 18 jer treba imati iza \n i \0 zbog fgetsa
#define DUZINASAVJETA 220 // max 218
#define MOVE -12
typedef struct vjesalo
{
    char rijec[DUZINARIJECI];
    char hint[DUZINASAVJETA];
} VJESALO;
// Funkcije
void encWord(VJESALO *v);
void decWord(VJESALO *v);
// Main
int main()
{
    VJESALO tmp;
    FILE *fp = fopen("words.txt", "rb+");
    if (fp == NULL)
    {
        printf("Fajl ne postoji.\n");
        fp = fopen("words.txt", "wb");
    }
    fseek(fp, 0, SEEK_END); //Na kraj fajla
    char control = 'a';
    do
    {
        printf("Word(max number of symbols is 18): ");
        fgets(tmp.rijec, DUZINARIJECI, stdin);
        printf("Definition(218 chars max): ");
        fgets(tmp.hint, DUZINASAVJETA, stdin);
        encWord(&tmp);
        fwrite(&tmp, sizeof(VJESALO), 1, fp);
        printf("DALJE(d)KRAJ(k)?");
        scanf(" %c", &control);
        fflush(stdin);
    } while (control != 'k');
    fclose(fp);
    FILE *cit = fopen("words.txt", "rb");
    if (cit != NULL)
    {
        printf("Rijeci koje se nalaze u fajlu:\n");
        int counter = 1;
        while (fread(&tmp, sizeof(VJESALO), 1, cit))
        {
            decWord(&tmp);
            printf("%d)%sHINT:%s", counter, tmp.rijec, tmp.hint);
            counter++;
        }
    }
    else
        printf("Nema fajla.\n");
    fclose(cit);
}
//
void encWord(VJESALO *v)
{
    for (int i = 0; i < DUZINARIJECI; i++)
    {
        v->rijec[i] = v->rijec[i] + MOVE;
    }
    for (int i = 0; i < DUZINASAVJETA; i++)
    {
        v->hint[i] = v->hint[i] + MOVE;
    }
}
//
void decWord(VJESALO *v)
{
    for (int i = 0; i < DUZINARIJECI; i++)
    {
        v->rijec[i] = v->rijec[i] - MOVE;
    }
    for (int i = 0; i < DUZINASAVJETA; i++)
    {
        v->hint[i] = v->hint[i] - MOVE;
    }
}