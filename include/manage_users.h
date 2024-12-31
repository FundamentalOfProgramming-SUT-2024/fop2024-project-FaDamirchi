#ifndef MANAGE_USERS
#define MANAGE_USERS

#include <stdbool.h>

// files
#define USERS_FILE "users.txt"
#define SCORE_FILE "score.txt"
#define PROGRESS_FILE "progress.txt"
#define FINISHED_GAME_FILE "finished_game.txt"

// functions
bool is_email_valid(char email[]);
bool is_email_unique(char email[]);
bool is_username_unique(char username[]);
bool is_password_valid(char password[]);

#endif