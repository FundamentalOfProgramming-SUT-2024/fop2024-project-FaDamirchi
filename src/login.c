#include "login.h"
#include "global_defines.h"
#include "ui_utils.h"
#include "manage_users.h"
#include "signup.h"
#include "pregame_menu.h"
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
    int start_y = (max_y / 2) - (NUM_FIELDS_LOGIN / 2);
    int start_x = (max_x / 2) - 10;

    show_title(start_y - 2, start_x, "=== Login ===");
    show_title(start_y - 1, start_x, "-------------");

    show_field(start_y, start_x, "Username: ");     // start getting the username
    echo();
    curs_set(1);
    getstr(user.username);
    curs_set(0);
    noecho();

    show_field(start_y + 1, start_x, "Password: "); // start getting the password
    echo();
    curs_set(1);
    getstr(user.password);
    curs_set(0);
    noecho();

    do
    {
        int login_status = authenticate_user(user.username, user.password);

        if (login_status == INCORRECT_PASSWORD)
        {
            show_alert_message(start_y + 3, start_x, "Incorrect password!", 1.5);
            show_alert_message(start_y + 3, start_x, "Do you want to recover your password? (y/n)", 0);

            char ch = getch();

            if (ch == 'y' || ch == 'Y')
            {
                move(start_y + 3, start_x); // move cursor to the start of the line
                clrtoeol();                 // clear the line

                char recovery_email[320];
                show_title(start_y + 3, start_x, "Enter your email: ");
                echo();
                curs_set(1);
                getstr(recovery_email);
                curs_set(0);
                noecho();

                password_recovery(user.username, recovery_email, start_y + 5, start_x);
                break;
            }
            else if (ch == 'n' || ch == 'N')
            {
                move(start_y + 3, start_x);                    // move cursor to the start of the line
                clrtoeol();                                    // clear the line
                strcpy(user.username, "");                     // remove the prevoius username
                move(start_y, start_x + strlen("Username: ")); // move cursor to the start of the username input area
                clrtoeol();                                    // clear the line from the cursor to the end
                move(start_y + 1, start_x);                    // move cursor to the start of the next line
                clrtoeol();                                    // clear the line

                show_field(start_y, start_x, "Username: ");    // start getting the username
                echo();
                curs_set(1);
                getstr(user.username);
                curs_set(0);
                noecho();

                show_field(start_y + 1, start_x, "Password: "); // start getting the password
                echo();
                curs_set(1);
                getstr(user.password);
                curs_set(0);
                noecho();
            }
        }
        else if (login_status == USERNAME_NOT_FOUND)
        {
            show_alert_message(start_y + 3, start_x, "User not found!", 1.5);
            show_alert_message(start_y + 3, start_x, "Do you want to create account? (y/n)", 0);

            char ch = getch();

            if (ch == 'y' || ch == 'Y')
            {
                show_signup_form();
            }
            else if (ch == 'n' || ch == 'N')
            {
                return;
            }
        }
        else if (login_status == SUCCESSFULL_LOGIN)
        {
            char welcome_message[124];
            strcpy(welcome_message, "Welcome ");
            strcat(welcome_message, user.username);
            strcat(welcome_message, "!");
            show_success_message(start_y + 3, start_x, welcome_message, 2.5);
            break;
        }

    } while (1);

    show_pregame_menu(user.username, 0);
}