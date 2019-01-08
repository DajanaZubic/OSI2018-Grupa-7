#include "pogadjanje.h"
#include "consolemanip.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <limits.h>
int normal()//funkcija koja poziva normalan mod igre
{
    srand((unsigned)time(NULL));                                        //seeding
    int rnd=rand()%101, u, c=1;                                         //rnd dobija random vrijednost od 0 do 100, u je ulazna varijabla
    int i;
    for(i=0; i<5 && c; i++)                                             //c je kontrolna varijabla za izlazak iz petlje
    {
        u=unos(i, kontrolaUnosa);                                       //unos sa kontrolom
        if(u==rnd)
        {
            changeTextColor(LIGHT_GREEN);
            printf("Pogodak!"); c=0; return (100/(i+1));
            changeTextColor(DEFAULT);
        }       //uslov za pogodak, izlaz iz petlje
        else if(u<rnd)
        {
            changeTextColor(YELLOW);
            printf("Broj koji trazite je veci od unesenog broja!\n\n");
            changeTextColor(DEFAULT);
        }
        else if(u>rnd)
        {
            changeTextColor(YELLOW);
            printf("Broj koji trazite je manji od unesenog broja!\n\n");
            changeTextColor(DEFAULT);
        }
    }
    if(c)                                        //ako pogodak nije ostvaren iz petog puta...
    {
        changeTextColor(RED);
        printf("Izgubili ste! Broj je %d", rnd); //ispis poruke o tacnom broju
        changeTextColor(DEFAULT);
        return 0;                                //vracanje 0 bodova
    }
}

int easy()//funkcija koja poziva olaksani mod igre
{
    srand((unsigned)time(NULL));
    int rnd=rand()%101, u, c, donji=-1, gornji=101;
    const int RANGE=rand()%6+7;            //RANGE se uzima slucajno izmedju 7 i 12
    if((rnd+RANGE)>100) rnd-=RANGE;        //ako je rnd veci od 100-RANGE, potrebno ga je smanjiti da bi se sigurno moglo ukljuciti RANGE uzastopnih brojeva iz dozvoljenog opsega
    c=1;
    int i;
    for(i=0; i<5 && c; i++)
    {
        u=unos(i, kontrolaUnosa);                                      //unos sa kontrolom
        if((u>=rnd && u<rnd+RANGE) || (i==4 && u>donji && u<gornji))   //provjera da li u pada u opseg od rnd do rnd+RANGE koji se smatra tacnim; da li 5. pokusaj ulazi u vanjske granice
        {
            changeTextColor(LIGHT_GREEN);
            printf("Pogodak!\n");
            changeTextColor(DEFAULT);
            c=0;
            return (100/(i+1));                                        //vraca se broj poena 100/broj_pokusaja
        }
        else if(u<rnd)
        {
            changeTextColor(YELLOW);
            printf("Broj koji trazite je veci od unesenog broja!\n\n");
            changeTextColor(DEFAULT);
            if(u>donji) donji=u;                                       //azuriranje vanjske donje granice
        }
        else if(u>=rnd+RANGE)
        {
            changeTextColor(YELLOW);
            printf("Broj koji trazite je manji od unesenog broja!\n\n");
            changeTextColor(DEFAULT);
            if(u<gornji) gornji=u;                                     //azuriranje vanjske gornje granice
        }
    }
    if(c)
    {
        changeTextColor(RED);
        printf("Izgubili ste! Broj je %d\n", rnd);
        changeTextColor(DEFAULT);
        return 0;
    }
}
int kontrolaUnosa(char* string, int *br)
{
    int i, broj, duz=strlen(string);
    if(!duz)                                    //ako se pritisne samo enter
    {
        printf("Unesite broj od 0 do 100!\n");
        return 1;
    }
    for(i=0; i<duz; i++)                        //kroz cijeli unijeti string se provjerava...
    {
        if(!isNumber1(string[i]))                //...da li ima znakova koji nisu cifre od 0 do 9
        {
            printf("Prihvataju se samo cifre od 0 do 9!\n");
            return 1;
        }
    }
    broj=atoi(string);                          //konverzija string-a u integer
    if(broj<0 || broj>100)                      //provjera da li int zadovoljava granice
    {
        printf("Unesite broj od 0 do 100!\n");
        return 1;
    }
    *br=broj;
    return 0;
}
int isNumber1(char karakter)
{
    if(karakter>='0' && karakter<='9') return 1;
    return 0;
}
int unos(int i, int (*pf)(char*, int*))
{
    int u;
    char broj[BUFFERSIZE1]={0};
    do
    {
        if(i!=-1) printf("%d. pokusaj: ", i+1);
        fgets(broj, BUFFERSIZE1, stdin);
        int duz=strlen(broj);
        if ((duz > 0) && (broj[duz - 1] == '\n')) broj[duz - 1] = '\0';
    }while((*pf)(broj, &u));
    u=atoi(broj);
    return u;
}

int playPogadjanje(int brojIgranja, int izgubljeniPoeniIns)
{
    int bodovi;
    if(brojIgranja<3) bodovi=easy();
    else if(izgubljeniPoeniIns>=100 && izgubljeniPoeniIns!=INT_MAX) bodovi=impossible();
    else if(izgubljeniPoeniIns==INT_MAX) bodovi=normal();
    changeTextColor(CYAN);
    printf("\nOsvojeno %d bodova\n\n", bodovi);
    changeTextColor(DEFAULT);
    return bodovi;
}
int impossible()
{
    srand((unsigned)time(NULL));
    int u, i, donji=0, gornji=100;
    for(i=0; i<5; i++)
    {
        u=unos(i, kontrolaUnosa);
        if(u>=donji && u<=gornji)
        {
            if(u-donji>gornji-u)
            {
                gornji=u;
                changeTextColor(YELLOW);
                printf("Broj koji trazite je manji od unesenog broja!\n\n");
                changeTextColor(DEFAULT);
            }
            else if(u-donji<gornji-u)
            {
                donji=u;
                changeTextColor(YELLOW);
                printf("Broj koji trazite je veci od unesenog broja!\n\n");
                changeTextColor(DEFAULT);
            }
            else
            {
                int rnd=rand()%2;
                if(rnd)
                {
                    gornji=u;
                    changeTextColor(YELLOW);
                    printf("Broj koji trazite je manji od unesenog broja!\n\n");
                    changeTextColor(DEFAULT);
                }
                else
                {
                    donji=u;
                    changeTextColor(YELLOW);
                    printf("Broj koji trazite je veci od unesenog broja!\n\n");
                    changeTextColor(DEFAULT);
                }
            }
        }
        else
        {
            if(u<donji)
            {
                changeTextColor(YELLOW);
                printf("Broj koji trazite je veci od unesenog broja!\n\n");
                changeTextColor(DEFAULT);
            }
            else if(u>gornji)
            {
                changeTextColor(YELLOW);
                printf("Broj koji trazite je manji od unesenog broja!\n\n");
                changeTextColor(DEFAULT);
            }
        }
    }
    gornji-=1;
    donji+=1;
    int rnd=rand() % (gornji + 1 - donji) + donji;
    changeTextColor(RED);
    printf("Izgubili ste! Broj je %d", rnd);
    changeTextColor(DEFAULT);
    return 0;
}
