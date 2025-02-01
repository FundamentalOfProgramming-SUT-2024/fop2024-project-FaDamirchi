#include "player.h"
#include "map.h"
#include "global_defines.h"

void show_message(char *message)
{
    move(0, 0);
    clrtoeol();
    mvprintw(0, 0, "%s", message);
}

bool can_move(Player *player, Room **rooms, int rooms_number, bool ***map, int next_y, int next_x)
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
                if (!rooms[i]->isSeen)
                {
                    strcpy(player->message, "You discovered a new room!");
                    rooms[i]->isSeen = true;
                }

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

void move_player(int ch, Floor **floors, Room **rooms, int rooms_number, Player *player)
{
    if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == '8')
    {
        if (can_move(player, rooms, rooms_number,
                     floors[player->current_floor]->map,
                     player->position.y - 1,
                     player->position.x))
        {
            player->position.y--;
            player->passed_blockes++;
            return;
        }
    }

    if (ch == KEY_DOWN || ch == 'x' || ch == 'X' || ch == '2')
    {
        if (can_move(player, rooms, rooms_number,
                     floors[player->current_floor]->map,
                     player->position.y + 1,
                     player->position.x))
        {
            player->position.y++;
            player->passed_blockes++;
            return;
        }
    }

    if (ch == KEY_LEFT || ch == 'a' || ch == 'A' || ch == '4')
    {
        if (can_move(player, rooms, rooms_number,
                     floors[player->current_floor]->map,
                     player->position.y,
                     player->position.x - 1))
        {
            player->position.x--;
            player->passed_blockes++;
            return;
        }
    }

    if (ch == KEY_RIGHT || ch == 'd' || ch == 'D' || ch == '6')
    {
        if (can_move(player, rooms, rooms_number,
                     floors[player->current_floor]->map,
                     player->position.y,
                     player->position.x + 1))
        {
            player->position.x++;
            player->passed_blockes++;
            return;
        }
    }

    if (ch == 'q' || ch == 'Q' || ch == '7')
    {
        if (can_move(player, rooms, rooms_number,
                     floors[player->current_floor]->map,
                     player->position.y - 1,
                     player->position.x - 1))
        {
            player->position.y--;
            player->position.x--;
            player->passed_blockes++;
            return;
        }
    }
    if (ch == 'e' || ch == 'E' || ch == '9')
    {
        if (can_move(player, rooms, rooms_number,
                     floors[player->current_floor]->map,
                     player->position.y - 1,
                     player->position.x + 1))
        {
            player->position.y--;
            player->position.x++;
            player->passed_blockes++;
            return;
        }
    }

    if (ch == 'z' || ch == 'Z' || ch == '1')
    {
        if (can_move(player, rooms, rooms_number,
                     floors[player->current_floor]->map,
                     player->position.y + 1,
                     player->position.x - 1))
        {
            player->position.y++;
            player->position.x--;
            player->passed_blockes++;
            return;
        }
    }

    if (ch == 'c' || ch == 'C' || ch == '3')
    {
        if (can_move(player, rooms, rooms_number,
                     floors[player->current_floor]->map,
                     player->position.y + 1,
                     player->position.x + 1))
        {
            player->position.y++;
            player->position.x++;
            player->passed_blockes++;
            return;
        }
    }
}

void fast_move(Floor **floors, Room **rooms, int rooms_number, Player *player)
{
    int ch = getch();

    if (ch == 'f' || ch == 'F')
    {
        return;
    }

    if (ch == KEY_UP || ch == 'w' || ch == 'W' || ch == '8')
    {
        int counter = 0;
        while (can_move(player, rooms, rooms_number,
                        floors[player->current_floor]->map,
                        player->position.y - counter,
                        player->position.x))
        {
            counter++;
        }

        player->position.y -= (counter - 1);
        player->passed_blockes += (counter - 1);
        return;
    }

    if (ch == KEY_DOWN || ch == 'x' || ch == 'X' || ch == '2')
    {
        int counter = 0;
        while (can_move(player, rooms, rooms_number,
                        floors[player->current_floor]->map,
                        player->position.y + counter,
                        player->position.x))
        {
            counter++;
        }

        player->position.y += (counter - 1);
        player->passed_blockes += (counter - 1);
        return;
    }

    if (ch == KEY_LEFT || ch == 'a' || ch == 'A' || ch == '4')
    {
        int counter = 0;
        while (can_move(player, rooms, rooms_number,
                        floors[player->current_floor]->map,
                        player->position.y,
                        player->position.x - counter))
        {
            counter++;
        }

        player->position.x -= (counter - 1);
        player->passed_blockes += (counter - 1);
        return;
    }

    if (ch == KEY_RIGHT || ch == 'd' || ch == 'D' || ch == '6')
    {
        int counter = 0;
        while (can_move(player, rooms, rooms_number,
                        floors[player->current_floor]->map,
                        player->position.y,
                        player->position.x + counter))
        {
            counter++;
        }

        player->position.x += (counter - 1);
        player->passed_blockes += (counter - 1);
        return;
    }

    if (ch == 'q' || ch == 'Q' || ch == '7')
    {
        int counter = 0;
        while (can_move(player, rooms, rooms_number,
                        floors[player->current_floor]->map,
                        player->position.y - counter,
                        player->position.x - counter))
        {
            counter++;
        }

        player->position.y -= (counter - 1);
        player->position.x -= (counter - 1);
        player->passed_blockes += (counter - 1);
        return;
    }
    if (ch == 'e' || ch == 'E' || ch == '9')
    {
        int counter = 0;
        while (can_move(player, rooms, rooms_number,
                        floors[player->current_floor]->map,
                        player->position.y - counter,
                        player->position.x + counter))
        {
            counter++;
        }

        player->position.y -= (counter - 1);
        player->position.x += (counter - 1);
        player->passed_blockes += (counter - 1);
        return;
    }

    if (ch == 'z' || ch == 'Z' || ch == '1')
    {
        int counter = 0;
        while (can_move(player, rooms, rooms_number,
                        floors[player->current_floor]->map,
                        player->position.y + counter,
                        player->position.x - counter))
        {
            counter++;
        }

        player->position.y += (counter - 1);
        player->position.x -= (counter - 1);
        player->passed_blockes += (counter - 1);
        return;
    }

    if (ch == 'c' || ch == 'C' || ch == '3')
    {
        int counter = 0;
        while (can_move(player, rooms, rooms_number,
                        floors[player->current_floor]->map,
                        player->position.y + counter,
                        player->position.x + counter))
        {
            counter++;
        }

        player->position.y += (counter - 1);
        player->position.x += (counter - 1);
        player->passed_blockes += (counter - 1);
        return;
    }
}

Player *player_setup(Room **rooms, int rooms_number)
{
    Player *newPlayer = (Player *)malloc(sizeof(Player));

    int initial_room = rand() % rooms_number;

    // the first room shouldn't have stairs
    while (rooms[initial_room]->stairs.has_stairs)
    {
        initial_room = rand() % rooms_number;
    }

    newPlayer->position.y = rooms[initial_room]->start.y + 1 + rand() % (rooms[initial_room]->height - 2);
    newPlayer->position.x = rooms[initial_room]->start.x + 1 + rand() % (rooms[initial_room]->width - 2);

    // other properties
    rooms[initial_room]->isSeen = true;
    newPlayer->current_floor = 0;
    newPlayer->gold = 0;
    newPlayer->health = 100;
    newPlayer->passed_blockes = 0;

    return newPlayer;
}

void handle_player_actions(Floor **floors, Room **rooms, Player *player)
{
    Room *current_room = NULL;

    for (int i = 0; i < floors[player->current_floor]->rooms_number; i++)
    {
        if (player->position.y > rooms[i]->start.y && player->position.y < rooms[i]->start.y + rooms[i]->height - 1 &&
            player->position.x > rooms[i]->start.x && player->position.x < rooms[i]->start.x + rooms[i]->width - 1)
        {
            current_room = rooms[i];
        }
    }

    if (current_room == NULL)
    {
        return;
    }

    // check for gold
    if (current_room->gold_number != 0)
    {
        for (int i = 0; i < current_room->gold_number; i++)
        {
            if (current_room->gold_position[i].y == player->position.y && current_room->gold_position[i].x == player->position.x)
            {
                strcpy(player->message, "You collected a gold!");
                show_message(player->message);

                player->gold++;
                current_room->gold_position[i].y = -1;
                current_room->gold_position[i].x = -1;
                return;
            }
        }
    }

    // check for stairs
    if (current_room->stairs.has_stairs &&
        current_room->stairs.previous_floor == player->current_floor &&
        player->position.y == current_room->stairs.position.y && player->position.x == current_room->stairs.position.x)
    {
        strcpy(player->message, "Do you want to go to the next floor? (y / n)");
        show_message(player->message);

        int ch = getch();
        if (ch == 'y' || ch == 'Y')
        {
            player->current_floor++;
            strcpy(player->message, "You moved to the next floor!");
            show_message(player->message);
            return;
        }
        else
        {
            return;
        }
    }
    else if (current_room->stairs.has_stairs &&
             current_room->stairs.previous_floor != player->current_floor &&
             player->position.y == current_room->stairs.position.y && player->position.x == current_room->stairs.position.x)
    {
        strcpy(player->message, "Do you want to go to the previous floor? (y / n)");
        show_message(player->message);

        int ch = getch();
        if (ch == 'y' || ch == 'Y')
        {
            player->current_floor--;
            strcpy(player->message, "You moved to the previous floor!");
            show_message(player->message);
            return;
        }
        else
        {
            return;
        }
    }

    // check for foods
    for (int i = 0; i < current_room->foods_number; i++)
    {
        if (current_room->foods[i].position.y == player->position.y && current_room->foods[i].position.x == player->position.x)
        {
            strcpy(player->message, "Do you want to pick up this food? (y / n)");
            show_message(player->message);

            int ch = getch();
            if (ch == 'y' || ch == 'Y')
            {
                current_room->foods[i].position.y = -1;
                current_room->foods[i].position.x = -1;
                strcpy(player->message, "You picked up the food!");
                show_message(player->message);
                return;
            }
            else
            {
                return;
            }
        }
    }
}

void show_status(Player *player)
{
    mvprintw(30, 0, "Current floor: %d", player->current_floor + 1);
    mvprintw(30, 25, "Health: %d", player->health);
    mvprintw(30, 50, "Gold: %d", player->gold);
}

void player_update(Floor **floors, Room **rooms, int rooms_number, Player *player, int color)
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

    handle_player_actions(floors, rooms, player);
    use_windows(player, rooms, rooms_number);

    int ch = getch();
    player->message[0] = '\0'; // update the message

    // check for map overview
    if (ch == 'm' || ch == 'M')
    {
        strcpy(player->message, "Showing the whole map. (press M key again to cancel)");
        show_message(player->message);

        draw_all_map(rooms, rooms_number, floors[player->current_floor]->map);

        int ans = getch();
        while (!(ans == 'm' || ans == 'M'))
        {
            ans = getch();
        }
        player->message[0] = '\0';
    }

    // check for fast mode
    else if (ch == 'f' || ch == 'F')
    {
        strcpy(player->message, "Fast mode activated. Choose a direction. (press F key again to cancel)");
        show_message(player->message);

        fast_move(floors, rooms, rooms_number, player);
        player->message[0] = '\0';
    }

    // handle the character moving
    else
    {
        move_player(ch, floors, rooms, rooms_number, player);

        // reduce health by 1 after moving 10 blocks
        while (player->passed_blockes > 10)
        {
            player->passed_blockes -= 10;
            player->health--;
        }
    }
}
