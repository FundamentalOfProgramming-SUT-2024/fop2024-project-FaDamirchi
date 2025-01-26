#ifndef MAP
#define MAP

#include "global_defines.h"

// consts
#define MAP_WIDTH 120
#define MAP_HEIGHT 30

#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3

// variables
extern Position come_from[40][130];
extern bool map[40][130][2];

// objects
typedef struct
{
    Position position;
    bool isConnected;
} Door;

typedef struct {
    Position position;
    int side;
} Window;

typedef struct
{
    Position start; // starting point - upper left
    int width;
    int height;

    Door doors[4];
    int doors_number;

    Window windows[3];
    int windows_number;

    bool isSeen;

    bool has_stair;
    Position stair;

    // other options...
} Room;

// functions
Room *generate_room(int grid);
void draw_room(Room **room, int rooms_number);

void is_nextto_door(Room **rooms, int rooms_number, int y, int x);
void import_hallway(Room **rooms, int rooms_number, Position pos, Position start);
bool is_room(Room **rooms, int rooms_number, int y, int x);
void find_path(Room **rooms, int rooms_number, Position start, Position end);
void connect_rooms(Room **rooms, int rooms_number);

void place_stairs(Room **room, int rooms_number);

Room **map_setup(int *rooms_number);

#endif