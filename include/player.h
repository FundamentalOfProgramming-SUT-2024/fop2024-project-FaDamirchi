#ifndef PLAYER
#define PLAYER

// includes
#include "global_defines.h"
#include "map.h"

// objects
typedef struct 
{
    Position position;

    bool is_in_room;
    Room *currunt_room;

    // other options...
} Player;


// functions
bool can_move(Room **rooms, int rooms_number, Player *player, int next_y, int next_x);
void move_player(Room **rooms, int rooms_number, Player *player);
Player *player_setup(Room **rooms, int rooms_number);
void show_next(Room **rooms, Player *player, int rooms_number);

void player_update(Room **rooms, int rooms_number, Player *player);

#endif