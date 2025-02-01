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

#define COLOR_WALLS         8
#define COLOR_DOORS         9
#define COLOR_HALLS         10
#define COLOR_UNSEEN        11
#define COLOR_WINDOWS       12
#define COLOR_STAIRS_GOING  13
#define COLOR_STAIRS_COMING 14

#define COLOR_PLAYER_WHITE   15
#define COLOR_PLAYER_PURPULE 16
#define COLOR_PLAYER_BLUE    17

#define COLOR_GOLD_ORDINARY 18
#define COLOR_GOLD_BLACK    19

#define COLOR_FOOD_ORDINARY  20
#define COLOR_FOOD_EXCELLENT 21
#define COLOR_FOOD_MAGIC     22
#define COLOR_FOOD_CORRUPT   23

#define COLOR_SPELL_HEALTH 24
#define COLOR_SPELL_SPEED  25
#define COLOR_SPELL_DAMAGE 26

#define COLOR_WEAPONS 27

#define COLOR_WALLS_TREASURE 28
#define COLOR_FLOOR_TREASURE 29
#define COLOR_STUFF_TREASURE 30

#define COLOR_WALLS_ENCHANT 31
#define COLOR_FLOOR_ENCHANT 32
#define COLOR_STUFF_ENCHANT 33

#define COLOR_WALLS_NIGHMARE  34
#define COLOR_FLOOR_NIGHMARE  35
#define COLOR_STUFF_NUGHTMARE 36

#define COLOR_DARK_GRAY  100
#define COLOR_LIGHT_GRAY 101

// functions
void init_colors();
void draw_border(int start_y, int start_x, int height, int width);
void highlight_choice(int start_y, int start_x, const char **options, int num_choices, int choice);
void show_title(int start_y, int start_x, char *title);
void show_field(int start_y, int start_x, char *filed);
void show_alert_message(int start_y, int start_x, char message[], float sleep_time);
void show_success_message(int start_y, int start_x, char message[], float sleep_time);

#endif