#include "signup.h"
#include "global_defines.h"
#include "ui_utils.h"
#include "manage_users.h"
#include <ncurses.h>
#include <string.h>

typedef struct
{
    char email[320];
    char username[64];
    char password[64];
} User;

void show_signup_form()
{
    User newUser;

    // getting console size
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    clear();

    // find center
    int start_y = (max_y / 2) - (NUM_FEILDS / 2);
    int start_x = (max_x / 2) - 10;

    show_title(start_y - 2, start_x, "=== Sign up ===");
    show_title(start_y - 1, start_x, "---------------");

    do
    {
        strcpy(newUser.email, "");                  // remove the prevoius email
        move(start_y, start_x + strlen("Email: ")); // move cursor to the start of the email input area
        clrtoeol();                                 // clear the line from the cursor to the end
        move(start_y + 1, start_x);                 // move cursor to the start of the next line
        clrtoeol();                                 // clear the line

        show_field(start_y, start_x, "Email: ");    // start getting the email again
        echo();
        getstr(newUser.email);
        noecho();
    } while (is_email_valid(start_y + 1, start_x, newUser.email) == false ||
             is_email_unique(start_y + 1, start_x, newUser.email) == false);

    do
    {
        strcpy(newUser.username, "");                      // remove the prevoius username
        move(start_y + 1, start_x + strlen("Username: ")); // move cursor to the start of the username input area
        clrtoeol();                                        // clear the line from the cursor to the end
        move(start_y + 2, start_x);                        // move cursor to the start of the next line
        clrtoeol();                                        // clear the line

        show_field(start_y + 1, start_x, "Username: ");    // start getting the username again
        echo();
        getstr(newUser.username);
        noecho();
    } while (is_username_unique(start_y + 2, start_x, newUser.username) == false);

    do
    {
        strcpy(newUser.password, "");                      // remove the prevoius password
        move(start_y + 2, start_x + strlen("Password: ")); // move cursor to the start of the password input area
        clrtoeol();                                        // clear the line from the cursor to the end
        move(start_y + 3, start_x);                        // move cursor to the start of the next line
        clrtoeol();                                        // clear the line

        show_field(start_y + 2, start_x, "Password: ");    // start getting the password again
        echo();
        getstr(newUser.password);
        noecho();
    } while (is_password_valid(start_y + 3, start_x, newUser.password) == false);
}