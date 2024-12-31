#include "signup.h"
#include "global_defines.h"
#include "ui_utils.h"
#include "manage_users.h"
#include <ncurses.h>
#include <string.h>
#include <stdbool.h>

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

    show_title(start_y - 2, start_x, "=== Sign up ===");
    show_title(start_y - 1, start_x, "---------------");

    do
    {
        show_field(start_y, start_x, "Email: ");
        echo();
        getstr(newUser.email);
        noecho();
    } while (is_email_valid() == false && is_email_unique() == false);

    do
    {
        show_field(start_y + 1, start_x, "Username: ");
        echo();
        getstr(newUser.username);
        noecho();
    } while (is_username_unique() == false);

    // generate random password? (Y/n)

    show_field(start_y + 2, start_x, "Password: ");
    echo();
    getstr(newUser.password);
    noecho();

    // check conditions for password...
}