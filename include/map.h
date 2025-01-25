#ifndef MAP
#define MAP

#include "global_defines.h"

// consts
bool map[25][120][2] = {0};

// objects
typedef struct
{
    Position position;
    bool isConnected;
} Door;

typedef struct
{
    Position start; // starting point - upper left
    int width;
    int height;

    Door doors[4];
    int doors_number;

    // other options...
} Room;

// functions
Room *generate_room(int grid);
void draw_room(Room *room);
void rooms_setup();

#endif