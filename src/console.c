#include "include/console.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void clear_console()
{
    #ifndef _WIN32
        printf("\e[1;1H\e[2J"); // this is more fast than system("clear") ! only for linux
    #endif

    return;
}

void hide_cursor()
{
    #ifdef _WIN32
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 10;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(consoleHandle, &info);
    #else
        printf("\e[?25l");
    #endif

    return;
}

void show_cursor()
{
    #ifdef _WIN32
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 10;
        info.bVisible = TRUE;
        SetConsoleCursorInfo(consoleHandle, &info);
    #else
        printf("\e[?25h");
    #endif
    
    return;
}