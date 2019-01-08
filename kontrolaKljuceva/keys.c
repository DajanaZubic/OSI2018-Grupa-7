#include "keys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
int kontrolaKljuca(int igra)
{
    KEY *key;
    int brojKljuceva, found=0, changeKey=0, i, notPass=0;;
        key=readKeys(&brojKljuceva);
        //pretrazivanje aktivnog kljuca
        i=-1;
        while(!found && ++i<brojKljuceva) if(key[i].game==igra && key[i].id=='a') found=1;
        //ako ga nadje
        if(found)
        {
            //kontrola trajanja i potrosenog vremena u datoj igri
            if((key[i].key_type==SAT && key[i].time_spent<SAT) || (key[i].key_type==DAN && key[i].time_spent<DAN) || (key[i].key_type==SEDAM_DANA && key[i].time_spent<SEDAM_DANA) || key[i].key_type==NEOGRANICEN) {free(key); return 1;}
            else
            {
                //SMINKANJE
                printf("Kljuc za igranje ove igre je istekao!\n");
                //SMINKANJE
                changeKey=1;
            }
        }
        if(changeKey) key[i].id='o'; //ako je aktivni kljuc potrosen, stavlja mu se marker "o"-old
        //SMINKANJE
        printf("Unesite kljuc sa 16 brojeva u grupama po 4 broja odvojena znakom \"-\":\n");
        //SMINKANJE
        char *tempkey=unosKey();
        found=0, changeKey=0;
        i=-1;
        while(!found && ++i<brojKljuceva)
        {
            char *cp;
            if(!strcmp(tempkey, cp=decrypt(key[i].encrypted_key))) found=1;
            free(cp);
        }
        free(tempkey);
        if(!found)
        {
            //SMINKANJE
            printf("Kljuc nije validan!\n");
            //SMINKANJE
            notPass=1;
        }
        else if(found && key[i].id=='o')
        {
            //SMINKANJE
            printf("Kljuc je vec iskoristen!\n");
            //SMINKANJE
            notPass=1;
        }
        else if(found && key[i].id=='n')
        {
            //SMINKANJE
            printf("Kljuc je prihvacen!\n");
            //SMINKANJE
            Sleep(1000);
            key[i].id='a';
        }
        writeKeys(key, &brojKljuceva);
        if(notPass)
        {
            return 0;
        }
        else return 1;
}
void timeSpent(int igra, time_t pocetakIgranja, time_t krajIgranja)
{
    int brojKljuceva;
    KEY *key=readKeys(&brojKljuceva);
    for(int i=0; i<brojKljuceva; i++)
        if(key[i].game==igra && key[i].id=='a')
        {
            key[i].time_spent+=(int)(krajIgranja-pocetakIgranja);
        }
    writeKeys(key, &brojKljuceva);
}
char* unosKey()
{
    char key[75]={0};
    do
    {
        fgets(key, 75, stdin);
        int duz=strlen(key);
        if ((duz > 0) && (key[duz - 1] == '\n')) key[duz - 1] = '\0';
    }while(kontrolaUnosaKey(key));
    char *temp=(char*)calloc(20,sizeof(char));
    strcpy(temp, key);
    return temp;
}
int kontrolaUnosaKey(char *unos)
{
    if(strlen(unos)!=19) {
        //SMINKANJE
        printf("Nepravilan unos. Mora se unijeti tacno 19 znakova\n");
        //SMINKANJE
        return 1;
    }
    if(pronadjiNedozvoljeni(unos))
    {
        //SMINKANJE
        printf("Prihvataju se samo cifre od 0 do 9 i znak \"-\"\n");
        //SMINKANJE
        return 1;
    }
    if(unos[4]!='-' || unos[9]!='-' || unos[14]!='-')
    {
        //SMINKANJE
        printf("Nepravilan format unosa\n");
        //SMINKANJE
        return 1;
    }
    for(int i=0; i<19; i++)
    {
        if((i+1)%5==0) continue;
        if(!isdigit(unos[i]))
        {
            //SMINKANJE
            printf("Nepravilan format unosa\n");
            //SMINKANJE
            return 1;
        }
    }
    return 0;
}
int pronadjiNedozvoljeni(char *unos)
{
    for(int i=0; i<strlen(unos); i++)
    {
        if(!isdigit(unos[i]) && unos[i]!='-') return 1;
    }
    return 0;
}
void encrypt(KEY *key)
{
    for(int i=0; i<19; i++)
    {
        key->encrypted_key[i]+=POMJERAJ;
    }
}
char* decrypt(char *cryptedKey)
{
    char *temp=(char*)calloc(20, sizeof(char));
    strcpy(temp, cryptedKey);
    for(int i=0; i<strlen(temp); i++) temp[i]-=POMJERAJ;//testno blokiranje
    return temp;
}
KEY* readKeys(int *brojKljuceva)
{
    FILE *fp;
    if((fp=fopen("keys.dat", "rb"))!=NULL)
    {
        fread(brojKljuceva, sizeof(int), 1, fp);
        KEY* key=(KEY*)malloc(*brojKljuceva*sizeof(KEY));
        fread(key, sizeof(KEY), *brojKljuceva, fp);
        fclose(fp);
        return key;
    }
    else
    {
        printf("Greska kod otvaranja datoteke sa kljucevima!");
        return NULL;
    }
}
int writeKeys(KEY *key,int *brojKljuceva)
{
    FILE *fp;
    if((fp=fopen("keys.dat", "wb"))!=NULL)
    {
        fwrite(brojKljuceva, sizeof(int), 1, fp);
        fwrite(key, sizeof(KEY), *brojKljuceva, fp);
        fclose(fp);
        free(key);
        return 1;
    }
    else
    {
        printf("Greska kod otvaranja datoteke sa kljucevima!");
        return 0;
    }
}
