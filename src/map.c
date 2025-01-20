#include "map.h"
#include "ui_utils.h"
#include "global_defines.h"
#include <time.h>
#include <stdlib.h>

Room *generate_room(int grid)
{
    Room *newRoom = (Room *)malloc(sizeof(Room));

    switch (grid)
    {
    case 0:
        newRoom->start.x = 1;
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
        newRoom->start.x = 1;
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

    newRoom->doors_number = 1 + rand() % 4; // min: 1, max: 4
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
            newRoom->doors[i].x = newRoom->start.x + 1 + rand() % (newRoom->width - 2);
            newRoom->doors[i].y = newRoom->start.y;
        }
        else if (side == 1) // right
        {
            newRoom->doors[i].x = newRoom->start.x + newRoom->width - 1;
            newRoom->doors[i].y = newRoom->start.y + 1 + rand() % (newRoom->height - 2);
        }
        else if (side == 2) // bottom
        {
            newRoom->doors[i].x = newRoom->start.x + 1 + rand() % (newRoom->width - 2);
            newRoom->doors[i].y = newRoom->start.y + newRoom->height - 1;
        }
        else if (side == 3) // left
        {
            newRoom->doors[i].x = newRoom->start.x;
            newRoom->doors[i].y = newRoom->start.y + 1 + rand() % (newRoom->height - 2);
        }
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
        mvprintw(room->doors[i].y, room->doors[i].x, "+");
    }
    attroff(COLOR_PAIR(COLOR_DOORS) | A_BOLD);
}

void rooms_setup()
{
    srand(time(NULL));
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

    for (int i = 0; i < rooms_number; i++)
    {
        free(rooms[i]);
    }
    free(rooms);
}