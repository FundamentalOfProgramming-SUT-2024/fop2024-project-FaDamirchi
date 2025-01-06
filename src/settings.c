#include "settings.h"
#include "ui_utils.h"
#include "global_defines.h"
#include "manage_users.h"
#include <string.h>

void show_settings_menu(char *username)
{
    int choice = 0;

    const char *options[NUM_FIELDS_SETTINGS] = {
        "Change difficulty of the game",
        "Change color of the main character",
        "Music"};

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
        int start_y = (max_y / 2) - (NUM_FIELDS_SETTINGS / 2);
        int start_x = (max_x / 2) - 10;

        // displaying the menu
        int height = NUM_FIELDS_SETTINGS + 1;
        int width = strlen("Change color of the main character");
        draw_border(start_y, start_x, height, width);

        show_title(start_y - 2, start_x + 9, "=== Settings ===");

        highlight_choice(start_y, start_x, options, NUM_FIELDS_SETTINGS, choice);

        // moving in the list
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = NUM_FIELDS_SETTINGS - 1; // loop to the last option
            break;

        case KEY_DOWN:
            choice++;
            if (choice >= NUM_FIELDS_SETTINGS)
                choice = 0; // loop to the first option
            break;

        case ENTER:
            if (choice == 0)
            {
                // change level
            }
            else if (choice == 1)
            {
                // change color
            }
            else if (choice == 2)
            {

                // turn the music on or off
            }

            break;

        default:
            break;
        }
    }
    // ********* END **********

    FILE *file = fopen(SETTINGS_FILE, "r");
}