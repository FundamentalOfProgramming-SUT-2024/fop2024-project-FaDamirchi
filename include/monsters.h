#ifndef MONSTERS
#define MONSTERS

// includes
#include "global_defines.h"
#include "map.h"

// forward declaration
typedef struct Room Room;

// consts
#define DEAMON 1
#define FIRE   2
#define GIANT  3
#define SNAKE  4
#define UNDEED 5

#define TIRED  6
#define ALWAYS 7

// objects
typedef struct Monster
{
    int monster_type;
    int moving_type;
    int damage;
    int health;

    Position position;
} Monster;

// function
void deamon_setup(Room *room, Monster *monster);
void fire_setup(Room *room, Monster *monster);
void giant_setup(Room *room, Monster *monster);
void snake_setup(Room *room, Monster *monster);
void undeed_setup(Room *room, Monster *monster);
void monster_setup(Room *room, int level);

#endif