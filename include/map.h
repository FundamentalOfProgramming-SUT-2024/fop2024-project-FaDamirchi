#ifndef MAP
#define MAP

#include "global_defines.h"

// consts
#define MAP_WIDTH 120
#define MAP_HEIGHT 30

// variables
extern Position frontier[40 * 130];
extern Position come_from[40][130];

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
    int connected_doors_number;

    // other options...
} Room;

// functions
Room *generate_room(int grid);
void draw_room(Room *room);

bool is_room(Room **rooms, int rooms_number, int y, int x);
void find_path(Room **rooms, int rooms_number, Position start, Position end);
void import_path(Position start, Position currunt_position);
void connect_rooms(Room **rooms, int rooms_number);

void map_setup();

#endif