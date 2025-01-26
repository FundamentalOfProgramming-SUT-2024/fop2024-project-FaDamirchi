#ifndef PLAYER
#define PLAYER

// includes
#include "global_defines.h"
#include "map.h"

// objects
typedef struct 
{
    Position position;
    Room *currunt_room;

    // other options...
} Player;


// functions
void move_player(Player *player);
Player *player_setup(Room **rooms, int rooms_number);

void player_update(Player *player);

#endif