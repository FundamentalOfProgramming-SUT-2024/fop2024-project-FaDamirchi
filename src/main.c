#include <stdio.h>
#include <ncurses.h>
#include "main_menu.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    show_main_menu();

    endwin();
    return 0;
}