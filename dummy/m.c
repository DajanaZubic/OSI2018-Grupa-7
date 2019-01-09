#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <limits.h>
#include "consolemanip.h"
#include "meni.h"
#include "bafer.h"
#include "utility.h" // FJA ZA KONTROLU DOBITKA BODOVE
//Igre
#include "igra2.h"
#include "igra4.h"
#include "loto.h"
#include "pogadjanje.h"
// Kljucevi
#include "keys.h"
# define MG "MAGENT GAMES"
//
PLAYER igrac; // GLOBALNO BICE
int main()
{
    changeConsoleTitle(MG);
    system("mode 80,40"); // Podesiti konzolu
    BAFERREZULTATA b1, b2, b3;
    inicijalizujBafer(&b1);
    inicijalizujBafer(&b2);
    inicijalizujBafer(&b3);
    impBaferi(&b1, &b2, &b3);
    // BAFERI su ucitani ako ih ima i pravilno inicijalizovani ako ih nema
    if (!ucitajPlayera(&igrac))
    {
        stvoriPlayera(&igrac);
        upisiPlayera(&igrac);// ODMAH UPISI NA BINARNU DATOTEKU

    }
    pozdravPlayera(&igrac);
    //
    spawnKeys(); // Testna f-ja // POTREBNO OTKOCITI PRILIKOM FINALNE VERZIJE
    //
    // n1 vanjski meni, n2 unutrasnji meniji
    int navigation1 = 1;
    int navigation2;
    time_t poc, kr;    // kontrolna vremena
    int expectedLoss;  // predikcija za datu igru
    int currentResult; // trenutni rezultat igre
    while (navigation1 != 5)
    {
        screen0();                                  // Pocetni ekran menija
        navigation1 = obradibrojniUnos(5, screen0); // Obrada inputa
        switch (navigation1)
        {
        case 1:
            navigation2 = obradiSpecijal1(5, screen1, &igrac); // Obrada drugog inputa oS1() sama printa pravi ekran
            while (navigation2 != 5)
            {
                if (navigation2 == 1) // POGADJANJE
                {
                    if (kontrolaKljuca(1))
                    {
                        changeConsoleTitle("POGADJANJE");
                        system("mode 80,30");
                        expectedLoss = calcNTLPoints(igrac.ukupniDobijeniPoeni, igrac.ukupniIzgubljeniPoeni, igrac.brojOdigranihPartija);
                        poc = time(0);
                        currentResult = playPogadjanje(expectedLoss);
                        kr = time(0);
                        timeSpent(1, poc, kr);
                        igrac.ukupniDobijeniPoeni = igrac.ukupniDobijeniPoeni + currentResult;
                        igrac.brojOdigranihPartija++;
                        dodajRezultat(&b1, currentResult);
                        changeConsoleTitle(MG);
                        system("mode 80,40");
                    }
                }
                if (navigation2 == 2) // KVIZ
                {
                    if (kontrolaKljuca(2))
                    {
                        //
                        changeConsoleTitle("KVIZ");
                        system("mode 160,20");
                        expectedLoss = calcNTLPoints(igrac.ukupniDobijeniPoeni, igrac.ukupniIzgubljeniPoeni, igrac.brojOdigranihPartija);
                        if (expectedLoss == INT_MAX) // Radi sistema daje onda kviz 3 laka 2 teska
                            expectedLoss = 0;
                        poc = time(0);
                        currentResult = igrajIgru2(expectedLoss);
                        kr = time(0);
                        timeSpent(2, poc, kr);
                        // Malo fensi ispis
                        printf("%s ste %d bodova", currentResult < 0 ? "Izgubili" : "Dobili",
                               currentResult < 0 ? currentResult * -1 : currentResult); // OVDJE DODATI SVASTA
                        Sleep(1800);
                        // U zavisnosti od rezultata, incrementuje se sta treba
                        if (currentResult < 0)
                            igrac.ukupniIzgubljeniPoeni = igrac.ukupniIzgubljeniPoeni - currentResult;
                        else if (currentResult > 0)
                            igrac.ukupniDobijeniPoeni = igrac.ukupniDobijeniPoeni + currentResult;
                        igrac.brojOdigranihPartija++;
                        dodajRezultat(&b2, currentResult);
                        changeConsoleTitle(MG);
                        system("mode 80,40");
                    }
                }
                if (navigation2 == 3) // LOTO
                {
                    if (kontrolaKljuca(3))
                    {
                        changeConsoleTitle("LOTO");
                        system("mode 90,30"); // "mode 120,30"
                        expectedLoss = calcNTLPoints(igrac.ukupniDobijeniPoeni, igrac.ukupniIzgubljeniPoeni, igrac.brojOdigranihPartija);
                        poc = time(0);
                        currentResult = playLoto(expectedLoss, &(igrac.ukupniIzgubljeniPoeni), &(igrac.ukupniDobijeniPoeni));
                        kr = time(0);
                        timeSpent(3, poc, kr);
                        // Loto ima bocni efekat na igraca
                        // Sam ispisuje rezultat sa 1.8 sekundnim delayom
                        igrac.brojOdigranihPartija++;
                        dodajRezultat(&b3, currentResult);
                        changeConsoleTitle(MG);
                        system("mode 80,40");
                    }
                }
                if (navigation2 == 4) // VJESALA
                {
                    if (kontrolaKljuca(4))
                    {
                        changeConsoleTitle("VJESALA");
                        system("mode 80,25");
                        poc = time(0);
                        igraj4();
                        kr = time(0);
                        timeSpent(4, poc, kr);
                        changeConsoleTitle(MG);
                        system("mode 80,40");
                    }
                }
                // IZVOZ BAFERA I IGRACA NA BINARNI FAJL
                expBaferi(&b1, &b2, &b3);
                upisiPlayera(&igrac);
                navigation2 = obradiSpecijal1(5, screen1, &igrac);
            }
            break;
        case 2:
            // OVO JE OPCIJA ZA STATISTIKU
            navigation2 = obradiSpecijal2(2, screen2, &b1, &b2, &b3); // Obrada i prikaz tabele statistike
            if (navigation2 == 1)
            {
                // IZVOZ U CSV I PORUKA
                pisiCSV(&b1, &b2, &b3);
                gotoxy(30, 35);
                changeTextColor(RED);
                printf("CSV FAJL KREIRAN");
                changeTextColor(DEFAULT);
                Sleep(1200);
            }
            break;
        case 3: // KLJUCEVI
            showCancelKeys();
            break;
        case 4:
            screen4(); // ISPIS INSTRUKCIJA 
            navigation2 = obradibrojniUnos(1, screen4);
            break;
        case 5:
            upisiPlayera(&igrac); // IZLAZ, UPIS IGRACA ZA SVAKI SLUCAJ UVIJEK
            break;
        }
    }
}
//