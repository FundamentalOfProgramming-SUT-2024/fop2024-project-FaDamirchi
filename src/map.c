#include "map.h"
#include "player.h"
#include "ui_utils.h"
#include "global_defines.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

Position come_from[40][130];

int connected_doors = 0;

Room *generate_room(int grid)
{
    Room *newRoom = (Room *)malloc(sizeof(Room));

    switch (grid)
    {
    case 0:
        newRoom->start.x = 3;
        newRoom->start.y = 2;
        break;
    case 1:
        newRoom->start.x = 24;
        newRoom->start.y = 2;
        break;
    case 2:
        newRoom->start.x = 48;
        newRoom->start.y = 2;
        break;
    case 3:
        newRoom->start.x = 72;
        newRoom->start.y = 2;
        break;
    case 4:
        newRoom->start.x = 96;
        newRoom->start.y = 2;
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
        if (side == UP)
        {
            newRoom->doors[i].position.x = newRoom->start.x + 1 + rand() % (newRoom->width - 2);
            newRoom->doors[i].position.y = newRoom->start.y;
        }
        else if (side == RIGHT)
        {
            newRoom->doors[i].position.x = newRoom->start.x + newRoom->width - 1;
            newRoom->doors[i].position.y = newRoom->start.y + 1 + rand() % (newRoom->height - 2);
        }
        else if (side == DOWN)
        {
            newRoom->doors[i].position.x = newRoom->start.x + 1 + rand() % (newRoom->width - 2);
            newRoom->doors[i].position.y = newRoom->start.y + newRoom->height - 1;
        }
        else if (side == LEFT)
        {
            newRoom->doors[i].position.x = newRoom->start.x;
            newRoom->doors[i].position.y = newRoom->start.y + 1 + rand() % (newRoom->height - 2);
        }

        newRoom->doors[i].isConnected = false;
    }

    // generating windows
    newRoom->windows_number = rand() % 3;
    bool hasWindow[4] = {0};

    for (int i = 0; i < newRoom->windows_number; i++)
    {
        newRoom->windows[i].side = rand() % 4;

        if (grid >= 1 && grid <= 3)
        {
            while (newRoom->windows[i].side == UP || hasWindow[newRoom->windows[i].side])
            {
                newRoom->windows[i].side = rand() % 4;
            }
        }

        if (grid >= 4 && grid <= 8)
        {
            while (newRoom->windows[i].side == DOWN || hasWindow[newRoom->windows[i].side])
            {
                newRoom->windows[i].side = rand() % 4;
            }
        }

        if (grid == 0)
        {
            while ((newRoom->windows[i].side == UP || newRoom->windows[i].side == LEFT) ||
                   hasWindow[newRoom->windows[i].side])
            {
                newRoom->windows[i].side = rand() % 4;
            }
        }

        if (grid == 4)
        {
            while ((newRoom->windows[i].side == UP || newRoom->windows[i].side == RIGHT) ||
                   hasWindow[newRoom->windows[i].side])
            {
                newRoom->windows[i].side = rand() % 4;
            }
        }

        if (grid == 5)
        {
            while ((newRoom->windows[i].side == DOWN || newRoom->windows[i].side == LEFT) ||
                   hasWindow[newRoom->windows[i].side])
            {
                newRoom->windows[i].side = rand() % 4;
            }
        }

        if (grid == 9)
        {
            while ((newRoom->windows[i].side == DOWN || newRoom->windows[i].side == RIGHT) ||
                   hasWindow[newRoom->windows[i].side])
            {
                newRoom->windows[i].side = rand() % 4;
            }
        }

        hasWindow[newRoom->windows[i].side] = 1;

        // placing the windows
        bool valid_position = false;
        while (!valid_position)
        {
            if (newRoom->windows[i].side == UP)
            {
                newRoom->windows[i].position.x = newRoom->start.x + 1 + rand() % (newRoom->width - 2);
                newRoom->windows[i].position.y = newRoom->start.y;
            }
            else if (newRoom->windows[i].side == RIGHT)
            {
                newRoom->windows[i].position.x = newRoom->start.x + newRoom->width - 1;
                newRoom->windows[i].position.y = newRoom->start.y + 1 + rand() % (newRoom->height - 2);
            }
            else if (newRoom->windows[i].side == DOWN)
            {
                newRoom->windows[i].position.x = newRoom->start.x + 1 + rand() % (newRoom->width - 2);
                newRoom->windows[i].position.y = newRoom->start.y + newRoom->height - 1;
            }
            else if (newRoom->windows[i].side == LEFT)
            {
                newRoom->windows[i].position.x = newRoom->start.x;
                newRoom->windows[i].position.y = newRoom->start.y + 1 + rand() % (newRoom->height - 2);
            }

            // check if the window position overlaps with any door
            valid_position = true;
            for (int j = 0; j < newRoom->doors_number; j++)
            {
                if (newRoom->windows[i].position.x == newRoom->doors[j].position.x &&
                    newRoom->windows[i].position.y == newRoom->doors[j].position.y)
                {
                    valid_position = false;
                    break;
                }
            }
        }
    }

    // initializing other properties
    newRoom->grid = grid;
    newRoom->isSeen = false;
    newRoom->stairs.has_stairs = false;
    newRoom->type = ORDINARY;

    return newRoom;
}

void draw_map(Room **rooms, int rooms_number, bool ***map, int current_floor)
{
    for (int idx = 0; idx < rooms_number; idx++)
    {
        if (!rooms[idx]->isSeen)
        {
            continue;
        }

        if (rooms[idx]->type == TREASURE)
        {
            // draw top and bottom
            attron(COLOR_PAIR(COLOR_WALLS_TREASURE) | A_BOLD);
            for (int i = rooms[idx]->start.x; i < rooms[idx]->start.x + rooms[idx]->width; i++)
            {
                mvprintw(rooms[idx]->start.y, i, "-");                          // top border
                mvprintw(rooms[idx]->start.y + rooms[idx]->height - 1, i, "-"); // bottom border
            }
            attroff(COLOR_PAIR(COLOR_WALLS_TREASURE) | A_BOLD);

            // draw floor and side walls
            for (int i = rooms[idx]->start.y + 1; i < rooms[idx]->start.y + rooms[idx]->height - 1; i++)
            {
                attron(COLOR_PAIR(COLOR_WALLS_TREASURE) | A_BOLD);
                mvprintw(i, rooms[idx]->start.x, "|");                         // left border
                mvprintw(i, rooms[idx]->start.x + rooms[idx]->width - 1, "|"); // right border
                attroff(COLOR_PAIR(COLOR_WALLS_TREASURE) | A_BOLD);

                attron(COLOR_PAIR(COLOR_FLOOR_TREASURE) | A_BOLD);
                for (int j = rooms[idx]->start.x + 1; j < rooms[idx]->start.x + rooms[idx]->width - 1; j++)
                {
                    mvprintw(i, j, ".");
                }
                attroff(COLOR_PAIR(COLOR_FLOOR_TREASURE) | A_BOLD);
            }

            // draw doors
            attron(COLOR_PAIR(COLOR_STUFF_TREASURE));
            for (int i = 0; i < rooms[idx]->doors_number; i++)
            {
                mvprintw(rooms[idx]->doors[i].position.y, rooms[idx]->doors[i].position.x, "+");
            }

            // draw windows
            for (int i = 0; i < rooms[idx]->windows_number; i++)
            {
                mvprintw(rooms[idx]->windows[i].position.y, rooms[idx]->windows[i].position.x, "=");
            }
            attroff(COLOR_PAIR(COLOR_STUFF_TREASURE));
        }
        else
        {
            // draw top and bottom
            attron(COLOR_PAIR(COLOR_WALLS) | A_BOLD);
            for (int i = rooms[idx]->start.x; i < rooms[idx]->start.x + rooms[idx]->width; i++)
            {
                mvprintw(rooms[idx]->start.y, i, "-");                          // top border
                mvprintw(rooms[idx]->start.y + rooms[idx]->height - 1, i, "-"); // bottom border
            }
            attroff(COLOR_PAIR(COLOR_WALLS) | A_BOLD);

            // draw floor and side walls
            for (int i = rooms[idx]->start.y + 1; i < rooms[idx]->start.y + rooms[idx]->height - 1; i++)
            {
                attron(COLOR_PAIR(COLOR_WALLS) | A_BOLD);
                mvprintw(i, rooms[idx]->start.x, "|");                         // left border
                mvprintw(i, rooms[idx]->start.x + rooms[idx]->width - 1, "|"); // right border
                attroff(COLOR_PAIR(COLOR_WALLS) | A_BOLD);

                attron(COLOR_PAIR(COLOR_DEFAULT));
                for (int j = rooms[idx]->start.x + 1; j < rooms[idx]->start.x + rooms[idx]->width - 1; j++)
                {
                    mvprintw(i, j, ".");
                }
                attroff(COLOR_PAIR(COLOR_DEFAULT));
            }

            // draw doors
            attron(COLOR_PAIR(COLOR_DOORS));
            for (int i = 0; i < rooms[idx]->doors_number; i++)
            {
                mvprintw(rooms[idx]->doors[i].position.y, rooms[idx]->doors[i].position.x, "+");
            }
            attroff(COLOR_PAIR(COLOR_DOORS));

            // draw windows
            attron(COLOR_PAIR(COLOR_WINDOWS) | A_BOLD);
            for (int i = 0; i < rooms[idx]->windows_number; i++)
            {
                mvprintw(rooms[idx]->windows[i].position.y, rooms[idx]->windows[i].position.x, "=");
            }
            attroff(COLOR_PAIR(COLOR_WINDOWS) | A_BOLD);

            // draw stairs
            if (rooms[idx]->stairs.has_stairs)
            {
                if (rooms[idx]->stairs.previous_floor == current_floor)
                {
                    attron(COLOR_PAIR(COLOR_STAIRS_GOING) | A_BOLD | A_BLINK);
                    mvprintw(rooms[idx]->stairs.position.y, rooms[idx]->stairs.position.x, "<");
                    attroff(COLOR_PAIR(COLOR_STAIRS_GOING) | A_BOLD | A_BLINK);
                }
                else
                {
                    attron(COLOR_PAIR(COLOR_STAIRS_COMING) | A_BOLD | A_BLINK);
                    mvprintw(rooms[idx]->stairs.position.y, rooms[idx]->stairs.position.x, "<");
                    attroff(COLOR_PAIR(COLOR_STAIRS_COMING) | A_BOLD | A_BLINK);
                }
            }
        }
    }

    attron(COLOR_PAIR(COLOR_HALLS));
    // draw hallways
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j][1])
            {
                mvprintw(i, j, "#");
            }
        }
    }
    attroff(COLOR_PAIR(COLOR_HALLS));
}

void draw_all_map(Room **rooms, int rooms_number, bool ***map)
{
    attron(COLOR_PAIR(COLOR_UNSEEN));
    for (int idx = 0; idx < rooms_number; idx++)
    {
        // draw top and bottom
        attron(A_BOLD);
        for (int i = rooms[idx]->start.x; i < rooms[idx]->start.x + rooms[idx]->width; i++)
        {
            mvprintw(rooms[idx]->start.y, i, "-");                          // top border
            mvprintw(rooms[idx]->start.y + rooms[idx]->height - 1, i, "-"); // bottom border
        }
        attroff(A_BOLD);

        // draw floor and side walls
        for (int i = rooms[idx]->start.y + 1; i < rooms[idx]->start.y + rooms[idx]->height - 1; i++)
        {
            attron(A_BOLD);
            mvprintw(i, rooms[idx]->start.x, "|");                         // left border
            mvprintw(i, rooms[idx]->start.x + rooms[idx]->width - 1, "|"); // right border
            attroff(A_BOLD);

            for (int j = rooms[idx]->start.x + 1; j < rooms[idx]->start.x + rooms[idx]->width - 1; j++)
            {
                mvprintw(i, j, ".");
            }
        }

        // draw doors
        for (int i = 0; i < rooms[idx]->doors_number; i++)
        {
            mvprintw(rooms[idx]->doors[i].position.y, rooms[idx]->doors[i].position.x, "+");
        }

        // draw windows
        attron(A_BOLD);
        for (int i = 0; i < rooms[idx]->windows_number; i++)
        {
            mvprintw(rooms[idx]->windows[i].position.y, rooms[idx]->windows[i].position.x, "=");
        }
        attroff(A_BOLD);

        // draw stairs
        if (rooms[idx]->stairs.has_stairs)
        {
            attron(A_BOLD | A_BLINK);
            mvprintw(rooms[idx]->stairs.position.y, rooms[idx]->stairs.position.x, "<");
            attroff(A_BOLD | A_BLINK);
        }
    }

    // draw hallways
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j][0])
            {
                mvprintw(i, j, "#");
            }
        }
    }
    attroff(COLOR_PAIR(COLOR_UNSEEN));
}

void draw_room(Room *room)
{
    attron(COLOR_PAIR(COLOR_UNSEEN) | A_BOLD);
    for (int i = room->start.x; i < room->start.x + room->width; i++)
    {
        mvprintw(room->start.y, i, "-");                    // top border
        mvprintw(room->start.y + room->height - 1, i, "-"); // bottom border
    }
    attroff(A_BOLD);

    // draw floor and side walls
    for (int i = room->start.y + 1; i < room->start.y + room->height - 1; i++)
    {
        attron(A_BOLD);
        mvprintw(i, room->start.x, "|");                   // left border
        mvprintw(i, room->start.x + room->width - 1, "|"); // right border
        attroff(A_BOLD);

        for (int j = room->start.x + 1; j < room->start.x + room->width - 1; j++)
        {
            mvprintw(i, j, ".");
        }
    }

    // draw doors
    for (int i = 0; i < room->doors_number; i++)
    {
        mvprintw(room->doors[i].position.y, room->doors[i].position.x, "+");
    }

    // draw windows
    attron(A_BOLD);
    for (int i = 0; i < room->windows_number; i++)
    {
        mvprintw(room->windows[i].position.y, room->windows[i].position.x, "=");
    }
    attroff(A_BOLD);

    // draw stairs
    attron(A_BOLD | A_BLINK);
    if (room->stairs.has_stairs)
    {
        mvprintw(room->stairs.position.y, room->stairs.position.x, "<");
    }
    attroff(COLOR_PAIR(COLOR_UNSEEN) | A_BOLD | A_BLINK);
}

void use_windows(Player *player, Room **rooms, int rooms_number)
{
    int currunt_room = -1;

    for (int i = 0; i < rooms_number; i++)
    {
        if (player->position.y > rooms[i]->start.y && player->position.y < rooms[i]->start.y + rooms[i]->height - 1 &&
            player->position.x > rooms[i]->start.x && player->position.x < rooms[i]->start.x + rooms[i]->width - 1)
        {
            currunt_room = i;
            break;
        }
    }

    if (currunt_room == -1)
    {
        return;
    }

    int delta_y[4] = {-1, 0, 1, 0};
    int delta_x[4] = {0, 1, 0, -1};

    // check four directions for windows
    for (int win = 0; win < rooms[currunt_room]->windows_number; win++)
    {
        for (int idx = 0; idx < 4; idx++)
        {
            bool isDoor = false;

            if (player->position.y + delta_y[idx] == rooms[currunt_room]->windows[win].position.y &&
                player->position.x + delta_x[idx] == rooms[currunt_room]->windows[win].position.x)
            {
                // don't show the next room if player is on a door next to the window
                for (int i = 0; i < rooms[currunt_room]->doors_number; i++)
                {
                    if (player->position.y == rooms[currunt_room]->doors[i].position.y &&
                        player->position.x == rooms[currunt_room]->doors[i].position.x)
                    {
                        isDoor = true;
                        break;
                    }
                }

                if (isDoor)
                {
                    continue;
                }

                // start showing the next room in dark gray
                if (rooms[currunt_room]->windows[win].side == UP)
                {
                    for (int i = 0; i < rooms_number; i++)
                    {
                        if (rooms[i]->grid == rooms[currunt_room]->grid - 5 && !rooms[i]->isSeen)
                        {
                            draw_room(rooms[i]);
                            return;
                        }
                    }
                }

                else if (rooms[currunt_room]->windows[win].side == RIGHT)
                {
                    for (int i = 0; i < rooms_number; i++)
                    {
                        if (rooms[i]->grid == rooms[currunt_room]->grid + 1 && !rooms[i]->isSeen)
                        {
                            draw_room(rooms[i]);
                            return;
                        }
                    }
                }

                else if (rooms[currunt_room]->windows[win].side == DOWN)
                {
                    for (int i = 0; i < rooms_number; i++)
                    {
                        if (rooms[i]->grid == rooms[currunt_room]->grid + 5 && !rooms[i]->isSeen)
                        {
                            draw_room(rooms[i]);
                            return;
                        }
                    }
                }

                else if (rooms[currunt_room]->windows[win].side == LEFT)
                {
                    for (int i = 0; i < rooms_number; i++)
                    {
                        if (rooms[i]->grid == rooms[currunt_room]->grid - 1 && !rooms[i]->isSeen)
                        {
                            draw_room(rooms[i]);
                            return;
                        }
                    }
                }
            }
        }
    }
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

void import_hallway(Room **rooms, int rooms_number, Position pos, Position start, bool ***map)
{
    if (pos.y == start.y && pos.x == start.x)
    {
        return;
    }

    map[pos.y][pos.x][0] = 1;
    map[pos.y][pos.x][1] = 0;

    int delta_x[4] = {1, 0, -1, 0};
    int delta_y[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++)
    {
        is_nextto_door(rooms, rooms_number, pos.y + delta_y[i], pos.x + delta_x[i]);
    }

    import_hallway(rooms, rooms_number, come_from[pos.y][pos.x], start, map);
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

void find_path(Room **rooms, int rooms_number, Position start, Position end, bool ***map)
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
        if (currunt_position.y > 1 &&
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

    import_hallway(rooms, rooms_number, come_from[end.y][end.x], start, map);
}

void connect_rooms(Room **rooms, int rooms_number, bool ***map)
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

        find_path(rooms, rooms_number, rooms[room_1]->doors[door_1].position, rooms[room_2]->doors[door_2].position, map);
    }
}

void place_stairs(Room **rooms, int rooms_number, int curruent_floor)
{
    int chosen_room = rand() % rooms_number;

    while (rooms[chosen_room]->stairs.has_stairs)
    {
        chosen_room = rand() % rooms_number;
    }

    rooms[chosen_room]->stairs.has_stairs = true;
    rooms[chosen_room]->stairs.position.y = rooms[chosen_room]->start.y + 1 + rand() % (rooms[chosen_room]->height - 2);
    rooms[chosen_room]->stairs.position.x = rooms[chosen_room]->start.x + 1 + rand() % (rooms[chosen_room]->width - 2);
    rooms[chosen_room]->stairs.previous_floor = curruent_floor;
    rooms[chosen_room]->stairs.next_floor = curruent_floor + 1;
}

Room **map_setup(int rooms_number, bool ***map, Room *previous_room, bool isLast, int current_floor)
{
    Room **rooms = (Room **)malloc(sizeof(Room *) * rooms_number);

    if (!isLast) // check if it's the last floor
    {
        if (previous_room) // check if it's the first floor
        {
            rooms[0] = previous_room;

            // setting up rooms
            bool isFilled[10] = {0};
            isFilled[previous_room->grid] = 1;

            for (int i = 1; i < rooms_number; i++)
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
            }

            connect_rooms(rooms, rooms_number, map);
            place_stairs(rooms, rooms_number, current_floor);
        }
        else
        {
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
            }

            connect_rooms(rooms, rooms_number, map);
            place_stairs(rooms, rooms_number, current_floor);
        }
    }
    else
    {
        rooms[0] = previous_room;

        // setting up rooms
        bool isFilled[10] = {0};
        isFilled[previous_room->grid] = 1;

        for (int i = 1; i < rooms_number; i++)
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
        }

        connect_rooms(rooms, rooms_number, map);

        int treasure_room = rand() % rooms_number;
        while (treasure_room == 0)
        {
            treasure_room = rand() % rooms_number;
        }
        rooms[treasure_room]->type = TREASURE;
    }

    return rooms;
}

void show_next_step(Room **rooms, Player *player, int rooms_number, bool ***map)
{
    int delta_y[4] = {-1, 0, 1, 0};
    int delta_x[4] = {0, 1, 0, -1};

    // show near hallways
    attron(COLOR_PAIR(COLOR_UNSEEN));
    for (int i = 0; i < 4; i++)
    {
        if (!(player->position.y + delta_y[i] >= 0 && player->position.y + delta_y[i] <= MAP_HEIGHT &&
              player->position.x + delta_x[i] >= 0 && player->position.x + delta_x[i] <= MAP_WIDTH))
        {
            continue;
        }

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