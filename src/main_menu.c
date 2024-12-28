#include "main_menu.h"
#include "global_defines.h"
#include <ncurses.h>
#include <string.h>

void show_main_menu()
{
    int choice = 0;

    const char *choices[NUM_CHOICES] = {
        "Login",
        "Sign up",
        "Exit"};

    // color settings
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    // getting console size
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    while (1)
    {
        clear();

        // find center to start showing the menu
        int start_y = (max_y / 2) - (NUM_CHOICES / 2);
        int start_x = (max_x / 2) - 10;

        // displaying the menu
        // ********** START **********
        attron(COLOR_PAIR(3));
        mvprintw(start_y - 2, start_x, "=== Main Menu ===");
        attroff(COLOR_PAIR(3));

        // making the choice highlighted
        For(i, NUM_CHOICES)
        {
            if (i == choice)
            {
                attron(COLOR_PAIR(2));
            }
            else
            {
                attron(COLOR_PAIR(1));
            }
            mvprintw(start_y + i, start_x, "%s", choices[i]);
            attroff(COLOR_PAIR(1) | COLOR_PAIR(2));
        }

        // moving in the list
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = NUM_CHOICES - 1; // loop to the end option
            break;

        case KEY_DOWN:
            choice++;
            if (choice >= NUM_CHOICES)
                choice = 0; // loop to the first option
            break;

        case ENTER:
            if (choice == 0)
            {
                attron(COLOR_PAIR(4));
                /*Login option*/
            }
            else if (choice == 1)
            {
                attron(COLOR_PAIR(4));
                /*Sign up option*/
            }
            else if (choice == 2)
            {
                attron(COLOR_PAIR(4));
                mvprintw(start_y + NUM_CHOICES + 1, start_x, "Exiting...");
                attroff(COLOR_PAIR(3));
                refresh();
                return;
            }
            break;

        default:
            break;
        }
        // ********** END **********
    }
}