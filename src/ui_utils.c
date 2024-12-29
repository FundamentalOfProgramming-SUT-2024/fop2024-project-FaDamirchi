#include "ui_utils.h"
#include "global_defines.h"
#include <ncurses.h>

void init_colors()
{
    start_color();
    init_pair(COLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_HIGHLIGHT, COLOR_BLACK, COLOR_GREEN);
    init_pair(COLOR_TITLE, COLOR_CYAN, COLOR_BLACK);
    init_pair(COLOR_MESSAGE, COLOR_RED, COLOR_BLACK);
    init_pair(COLOR_BORDER, COLOR_YELLOW, COLOR_BLACK);
}

void draw_border(int start_y, int start_x, int height, int width)
{
    attron(COLOR_PAIR(COLOR_BORDER) | A_BOLD);
    for (int i = start_x; i < start_x + width; i++)
    {
        mvprintw(start_y - 1, i, "-");          // top border
        mvprintw(start_y + height - 1, i, "-"); // bottom border
    }

    for (int i = start_y; i < start_y + height; i++)
    {
        mvprintw(i, start_x - 1, "|");         // left border
        mvprintw(i, start_x + width - 1, "|"); // right border
    }

    mvprintw(start_y - 1, start_x - 1, "+");                  // top-left corner
    mvprintw(start_y - 1, start_x + width - 1, "+");          // top-right corner
    mvprintw(start_y + height - 1, start_x - 1, "+");         // bottom-left corner
    mvprintw(start_y + height - 1, start_x + width - 1, "+"); // bottom-right corner

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
    mvprintw(start_y, start_x,"%s", title);
    attroff(COLOR_PAIR(COLOR_TITLE));
}