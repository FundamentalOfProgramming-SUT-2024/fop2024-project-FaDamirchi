#ifndef MAP
#define MAP

// includes
#include "global_defines.h"
#include "player.h"
#include "new_game.h"

// forward declaration
typedef struct Player Player;
typedef struct Floor Floor;

// consts
#define MAP_WIDTH 120
#define MAP_HEIGHT 30

#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3

#define ROOM_ORDINARY  4
#define ROOM_TREASURE  5
#define ROOM_ENCHANT   6
#define ROOM_NIGHTMARE 7

#define DOOR_ORDINARY 8
#define DOOR_HIDDEN   9
#define DOOR_LOCKED   10

#define FOOD_ORDINARY  11
#define FOOD_EXCELLENT 12
#define FOOD_MAGIC     13
#define FOOD_CORRUPT   14

#define SPELL_HEALTH 15
#define SPELL_SPEED  16
#define SPELL_DAMAGE 17

#define WEAPON_DAGGER 18
#define WEAPON_WAND   19
#define WEAPON_ARROW  20
#define WEAPON_SWORD  21

// variables
extern Position come_from[40][130];

// objects
typedef struct Door
{
    Position position;
    bool isConnected;

    int type;
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

typedef struct Food
{
    Position position;
    int type;
} Food;

typedef struct Spell
{
    Position position;
    int type;
} Spell;

typedef struct Weapon
{
    Position position;
    int type;
} Weapon;

typedef struct Room
{
    Position start; // starting point - upper left
    int width;
    int height;

    int grid;
    int type;

    Door doors[4];
    int doors_number;

    Window windows[3];
    int windows_number;

    bool isSeen;

    Stair stairs;

    Position *reserved_poitions;
    int reserved_number;

    Position *gold_position;
    int gold_number;

    Food *foods;
    int foods_number;

    Spell *spells;
    int spells_number;

    Weapon *weapons;
    int weapons_number;
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
void place_gold(Room **rooms, int rooms_number);
void place_food(Room **rooms, int rooms_number, int level);
void place_spell(Room **rooms, int rooms_number);
void place_weapon(Room **rooms, int rooms_number);

void set_rooms_type(Floor **floors, int floors_number, int level);
void complete_map(Floor **floors, int floors_number, int level);

Room **map_setup(int rooms_number, bool ***map, Room *previous_room, bool isLast, int current_floor);
void show_next_step(Room **rooms, Player *player, int rooms_number, bool ***map);

#endif