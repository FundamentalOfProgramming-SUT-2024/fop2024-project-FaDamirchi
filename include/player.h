#ifndef PLAYER
#define PLAYER

// includes
#include "global_defines.h"
#include "new_game.h"

// forward declaration
typedef struct Room Room;
typedef struct Floor Floor;

// objects
typedef struct Stuff
{
    // foods
    int food_ordinary;
    int food_excellent;
    int food_magic;
    int food_corrupt;

    // other options...
} Stuff;

typedef struct Player
{
    Position position;
    int current_floor;
    int passed_blockes;

    int gold;
    int health;

    Stuff stuff;

    char message[100];

    // other options...
} Player;

// functions
void show_message(char *message);

bool can_move(Player *player, Room **rooms, int rooms_number, bool ***map, int next_y, int next_x);
void move_player(int ch, Floor **floors, Room **rooms, int rooms_number, Player *player);
void fast_move(Floor **floors, Room **rooms, int rooms_number, Player *player);
Player *player_setup(Room **rooms, int rooms_number);
void handle_player_actions(Floor **floors, Room **rooms, Player *player);
void show_stuff(Stuff *player);

void show_status(Player *player);
void player_update(Floor **floors, Room **rooms, int rooms_number, Player *player, int color);

#endif