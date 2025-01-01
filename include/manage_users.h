#ifndef MANAGE_USERS
#define MANAGE_USERS

#include <stdbool.h>

// files
#define USERS_FILE "data/users.txt"
#define SCORE_FILE "data/score.txt"
#define PROGRESS_FILE "data/progress.txt"
#define FINISHED_GAME_FILE "data/finished_game.txt"

// functions
bool is_email_valid(int start_y, int start_x, char *email);
bool is_email_unique(int start_y, int start_x, char *email);
bool is_username_unique(int start_y, int start_x, char *username);
bool is_password_valid(int start_y, int start_x, char *password);
void create_new_user(char *email, char *username, char *password);

#endif