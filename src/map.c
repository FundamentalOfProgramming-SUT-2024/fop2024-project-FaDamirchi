#include "map.h"
#include "ui_utils.h"
#include "global_defines.h"
#include <time.h>
#include <stdlib.h>

Position come_from[40][130];
int connected_doors = 0;

Room *generate_room(int grid)
{
    Room *newRoom = (Room *)malloc(sizeof(Room));

    switch (grid)
    {
    case 0:
        newRoom->start.x = 3;
        newRoom->start.y = 1;
        break;
    case 1:
        newRoom->start.x = 24;
        newRoom->start.y = 1;
        break;
    case 2:
        newRoom->start.x = 48;
        newRoom->start.y = 1;
        break;
    case 3:
        newRoom->start.x = 72;
        newRoom->start.y = 1;
        break;
    case 4:
        newRoom->start.x = 96;
        newRoom->start.y = 1;
        break;
    case 5:
        newRoom->start.x = 3;
        newRoom->start.y = 15;
        break;
    case 6:
        newRoom->start.x = 24;
        newRoom->start.y = 15;
        break;
    case 7:
        newRoom->start.x = 48;
        newRoom->start.y = 15;
        break;
    case 8:
        newRoom->start.x = 72;
        newRoom->start.y = 15;
        break;
    case 9:
        newRoom->start.x = 96;
        newRoom->start.y = 15;
        break;

    default:
        break;
    }

    newRoom->width = 6 + rand() % 9;  // min: 4, max: 14
    newRoom->height = 4 + rand() % 9; // min: 4, max: 12

    // generate random starting points
    newRoom->start.x += rand() % (15 - newRoom->width);
    newRoom->start.y += rand() % (13 - newRoom->height);

    // generating doors
    newRoom->doors_number = 1 + rand() % 4; // min: 1, max: 4
    newRoom->connected_doors_number = 0;
    bool hasDoor[4] = {0};

    for (int i = 0; i < newRoom->doors_number; i++)
    {
        int side;
        while (1)
        {
            side = rand() % 4;
            if (!hasDoor[side])
            {
                hasDoor[side] = 1;
                break;
            }
        }

        // placing the doors
        if (side == 0) // top
        {
            newRoom->doors[i].position.x = newRoom->start.x + 1 + rand() % (newRoom->width - 2);
            newRoom->doors[i].position.y = newRoom->start.y;
        }
        else if (side == 1) // right
        {
            newRoom->doors[i].position.x = newRoom->start.x + newRoom->width - 1;
            newRoom->doors[i].position.y = newRoom->start.y + 1 + rand() % (newRoom->height - 2);
        }
        else if (side == 2) // bottom
        {
            newRoom->doors[i].position.x = newRoom->start.x + 1 + rand() % (newRoom->width - 2);
            newRoom->doors[i].position.y = newRoom->start.y + newRoom->height - 1;
        }
        else if (side == 3) // left
        {
            newRoom->doors[i].position.x = newRoom->start.x;
            newRoom->doors[i].position.y = newRoom->start.y + 1 + rand() % (newRoom->height - 2);
        }

        newRoom->doors[i].isConnected = false;
    }

    return newRoom;
}

void draw_room(Room *room)
{
    // draw top and bottom
    attron(COLOR_PAIR(COLOR_WALLS) | A_BOLD);
    for (int i = room->start.x; i < room->start.x + room->width; i++)
    {
        mvprintw(room->start.y, i, "-");                    // top border
        mvprintw(room->start.y + room->height - 1, i, "-"); // bottom border
    }
    attroff(COLOR_PAIR(COLOR_WALLS) | A_BOLD);

    // draw floor and side walls
    for (int i = room->start.y + 1; i < room->start.y + room->height - 1; i++)
    {
        attron(COLOR_PAIR(COLOR_WALLS) | A_BOLD);
        mvprintw(i, room->start.x, "|");                   // left border
        mvprintw(i, room->start.x + room->width - 1, "|"); // right border
        attroff(COLOR_PAIR(COLOR_WALLS) | A_BOLD);

        attron(COLOR_PAIR(COLOR_DEFAULT));
        for (int j = room->start.x + 1; j < room->start.x + room->width - 1; j++)
        {
            mvprintw(i, j, ".");
        }
        attroff(COLOR_PAIR(COLOR_DEFAULT));
    }

    // draw doors
    attron(COLOR_PAIR(COLOR_DOORS) | A_BOLD);
    for (int i = 0; i < room->doors_number; i++)
    {
        mvprintw(room->doors[i].position.y, room->doors[i].position.x, "+");
    }
    attroff(COLOR_PAIR(COLOR_DOORS) | A_BOLD);
}

void is_nextto_door(Room **rooms, int rooms_number, int y, int x)
{
    for (int i = 0; i < rooms_number; i++)
    {
        for (int j = 0; j < rooms[i]->doors_number; j++)
        {
            if (y == rooms[i]->doors[j].position.y && x == rooms[i]->doors[j].position.x)
            {
                if (!rooms[i]->doors[j].isConnected)
                {
                    rooms[i]->doors[j].isConnected = true;
                    connected_doors++;
                }
                return;
            }
        }
    }
}

void print_hallway(Room **rooms, int rooms_number, Position pos, Position start)
{
    if (pos.y == start.y && pos.x == start.x)
    {
        return;
    }

    attron(COLOR_PAIR(COLOR_HALLS));
    mvprintw(pos.y, pos.x, "#");
    attroff(COLOR_PAIR(COLOR_HALLS));

    int delta_x[4] = {1, 0, -1, 0};
    int delta_y[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++)
    {
        is_nextto_door(rooms, rooms_number, pos.y + delta_y[i], pos.x + delta_x[i]);
    }

    print_hallway(rooms, rooms_number, come_from[pos.y][pos.x], start);
}

bool is_room(Room **rooms, int rooms_number, int y, int x)
{
    for (int i = 0; i < rooms_number; i++)
    {
        if (y >= rooms[i]->start.y && y < rooms[i]->start.y + rooms[i]->height &&
            x >= rooms[i]->start.x && x < rooms[i]->start.x + rooms[i]->width)
        {
            // check if it's a door
            for (int j = 0; j < rooms[i]->doors_number; j++)
            {
                if (y == rooms[i]->doors[j].position.y && x == rooms[i]->doors[j].position.x)
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void find_path(Room **rooms, int rooms_number, Position start, Position end)
{
    Position frontier[40 * 130];
    int frontier_count = 0;
    int frontier_index = 0;

    frontier[frontier_count] = start;
    frontier_count++;

    Position currunt_position;

    while (frontier_index < frontier_count)
    {
        currunt_position = frontier[frontier_index];
        frontier_index++;

        if (currunt_position.y == end.y && currunt_position.x == end.x)
        {
            break;
        }

        // adding the upper neighbor
        if (currunt_position.y > 0 &&
            come_from[currunt_position.y - 1][currunt_position.x].y == -1 &&
            !is_room(rooms, rooms_number, currunt_position.y - 1, currunt_position.x))
        {
            frontier[frontier_count].y = currunt_position.y - 1;
            frontier[frontier_count].x = currunt_position.x;
            frontier_count++;

            come_from[currunt_position.y - 1][currunt_position.x] = currunt_position;
        }

        // adding the right neighbor
        if (currunt_position.x < MAP_WIDTH - 1 &&
            come_from[currunt_position.y][currunt_position.x + 1].y == -1 &&
            !is_room(rooms, rooms_number, currunt_position.y, currunt_position.x + 1))
        {
            frontier[frontier_count].y = currunt_position.y;
            frontier[frontier_count].x = currunt_position.x + 1;
            frontier_count++;

            come_from[currunt_position.y][currunt_position.x + 1] = currunt_position;
        }

        // adding the lower neighbor
        if (currunt_position.y < MAP_HEIGHT - 1 &&
            come_from[currunt_position.y + 1][currunt_position.x].y == -1 &&
            !is_room(rooms, rooms_number, currunt_position.y + 1, currunt_position.x))
        {
            frontier[frontier_count].y = currunt_position.y + 1;
            frontier[frontier_count].x = currunt_position.x;
            frontier_count++;

            come_from[currunt_position.y + 1][currunt_position.x] = currunt_position;
        }

        // adding the left neighbor
        if (currunt_position.x > 0 &&
            come_from[currunt_position.y][currunt_position.x - 1].y == -1 &&
            !is_room(rooms, rooms_number, currunt_position.y, currunt_position.x - 1))
        {
            frontier[frontier_count].y = currunt_position.y;
            frontier[frontier_count].x = currunt_position.x - 1;
            frontier_count++;

            come_from[currunt_position.y][currunt_position.x - 1] = currunt_position;
        }
    }

    print_hallway(rooms, rooms_number, come_from[end.y][end.x], start);
}

/* void import_path(Position start, Position currunt_position)
// {
//     if (currunt_position.x == start.x && currunt_position.y == start.y)
//     {
//         return;
//     }

//     map[currunt_position.y][currunt_position.x][0] = 1;

//     import_path(start, come_from[currunt_position.y][currunt_position.x]);
// } */

void connect_rooms(Room **rooms, int rooms_number)
{
    int total_doors_count = 0;
    for (int i = 0; i < rooms_number; i++)
    {
        total_doors_count += rooms[i]->doors_number;
    }

    // reset connected doors and their statuses
    connected_doors = 0;
    for (int i = 0; i < rooms_number; i++)
    {
        for (int j = 0; j < rooms[i]->doors_number; j++)
        {
            rooms[i]->doors[j].isConnected = false;
        }
    }

    while (connected_doors < total_doors_count)
    {
        int room_1 = rand() % rooms_number;
        int room_2;
        do
        {
            room_2 = rand() % rooms_number;
        } while (room_2 == room_1);

        int door_1 = rand() % rooms[room_1]->doors_number;
        int door_2 = rand() % rooms[room_2]->doors_number;

        for (int i = 0; i < MAP_HEIGHT; i++)
        {
            for (int j = 0; j < MAP_WIDTH; j++)
            {
                come_from[i][j].x = -1;
                come_from[i][j].y = -1;
            }
        }

        find_path(rooms, rooms_number, rooms[room_1]->doors[door_1].position, rooms[room_2]->doors[door_2].position);
    }
}

void map_setup()
{
    srand(time(NULL));

    // setting up rooms
    int rooms_number = 6 + rand() % 5;

    Room **rooms = (Room **)malloc(sizeof(Room *) * rooms_number);

    bool isFilled[10] = {0};

    for (int i = 0; i < rooms_number; i++)
    {
        int grid;
        while (1)
        {
            grid = rand() % 10;
            if (!isFilled[grid])
            {
                isFilled[grid] = 1;
                break;
            }
        }
        rooms[i] = generate_room(grid);
        draw_room(rooms[i]);
    }

    connect_rooms(rooms, rooms_number);

    for (int i = 0; i < rooms_number; i++)
    {
        free(rooms[i]);
    }
    free(rooms);
}