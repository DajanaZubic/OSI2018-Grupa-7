#ifndef CONSOLEMANIP_H_INCLUDED
#define CONSOLEMANIP_H_INCLUDED
//makroi za boje koji se prosljedjuju changeTextColor() f-ji
#define BLACK 1
#define BLUE 2
#define GREEN 3
#define DARK_CYAN 4
#define DARK_RED 5
#define PURPLE 6
#define GOLD 7
#define DARK_GRAY 9
#define DEFAULT 8
#define LIGHT_BLUE 10
#define LIGHT_GREEN 11
#define CYAN 12
#define RED 13
#define PINK 14
#define YELLOW 15
#define WHITE 16
void changeTextColor(int);             //mijenja boju teksta
void gotoxy(int, int);                 //pozicionira kursor na (x, y)
void changeConsoleTitle(const char*);  //mijenja naslov konzole
#endif // CONSOLEMANIP_H_INCLUDED
