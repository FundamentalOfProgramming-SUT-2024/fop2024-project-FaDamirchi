#include "main_menu.h"
#include "global_defines.h"
#include "signup.h"
#include "login.h"
#include "pregame_menu.h"
#include "manage_users.h"

void reset_guest_settings()
{
    FILE *file = fopen(SETTINGS_FILE, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // read the first line
    char first_line[256];
    if (fgets(first_line, sizeof(first_line), file) == NULL)
    {
        perror("Error reading file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // modify the first line
    char *colon = strchr(first_line, ':');
    if (colon != NULL)
    {
        sprintf(colon + 1, "1-1-1\n");
    }

    // read the rest of the file
    char rest_of_file[4096];
    size_t rest_size = fread(rest_of_file, 1, sizeof(rest_of_file), file);
    fclose(file);

    // write the modified first line and the rest of the file back
    file = fopen(SETTINGS_FILE, "w");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    fputs(first_line, file);
    fwrite(rest_of_file, 1, rest_size, file);
    fclose(file);
}

void show_main_menu()
{
    int choice = 0;

    const char *options[NUM_CHOICES_MAINMENU] = {
        "Log in",
        "Sign up",
        "Play as a Guest",
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
        int start_y = (max_y / 2) - (NUM_CHOICES_MAINMENU / 2);
        int start_x = (max_x / 2) - 10;

        // displaying the menu
        int height = NUM_CHOICES_MAINMENU + 1;
        int width = strlen("=== Main Menu ===");
        draw_border(start_y, start_x, height, width);

        show_title(start_y - 2, start_x, "=== Main Menu ===");

        highlight_choice(start_y, start_x, options, NUM_CHOICES_MAINMENU, choice);

        // moving in the list
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = NUM_CHOICES_MAINMENU - 1; // loop to the last option
            break;

        case KEY_DOWN:
            choice++;
            if (choice >= NUM_CHOICES_MAINMENU)
                choice = 0; // loop to the first option
            break;

        case ENTER:
            if (choice == 0)
            {
                show_login_form();
            }
            else if (choice == 1)
            {
                show_signup_form();
            }
            else if (choice == 2)
            {
                show_alert_message(start_y + NUM_CHOICES_MAINMENU + 2, start_x - 2, "Attention:", 1);
                show_success_message(start_y + NUM_CHOICES_MAINMENU + 3, start_x - 2, "By playing as a guest,", 0);
                show_success_message(start_y + NUM_CHOICES_MAINMENU + 4, start_x - 2, "your progress won\'t be saved!", 2.5);

                show_pregame_menu("53e00d37bf3fdef41c074b9d53b509b07c32b459", 1);
            }

            else if (choice == 3)
            {
                show_alert_message(start_y + NUM_CHOICES_MAINMENU + 2, start_x, "Exiting...", 1.5);
                return;
            }
            break;

        default:
            break;
        }
    }
    // ********* END **********
}