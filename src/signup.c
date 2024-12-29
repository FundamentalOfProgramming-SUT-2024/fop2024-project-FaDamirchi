#include "signup.h"
#include "global_defines.h"
#include "ui_utils.h"
#include "ncurses.h"

void show_signup_form()
{
    char *fields[] = {
        "Email: ",
        "Username: ",
        "Password: ",
        "Sign up"};

    char email[320];
    char username[20];
    char password[64];

    int currunt_field = 0;

    // getting console size
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    curs_set(0); // hiding cursor

    // displaying the signup form
    // ********* START **********
    while (1)
    {
        clear();

        // find center to start showing the menu
        int start_y = (max_y / 2) - (NUM_FEILDS / 2);
        int start_x = (max_x / 2) - 10;

        // displaying the menu
        int height = NUM_FEILDS + 2;
        int width = strlen("=== Sign up ===");
        draw_border(start_y, start_x, height, width);

        show_title(start_y - 2, start_x, "=== Sign up ===");

        highlight_choice(start_y, start_x, fields, NUM_FEILDS, currunt_field);

        // moving in the list
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            currunt_field--;
            if (currunt_field < 0)
                currunt_field = NUM_FEILDS - 1; // loop to the last field
            break;

        case KEY_DOWN:
            currunt_field++;
            if (currunt_field >= NUM_FEILDS)
                currunt_field = 0; // loop to the first field
            break;

        case ENTER:
            if (currunt_field == 0)
            {
                attron(COLOR_PAIR(COLOR_MESSAGE));
                /*Login option*/
            }
            else if (currunt_field == 1)
            {
                attron(COLOR_PAIR(COLOR_MESSAGE));
                /*Sign up option*/
            }
            else if (currunt_field == 2)
            {
                return;
            }
            break;

        default:
            break;
        }
    }

    // ********* END **********
}