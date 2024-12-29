#ifndef UI_UTILS
#define UI_UTILS

#include <ncurses.h>

// define colors
#define COLOR_DEFAULT   1
#define COLOR_HIGHLIGHT 2
#define COLOR_TITLE     3
#define COLOR_MESSAGE   4
#define COLOR_BORDER    5

// functions
void init_colors();
void draw_border(int start_y, int start_x, int height, int width);
void highlight_choice(int start_y, int start_x, const char **options, int num_choices, int choice);
void show_title(int start_y, int start_x, char *title);

#endif