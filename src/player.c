#include "player.h"
#include "ui_utils.h"
#include <stdlib.h>

void move_player(Player *player)
{
    int ch = getch();

    if (ch == KEY_UP || ch == 'w' || ch == 'W')
    {
        if (1)
        {
            player->position.y--;
            return;
        }
        
    }

    if (ch == KEY_DOWN || ch == 'x' || ch == 'X')
    {
        if (1)
        {
            player->position.y++;
            return;
        }
        
    }

    if (ch == KEY_LEFT || ch == 'a' || ch == 'A')
    {
        if (1)
        {
            player->position.x--;
            return;
        }
        
    }

    if (ch == KEY_RIGHT || ch == 'd' || ch == 'D')
    {
        if (1)
        {
            player->position.x++;
            return;
        }
        
    }

    if (ch == 'q' || ch == 'Q')
    {
        if (1)
        {
            player->position.y--;
            player->position.x--;
            return;
        }
        
    }
    if (ch == 'e' || ch == 'E')
    {
        if (1)
        {
            player->position.y--;
            player->position.x++;
            return;
        }
        
    }

    if (ch == 'z' || ch == 'Z')
    {
        if (1)
        {
            player->position.y++;
            player->position.x--;
            return;
        }
        
    }

    if (ch == 'c' || ch == 'C')
    {
        if (1)
        {
            player->position.y++;
            player->position.x++;
            return;
        }
        
    }
}

Player *player_setup(Room **rooms, int rooms_number)
{
    Player *newPlayer = (Player *)malloc(sizeof(Player));

    int initial_room = rand() % rooms_number;
    while (rooms[initial_room]->has_stair) // the initial room shouldn't have stairs
    {
        initial_room = rand() % rooms_number;
    }

    newPlayer->position.y = rooms[initial_room]->start.y + 1 + rand() % (rooms[initial_room]->height - 2);
    newPlayer->position.x = rooms[initial_room]->start.x + 1 + rand() % (rooms[initial_room]->width - 2);
    
    rooms[initial_room]->isSeen = true;

    newPlayer->currunt_room = rooms[initial_room];

    return newPlayer;
}

void player_update(Player *player)
{
    mvprintw(player->position.y, player->position.x, "@");
    move_player(player);
}