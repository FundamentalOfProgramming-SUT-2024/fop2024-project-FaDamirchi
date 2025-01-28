#include "pregame_menu.h"
#include "global_defines.h"
#include "settings.h"
#include "new_game.h"

void show_pregame_menu(char *username, int isNew)
{
    if (isNew == 1)
    {
        const char *options[NUM_CHOICES_NEW_USER] = {
            "Start game",
            "Score board",
            "Settings"};

        int choice = 0;

        init_colors();

        // getting console size
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        curs_set(0); // hiding cursor

        // displaying the pregame menu
        // ********* START **********
        while (1)
        {
            clear();

            // find center to start showing the menu
            int start_y = (max_y / 2) - (NUM_CHOICES_NEW_USER / 2);
            int start_x = (max_x / 2) - 10;

            // displaying the menu
            int height = NUM_CHOICES_NEW_USER + 1;
            int width = strlen("=== Pregame Menu ===");
            draw_border(start_y, start_x, height, width);

            show_title(start_y - 2, start_x, "=== Pregame Menu ===");

            highlight_choice(start_y, start_x, options, NUM_CHOICES_NEW_USER, choice);

            // moving in the list
            int ch = getch();
            switch (ch)
            {
            case KEY_UP:
                choice--;
                if (choice < 0)
                    choice = NUM_CHOICES_NEW_USER - 1; // loop to the last option
                break;

            case KEY_DOWN:
                choice++;
                if (choice >= NUM_CHOICES_NEW_USER)
                    choice = 0; // loop to the first option
                break;

            case ENTER:
                if (choice == 0)
                {
                    new_game();
                }
                else if (choice == 1)
                {
                    // show score board
                }
                else if (choice == 2)
                {
                    show_settings_menu(username);
                }

                break;

            default:
                break;
            }
        }
        // ********* END **********
    }

    else
    {
        int choice = 0;

        const char *options[NUM_CHOICES_DEFAULT] = {
            "New game",
            "Resume game",
            "Score board",
            "Settings"};

        init_colors();

        // getting console size
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);

        curs_set(0); // hiding cursor

        // displaying the pregame menu
        // ********* START **********
        while (1)
        {
            clear();

            // find center to start showing the menu
            int start_y = (max_y / 2) - (NUM_CHOICES_DEFAULT / 2);
            int start_x = (max_x / 2) - 10;

            // displaying the menu
            int height = NUM_CHOICES_DEFAULT + 1;
            int width = strlen("=== Pregame Menu ===");
            draw_border(start_y, start_x, height, width);

            show_title(start_y - 2, start_x, "=== Pregame Menu ===");

            highlight_choice(start_y, start_x, options, NUM_CHOICES_DEFAULT, choice);

            // moving in the list
            int ch = getch();
            switch (ch)
            {
            case KEY_UP:
                choice--;
                if (choice < 0)
                    choice = NUM_CHOICES_DEFAULT - 1; // loop to the last option
                break;

            case KEY_DOWN:
                choice++;
                if (choice >= NUM_CHOICES_DEFAULT)
                    choice = 0; // loop to the first option
                break;

            case ENTER:
                if (choice == 0)
                {
                    new_game();
                }
                else if (choice == 1)
                {
                    new_game();
                }
                else if (choice == 2)
                {
                    // show score board
                }

                else if (choice == 3)
                {
                    show_settings_menu(username);
                }
                break;

            default:
                break;
            }
        }
        // ********* END **********
    }
}