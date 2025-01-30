#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "main_menu.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    srand(time(NULL));

    reset_guest_settings();
    show_main_menu();

    endwin();
    return 0;
}