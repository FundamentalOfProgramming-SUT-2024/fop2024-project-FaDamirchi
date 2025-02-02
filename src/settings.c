#include "settings.h"
#include "global_defines.h"
#include "manage_users.h"

void update_settings(const char *username, int level, int color, int music)
{
    FILE *file = fopen(SETTINGS_FILE, "r+");
    if (!file)
    {
        perror("Error opening settings file");
        return;
    }

    char temp_file_name[] = "temp_settings.txt";
    FILE *temp_file = fopen(temp_file_name, "w");

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        char stored_username[320];
        sscanf(line, "%[^:]:", stored_username);

        if (strcmp(stored_username, username) == 0)
        {
            fprintf(temp_file, "%s:%d-%d-%d\n", username, level, color, music);
        }
        else
        {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(SETTINGS_FILE);
    rename(temp_file_name, SETTINGS_FILE);
}

void show_settings_menu(char *username)
{
    FILE *file = fopen(SETTINGS_FILE, "r");

    char line[1024];
    int level = 1;
    int color = 1;
    int music = 1;

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
    const char *color_options[] = {" White ", "Purpule", " Blue  "};
    const char *music_options[] = {"OFF", "Music 1", "Music 2"};

    const char *options[NUM_FIELDS_SETTINGS + 1] = {
        "Level",
        "Color",
        "Music",
        "Save",
        "Return"};

    init_colors();

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    curs_set(0);

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
                mvprintw(start_y + i, start_x + 10, "< %s >", level_options[level - 1]);
            else if (i == 1)
                mvprintw(start_y + i, start_x + 10, "< %s >", color_options[color - 1]);
            else if (i == 2)
                mvprintw(start_y + i, start_x + 10, "< %s >", music_options[music]);

            if (choice == i)
                attroff(A_REVERSE);
        }

        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice = (choice - 1 + NUM_FIELDS_SETTINGS) % NUM_FIELDS_SETTINGS;
            break;
        case KEY_DOWN:
            choice = (choice + 1) % NUM_FIELDS_SETTINGS;
            break;
        case KEY_LEFT:
            if (choice == 0)
                level = ((level - 2 + 3) % 3) + 1;
            else if (choice == 1)
                color = ((color - 2 + 3) % 3) + 1;
            else if (choice == 2)
                music = (music - 1 + 3) % 3;
            unsaved_changes = 1;
            break;
        case KEY_RIGHT:
            if (choice == 0)
                level = (level % 3) + 1;
            else if (choice == 1)
                color = (color % 3) + 1;
            else if (choice == 2)
                music = (music + 1) % 3;
            unsaved_changes = 1;
            break;
        case ENTER:
            if (choice == 3)
            {
                update_settings(username, level, color, music);
                show_success_message(start_y + 7, start_x - 2, "Changes successfully saved!", 1.5);
                return;
            }
            else if (choice == 4)
            {
                if (unsaved_changes)
                {
                    show_alert_message(start_y + 7, start_x - 2, "You have unsaved changes.", 0);
                    show_alert_message(start_y + 8, start_x - 2, "Save before exiting? (y/n)", 0);
                    char ch = getch();
                    if (ch == 'y' || ch == 'Y')
                    {
                        update_settings(username, level, color, music);
                    }
                }
                return;
            }
            break;
        }
    }
}