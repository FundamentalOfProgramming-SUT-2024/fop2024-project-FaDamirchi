#include "player.h"
#include "global_defines.h"

bool can_move(Room **rooms, int rooms_number, Player *player, int next_y, int next_x)
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
    else
    {
        for (int i = 0; i < rooms_number; i++)
        {
            for (int j = 0; j < rooms[i]->doors_number; j++)
            {
                if (next_y == rooms[i]->doors[j].position.y &&
                    next_x == rooms[i]->doors[j].position.x)
                {
                    player->currunt_room = rooms[i];
                    player->currunt_room->isSeen = true;
                    player->is_in_room = true;
                    return true;
                }
            }
        }
    }

    if (map[next_y][next_x][0] == 1)
    {
        map[next_y][next_x][1] = 1;
        return true;
    }

    return false;
}

void move_player(Room **rooms, int rooms_number, Player *player)
{
    int ch = getch();

    if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == '8')
    {
        if (can_move(rooms, rooms_number, player, player->position.y - 1, player->position.x))
        {
            player->position.y--;
            return;
        }
    }

    if (ch == KEY_DOWN || ch == 'x' || ch == 'X' || ch == '2')
    {
        if (can_move(rooms, rooms_number, player, player->position.y + 1, player->position.x))
        {
            player->position.y++;
            return;
        }
    }

    if (ch == KEY_LEFT || ch == 'a' || ch == 'A' || ch == '4')
    {
        if (can_move(rooms, rooms_number, player, player->position.y, player->position.x - 1))
        {
            player->position.x--;
            return;
        }
    }

    if (ch == KEY_RIGHT || ch == 'd' || ch == 'D' || ch == '6')
    {
        if (can_move(rooms, rooms_number, player, player->position.y, player->position.x + 1))
        {
            player->position.x++;
            return;
        }
    }

    if (ch == 'q' || ch == 'Q' || ch == '7')
    {
        if (can_move(rooms, rooms_number, player, player->position.y - 1, player->position.x - 1))
        {
            player->position.y--;
            player->position.x--;
            return;
        }
    }
    if (ch == 'e' || ch == 'E' || ch == '9')
    {
        if (can_move(rooms, rooms_number, player, player->position.y - 1, player->position.x + 1))
        {
            player->position.y--;
            player->position.x++;
            return;
        }
    }

    if (ch == 'z' || ch == 'Z' || ch == '1')
    {
        if (can_move(rooms, rooms_number, player, player->position.y + 1, player->position.x - 1))
        {
            player->position.y++;
            player->position.x--;
            return;
        }
    }

    if (ch == 'c' || ch == 'C' || ch == '3')
    {
        if (can_move(rooms, rooms_number, player, player->position.y + 1, player->position.x + 1))
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

void show_next(Room **rooms, Player *player, int rooms_number)
{
    int delta_y[4] = {-1, 0, 1, 0};
    int delta_x[4] = {0, 1, 0, -1};

    // show near hallways
    attron(COLOR_PAIR(COLOR_UNSEEN));
    for (int i = 0; i < 4; i++)
    {
        if (map[player->position.y + delta_y[i]][player->position.x + delta_x[i]][0] &&
            !map[player->position.y + delta_y[i]][player->position.x + delta_x[i]][1])
        {
            mvprintw(player->position.y + delta_y[i], player->position.x + delta_x[i], "#");
        }
    }
    attroff(COLOR_PAIR(COLOR_UNSEEN));

    // show near doors
    attron(COLOR_PAIR(COLOR_DOORS));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < rooms_number; j++)
        {
            for (int k = 0; k < rooms[j]->doors_number; k++)
            {
                if (player->position.y + delta_y[i] == rooms[j]->doors[k].position.y &&
                    player->position.x + delta_x[i] == rooms[j]->doors[k].position.x)
                {
                    mvprintw(player->position.y + delta_y[i], player->position.x + delta_x[i], "+");
                }
            }
        }
    }
    attroff(COLOR_PAIR(COLOR_DOORS));
}

void player_update(Room **rooms, int rooms_number, Player *player)
{
    mvprintw(player->position.y, player->position.x, "@");
    move_player(rooms, rooms_number, player);

    if (player->is_in_room)
    {
        if (player->position.y < player->currunt_room->start.y ||
            player->position.y > player->currunt_room->start.y + player->currunt_room->height - 1 ||
            player->position.x < player->currunt_room->start.x ||
            player->position.x > player->currunt_room->start.x + player->currunt_room->width - 1)
        {
            player->currunt_room = NULL;
            player->is_in_room = false;
        }
        
    }
    
}