#ifndef MONSTERS
#define MONSTERS

// includes
#include "global_defines.h"

// objects
typedef struct Monster
{
    char symbol;
    Position position;
    int lives;
} Monster;


#endif