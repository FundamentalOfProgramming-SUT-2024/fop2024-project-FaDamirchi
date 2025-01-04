#ifndef MANAGE_USERS
#define MANAGE_USERS

#include <stdbool.h>

// codes
#define SUCCESSFULL_LOGIN    200
#define USERNAME_NOT_FOUND   404
#define INCORRECT_PASSWORD   401

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
void generate_password(char *user_password);
void create_new_user(char *email, char *username, char *password);
int authenticate_user(char *username, char *password);
void password_recovery(char *username, char *email, int start_y, int start_x);

#endif