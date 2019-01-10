#include "bafer.h"
void kopirajVrijeme(struct tm *dest, struct tm *a)
{
    dest->tm_hour = a->tm_hour;
    dest->tm_isdst = a->tm_isdst;
    dest->tm_mday = a->tm_mday;
    dest->tm_min = a->tm_min;
    dest->tm_mon = a->tm_mon;
    dest->tm_sec = a->tm_sec;
    dest->tm_wday = a->tm_wday;
    dest->tm_yday = a->tm_yday;
    dest->tm_year = a->tm_year;
}
void dodajRezultat(BAFERREZULTATA *bf, int bodovi)
{
    time_t vrijeme;
    time(&vrijeme);
    struct tm *a = localtime(&vrijeme);
    // Prekopiravanje sa structa, malo sakato ali mi nije drugo palo na pamet
    kopirajVrijeme(&(bf->podaci[bf->rear].vrijemeDatum), a);
    bf->podaci[bf->rear].brojBodova = bodovi;
    bf->rear = ++bf->rear % SIZE;
}
void inicijalizujBafer(BAFERREZULTATA *bf)
{
    for (int i = 0; i < 10; i++)
    {
        bf->podaci[i].brojBodova = INT_MIN;
    }
    bf->rear = 0;
}
REZULTAT **kreirajPomocniNiz(BAFERREZULTATA *izvor, int *b)
{
    int size = 0;
    for (int i = 0; i < 10; i++)
        if (izvor->podaci[i].brojBodova != INT_MIN)
            size++;
    *b = size;
    REZULTAT **pomNiz = (REZULTAT **)calloc(size, sizeof(REZULTAT *));
    for (int i = 0; i < size; i++)
    {
        pomNiz[i] = &(izvor->podaci[i]);
    }
    return pomNiz;
}
void sortirajPomocniNiz(REZULTAT **niz, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int max = i;
        for (int j = i + 1; j < size; j++)
            if (niz[max]->brojBodova < niz[j]->brojBodova)
                max = j;
        REZULTAT *tmp = niz[i];
        niz[i] = niz[max];
        niz[max] = tmp;
    }
}
void pisiCSV(BAFERREZULTATA *igra1, BAFERREZULTATA *igra2, BAFERREZULTATA *igra3)
{
    FILE *csv = fopen("Pregled_statistike.csv", "w");
    int size1, size2, size3;
    REZULTAT **pomocni1 = kreirajPomocniNiz(igra1, &size1);
    REZULTAT **pomocni2 = kreirajPomocniNiz(igra2, &size2);
    REZULTAT **pomocni3 = kreirajPomocniNiz(igra3, &size3);
    sortirajPomocniNiz(pomocni1, size1);
    sortirajPomocniNiz(pomocni2, size2);
    sortirajPomocniNiz(pomocni3, size3);
    fprintf(csv, "Bodovi,Vrijeme,Datum,Godina\n");
    fprintf(csv, "Igra1\n");
    for (int i = 0; i < size1; i++)
        fprintf(csv, "%d,%s%d:%s%d,%d.%d.,%d.\n", pomocni1[i]->brojBodova,
                pomocni1[i]->vrijemeDatum.tm_hour / 10 != 0 ? "" : "0", pomocni1[i]->vrijemeDatum.tm_hour,
                pomocni1[i]->vrijemeDatum.tm_min / 10 != 0 ? "" : "0", pomocni1[i]->vrijemeDatum.tm_min,
                pomocni1[i]->vrijemeDatum.tm_mday, pomocni1[i]->vrijemeDatum.tm_mon + 1,
                pomocni1[i]->vrijemeDatum.tm_year + 1900); // +1 month i 1900 mora zbog definicije structa
    fprintf(csv, "Igra2\n");
    for (int i = 0; i < size2; i++)
        fprintf(csv, "%d,%s%d:%s%d,%d.%d.,%d.\n", pomocni2[i]->brojBodova,
                pomocni2[i]->vrijemeDatum.tm_hour / 10 != 0 ? "" : "0", pomocni2[i]->vrijemeDatum.tm_hour,
                pomocni2[i]->vrijemeDatum.tm_min / 10 != 0 ? "" : "0", pomocni2[i]->vrijemeDatum.tm_min,
                pomocni2[i]->vrijemeDatum.tm_mday, pomocni2[i]->vrijemeDatum.tm_mon + 1,
                pomocni2[i]->vrijemeDatum.tm_year + 1900);
    fprintf(csv, "Igra3\n");
    for (int i = 0; i < size3; i++)
        fprintf(csv, "%d,%s%d:%s%d,%d.%d.,%d.\n", pomocni3[i]->brojBodova,
                pomocni3[i]->vrijemeDatum.tm_hour / 10 != 0 ? "" : "0", pomocni3[i]->vrijemeDatum.tm_hour,
                pomocni3[i]->vrijemeDatum.tm_min / 10 != 0 ? "" : "0", pomocni3[i]->vrijemeDatum.tm_min,
                pomocni3[i]->vrijemeDatum.tm_mday, pomocni3[i]->vrijemeDatum.tm_mon + 1,
                pomocni3[i]->vrijemeDatum.tm_year + 1900);
    free(pomocni1);
    free(pomocni2);
    free(pomocni3);
    fclose(csv);
}
void prikaziTabeluStatistike(BAFERREZULTATA *igra1, BAFERREZULTATA *igra2, BAFERREZULTATA *igra3) // DA SE PRIKAZE TABELA REZULTATA SVE 3 IGRE
{
    int size1, size2, size3;
    REZULTAT **pomocni1 = kreirajPomocniNiz(igra1, &size1);
    REZULTAT **pomocni2 = kreirajPomocniNiz(igra2, &size2);
    REZULTAT **pomocni3 = kreirajPomocniNiz(igra3, &size3);
    sortirajPomocniNiz(pomocni1, size1);
    sortirajPomocniNiz(pomocni2, size2);
    sortirajPomocniNiz(pomocni3, size3);
    char linije[] = "---------";
    printf("%9.9s|%9.9s|%9.9s|%9.9s\n", "Bodovi", "Vrijeme", "Datum", "Godina");
    printf("%s|%s|%s|%s\n", linije, linije, linije, linije);
    printf("%9.9s|%s-%s-%s\n", "Igra1", linije, linije, linije); // Printanje igre 1 pocinje
    for (int i = 0; i < size1; i++)
    {
        printf("%9d|    %s%d:%s%d|   %2d.%2d.|%9d.\n", pomocni1[i]->brojBodova,
               pomocni1[i]->vrijemeDatum.tm_hour / 10 != 0 ? "" : "0", pomocni1[i]->vrijemeDatum.tm_hour,
               pomocni1[i]->vrijemeDatum.tm_min / 10 != 0 ? "" : "0", pomocni1[i]->vrijemeDatum.tm_min,
               pomocni1[i]->vrijemeDatum.tm_mday, pomocni1[i]->vrijemeDatum.tm_mon + 1,
               pomocni1[i]->vrijemeDatum.tm_year + 1900);
    }
    printf("%9.9s|%s-%s-%s\n", "Igra2", linije, linije, linije); // Printanje igre 1 pocinje
    for (int i = 0; i < size2; i++)
    {
        printf("%9d|    %s%d:%s%d|   %2d.%2d.|%9d.\n", pomocni2[i]->brojBodova,
               pomocni2[i]->vrijemeDatum.tm_hour / 10 != 0 ? "" : "0", pomocni2[i]->vrijemeDatum.tm_hour,
               pomocni2[i]->vrijemeDatum.tm_min / 10 != 0 ? "" : "0", pomocni2[i]->vrijemeDatum.tm_min,
               pomocni2[i]->vrijemeDatum.tm_mday, pomocni2[i]->vrijemeDatum.tm_mon + 1,
               pomocni2[i]->vrijemeDatum.tm_year + 1900);
    }
    printf("%9.9s|%s-%s-%s\n", "Igra3", linije, linije, linije); // Printanje igre 1 pocinje
    for (int i = 0; i < size3; i++)
    {
        printf("%9d|    %s%d:%s%d|   %2d.%2d.|%9d.\n", pomocni3[i]->brojBodova,
               pomocni3[i]->vrijemeDatum.tm_hour / 10 != 0 ? "" : "0", pomocni3[i]->vrijemeDatum.tm_hour,
               pomocni3[i]->vrijemeDatum.tm_min / 10 != 0 ? "" : "0", pomocni3[i]->vrijemeDatum.tm_min,
               pomocni3[i]->vrijemeDatum.tm_mday, pomocni3[i]->vrijemeDatum.tm_mon + 1,
               pomocni3[i]->vrijemeDatum.tm_year + 1900);
    }
    free(pomocni1);
    free(pomocni2);
    free(pomocni3);
}
void expBaferi(BAFERREZULTATA *igra1, BAFERREZULTATA *igra2, BAFERREZULTATA *igra3)
{
    FILE *fo = fopen("baferi.dat", "wb");
    fwrite(igra1, sizeof(BAFERREZULTATA), 1, fo);
    fwrite(igra2, sizeof(BAFERREZULTATA), 1, fo);
    fwrite(igra3, sizeof(BAFERREZULTATA), 1, fo);
    fclose(fo);
}
void impBaferi(BAFERREZULTATA *igra1, BAFERREZULTATA *igra2, BAFERREZULTATA *igra3)
{
    FILE *fo = fopen("baferi.dat", "rb");
    if (fo != NULL)
    {
        fread(igra1, sizeof(BAFERREZULTATA), 1, fo);
        fread(igra2, sizeof(BAFERREZULTATA), 1, fo);
        fread(igra3, sizeof(BAFERREZULTATA), 1, fo);
        fclose(fo);
    }
}
