#ifndef MAP
#define MAP

#include "global_defines.h"
// consts

// objects
typedef struct
{
    Position start; // starting point - upper left
    int width;
    int height;

    Position doors[4];
    int doors_number;

    // other options...
} Room;

// functions
Room *generate_room(int grid);
void draw_room(Room *room);
void rooms_setup();

#endif