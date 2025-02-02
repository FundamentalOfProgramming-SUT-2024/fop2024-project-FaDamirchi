#ifndef RESUME_GAME
#define RESUME_GAME

// includes
#include "new_game.h"
#include "map.h"
#include "player.h"
#include "monsters.h"

// forward declaration
typedef struct Game Game;

// functions
bool recover_information(Game *game, char *username);
void resume_game(char *username, int color);

#endif