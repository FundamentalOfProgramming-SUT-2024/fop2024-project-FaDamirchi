#include "pregame_menu.h"
#include "ui_utils.h"
#include "global_defines.h"
#include <ncurses.h>
#include <string.h>

void show_pregame_menu(char *username)
{
    int choice = 0;

    const char *options[NUM_CHOICES_PREGAME] = {
        "New game",
        "Resume game",
        "Score board",
        "Settings"};

    init_colors();

    // getting console size
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    curs_set(0); // hiding cursor

    // displaying the main menu
    // ********* START **********
    while (1)
    {
        clear();

        // find center to start showing the menu
        int start_y = (max_y / 2) - (NUM_CHOICES_PREGAME / 2);
        int start_x = (max_x / 2) - 10;

        // displaying the menu
        int height = NUM_CHOICES_PREGAME + 1;
        int width = strlen("=== Pregame Menu ===");
        draw_border(start_y, start_x, height, width);

        show_title(start_y - 2, start_x, "=== Pregame Menu ===");

        highlight_choice(start_y, start_x, options, NUM_CHOICES_PREGAME, choice);

        // moving in the list
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = NUM_CHOICES_PREGAME - 1; // loop to the last option
            break;

        case KEY_DOWN:
            choice++;
            if (choice >= NUM_CHOICES_PREGAME)
                choice = 0; // loop to the first option
            break;

        case ENTER:
            if (choice == 0)
            {
                // start new game
            }
            else if (choice == 1)
            {
                // resume old game
            }
            else if (choice == 2)
            {
                // show score board
            }

            else if (choice == 3)
            {
                // show settings
            }
            break;

        default:
            break;
        }
    }
    // ********* END **********
}