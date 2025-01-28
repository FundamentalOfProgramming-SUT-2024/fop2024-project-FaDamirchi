#ifndef PLAYER
#define PLAYER

// includes
#include "global_defines.h"

// forward declaration
typedef struct Room Room;

// objects
typedef struct Player
{
    Position position;
    Room *currunt_room;

    // other options...
} Player;

// functions
bool can_move(Room **rooms, int rooms_number, Player *player, int next_y, int next_x);
void move_player(Room **rooms, int rooms_number, Player *player);
Player *player_setup(Room **rooms, int rooms_number);

void player_update(Room **rooms, int rooms_number, Player *player);

#endif