#include "keys.h"
#include "consolemanip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
int kontrolaKljuca(int igra)
{
    system("cls");
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
            if(!strcmp(tempkey, cp=decrypt(key[i].encrypted_key)) && key[i].game==igra) found=1;
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
        Sleep(1200);// Dodato da procita poruku
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
    int open=0;
    if((fp=fopen("keys.dat", "rb"))!=NULL) open=1;
    if(!open)
    {
        if((fp=fopen("keys.dat", "wb"))!=NULL)
        {
            *brojKljuceva=0;
            fwrite(brojKljuceva, sizeof(int), 1, fp);
            fclose(fp);
        }
    }
    if(open || (fp=fopen("keys.dat", "rb"))!=NULL)
    {
        fread(brojKljuceva, sizeof(int), 1, fp);
        KEY* key=(KEY*)malloc(*brojKljuceva*sizeof(KEY));
        fread(key, sizeof(KEY), *brojKljuceva, fp);
        fclose(fp);
        return key;
    }
    return NULL;
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
void prikaziKljuceve(int x, int y)
{
    KEY *key;
    int brojKljuceva;
    int keyIndex[]={-1, -1, -1, -1};
    key=readKeys(&brojKljuceva);//treba i writeKeys da ga oslobodi
    for(int i=0; i<brojKljuceva; i++)
    {
        if(key[i].game==1 && key[i].id=='a' && key[i].time_spent<key[i].key_type) keyIndex[0]=i;
        else if(key[i].game==2 && key[i].id=='a' && key[i].time_spent<key[i].key_type) keyIndex[1]=i;
        else if(key[i].game==3 && key[i].id=='a' && key[i].time_spent<key[i].key_type) keyIndex[2]=i;
        else if(key[i].game==4 && key[i].id=='a') keyIndex[3]=i;
    }
    changeTextColor(YELLOW);
    gotoxy(x+28, 0); printf("LISTA AKTIVNIH KLJUCEVA");
    changeTextColor(DEFAULT);
    printTableKey(x+4, y+2);
    for(int i=0; i<4; i++)
    {
        if(keyIndex[i]!=-1)
        {
            gotoxy(x+19, y+8+i*4);
            char *cp;
            printf("%s", cp=decrypt(key[keyIndex[i]].encrypted_key));
            free(cp);
            int tempTS=key[keyIndex[i]].key_type-key[keyIndex[i]].time_spent;
            if(i<3)
            {
                gotoxy(x+41, y+8+i*4);
                if(tempTS<0.05*key[keyIndex[i]].key_type) changeTextColor(RED);
                int days=tempTS/DAN, hours=tempTS%DAN/SAT, minutes=tempTS%DAN%SAT/60, seconds=tempTS%DAN%SAT%60;
                printf("%dd : %2dh : %2dm : %2ds", days, hours, minutes, seconds);
                changeTextColor(DEFAULT);
            }
            else
            {
                gotoxy(x+51, y+8+i*4);
                printf("%c", 236);
            }
            gotoxy(x+64, y+8+i*4);
            switch(key[keyIndex[i]].key_type)
            {
                case SAT: gotoxy(x+67, y+8+i*4); printf("1 sat"); break;
                case DAN: gotoxy(x+67, y+8+i*4); printf("1 dan"); break;
                case SEDAM_DANA: gotoxy(x+67, y+8+i*4); printf("7 dana"); break;
                case NEOGRANICEN: printf("Neogranicen"); break;
            }
        }
        else
        {
            gotoxy(x+28, y+8+i*4);
            printf("-");
            gotoxy(x+51, y+8+i*4);
            printf("-");
            gotoxy(x+69, y+8+i*4);
            printf("-");
        }
    }
    gotoxy(x, y+24);
    writeKeys(key, &brojKljuceva);
}
void printTableKey(int x, int y)
{
    FILE *fp;
    if((fp=fopen("table.txt", "r"))!=NULL)
    {
        unsigned char c;
        int pom=0;
        gotoxy(x,y);
        changeTextColor(GREEN);
        while((c=fgetc(fp))!='-')
        {
            switch(c)
            {
                case '1': c=186; break;
                case '2': c=205; break;
                case '3': c=206; break;
                case '4': c=185; break;
                case '5': c=204; break;
                case '6': c=203; break;
                case '7': c=202; break;
                case '8': c=201; break;
                case '9': c=187; break;
                case 'a': c=200; break;
                case 'b': c=188; break;
            }
            printf("%c", c);
            if(c=='\n') gotoxy(x,y+(pom+=1));
        }
        changeTextColor(DEFAULT);
        fclose(fp);
    }
    else printf("Greska kod otvaranja tabele!");
    gotoxy(x+5, y+2); printf("IGRA"); gotoxy(x+22, y+2); printf("KLJUC"); gotoxy(x+38,y+2); printf("PREOSTALO VRIJEME"); gotoxy(x+60, y+2); printf("TIP KLJUCA");
    gotoxy(x+2, y+6); printf("Pogadjanje");
    gotoxy(x+5, y+10); printf("Kviz");
    gotoxy(x+5, y+14); printf("Loto");
    gotoxy(x+3, y+18); printf("Vjesala");
}
void spawnKeys()//testna
{
    FILE *fp;
    int brojKljuceva=6;    //inicijalizovanje broja kljuceva
    //definisanje kljuceva
    KEY key1active={1, 'a', {'2', '5', '1', '2', '-', '7', '7', '2', '1', '-', '6', '3', '3','9', '-', '5', '8', '8', '7','\0'}, SAT, 3400};
    KEY key1new={1, 'n', {'1', '4', '0', '1', '-', '8', '8', '1', '0', '-', '7', '4', '2','4', '-', '5', '9', '8', '3','\0'}, DAN, 0};
    KEY key1old={1, 'o', {'3', '3', '2', '1', '-', '7', '9', '4', '4', '-', '4', '1', '2','9', '-', '3', '2', '1', '3','\0'}, DAN, 86450};
    KEY key2active={2, 'a', {'1', '1', '3', '9', '-', '6', '4', '4', '8', '-', '4', '4', '4','4', '-', '3', '3', '2', '7','\0'}, SEDAM_DANA, SEDAM_DANA-1};
    KEY key4active={4, 'a', {'1', '2', '3', '4', '-', '5', '6', '5', '6', '-', '9', '8', '7','6', '-', '0', '0', '9', '6','\0'}, NEOGRANICEN, 3700};
    KEY key3new={3,'n',{'1','2','3','4','-','1','2','3','4','-','1','2','3','4','-','1','2','3','4','\0'},DAN,0};
    //sifrovanje kljuceva
    encrypt(&key1active);
    encrypt(&key1new);
    encrypt(&key1old);
    encrypt(&key2active);
    encrypt(&key4active);
    encrypt(&key3new);
    //upis u datoteku i zatvaranje
    if((fp=fopen("keys.dat", "wb"))!=NULL)
    {
        fwrite(&brojKljuceva, sizeof(int), 1, fp);
        // Dodavanje kjuceva
        fwrite(&key1active, sizeof(KEY), 1, fp);
        fwrite(&key1new, sizeof(KEY), 1, fp);
        fwrite(&key1old, sizeof(KEY), 1, fp);
        fwrite(&key2active, sizeof(KEY), 1, fp);
        fwrite(&key4active, sizeof(KEY), 1, fp);
        fwrite(&key3new,sizeof(KEY),1,fp);
        fclose(fp);
    }
    else printf("Greska kod otvaranja datoteke sa kljucevima!");
}
void otkaziKljuc(int igra)
{
    int brojKljuceva, found=0;
    KEY *key=readKeys(&brojKljuceva);
    for(int i=0; i<brojKljuceva; i++)
    {
        if(key[i].id=='a' && key[i].game==igra)
        {
            key[i].id='o';
            found=1;
        }
    }
    if(found) {changeTextColor(LIGHT_GREEN); printf("Kljuc za %d. igru je uspjesno otkazan!\n", igra); changeTextColor(DEFAULT);}
    else printf("Nema aktivnog kljuca za %d. igru. Otkazivanje neuspjesno!\n", igra);
    writeKeys(key, &brojKljuceva);
    Sleep(2000);
    system("cls");
}
int kontrolaUnosaOtk1(char* string, int *br)
{
    int i, broj, duz=strlen(string);
    if(!duz)                                    //ako se pritisne samo enter
    {
        changeTextColor(YELLOW);
        printf("Unesite 0 ili 1!\n");
        Sleep(2000);
        clsInput();
        changeTextColor(DEFAULT);
        return 1;
    }
    for(i=0; i<duz; i++)                        //kroz cijeli unijeti string se provjerava...
    {
        if(!isdigit(string[i]))
        {
            changeTextColor(YELLOW);
            printf("Prihvataju se samo cifre 0 i 1!\n");
            Sleep(3000);
        clsInput();
            changeTextColor(DEFAULT);
            return 1;
        }
    }
    broj=atoi(string);                          //konverzija string-a u integer
    if(broj<0 || broj>1)                      //provjera da li int zadovoljava granice
    {
        changeTextColor(YELLOW);
        printf("Unesite 1-da ili 0-ne\n");
        Sleep(2000);
        clsInput();
        changeTextColor(DEFAULT);
        return 1;
    }
    *br=broj;
    return 0;
}
int unosOtkazivanje(int (*pf)(char*, int*))
{
    int u;
    char broj[100]={0};
    do
    {
        if(pf==kontrolaUnosaOtk1) printf("Da li zelite da otkazete kljuc? (1-DA, 0-NE) : ");
        else if(pf==kontrolaUnosaOtk2) printf("Unesite broj igre ciji kljuc zelite da otkazete:\nPogadjanje - 1 \nKviz       - 2 \nLoto       - 3\nVjesala    - 4\nIzlaz      - 0 \nUnos: ");
        fgets(broj, 100, stdin);
        int duz=strlen(broj);
        if ((duz > 0) && (broj[duz - 1] == '\n')) broj[duz - 1] = '\0';
    }while((*pf)(broj, &u));
    u=atoi(broj);
    return u;
}
int kontrolaUnosaOtk2(char* string, int *br)
{
    int i, broj, duz=strlen(string);
    if(!duz)                                    //ako se pritisne samo enter
    {
        changeTextColor(YELLOW);
        printf("Unesite broj od 0 do 4! ");
        Sleep(2000);
        clsInput();
        changeTextColor(DEFAULT);
        return 1;
    }
    for(i=0; i<duz; i++)                        //kroz cijeli unijeti string se provjerava...
    {
        if(!isdigit(string[i]))
        {
            changeTextColor(YELLOW);
            printf("Prihvataju se samo cifre od 0 do 4! ");
            Sleep(3000);
            clsInput();
            changeTextColor(DEFAULT);
            return 1;
        }
    }
    broj=atoi(string);                          //konverzija string-a u integer
    if(broj<0 || broj>4)                      //provjera da li int zadovoljava granice
    {
        changeTextColor(YELLOW);
        printf("Unesite broj od 0 do 4! ");
        Sleep(2000);
        clsInput();
        changeTextColor(DEFAULT);
        return 1;
    }
    *br=broj;
    return 0;
}
void showCancelKeys()
{
    int unos;
    system("mode 80,40");
    do
    {
        prikaziKljuceve(0, 0);
        unos=unosOtkazivanje(kontrolaUnosaOtk1);
        if(unos==0) {system("cls"); return;}
        clsInput();
        unos=unosOtkazivanje(kontrolaUnosaOtk2);
        switch(unos)
        {
            case 1: otkaziKljuc(1); break;
            case 2: otkaziKljuc(2); break;
            case 3: otkaziKljuc(3); break;
            case 4: otkaziKljuc(4); break;
        }
    }while(unos);
    system("cls");
}
void clsInput()
{
    gotoxy(0, 24); for(int i=0; i<80*15; i++) printf(" "); gotoxy(0, 24);
}

