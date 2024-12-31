#include "main_menu.h"
#include "global_defines.h"
#include "ui_utils.h"
#include "signup.h"
#include <ncurses.h>
#include <string.h>
#include <unistd.h>

void show_main_menu()
{
    int choice = 0;

    const char *options[NUM_CHOICES] = {
        "Login",
        "Sign up",
        "Exit"};

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
        int start_y = (max_y / 2) - (NUM_CHOICES / 2);
        int start_x = (max_x / 2) - 10;

        // displaying the menu
        int height = NUM_CHOICES + 2;
        int width = strlen("=== Main Menu ===");
        draw_border(start_y, start_x, height, width);

        show_title(start_y - 2, start_x, "=== Main Menu ===");

        highlight_choice(start_y, start_x, options, NUM_CHOICES, choice);

        // moving in the list
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = NUM_CHOICES - 1; // loop to the last option
            break;

        case KEY_DOWN:
            choice++;
            if (choice >= NUM_CHOICES)
                choice = 0; // loop to the first option
            break;

        case ENTER:
            if (choice == 0)
            {
                attron(COLOR_PAIR(COLOR_MESSAGE));
                /*Login option*/
            }
            else if (choice == 1)
            {
                attron(COLOR_PAIR(COLOR_MESSAGE));
                show_signup_form();
            }
            else if (choice == 2)
            {
                show_message(start_y + NUM_CHOICES + 2, start_x, "Exiting...");
                return;
            }
            break;

        default:
            break;
        }
    }
    // ********* END **********
}