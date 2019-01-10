#include "utility.h"
#include <limits.h>
#include <windows.h>

int calcNTLPoints(int ukupniDobijeniBodovi, int ukupniIzgubljeniBodovi, int brojIgre)
{
    if (brojIgre * KOEFICIJENT_RASTA_ODNOSA <= 1.4)
    {
        if ((double)ukupniIzgubljeniBodovi / (double)ukupniDobijeniBodovi <= brojIgre * KOEFICIJENT_RASTA_ODNOSA)
            return brojIgre * KOEFICIJENT_RASTA_ODNOSA * ukupniDobijeniBodovi - ukupniIzgubljeniBodovi;
        else
            return ukupniDobijeniBodovi - ukupniIzgubljeniBodovi / (brojIgre * KOEFICIJENT_RASTA_ODNOSA);
    }
    else if ((double)ukupniIzgubljeniBodovi / (double)(ukupniDobijeniBodovi + 180) <= 1.4)
    {
        return 100;
    }
    return INT_MAX;
}
