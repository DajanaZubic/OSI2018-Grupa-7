#include "consolemanip.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>
void changeTextColor(int i)
{
    HANDLE hStdout;
    //HANDLE hStdin;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    //hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (i == 1)
    {
        if (!SetConsoleTextAttribute(hStdout, 0))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 2)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 3)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 4)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 5)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_RED))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 6)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 7)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 8)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 9)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_INTENSITY))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 10)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 11)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 12)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 13)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 14)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 15)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
    else if (i == 16)
    {
        if (!SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY))
        {
            MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
                       TEXT("Console Error"), MB_OK);
            return;
        }
    }
}
//
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void changeConsoleTitle(const char *naslov)
{
    char szNewTitle[MAX_PATH] = {0};
    strcpy(szNewTitle, naslov);
    SetConsoleTitle(szNewTitle);
}
