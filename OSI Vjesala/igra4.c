#include <time.h>
#include <string.h>
#include <windows.h>
#include "igra4.h"
VJESALO *izvuci(FILE *fp)
{
    char mode[10] = {0};
    printf("Select difficulty:\n1. Easy peasy\n2. A bit harder\n3. Sunless sea\n");
    fgets(mode, 9, stdin);
    fflush(stdin);
    while (strlen(mode) != 2 || (mode[0] != '1' && mode[0] != '2' && mode[0] != '3'))
    {
        printf("Use nubmers 1,2 or 3 to select the difficulty you blithering idiot!\n");
        fgets(mode, 9, stdin);
        fflush(stdin);
    }
    int difficulty = mode[0] - 48; // Pretvara char is ASCII u int
    srand((unsigned)time(NULL));   // seed random
    int randWord;
    switch (difficulty)
    {
    case 1:
        randWord = rand() % MEDIUMWORDS;
        break;
    case 2:
        randWord = rand() % (HARDWORDS - MEDIUMWORDS) + MEDIUMWORDS;
        break;
    case 3:
        randWord = rand() % (TOTALWORDS - HARDWORDS) + HARDWORDS;
        break;
    }
    VJESALO *vjes = (VJESALO *)calloc(1, sizeof(VJESALO));
    fseek(fp, randWord * sizeof(VJESALO), SEEK_SET);
    fread(vjes, sizeof(VJESALO), 1, fp);
    decWord(vjes); // Obavezno
    system("cls"); // Ocisti ekran
    return vjes;
}
int igrajInstancu4(VJESALO *v)
{
    int hint; // BEEF HINTS UP
    char hintBuffer[20];
    printf("Hints:\n1. On\n2. Off\n");
    fgets(hintBuffer, 20, stdin);
    fflush(stdin);
    while (strlen(hintBuffer) != 2 || (hintBuffer[0] != '1' && hintBuffer[0] != '2' && hintBuffer[0] != '3'))
    {
        printf("I don't think you should be playing this game.\nPress 1 or 2 to turn hints on or off!\n");
        fgets(hintBuffer, 20, stdin);
        fflush(stdin);
    }
    // OVAJ LOOP GORE IZNAD UTENKATI
    hint = hintBuffer[0] - 48;
    system("cls");
    char tmp[DUZINARIJECI];
    int i = 0;
    int faliures = 0;
    // Petlja da se napravi tmp oblika npr -----x---x
    while (v->rijec[i] != '\n')
    {
        tmp[i] = '-';
        i++;
    }
    tmp[i] = '\0'; // Dodaje se terminator stringa
    while (faliures < 9)
    {
        char t;
        char tr[20];
        printf("%s%s", hint == 1 ? "HINT: " : "", hint == 1 ? v->hint : "\n");
        printf("%s\n", tmp);
        printf("%d/8 faliures.\nNext letter:", faliures);
        fgets(tr, 20, stdin);
        while (strlen(tr) != 2 || !((tr[0] >= 'A' && tr[0] <= 'Z') || (tr[0] >= 'a' && tr[0] <= 'z')))
        {
            printf("Use letters please.\n");
            printf("%d/8 faliures, try letter next:", faliures);
            fgets(tr, 20, stdin);
            fflush(stdin);
        };
        t = tr[0];
        if (t >= 'A' && t <= 'Z')
            t += 32;
        int hits = 0; // Koliko je pogodio
        int j = 0;
        //
        for (int k = 0; k < strlen(tmp); k++)
        {
            if (tmp[k] == t){
                printf("You have already tried %c.\n",t);
                Sleep(1200); // saceka 1.2 sekunde da se vidi
                break;
            }
        }
        //
        while (v->rijec[j] != '\n')
        {
            if (v->rijec[j] == t)
            {
                tmp[j] = t;
                hits++;
            }
            j++;
        }
        if (hits == 0)
            faliures++;
        int complete = 0;
        for (int k = 0; k < strlen(tmp); k++)
        {
            if (tmp[k] != '-')
                complete++;
        }
        if (complete == strlen(tmp))
            break; // Nemojte me tuci ovako mi je najlakse bilo
        system("cls");
    }
    printf("%s is the correct word.\n", tmp);
    return faliures == 9 ? 0 : 1;
}
void igraj4()
{
    FILE *source = fopen("words.txt", "rb");
    if (source != NULL)
    {
        VJESALO *vj = izvuci(source);
        int rez = igrajInstancu4(vj);
        printf("%s", rez == 1 ? "Victory" : "Faliure"); // Ovo zamijeniti sa nekim fensi funkcijama
        free(vj);
    }
    else
        printf("Nema fajla potrebnog za igru.\n");
}
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
