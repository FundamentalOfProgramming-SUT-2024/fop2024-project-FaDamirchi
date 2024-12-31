#include "signup.h"
#include "global_defines.h"
#include "ui_utils.h"
#include "ncurses.h"
#include <string.h>

typedef struct
{
    char email[320];
    char username[20];
    char password[64];
} User;

void show_signup_form()
{
    User newUser;

    // getting console size
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    clear();

    int ch;
    int i = 0;

    // find center
    int start_y = (max_y / 2) - (NUM_FEILDS / 2);
    int start_x = (max_x / 2) - 10;

    while (1)
    {
        show_title(start_y - 2, start_x, "=== Sign up ===");
        show_title(start_y - 1, start_x, "---------------");

        show_field(start_y, start_x, "Email: ");
        echo();
        getstr(newUser.email);
        noecho();

        // check if the email exists...
        // check if the email is valid...

        show_field(start_y + 1, start_x, "Username: ");
        echo();
        getstr(newUser.username);
        noecho();

        // check if the username exists...

        // generate random password? (Y/n)

        show_field(start_y + 2, start_x, "Password: ");
        echo();
        getstr(newUser.password);
        noecho();

        // check conditions for password...
    }
}