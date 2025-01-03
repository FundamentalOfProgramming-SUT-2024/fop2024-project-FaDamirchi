#ifndef UI_UTILS
#define UI_UTILS

#include <ncurses.h>

// define colors
#define COLOR_DEFAULT         1
#define COLOR_HIGHLIGHT       2
#define COLOR_TITLE           3
#define COLOR_ALERT_MESSAGE   4
#define COLOR_SUCCESS_MESSAGE 5
#define COLOR_BORDER          6
#define COLOR_FIELD           7

// functions
void init_colors();
void draw_border(int start_y, int start_x, int height, int width);
void highlight_choice(int start_y, int start_x, const char **options, int num_choices, int choice);
void show_title(int start_y, int start_x, char *title);
void show_field(int start_y, int start_x, char *filed);
void show_alert_message(int start_y, int start_x, char message[]);
void show_success_message(int start_y, int start_x, char message[]);

#endif