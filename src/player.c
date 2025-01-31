#include "player.h"
#include "map.h"
#include "global_defines.h"

bool can_move(Room **rooms, int rooms_number, bool ***map, int next_y, int next_x)
{
    if (next_y < 0 || next_y > MAP_HEIGHT ||
        next_x < 0 || next_x > MAP_WIDTH)
    {
        return false;
    }

    for (int i = 0; i < rooms_number; i++)
    {
        if (next_y > rooms[i]->start.y && next_y < rooms[i]->start.y + rooms[i]->height - 1 &&
            next_x > rooms[i]->start.x && next_x < rooms[i]->start.x + rooms[i]->width - 1)
        {
            return true;
        }

        for (int j = 0; j < rooms[i]->doors_number; j++)
        {
            if (next_y == rooms[i]->doors[j].position.y &&
                next_x == rooms[i]->doors[j].position.x)
            {
                rooms[i]->isSeen = true;
                return true;
            }
        }

        if ((next_y >= rooms[i]->start.y && next_y <= rooms[i]->start.y + rooms[i]->height - 1 && next_x == rooms[i]->start.x) ||
            (next_y >= rooms[i]->start.y && next_y <= rooms[i]->start.y + rooms[i]->height - 1 && next_x == rooms[i]->start.x + rooms[i]->width - 1) ||
            (next_x >= rooms[i]->start.x && next_x <= rooms[i]->start.x + rooms[i]->width - 1 && next_y == rooms[i]->start.y) ||
            (next_x >= rooms[i]->start.x && next_x <= rooms[i]->start.x + rooms[i]->width - 1 && next_y == rooms[i]->start.y + rooms[i]->height - 1))
        {
            return false;
        }
    }

    if (map[next_y][next_x][0])
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
        if (can_move(rooms, rooms_number, player->currunt_floor->map, player->position.y - 1, player->position.x))
        {
            player->position.y--;
            return;
        }
    }

    if (ch == KEY_DOWN || ch == 'x' || ch == 'X' || ch == '2')
    {
        if (can_move(rooms, rooms_number, player->currunt_floor->map, player->position.y + 1, player->position.x))
        {
            player->position.y++;
            return;
        }
    }

    if (ch == KEY_LEFT || ch == 'a' || ch == 'A' || ch == '4')
    {
        if (can_move(rooms, rooms_number, player->currunt_floor->map, player->position.y, player->position.x - 1))
        {
            player->position.x--;
            return;
        }
    }

    if (ch == KEY_RIGHT || ch == 'd' || ch == 'D' || ch == '6')
    {
        if (can_move(rooms, rooms_number, player->currunt_floor->map, player->position.y, player->position.x + 1))
        {
            player->position.x++;
            return;
        }
    }

    if (ch == 'q' || ch == 'Q' || ch == '7')
    {
        if (can_move(rooms, rooms_number, player->currunt_floor->map, player->position.y - 1, player->position.x - 1))
        {
            player->position.y--;
            player->position.x--;
            return;
        }
    }
    if (ch == 'e' || ch == 'E' || ch == '9')
    {
        if (can_move(rooms, rooms_number, player->currunt_floor->map, player->position.y - 1, player->position.x + 1))
        {
            player->position.y--;
            player->position.x++;
            return;
        }
    }

    if (ch == 'z' || ch == 'Z' || ch == '1')
    {
        if (can_move(rooms, rooms_number, player->currunt_floor->map, player->position.y + 1, player->position.x - 1))
        {
            player->position.y++;
            player->position.x--;
            return;
        }
    }

    if (ch == 'c' || ch == 'C' || ch == '3')
    {
        if (can_move(rooms, rooms_number, player->currunt_floor->map, player->position.y + 1, player->position.x + 1))
        {
            player->position.y++;
            player->position.x++;
            return;
        }
    }
}

Player *player_setup(Floor *floor, Room **rooms, int rooms_number)
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
    newPlayer->currunt_floor = floor;

    return newPlayer;
}

void player_update(Room **rooms, int rooms_number, Player *player, int color)
{
    // displaying the player with the chosen color
    switch (color)
    {
    case 1:
        attron(COLOR_PAIR(COLOR_PLAYER_WHITE));
        mvprintw(player->position.y, player->position.x, "@");
        attroff(COLOR_PAIR(COLOR_PLAYER_WHITE));
        break;
    case 2:
        attron(COLOR_PAIR(COLOR_PLAYER_PURPULE));
        mvprintw(player->position.y, player->position.x, "@");
        attroff(COLOR_PAIR(COLOR_PLAYER_PURPULE));
        break;
    case 3:
        attron(COLOR_PAIR(COLOR_PLAYER_BLUE));
        mvprintw(player->position.y, player->position.x, "@");
        attroff(COLOR_PAIR(COLOR_PLAYER_BLUE));
        break;
    default:
        break;
    }

    use_windows(player, rooms, rooms_number);
    move_player(rooms, rooms_number, player);
}