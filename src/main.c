#include <stdio.h>
#include <ncurses.h>
#include "main_menu.h"
#include "music.h"

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    //play_music(1);

    reset_guest_settings();
    show_main_menu();

    stop_music();
    endwin();
    return 0;
}