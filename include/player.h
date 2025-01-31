#ifndef PLAYER
#define PLAYER

// includes
#include "global_defines.h"
#include "new_game.h"

// forward declaration
typedef struct Room Room;
typedef struct Floor Floor;

// objects
typedef struct Player
{
    Position position;

    int current_floor;

    // other options...
} Player;

// functions
bool can_move(Room **rooms, int rooms_number, bool ***map, int next_y, int next_x);
void move_player(Floor **floors, Room **rooms, int rooms_number, Player *player);
Player *player_setup(Room **rooms, int rooms_number);
bool handle_player_actions(Floor **floors, Room **rooms, Player *player);

void player_update(Floor **floors, Room **rooms, int rooms_number, Player *player, int color);

#endif