#include "login.h"
#include "global_defines.h"
#include "ui_utils.h"
#include "manage_users.h"
#include <string.h>

typedef struct
{
    char username[64];
    char password[64];
} User;

void show_login_form()
{
    User user;

    // getting console size
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    clear();

    // find center
    int start_y = (max_y / 2) - (LOGIN_NUM_FIELDS / 2);
    int start_x = (max_x / 2) - 10;

    show_title(start_y - 2, start_x, "=== Login ===");
    show_title(start_y - 1, start_x, "-------------");

    do
    {
        strcpy(user.username, "");                     // remove the prevoius username
        strcpy(user.password, "");                     // remove the prevoius password
        move(start_y, start_x + strlen("Username: ")); // move cursor to the start of the email input area
        clrtoeol();                                    // clear the line from the cursor to the end
        move(start_y + 1, start_x);                    // move cursor to the start of the next line
        clrtoeol();                                    // clear the line

        show_field(start_y, start_x, "Username: ");    // start getting the username
        echo();
        getstr(user.username);
        noecho();

        show_field(start_y + 1, start_x, "Password: "); // start getting the password
        echo();
        getstr(user.password);
        noecho();

        if (authenticate_user(user.username, user.password) == false)
        {
            show_alert_message(start_y + 3, start_x, "Authentication failed!");
            move(start_y + 3, start_x);
            clrtoeol();
        }
        else
        {
            show_success_message(start_y + 3, start_x, "Welcome!");
            break;
        }

    } while (1);

    // heading to the rest of the game
}