#include "ui_utils.h"
#include "global_defines.h"

void init_colors()
{
    start_color();
    init_color(COLOR_DARK_GRAY, 300, 300, 300);
    init_color(COLOR_LIGHT_GRAY, 600, 600, 600);

    init_pair(COLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_HIGHLIGHT, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOR_TITLE, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_ALERT_MESSAGE, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_SUCCESS_MESSAGE, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_BORDER, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_FIELD, COLOR_MAGENTA, COLOR_BLACK);

    init_pair(COLOR_DOORS, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_WALLS, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_HALLS, COLOR_LIGHT_GRAY, COLOR_BLACK);
    init_pair(COLOR_UNSEEN, COLOR_DARK_GRAY, COLOR_BLACK);
    init_pair(COLOR_WINDOWS, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_STAIRS_COMING, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_STAIRS_GOING, COLOR_CYAN, COLOR_BLACK);

    init_pair(COLOR_PLAYER_WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_PLAYER_PURPULE, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_PLAYER_BLUE, COLOR_CYAN, COLOR_BLACK);

    init_pair(COLOR_GOLD_ORDINARY, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_GOLD_BLACK, COLOR_CYAN, COLOR_BLACK);

    init_pair(COLOR_FOOD_ORDINARY, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_FOOD_EXCELLENT, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_FOOD_MAGIC, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_FOOD_CORRUPT, COLOR_RED, COLOR_BLACK);

    init_pair(COLOR_SPELL_HEALTH, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_SPELL_SPEED, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_SPELL_DAMAGE, COLOR_RED, COLOR_BLACK);

    init_pair(COLOR_WEAPONS, COLOR_YELLOW, COLOR_BLACK);

    init_pair(COLOR_WALLS_TREASURE, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_FLOOR_TREASURE, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_STUFF_TREASURE, COLOR_GREEN, COLOR_BLACK);

    init_pair(COLOR_WALLS_ENCHANT, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(COLOR_FLOOR_ENCHANT, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_STUFF_ENCHANT, COLOR_RED, COLOR_BLACK);

    init_pair(COLOR_WALLS_NIGHMARE, COLOR_BLUE, COLOR_BLACK);
    init_pair(COLOR_FLOOR_NIGHMARE, COLOR_DARK_GRAY, COLOR_BLACK);
    init_pair(COLOR_STUFF_NUGHTMARE, COLOR_RED, COLOR_BLACK);

    init_pair(COLOR_FIRST_SCORE, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_SECOND_SCORE, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_THIRD_SCORE, COLOR_RED, COLOR_BLACK);

    init_pair(COLOR_CURRENT_USER, COLOR_MAGENTA, COLOR_BLACK);

    init_pair(COLOR_MONSTER_DEAMON, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_MONSTER_FIRE, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_MONSTER_GIANT, COLOR_YELLOW, COLOR_BLACK);
    init_pair(COLOR_MONSTER_SNAKE, COLOR_GREEN, COLOR_BLACK);
    init_pair(COLOR_MONSTER_UNDEED, COLOR_MAGENTA, COLOR_BLACK);
}

void draw_border(int start_y, int start_x, int height, int width)
{
    attron(COLOR_PAIR(COLOR_BORDER) | A_BOLD);
    for (int i = start_x - 1; i < start_x + width + 2; i++)
    {
        mvprintw(start_y - 1, i, "-");          // top border
        mvprintw(start_y + height - 1, i, "-"); // bottom border
    }

    for (int i = start_y; i < start_y + height; i++)
    {
        mvprintw(i, start_x - 2, "|");         // left border
        mvprintw(i, start_x + width + 1, "|"); // right border
    }

    mvprintw(start_y - 1, start_x - 2, "+");                  // top-left corner
    mvprintw(start_y - 1, start_x + width + 1, "+");          // top-right corner
    mvprintw(start_y + height - 1, start_x - 2, "+");         // bottom-left corner
    mvprintw(start_y + height - 1, start_x + width + 1, "+"); // bottom-right corner

    attroff(COLOR_PAIR(COLOR_BORDER) | A_BOLD);
}

void highlight_choice(int start_y, int start_x, const char **options, int num_choices, int choice)
{
    for (int i = 0; i < num_choices; i++)
    {
        if (i == choice)
        {
            attron(COLOR_PAIR(COLOR_HIGHLIGHT));
        }
        else
        {
            attron(COLOR_PAIR(COLOR_DEFAULT));
        }
        mvprintw(start_y + i, start_x, "%s", options[i]);
        attroff(COLOR_PAIR(COLOR_DEFAULT) | COLOR_PAIR(COLOR_HIGHLIGHT));
    }
}

void show_title(int start_y, int start_x, char *title)
{
    attron(COLOR_PAIR(COLOR_TITLE));
    mvprintw(start_y, start_x, "%s", title);
    attroff(COLOR_PAIR(COLOR_TITLE));
}

void show_field(int start_y, int start_x, char *title)
{
    attron(COLOR_PAIR(COLOR_FIELD));
    mvprintw(start_y, start_x, "%s", title);
    attroff(COLOR_PAIR(COLOR_FIELD));
}

void show_alert_message(int start_y, int start_x, char message[], float sleep_time)
{
    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
    mvprintw(start_y, start_x, "%s", message);
    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
    refresh();
    sleep(sleep_time);
}

void show_success_message(int start_y, int start_x, char message[], float sleep_time)
{
    attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
    mvprintw(start_y, start_x, "%s", message);
    attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
    refresh();
    sleep(sleep_time);
}