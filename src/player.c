#include "player.h"
#include "ui_utils.h"
#include <stdlib.h>

bool can_move(Player *player, int next_y, int next_x)
{
    if (next_y < 0 || next_y > MAP_HEIGHT ||
        next_x < 0 || next_x > MAP_WIDTH)
    {
        return false;
    }

    if (player->is_in_room)
    {
        for (int i = 0; i < player->currunt_room->doors_number; i++)
        {
            if (next_y == player->currunt_room->doors[i].position.y &&
                next_x == player->currunt_room->doors[i].position.x)
            {
                return true;
            }
        }

        if (next_y > player->currunt_room->start.y && next_y < player->currunt_room->start.y + player->currunt_room->height - 1 &&
            next_x > player->currunt_room->start.x && next_x < player->currunt_room->start.x + player->currunt_room->width - 1)
        {
            return true;
        }
    }

    if (map[next_y][next_x][0] == 1)
    {
        map[next_y][next_x][1] = 1;
        return true;
    }

    return false;
}

void move_player(Player *player)
{
    int ch = getch();

    if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == '8')
    {
        if (can_move(player, player->position.y - 1, player->position.x))
        {
            player->position.y--;
            return;
        }
    }

    if (ch == KEY_DOWN || ch == 'x' || ch == 'X' || ch == '2')
    {
        if (can_move(player, player->position.y + 1, player->position.x))
        {
            player->position.y++;
            return;
        }
    }

    if (ch == KEY_LEFT || ch == 'a' || ch == 'A' || ch == '4')
    {
        if (can_move(player, player->position.y, player->position.x - 1))
        {
            player->position.x--;
            return;
        }
    }

    if (ch == KEY_RIGHT || ch == 'd' || ch == 'D' || ch == '6')
    {
        if (can_move(player, player->position.y, player->position.x + 1))
        {
            player->position.x++;
            return;
        }
    }

    if (ch == 'q' || ch == 'Q' || ch == '7')
    {
        if (can_move(player, player->position.y - 1, player->position.x - 1))
        {
            player->position.y--;
            player->position.x--;
            return;
        }
    }
    if (ch == 'e' || ch == 'E' || ch == '9')
    {
        if (can_move(player, player->position.y - 1, player->position.x + 1))
        {
            player->position.y--;
            player->position.x++;
            return;
        }
    }

    if (ch == 'z' || ch == 'Z' || ch == '1')
    {
        if (can_move(player, player->position.y + 1, player->position.x - 1))
        {
            player->position.y++;
            player->position.x--;
            return;
        }
    }

    if (ch == 'c' || ch == 'C' || ch == '3')
    {
        if (can_move(player, player->position.y + 1, player->position.x + 1))
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
    newPlayer->is_in_room = true;

    return newPlayer;
}

void draw_next(Room **rooms, Player *player, int rooms_number)
{
    int delta_y[4] = {-1, 0, 1, 0};
    int delta_x[4] = {0, 1, 0, -1};

    attron(COLOR_PAIR(COLOR_HALLS));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (map[player->position.y + delta_y[i]][player->position.x + delta_x[j]][0])
            {
                map[player->position.y + delta_y[i]][player->position.x + delta_x[j]][1] = 1;
                mvprintw(player->position.y + delta_y[i], player->position.x + delta_x[j], "#");
            }
        }
    }
    attroff(COLOR_PAIR(COLOR_HALLS));

    attron(COLOR_PAIR(COLOR_DOORS));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < rooms_number; k++)
            {
                for (int h = 0; h < rooms[k]->doors_number; h++)
                {
                    if (player->position.y + delta_y[i] == rooms[k]->doors[h].position.y &&
                        player->position.x + delta_x[j] == rooms[k]->doors[h].position.x)
                    {
                        mvprintw(player->position.y + delta_y[i], player->position.x + delta_x[j], "+");
                    }
                }
            }
        }
    }
    attroff(COLOR_PAIR(COLOR_DOORS));
}

void player_update(Player *player)
{
    mvprintw(player->position.y, player->position.x, "@");
    move_player(player);
}