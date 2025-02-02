#ifndef PLAYER
#define PLAYER

// includes
#include "global_defines.h"
#include "new_game.h"

// forward declaration
typedef struct Room Room;
typedef struct Floor Floor;

// consts
#define WIN     1
#define NOTHING 0
#define LOSS   -1

#define NUM_FOOD_MENU   5
#define NUM_SPELL_MENU  4
#define NUM_WEAPON_MENU 6

// objects
typedef struct Stuff
{
    // foods
    int food_ordinary;
    int food_excellent;
    int food_magic;
    int food_corrupt;

    int spell_health;
    int spell_speed;
    int spell_damage;

    bool weapon_mace;
    bool weapon_dagger;
    bool weapon_wand;
    bool weapon_arrow;
    bool weapon_sword;

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
void move_player(int inp, Floor **floors, Room **rooms, int rooms_number, Player *player);
void fast_move(Floor **floors, Room **rooms, int rooms_number, Player *player);
Player *player_setup(Room **rooms, int rooms_number);
void handle_player_actions(Floor **floors, Room **rooms, Player *player);
void show_foods(Player *player);
void show_spells(Player *player);
void show_weapons(Player *player);

void status_bar(Player *player);
void player_update(Floor **floors, Room **rooms, int rooms_number, Player *player, int color);
int check_status(Player *player, Floor **floors);

#endif