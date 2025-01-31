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
    
    int mosters_number;
    Monster **monsters;

    bool ***map;

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
void new_game(int level, int color);

#endif