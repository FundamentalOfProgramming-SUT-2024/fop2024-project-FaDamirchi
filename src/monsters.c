#include "monsters.h"
#include "global_defines.h"

void deamon_setup(Room *room, Monster *monster)
{
    monster->moving_type = TIRED;
    monster->health = 5;
    monster->damage = 5;

    monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
    monster->position.x = room->start.x + 1 + rand() % (room->width - 2);

    // check if the chosen position is reserved before
    for (int k = 0; k < room->reserved_number; k++)
    {
        while (monster->position.y == room->reserved_poitions[k].y &&
               monster->position.x == room->reserved_poitions[k].x)
        {
            monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
            monster->position.x = room->start.x + 1 + rand() % (room->width - 2);
        }
    }

    // adding the chosen position to reserved ones
    room->reserved_poitions[room->reserved_number].y = monster->position.y;
    room->reserved_poitions[room->reserved_number].x = monster->position.x;
    room->reserved_number++;
}

void fire_setup(Room *room, Monster *monster)
{
    monster->moving_type = TIRED;
    monster->health = 10;
    monster->damage = 7;

    monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
    monster->position.x = room->start.x + 1 + rand() % (room->width - 2);

    // check if the chosen position is reserved before
    for (int k = 0; k < room->reserved_number; k++)
    {
        while (monster->position.y == room->reserved_poitions[k].y &&
               monster->position.x == room->reserved_poitions[k].x)
        {
            monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
            monster->position.x = room->start.x + 1 + rand() % (room->width - 2);
        }
    }

    // adding the chosen position to reserved ones
    room->reserved_poitions[room->reserved_number].y = monster->position.y;
    room->reserved_poitions[room->reserved_number].x = monster->position.x;
    room->reserved_number++;
}

void giant_setup(Room *room, Monster *monster)
{
    monster->moving_type = TIRED;
    monster->health = 15;
    monster->damage = 10;

    monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
    monster->position.x = room->start.x + 1 + rand() % (room->width - 2);

    // check if the chosen position is reserved before
    for (int k = 0; k < room->reserved_number; k++)
    {
        while (monster->position.y == room->reserved_poitions[k].y &&
               monster->position.x == room->reserved_poitions[k].x)
        {
            monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
            monster->position.x = room->start.x + 1 + rand() % (room->width - 2);
        }
    }

    // adding the chosen position to reserved ones
    room->reserved_poitions[room->reserved_number].y = monster->position.y;
    room->reserved_poitions[room->reserved_number].x = monster->position.x;
    room->reserved_number++;
}

void snake_setup(Room *room, Monster *monster)
{
    monster->moving_type = ALWAYS;
    monster->health = 20;
    monster->damage = 15;

    monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
    monster->position.x = room->start.x + 1 + rand() % (room->width - 2);

    // check if the chosen position is reserved before
    for (int k = 0; k < room->reserved_number; k++)
    {
        while (monster->position.y == room->reserved_poitions[k].y &&
               monster->position.x == room->reserved_poitions[k].x)
        {
            monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
            monster->position.x = room->start.x + 1 + rand() % (room->width - 2);
        }
    }

    // adding the chosen position to reserved ones
    room->reserved_poitions[room->reserved_number].y = monster->position.y;
    room->reserved_poitions[room->reserved_number].x = monster->position.x;
    room->reserved_number++;
}

void undeed_setup(Room *room, Monster *monster)
{
    monster->moving_type = TIRED;
    monster->health = 30;
    monster->damage = 20;

    monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
    monster->position.x = room->start.x + 1 + rand() % (room->width - 2);

    // check if the chosen position is reserved before
    for (int k = 0; k < room->reserved_number; k++)
    {
        while (monster->position.y == room->reserved_poitions[k].y &&
               monster->position.x == room->reserved_poitions[k].x)
        {
            monster->position.y = room->start.y + 1 + rand() % (room->height - 2);
            monster->position.x = room->start.x + 1 + rand() % (room->width - 2);
        }
    }

    // adding the chosen position to reserved ones
    room->reserved_poitions[room->reserved_number].y = monster->position.y;
    room->reserved_poitions[room->reserved_number].x = monster->position.x;
    room->reserved_number++;
}

void monster_setup(Room *room, int level)
{
    if (room->type == ROOM_TREASURE)
    {
        return;
    }
    
    room->monsters_number = level + rand() % 2 - 1;
    room->monsters = (Monster **)malloc(sizeof(Monster *) * room->monsters_number);

    for (int i = 0; i < room->monsters_number; i++)
    {
        room->monsters[i] = (Monster *)malloc(sizeof(Monster) * room->monsters_number);

        room->monsters[i]->monster_type = level + rand() % 3;

        if (room->monsters[i]->monster_type == DEAMON)
        {
            deamon_setup(room, room->monsters[i]);
        }
        else if (room->monsters[i]->monster_type == FIRE)
        {
            fire_setup(room, room->monsters[i]);
        }
        else if (room->monsters[i]->monster_type == GIANT)
        {
            giant_setup(room, room->monsters[i]);
        }
        else if (room->monsters[i]->monster_type == SNAKE)
        {
            snake_setup(room, room->monsters[i]);
        }
        else if (room->monsters[i]->monster_type == UNDEED)
        {
            undeed_setup(room, room->monsters[i]);
        }
    }
}