#ifndef NEW_GAME
#define NEW_GAME

// includes
#include "map.h"
#include "player.h"
#include "monsters.h"

// forward declaration
typedef struct Room Room;
typedef struct Player Player;

// objects
typedef struct Floor
{
    int rooms_number;
    Room **rooms;

    bool ***map;
} Floor;

typedef struct Game
{
    Player *player;

    int floors_number;
    Floor **floors;
} Game;

// functions
void save_game(Game *game, char *username);
void new_game(char *username, int level, int color);

#endif