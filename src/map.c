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
        newRoom->start.x = 0;
        newRoom->start.y = 0;
        break;
    case 1:
        newRoom->start.x = 24;
        newRoom->start.y = 0;
        break;
    case 2:
        newRoom->start.x = 48;
        newRoom->start.y = 0;
        break;
    case 3:
        newRoom->start.x = 72;
        newRoom->start.y = 0;
        break;
    case 4:
        newRoom->start.x = 96;
        newRoom->start.y = 0;
        break;
    case 5:
        newRoom->start.x = 0;
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

    newRoom->width = 4 + rand() % 6; // min: 4, max: 9
    newRoom->height = 4 + rand() % 10; // min: 4, max: 13

    // generate random starting points
    newRoom->start.x += rand() % (10 - newRoom->width);
    newRoom->start.y += rand() % (14 - newRoom->height);

    return newRoom;
}

void draw_room(Room *room)
{
    // draw top and bottom
    attron(COLOR_PAIR(COLOR_BORDER) | A_BOLD);
    for (int i = room->start.x; i < room->start.x + room->width; i++)
    {
        mvprintw(room->start.y, i, "-");                    // top border
        mvprintw(room->start.y + room->height - 1, i, "-"); // bottom border
    }
    attroff(COLOR_PAIR(COLOR_BORDER) | A_BOLD);

    // draw floor and side walls
    for (int i = room->start.y + 1; i < room->start.y + room->height - 1; i++)
    {
        attron(COLOR_PAIR(COLOR_BORDER) | A_BOLD);
        mvprintw(i, room->start.x, "|");                   // left border
        mvprintw(i, room->start.x + room->width - 1, "|"); // right border
        attroff(COLOR_PAIR(COLOR_BORDER) | A_BOLD);

        attron(COLOR_PAIR(COLOR_DEFAULT) | A_BOLD);
        for (int j = room->start.x + 1; j < room->start.x + room->width - 1; j++)
        {
            mvprintw(i, j, ".");
        }
        attroff(COLOR_PAIR(COLOR_DEFAULT) | A_BOLD);
    }
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