#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "keys.h"
int unosGen(int (*)(char*, int*));
int kontrolaUnosaGen1(char*, int*);
int kontrolaUnosaGen2(char*, int*);
int kontrolaUnosaGen3(char*, int*);
void generateKey(KEY**, int*, int, int);
int keyExist(KEY*, KEY*, int);
void printNewKeys(KEY*, int);
int main()
{
    int brojKljuceva;
    int unos, unos2, unos3;
    do
    {
        KEY *key=readKeys(&brojKljuceva);
        //if(key==NULL) key=readKeys(&brojKljuceva);
        system("cls");
        printf("                               GENERATOR KLJUCEVA\n\n");
        printf("Generisi kljuc                        - 1\nLista prethodno generisanih kljuceva  - 2\nIzlaz                                 - 0\n");
        unos=unosGen(kontrolaUnosaGen1);
        if(unos==1)
        {
            system("cls");
            printf("                               GENERATOR KLJUCEVA\n\n");
            printf("Za koju igru zelite kljuc?\nPogadjanje - 1 \nKviz       - 2 \nLoto       - 3\nVjesala    - 4\nIzlaz      - 0 \n");
            unos2=unosGen(kontrolaUnosaGen2);
            if(unos2>0 && unos2<4)
            {
                system("cls");
                printf("                               GENERATOR KLJUCEVA\n\n");
                printf("Koji tip kljuca zelite?\n1 sat   - 1\n1 dan   - 2\n7 dana  - 3\nIzlaz   - 0\n");
                unos3=unosGen(kontrolaUnosaGen3);
                switch(unos3)
                {
                    case 1: generateKey(&key, &brojKljuceva, unos2, SAT); break;
                    case 2: generateKey(&key, &brojKljuceva, unos2, DAN); break;
                    case 3: generateKey(&key, &brojKljuceva, unos2, SEDAM_DANA); break;
                }
            }
            else if(unos2==4) generateKey(&key, &brojKljuceva, 4, NEOGRANICEN);
            if(unos2 && unos3)
            {
                writeKeys(key,&brojKljuceva);
                printf("Generisanje uspjesno.\n");
                system("pause");
            }
        }
        else if(unos==2)
        {
            system("cls");
            printNewKeys(key, brojKljuceva);
            printf("\n"); system("pause");
            free(key);
        }
    }while(unos);
    return 0;
}
int unosGen(int (*pf)(char*, int*))
{
    int u;
    char broj[100]={0};
    do
    {
        printf("Unos: ");
        fgets(broj, 100, stdin);
        int duz=strlen(broj);
        if ((duz > 0) && (broj[duz - 1] == '\n')) broj[duz - 1] = '\0';
    }while((*pf)(broj, &u));
    system("cls");
    u=atoi(broj);
    return u;
}
int kontrolaUnosaGen1(char* string, int *br)
{
    int i, broj, duz=strlen(string);
    if(!duz)                                    //ako se pritisne samo enter
    {
        printf("\nUnesite broj od 0 do 2!\n");
        return 1;
    }
    for(i=0; i<duz; i++)                        //kroz cijeli unijeti string se provjerava...
    {
        if(!isdigit(string[i]))
        {
            printf("\nUnesite broj od 0 do 2!\n");
            return 1;
        }
    }
    broj=atoi(string);
    if(broj<0 || broj>2)
    {
        printf("\nUnesite broj od 0 do 2!\n");
        return 1;
    }
    *br=broj;
    return 0;
}
int kontrolaUnosaGen2(char* string, int *br)
{
    int i, broj, duz=strlen(string);
    if(!duz)
    {
        printf("\nUnesite broj od 1 do 4!\n");
        return 1;
    }
    for(i=0; i<duz; i++)
    {
        if(!isdigit(string[i]))
        {
            printf("\nUnesite broj od 1 do 4!\n");
            return 1;
        }
    }
    broj=atoi(string);
    if(broj<0 || broj>4)
    {
        printf("\nUnesite broj od 1 do 4!\n");
        return 1;
    }
    *br=broj;
    return 0;
}
int kontrolaUnosaGen3(char* string, int *br)
{
    int i, broj, duz=strlen(string);
    if(!duz)
    {
        printf("\nUnesite broj od 0 do 3!\n");
        return 1;
    }
    for(i=0; i<duz; i++)
    {
        if(!isdigit(string[i]))
        {
            printf("\nUnesite broj od 0 do 3!\n");
            return 1;
        }
    }
    broj=atoi(string);
    if(broj<0 || broj>3)
    {
        printf("\nUnesite broj od 0 do 3!\n");
        return 1;
    }
    *br=broj;
    return 0;
}

void generateKey(KEY **key, int *brojKljuceva, int igra, int tip)
{
    char nwKeych[20]={0};
    KEY nwKey;
    nwKey.game=igra; nwKey.key_type=tip; nwKey.time_spent=0; nwKey.id='n';
    srand((unsigned)time(NULL));
    do
    {
        for(int i=0; i<19; i++)
        {
            if((i+1)%5==0) nwKeych[i]='-';
            else nwKeych[i]=rand() % 10 + 48;
        }
        strcpy(nwKey.encrypted_key, nwKeych);
    }while(keyExist(*key, &nwKey, *brojKljuceva));
    *key=(KEY*)realloc(*key, sizeof(KEY)*++*brojKljuceva);
    (*key)[*brojKljuceva-1]=nwKey;
}
int keyExist(KEY *key, KEY *nwKey, int brojKljuceva)
{
    encrypt(nwKey);
    for(int i=0; i<brojKljuceva; i++) if(!strcmp(key[i].encrypted_key, nwKey->encrypted_key)) return 1;
    return 0;
}
void printNewKeys(KEY *key, int brojKljuceva)
{
    printf("Kljucevi za igru Pogadjanje:\n----------------------------\n");
    for(int i=0; i<brojKljuceva; i++)
        if(key[i].game==1 && key[i].id=='n')
        {
            char *cp=decrypt(key[i].encrypted_key);
            printf("%s\n", cp);
            free(cp);
        }
    printf("\n");
    printf("Kljucevi za igru Kviz:\n----------------------------\n");
    for(int i=0; i<brojKljuceva; i++)
        if(key[i].game==2 && key[i].id=='n')
        {
            char *cp=decrypt(key[i].encrypted_key);
            printf("%s\n", cp);
            free(cp);
        }
    printf("\n");
    printf("Kljucevi za igru Loto:\n----------------------------\n");
    for(int i=0; i<brojKljuceva; i++)
        if(key[i].game==3 && key[i].id=='n')
        {
            char *cp=decrypt(key[i].encrypted_key);
            printf("%s\n", cp);
            free(cp);
        }
    printf("\n");
    printf("Kljucevi za igru Vjesala:\n----------------------------\n");
    for(int i=0; i<brojKljuceva; i++)
        if(key[i].game==4 && key[i].id=='n')
        {
            char *cp=decrypt(key[i].encrypted_key);
            printf("%s\n", cp);
            free(cp);
        }
}
