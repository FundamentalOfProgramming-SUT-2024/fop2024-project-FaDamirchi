#include "settings.h"
#include "ui_utils.h"
#include "global_defines.h"
#include "manage_users.h"
#include <string.h>
#include <stdlib.h>

void update_settings(const char *username, int level, int color, int music)
{
    FILE *file = fopen(SETTINGS_FILE, "r+");
    if (!file)
    {
        perror("Error opening settings file");
        return;
    }

    // create a temp file to store changes in it
    char temp_file_name[] = "temp_settings.txt";
    FILE *temp_file = fopen(temp_file_name, "w");

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        char stored_username[320];
        sscanf(line, "%[^:]:", stored_username);

        if (strcmp(stored_username, username) == 0)
        {
            // update the settings for the user
            fprintf(temp_file, "%s:%d-%d-%d\n", username, level, color, music);
        }
        else
        {
            // copy the line in the main file
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    // replace the old file with the updated file
    remove(SETTINGS_FILE);
    rename(temp_file_name, SETTINGS_FILE);
}

void show_settings_menu(char *username)
{
    // load user settings
    FILE *file = fopen(SETTINGS_FILE, "r");

    char line[1024];
    int level = 1; // default:       Medium
    int color = 1; // default color: Red
    int music = 1; // default:       ON

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

    int choice = 0;
    int unsaved_changes = 0;
    const char *level_options[] = {" Easy ", "Medium", " Hard "};
    const char *color_options[] = {" Red ", "Green", "Blue "};
    const char *music_options[] = {"OFF", "ON "};

    const char *options[NUM_FIELDS_SETTINGS + 1] = {
        "Level",
        "Color",
        "Music",
        "Save",
        "Return"};

    init_colors();

    // Getting console size
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    curs_set(0); // Hiding cursor

    while (1)
    {
        clear();

        int start_y = (max_y / 2) - ((NUM_FIELDS_SETTINGS) / 2);
        int start_x = (max_x / 2) - 10;

        int height = NUM_FIELDS_SETTINGS + 1;
        int width = strlen("=== Settings ===") + 5;
        draw_border(start_y, start_x, height, width);

        show_title(start_y - 2, start_x + 2, "=== Settings ===");

        for (int i = 0; i < NUM_FIELDS_SETTINGS; i++)
        {
            if (choice == i)
                attron(A_REVERSE);

            mvprintw(start_y + i, start_x, "%s", options[i]);

            if (i == 0)
                mvprintw(start_y + i, start_x + 10, "< %s >", level_options[level]);
            else if (i == 1)
                mvprintw(start_y + i, start_x + 10, "< %s >", color_options[color]);
            else if (i == 2)
                mvprintw(start_y + i, start_x + 10, "< %s >", music_options[music]);

            if (choice == i)
                attroff(A_REVERSE);
        }

        // move in the list
        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice--;
            if (choice < 0)
                choice = NUM_FIELDS_SETTINGS - 1; // loop to the last option
            break;

        case KEY_DOWN:
            choice++;
            if (choice > NUM_FIELDS_SETTINGS - 1)
                choice = 0; // loop to the first option
            break;

        case KEY_LEFT:
            if (choice == 0)
            {
                level = (level - 1 + 3) % 3; // cycle through level options
                unsaved_changes = 1;
            }
            else if (choice == 1)
            {
                color = (color - 1 + 3) % 3; // cycle through color options
                unsaved_changes = 1;
            }
            else if (choice == 2)
            {
                music = (music - 1 + 2) % 2; // cycle through music options
                unsaved_changes = 1;
            }
            break;

        case KEY_RIGHT:
            if (choice == 0)
            {
                level = (level + 1) % 3; // cycle through level options
                unsaved_changes = 1;
            }
            else if (choice == 1)
            {
                color = (color + 1) % 3; // cycle through color options
                unsaved_changes = 1;
            }
            else if (choice == 2)
            {
                music = (music + 1) % 2; // cycle through music options
                unsaved_changes = 1;
            }
            break;

        case ENTER:
            if (choice == 3) // save
            {
                update_settings(username, level, color, music);
                show_success_message(start_y + 7, start_x - 2, "Changes successfully saved!", 1.5);
                return;
                unsaved_changes = 0;
            }
            else if (choice == 4) // return
            {
                if (unsaved_changes)
                {
                    show_alert_message(start_y + 7, start_x - 2, "You have unsaved changes.", 0);
                    show_alert_message(start_y + 8, start_x - 2, "Save before exiting? (y/n)", 0);
                    char ch = getch();

                    if (IS_YES(ch))
                    {
                        update_settings(username, level, color, music);
                    }
                }
                return;
            }
            break;

        default:
            break;
        }
    }
}
