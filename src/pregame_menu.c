#include "pregame_menu.h"
#include "global_defines.h"
#include "settings.h"
#include "new_game.h"
#include "manage_users.h"
#include "music.h"
#include "resume_game.h"
#include "score_board.h"

void show_pregame_menu(char *username, int isNew)
{
    // settings properties
    int level = 1;
    int color = 1;
    int music = 1;

    FILE *file = fopen(SETTINGS_FILE, "r");

    char line[1024];

    while (fgets(line, sizeof(line), file))
    {
        char stored_username[320];
        sscanf(line, "%[^:]:", stored_username);

        if (strcmp(stored_username, username) == 0)
        {
            sscanf(line, "%*[^:]:%d-%d-%d", &level, &color, &music);
            break;
        }
    }

    if (music)
    {
        play_music(music);
    }
    else
    {
        stop_music();
    }

    fclose(file);

    if (isNew)
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
                    // load user settings
                    FILE *file = fopen(SETTINGS_FILE, "r");

                    char line[1024];

                    while (fgets(line, sizeof(line), file))
                    {
                        char stored_username[320];
                        sscanf(line, "%[^:]:", stored_username);

                        if (strcmp(stored_username, username) == 0)
                        {
                            sscanf(line, "%*[^:]:%d-%d-%d", &level, &color, &music);
                            break;
                        }
                    }

                    fclose(file);

                    // start the game with saved settings
                    new_game(username, level, color, 1);
                }
                else if (choice == 1)
                {
                    show_score_board(NULL);
                }
                else if (choice == 2)
                {
                    show_settings_menu(username);

                    // load user settings
                    FILE *file = fopen(SETTINGS_FILE, "r");

                    char line[1024];

                    while (fgets(line, sizeof(line), file))
                    {
                        char stored_username[320];
                        sscanf(line, "%[^:]:", stored_username);

                        if (strcmp(stored_username, username) == 0)
                        {
                            sscanf(line, "%*[^:]:%d-%d-%d", &level, &color, &music);
                            break;
                        }
                    }

                    if (music)
                    {
                        play_music(music);
                    }
                    else
                    {
                        stop_music();
                    }

                    fclose(file);
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
                    // load user settings
                    FILE *file = fopen(SETTINGS_FILE, "r");

                    char line[1024];

                    while (fgets(line, sizeof(line), file))
                    {
                        char stored_username[320];
                        sscanf(line, "%[^:]:", stored_username);

                        if (strcmp(stored_username, username) == 0)
                        {
                            sscanf(line, "%*[^:]:%d-%d-%d", &level, &color, &music);
                            break;
                        }
                    }

                    fclose(file);

                    // start the game with saved settings
                    new_game(username, level, color, 0);
                }
                else if (choice == 1)
                {
                    // load user settings
                    FILE *file = fopen(SETTINGS_FILE, "r");

                    char line[1024];

                    while (fgets(line, sizeof(line), file))
                    {
                        char stored_username[320];
                        sscanf(line, "%[^:]:", stored_username);

                        if (strcmp(stored_username, username) == 0)
                        {
                            sscanf(line, "%*[^:]:%d-%d-%d", &level, &color, &music);
                            break;
                        }
                    }

                    fclose(file);

                    // start the game with saved settings
                    resume_game(username, color);
                }
                else if (choice == 2)
                {
                    show_score_board(username);
                }

                else if (choice == 3)
                {
                    show_settings_menu(username);

                    // load user settings
                    FILE *file = fopen(SETTINGS_FILE, "r");

                    char line[1024];

                    while (fgets(line, sizeof(line), file))
                    {
                        char stored_username[320];
                        sscanf(line, "%[^:]:", stored_username);

                        if (strcmp(stored_username, username) == 0)
                        {
                            sscanf(line, "%*[^:]:%d-%d-%d", &level, &color, &music);
                            break;
                        }
                    }

                    if (music)
                    {
                        play_music(music);
                    }
                    else
                    {
                        stop_music();
                    }

                    fclose(file);
                }
                break;

            default:
                break;
            }
        }
        // ********* END **********
    }
}