#ifndef MONSTERS
#define MONSTERS

// includes
#include "global_defines.h"

// objects
typedef struct Monster
{
    int monster_type;
    int moving_type;
    int damage;
    int health;

    Position position;
} Monster;

#endif