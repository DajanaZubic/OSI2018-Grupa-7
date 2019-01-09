#include "consolemanip.h"
#include <stdio.h>
#include <windows.h>
#include "meni.h"
#include <stdlib.h>
#include <string.h>
#include "bafer.h"
// 4 nove za igraca
void stvoriPlayera(PLAYER *pla)
{
    system("cls");
    printajNaslov();
    gotoxy(15, 25);
    printf("Vase ime(max 30 slova): ");
    char tm[61] = {0};
    fgets(tm, 60, stdin);
    fflush(stdin);
    if (strlen(tm) > 30)
    {
        gotoxy(15, 24);
        changeTextColor(RED);
        printf("Uzece se vasih samo prvih 30 slova.");
        changeTextColor(DEFAULT);
        Sleep(2100);
    }
    strncpy(pla->ime, tm, 30);
    pla->ukupniDobijeniPoeni = 10; // Prekopiraj ime igraca i inicijalizuj poene
}
void pozdravPlayera(PLAYER *pla)
{
    system("cls");
    printajNaslov();
    gotoxy(20, 25);
    printf("Pozdrav: %s", pla->ime);
    Sleep(3800);
}
int ucitajPlayera(PLAYER *pla)
{
    FILE *fo = fopen("IGRAC.dat", "rb");
    if (fo == NULL)
    {
        return 0;
    }
    else
    {
        fread(pla, sizeof(PLAYER), 1, fo);
        fclose(fo);
        return 1;
    }
}
void upisiPlayera(PLAYER *pla)
{
    FILE *fp = fopen("IGRAC.dat", "wb");
    fwrite(pla, sizeof(PLAYER), 1, fp);
    fclose(fp);
}
//
// FUNKCIJE ZA IZLGED I VRACANJE BROJA KOJIM SE VRSI NAVIGACIJA

void printajNaslov()
{
    FILE *fp1 = fopen("naslov1.txt", "r");
    FILE *fp2 = fopen("naslov2.txt", "r");
    if (fp1 != NULL && fp2 != NULL)
    {
        char i;
        changeTextColor(LIGHT_BLUE);
        while ((i = fgetc(fp1)) != EOF)
            printf("%c", i == 'm' ? 219 : i);
        changeTextColor(RED);
        while ((i = fgetc(fp2)) != EOF)
            printf("%c", i == 'm' ? 219 : i);
        changeTextColor(DEFAULT);
        fclose(fp1);
        fclose(fp2);
    }
    else
    {
        changeTextColor(LIGHT_BLUE);
        gotoxy(32, 10);
        printf("MAGNET");
        changeTextColor(RED);
        gotoxy(32, 11);
        printf("GAMES");
        changeTextColor(DEFAULT);
    }
}
int obradibrojniUnos(int limit, void (*scr)())
{
    char tmp[10] = {0};
    gotoxy(10, 36);
    printf("VAS IZBOR: ");
    fgets(tmp, 9, stdin);
    fflush(stdin);
    while (strlen(tmp) != 2 || !(tmp[0] >= '1' && tmp[0] <= limit + '0'))
    {
        (*scr)(); // Ponovo ekran i promjeni poruku stas sad Dujla a ?
        gotoxy(10, 36);
        changeTextColor(YELLOW);
        printf("UNESITE JEDAN OD BROJEVA KOJI SU OPCIJE: ");
        changeTextColor(DEFAULT);
        fgets(tmp, 9, stdin);
        fflush(stdin);
    }
    return tmp[0] - '0';
}
void dummyGame(int param)
{
    system("cls");
    printf("IGRA SE IGRA");
    for (int i = 0; i < 3; i++)
    {
        Sleep(850);
        printf(".");
    }
    printf("%d\n", param);
}
void screen0()
{
    system("cls");
    printajNaslov();
    gotoxy(37, 21); // NA 37 JE SREDINA
    printf("MENI");
    gotoxy(30, 22);
    printf("1.IGRAJ IGRE");
    gotoxy(30, 23);
    printf("2.STATISTIKA");
    gotoxy(30, 24);
    printf("3.TRAJANJE KLJUCEVA");
    gotoxy(30, 25);
    printf("4.INSTRUKCIJE");
    gotoxy(30, 26);
    printf("5.IZLAZ");
}
void screen1()
{
    system("cls");
    printajNaslov();
    gotoxy(37, 21); // NA 37 JE SREDINA
    printf("IGRE");
    gotoxy(30, 24);
    printf("1.POGODI BROJ");
    gotoxy(30, 25);
    printf("2.KVIZ");
    gotoxy(30, 26);
    printf("3.LOTO");
    gotoxy(30, 27);
    printf("4.VJESALA");
    gotoxy(30, 28);
    printf("5.NAZAD");
}
//
void screen2()
{
    system("cls");
    gotoxy(30, 36);
    printf("1.PISI U CSV FAJL");
    gotoxy(30, 37);
    printf("2.NAZAD");
}
void screen3()
{
    system("cls");
    gotoxy(33, 30);
    printf("1.OTKAZITE KJUC");
    gotoxy(33, 31);
    printf("2.BACK");
}
void screen4()
{
    system("cls");
    Instrukcije();
    gotoxy(33, 35);
    printf("1.NAZAD");
}
void Instrukcije()
{
    printf("Prva igra: Pogadjanje broja\nCilj igre je pogoditi zamisljeni broj u intervalu od 1 do 100.\nIgrac na raspolaganju ima 5 pokusaja. Brojevi se unose sa tastature.\nNakon svakog pokusaja igracu se ispisuje smjernica da li je uneseni\nbroj manji ili veci od uneseneog. U skladu sa tim igrac unosi novi broj.\nBodovi za ovu igru se formiraju 100/(broj pokusaja).\n\nDruga igra: Kviz\nIgracu se prikazuje 5 nasumicno izabranih pitanja.\nIgrac treba odgovoriti na pitanje da bi mu se prikazalo sledece.\nUz svako pitanje su ponudjena 3 odgovora.\nIgrac bira odgovor za koji smatra da je tacan tako sto sa tastature unese slovo pored tacnog odgovora(a,b,c).Nepostojeci odgovor povlaci upozorenje.\nNakon drugog nevalidnog pokusaja bice kaznjen sa negativnim bodovima.\nZa svaki tacan odgovor igrac dobija 20 bodova.\nUkoliko uneseni odgovor nije tacan igrac gubi 30 bodova.\nSvih 5 tacnih odgovora dodaju jos 50 bonus bodova.\n\nTreca igra: Loto\nDa bi korisnik bio u mogucnosti da igra trecu igru mora da ulozi 100 bodova.\nNa pocetku igre igrac bira 7 brojeva u opsegu od 1 do 45.\nNakon toga zapocinje proces izvlacenja 20 brojeva.\nCilj igre je pogoditi sto vise brojeva.\nZa svaki pogodjeni broj korisnik dobija (redni broj pogodtka)*10 bodova.\nAko igrac pogodi svih 7 brojeva slijedi mu 280 bodova (10+20+30+40+50+60+70).\n\nCetvrta igra: Vjesala\nCilj je pogoditi rijec unoseci slova.\nIgracu ce biti naznaceno koliko slova sadrzi rijec.\nIgracu smije pogrijesiti 8 puta nakon cega gubi igru.\nOva igra ne nosi bodove. \nNAPOMENA: Rijeci su na engleskom jeziku.\n");
}
int obradiSpecijal1(int limit, void (*scr)(), PLAYER *pla)
{
    char tmp[10] = {0};
    (*scr)();
    gotoxy(10, 22);
    printf("Igrac: %s", pla->ime);
    gotoxy(10, 23);
    printf("Bodovi: %d", pla->ukupniDobijeniPoeni - pla->ukupniIzgubljeniPoeni);
    gotoxy(10, 36);
    printf("VAS IZBOR: ");
    fgets(tmp, 9, stdin);
    fflush(stdin);
    while (strlen(tmp) != 2 || !(tmp[0] >= '1' && tmp[0] <= limit + '0'))
    {
        (*scr)(); // Ponovo ekran i promjeni poruku stas sad Dujla a ?
        gotoxy(10, 22);
        printf("Igrac: %s", pla->ime);
        gotoxy(10, 23);
        printf("Bodovi: %d", pla->ukupniDobijeniPoeni - pla->ukupniIzgubljeniPoeni);
        // OVO iznad je da se radi
        gotoxy(10, 36);
        changeTextColor(YELLOW);
        printf("UNESITE JEDAN OD BROJEVA KOJI SU OPCIJE: ");
        changeTextColor(DEFAULT);
        fgets(tmp, 9, stdin);
        fflush(stdin);
    }
    return tmp[0] - '0';
}
int obradiSpecijal2(int limit, void (*scr)(), BAFERREZULTATA *b1, BAFERREZULTATA *b2, BAFERREZULTATA *b3)
{
    char tmp[10] = {0};
    (*scr)();
    gotoxy(0, 0);
    prikaziTabeluStatistike(b1, b2, b3);
    gotoxy(10, 38);
    printf("VAS IZBOR: ");
    fgets(tmp, 9, stdin);
    fflush(stdin);
    while (strlen(tmp) != 2 || !(tmp[0] >= '1' && tmp[0] <= limit + '0'))
    {
        (*scr)();
        gotoxy(0, 0);
        prikaziTabeluStatistike(b1, b2, b3);
        // Ponovo ekran i promjeni poruku stas sad Dujla a ?
        // OVO iznad je da se radi
        gotoxy(10, 38);
        changeTextColor(YELLOW);
        printf("UNESITE JEDAN OD BROJEVA KOJI SU OPCIJE: ");
        changeTextColor(DEFAULT);
        fgets(tmp, 9, stdin);
        fflush(stdin);
    }
    return tmp[0] - '0';
}