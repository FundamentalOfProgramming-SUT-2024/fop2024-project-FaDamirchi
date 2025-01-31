#ifndef MAP
#define MAP

// includes
#include "global_defines.h"
#include "player.h"

// forward declaration
typedef struct Player Player;

// consts
#define MAP_WIDTH 120
#define MAP_HEIGHT 30

#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3

#define ORDINARY 4
#define TREASURE 5

// variables
extern Position come_from[40][130];

// objects
typedef struct Door
{
    Position position;
    bool isConnected;
} Door;

typedef struct Window
{
    Position position;
    int side;
} Window;

typedef struct Stair
{
    bool has_stairs;
    Position position;
    int previous_floor;
    int next_floor;
} Stair;


typedef struct Room
{
    Position start; // starting point - upper left
    int width;
    int height;

    int grid;

    Door doors[4];
    int doors_number;

    Window windows[3];
    int windows_number;

    bool isSeen;

    Stair stairs;

    int type;
    // other options...
} Room;

// functions
Room *generate_room(int grid);
void draw_map(Room **rooms, int rooms_number, bool ***map, int current_floor);
void draw_all_map(Room **rooms, int rooms_number, bool ***map);
void draw_room(Room *room);
void use_windows(Player *player, Room **rooms, int rooms_number);

void is_nextto_door(Room **rooms, int rooms_number, int y, int x);
void import_hallway(Room **rooms, int rooms_number, Position pos, Position start, bool ***map);
bool is_room(Room **rooms, int rooms_number, int y, int x);
void find_path(Room **rooms, int rooms_number, Position start, Position end, bool ***map);
void connect_rooms(Room **rooms, int rooms_number, bool ***map);

void place_stairs(Room **rooms, int rooms_number, int curruent_floor);

Room **map_setup(int rooms_number, bool ***map, Room *previous_room, bool isLast, int current_floor);
void show_next_step(Room **rooms, Player *player, int rooms_number, bool ***map);

#endif