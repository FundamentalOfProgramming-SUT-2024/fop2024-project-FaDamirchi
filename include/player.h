#ifndef PLAYER
#define PLAYER

// includes
#include "global_defines.h"
#include "new_game.h"

// forward declaration
typedef struct Room Room;
typedef struct Floor Floor;

// objects
typedef struct Weapon
{
    int type;
    int damage;

    // other options...
} Weapon;

typedef struct Spell
{
    int type;

    // other options...
} Spell;

typedef struct Player
{
    Position position;
    int current_floor;

    int gold;
    int health;

    // other options...
} Player;

// functions
bool can_move(Room **rooms, int rooms_number, bool ***map, int next_y, int next_x);
void move_player(int ch, Floor **floors, Room **rooms, int rooms_number, Player *player);
void fast_move(Floor **floors, Room **rooms, int rooms_number, Player *player);
Player *player_setup(Room **rooms, int rooms_number);
void handle_player_actions(Floor **floors, Room **rooms, Player *player);

void show_status(Player *player);
void player_update(Floor **floors, Room **rooms, int rooms_number, Player *player, int color);

#endif