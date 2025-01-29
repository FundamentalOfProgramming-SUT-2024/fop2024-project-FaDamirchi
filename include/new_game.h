#ifndef NEW_GAME
#define NEW_GAME

// includes
#include "map.h"
#include "player.h"
#include "monsters.h"

// objects
typedef struct Floor
{
    int rooms_number;
    Room **rooms;
    
    int mosters_number;
    Monster **monsters;

    bool map[40][130][2];

    // other options...
} Floor;

typedef struct Game
{
    Player *player;

    int floors_number;
    Floor **floors;

    // int level;

    // other options...
} Game;

// functions
void new_game();

#endif
