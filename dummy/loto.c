#include "loto.h"
#include "consolemanip.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <limits.h>
int normal3(int *nizBrojeva)
{
    srand((unsigned)time(NULL));
    int nizIzvucenih[20], temp, pogodjeni = 0, suma = 0, x = 11;
    printf("\n\nIzvuceni su: ");
    for (int i = 0; i < 20; i++)
    {
        do
        {
            temp = rand() % 45 + 1;
        } while (pretraziNiz(nizIzvucenih, temp, i));
        nizIzvucenih[i] = temp;
        if (pretraziNiz(nizBrojeva, temp, 7))
        {
            pogodjeni++;
            changeTextColor(RED);
        }
        if (i == 0 || (nizIzvucenih[i - 1] / 10) == 0)
            gotoxy(x += 2, 2);
        else
            gotoxy(x += 3, 2);
        printf("%d", nizIzvucenih[i]);
        gotoxy(18, 5);
        printChar(nizIzvucenih[i]);
        Sleep(SLEEPTIME);
        changeTextColor(DEFAULT);
    }
    for (int i = 0; i < pogodjeni; i++)
        suma += (i + 1) * 10;
    printf("\n\nPogodili ste %d %s i osvojili %d bodova\n", pogodjeni, pogodjeni == 1 ? "broj" : (pogodjeni > 1 && pogodjeni < 5) ? "broja" : "brojeva", suma);
    return suma;
}
int pretraziNiz(int *niz, int unos, int i)
{
    for (int k = 0; k < i; k++)
        if (niz[k] == unos)
            return 1;
    return 0;
}
void unos3(int *nizBrojeva)
{
    for (int i = 0; i < 7; i++)
    {
        char string[BUFFERSIZE] = {0};
        int broj;
        do
        {
            printf("\n%d. broj: ", i + 1);
            fgets(string, BUFFERSIZE, stdin);
            int duz = strlen(string);
            if ((duz > 0) && (string[duz - 1] == '\n'))
                string[duz - 1] = '\0';
        } while (kontrolaUnosa3(string, &broj, nizBrojeva));
        nizBrojeva[i] = broj;
        system("cls");
        printf("Odabrali ste: ");
        for (int j = 0; nizBrojeva[j] && j < 7; j++)
            printf("%d ", nizBrojeva[j]);
    }
}

int kontrolaUnosa3(char *string, int *br, int *uneseniNiz)
{
    int i, broj, duz = strlen(string);
    if (!duz) //ako se pritisne enter bez unosa
    {
        printf("Unesite broj od 1 do 45!\n\n");
        return 1;
    }
    for (i = 0; i < duz; i++)
    {
        if (!isNumber(string[i])) //...da li ima znakova koji nisu cifre od 0 do 9
        {
            printf("Unesite broj od 1 do 45!\n\n");
            return 1;
        }
    }
    broj = atoi(string);       //konverzija string-a u integer
    if (broj < 1 || broj > 45) //provjera da li int zadovoljava granice
    {
        printf("Unesite broj od 1 do 45!\n\n");
        return 1;
    }
    i = 0;
    while (uneseniNiz[i] != 0)
    {
        if (uneseniNiz[i] == broj)
        {
            printf("Taj broj ste vec unijeli!\n\n");
            return 1;
        }
        i++;
    }
    *br = broj;
    return 0;
}
int isNumber(char karakter)
{
    if (karakter >= '0' && karakter <= '9')
        return 1;
    return 0;
}
int controlled3(int *nizBrojeva, int brojPogodjenih)
{
    srand((unsigned)time(NULL));
    int *nizPogInd, *nizPlaceInd, nizIzvucenih[20]; //niz slucajno odabranih pozicija brojeva polaznog niza nizBrojeva, niz slucajno odabranih pozicija za umetanje u nizIzvucenih
    if ((nizPogInd = (int *)calloc(brojPogodjenih, sizeof(int))) == NULL)
    {
        printf("Bad alloc!\n");
        return 0;
    };
    if ((nizPlaceInd = (int *)calloc(brojPogodjenih, sizeof(int))) == NULL)
    {
        printf("Bad alloc!\n");
        return 0;
    };
    for (int i = 0; i < brojPogodjenih; i++)
    {
        nizPogInd[i] = -1;
        nizPlaceInd[i] = -1;
    }
    for (int i = 0; i < brojPogodjenih; i++)
    {
        int rndInd;
        if (brojPogodjenih < 4)
        {
            do
            {
                rndInd = rand() % 7;
            } while (pretraziNiz(nizPogInd, rndInd, brojPogodjenih));
            nizPogInd[i] = rndInd;
        }
        else
        {
            nizPogInd[i] = i;
        }
        do
        {
            rndInd = rand() % 20;
        } while (pretraziNiz(nizPlaceInd, rndInd, brojPogodjenih));
        nizPlaceInd[i] = rndInd;
    }
    int temp, j = 0, suma = 0, x = 11;
    printf("\n\nIzvuceni su: ");
    for (int i = 0; i < 20; i++)
    {
        if (pretraziNiz(nizPlaceInd, i, brojPogodjenih))
        {
            nizIzvucenih[i] = nizBrojeva[nizPogInd[j++]];
            changeTextColor(RED);
        }
        else
        {
            do
            {
                temp = rand() % 45 + 1;
            } while (pretraziNiz(nizIzvucenih, temp, i) || pretraziNiz(nizBrojeva, temp, 7));
            nizIzvucenih[i] = temp;
        }
        if (i == 0 || (nizIzvucenih[i - 1] / 10) == 0)
            gotoxy(x += 2, 2);
        else
            gotoxy(x += 3, 2);
        printf("%d", nizIzvucenih[i]);
        gotoxy(18, 5);
        printChar(nizIzvucenih[i]);
        Sleep(SLEEPTIME);
        changeTextColor(DEFAULT);
    }
    for (int i = 0; i < brojPogodjenih; i++)
        suma += (i + 1) * 10;
    printf("\n\nPogodili ste %d %s i osvojili %d bodova\n", brojPogodjenih, brojPogodjenih == 1 ? "broj" : (brojPogodjenih > 1 && brojPogodjenih < 5) ? "broja" : "brojeva", suma);
    free(nizPogInd);
    free(nizPlaceInd);
    return suma;
}
int playLoto(int izgubljeniBodoviIns, int *ukupniIzgubljeniBodovi, int *ukupniDobijeniBodovi)
{
    if (*ukupniDobijeniBodovi - *ukupniIzgubljeniBodovi < 100)
    {
        printf("Nemate dovoljno bodova da biste igrali loto!\n");
        Sleep(2000);//dodato da bi se procitala poruka
        return 0;
    }
    int dobijeniBodovi, nizBrojeva[7] = {0};
    unos3(nizBrojeva);
    if (izgubljeniBodoviIns == INT_MAX)
        dobijeniBodovi = normal3(nizBrojeva);
    else
    {
        int dobijeniBodoviIns = 100 - izgubljeniBodoviIns;
        int moguciDobici[] = {0, 10, 30, 60, 100, 150, 210, 280}, min = 10000, indMin, i;
        for (i = 0; i < 8; i++)
        {
            if (abs(dobijeniBodoviIns - moguciDobici[i]) < min)
            {
                min = abs(dobijeniBodoviIns - moguciDobici[i]);
                indMin = i;
            }
        }
        dobijeniBodovi = controlled3(nizBrojeva, indMin);
    }
    if (100 - dobijeniBodovi >= 0)
        *ukupniIzgubljeniBodovi += (100 - dobijeniBodovi);
    else
        *ukupniDobijeniBodovi += dobijeniBodovi - 100;
    // DODATO ZA ISPIS;
    Sleep(1800);
    //
    return dobijeniBodovi;
}
void printChar(int brojZaIspis)
{
    FILE *fp;
    unsigned char broj[260] = {0}, c;
    int i = 0;
    if ((fp = fopen("broj.txt", "r")))
    {
        int mode = 0;
        unsigned char br[3] = {0};
        while ((c = fgetc(fp)) != EOF)
        {
            if (isNumber(c))
            {
                br[0] = c;
                c = fgetc(fp);
                br[1] = c;
            }
            //printf("Shvatio je broj kao %d\n", atoi(br));
            if (brojZaIspis == atoi(br))
                mode = 1;
            if (mode)
            {
                if (c == 'a')
                    broj[i++] = 219;
                else if (c == ' ')
                    broj[i++] = ' ';
                else if (c == '\n')
                    broj[i++] = '\n';
            }
            if (mode && c == '-')
                break;
        }
        for (i = 0; i < 234; i++)
        {
            printf("%c", broj[i]);
            if (i % 18 == 0)
                printf("                              ");
        }
        fclose(fp);
    }
    else
        printf("Ne otvara.\n");
}
