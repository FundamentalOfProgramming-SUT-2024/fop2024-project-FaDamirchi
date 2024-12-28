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

    while (1)
    {
        clear();
        printw("=== Main Menu ===\n");

        // making the choice highlighted
        For(i, NUM_CHOICES)
        {
            if (i == choice)
            {
                attron(A_REVERSE);
            }
            printw("%s\n", choices[i]);
            attroff(A_REVERSE);
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
                /*Login option*/
            }
            else if (choice == 1)
            {
                /*Sign up option*/
            }
            else if (choice == 2)
            {
                /*Exit option*/
            }
            break;

        default:
            break;
        }
    }
}