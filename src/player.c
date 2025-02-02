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

void move_player(int inp, Floor **floors, Room **rooms, int rooms_number, Player *player)
{
    if (inp == KEY_UP || inp == 'w' || inp == 'W' || inp == '8')
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

    if (inp == KEY_DOWN || inp == 'x' || inp == 'X' || inp == '2')
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

    if (inp == KEY_LEFT || inp == 'a' || inp == 'A' || inp == '4')
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

    if (inp == KEY_RIGHT || inp == 'd' || inp == 'D' || inp == '6')
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

    if (inp == 'q' || inp == 'Q' || inp == '7')
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
    if (inp == 'e' || inp == 'E' || inp == '9')
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

    if (inp == 'z' || inp == 'Z' || inp == '1')
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

    if (inp == 'c' || inp == 'C' || inp == '3')
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
    while (rooms[initial_room]->stairs.has_stairs ||
           rooms[initial_room]->type != ROOM_ORDINARY)
    {
        initial_room = rand() % rooms_number;
    }

    newPlayer->position.y = rooms[initial_room]->start.y + 1 + rand() % (rooms[initial_room]->height - 2);
    newPlayer->position.x = rooms[initial_room]->start.x + 1 + rand() % (rooms[initial_room]->width - 2);

    // make sure player starts in a safe position
    for (int i = 0; i < rooms[initial_room]->reserved_number; i++)
    {
        while (newPlayer->position.y == rooms[initial_room]->reserved_poitions[i].y &&
               newPlayer->position.x == rooms[initial_room]->reserved_poitions[i].x)
        {
            newPlayer->position.y = rooms[initial_room]->start.y + 1 + rand() % (rooms[initial_room]->height - 2);
            newPlayer->position.x = rooms[initial_room]->start.x + 1 + rand() % (rooms[initial_room]->width - 2);
        }
    }

    // setting up player stuff
    newPlayer->stuff.food_ordinary = 0;
    newPlayer->stuff.food_excellent = 0;
    newPlayer->stuff.food_magic = 0;
    newPlayer->stuff.food_corrupt = 0;

    newPlayer->stuff.spell_health = 0;
    newPlayer->stuff.spell_speed = 0;
    newPlayer->stuff.spell_damage = 0;

    newPlayer->stuff.weapon_mace = true;
    newPlayer->stuff.weapon_dagger = false;
    newPlayer->stuff.weapon_wand = false;
    newPlayer->stuff.weapon_arrow = false;
    newPlayer->stuff.weapon_sword = false;

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
    // check if the user is in a room
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

    // check for traps
    for (int i = 0; i < current_room->traps_number; i++)
    {
        if (current_room->traps_position[i].y == player->position.y && current_room->traps_position[i].x)
        {
            player->health -= 10;
            current_room->traps_position[i].y = -1;
            current_room->traps_position[i].x = -1;

            strcpy(player->message, "You stepped on a trap! Health was decreased by 10.");
            show_message(player->message);
            return;
        }
    }

    // check for gold
    if (current_room->golds_number != 0)
    {
        for (int i = 0; i < current_room->golds_number; i++)
        {
            if (current_room->golds[i].position.y == player->position.y && current_room->golds[i].position.x == player->position.x)
            {
                if (current_room->type == ROOM_NIGHTMARE)
                {
                    strcpy(player->message, "This gold is not real!");
                    show_message(player->message);
                    return;
                }

                if (current_room->golds->type == GOLD_ORDINARY)
                {
                    strcpy(player->message, "You collected a gold!");
                    show_message(player->message);

                    player->gold++;
                    current_room->golds[i].position.y = -1;
                    current_room->golds[i].position.x = -1;
                    return;
                }
                else if (current_room->golds->type == GOLD_BLACK)
                {
                    strcpy(player->message, "You collected 5 golds!");
                    show_message(player->message);

                    player->gold += 5;
                    current_room->golds[i].position.y = -1;
                    current_room->golds[i].position.x = -1;
                    return;
                }
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
                if (current_room->type == ROOM_NIGHTMARE)
                {
                    strcpy(player->message, "This food is not real!");
                    show_message(player->message);
                    return;
                }

                if (current_room->foods[i].type == FOOD_ORDINARY)
                {
                    player->stuff.food_ordinary++;
                }
                else if (current_room->foods[i].type == FOOD_EXCELLENT)
                {
                    player->stuff.food_excellent++;
                }
                else if (current_room->foods[i].type == FOOD_MAGIC)
                {
                    player->stuff.food_magic++;
                }
                else if (current_room->foods[i].type == FOOD_CORRUPT)
                {
                    player->stuff.food_corrupt++;
                }

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

    // check for spells
    if (current_room->type == ROOM_ENCHANT)
    {
        for (int i = 0; i < current_room->spells_number; i++)
        {
            if (player->position.y == current_room->spells[i].position.y &&
                player->position.x == current_room->spells[i].position.x)
            {
                strcpy(player->message, "Do you want to pick up this spell? (y / n)");
                show_message(player->message);

                int ch = getch();
                if (ch == 'y' || ch == 'Y')
                {
                    if (current_room->type == ROOM_NIGHTMARE)
                    {
                        strcpy(player->message, "This spell is not real!");
                        show_message(player->message);
                        return;
                    }

                    if (current_room->spells[i].type == SPELL_HEALTH)
                    {
                        player->stuff.spell_health++;
                    }
                    else if (current_room->spells[i].type == SPELL_SPEED)
                    {
                        player->stuff.spell_speed++;
                    }
                    if (current_room->spells[i].type == SPELL_DAMAGE)
                    {
                        player->stuff.spell_damage++;
                    }

                    current_room->spells[i].position.y = -1;
                    current_room->spells[i].position.x = -1;

                    strcpy(player->message, "You picked up the spell!");
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

    // check for weapons
    for (int i = 0; i < current_room->weapons_number; i++)
    {
        if (player->position.y == current_room->weapons[i].position.y &&
            player->position.x == current_room->weapons[i].position.x)
        {
            strcpy(player->message, "Do you want to pick up this weapon? (y / n)");
            show_message(player->message);

            int ch = getch();
            if (ch == 'y' || ch == 'Y')
            {
                if (current_room->type == ROOM_NIGHTMARE)
                {
                    strcpy(player->message, "This weapon is not real!");
                    show_message(player->message);
                    return;
                }

                if (current_room->weapons[i].type == WEAPON_DAGGER)
                {
                    player->stuff.weapon_dagger = true;
                }
                else if (current_room->weapons[i].type == WEAPON_WAND)
                {
                    player->stuff.weapon_wand = true;
                }
                else if (current_room->weapons[i].type == WEAPON_ARROW)
                {
                    player->stuff.weapon_arrow = true;
                }
                else if (current_room->weapons[i].type == WEAPON_SWORD)
                {
                    player->stuff.weapon_sword = true;
                }

                current_room->weapons[i].position.y = -1;
                current_room->weapons[i].position.x = -1;

                strcpy(player->message, "You picked up the weapon!");
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

void show_foods(Player *player)
{
    int choice = 0;
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    curs_set(0); // Hide cursor

    const char *food_options[] = {
        "Ordinary food",
        "Excellent food",
        "Magic food",
        "Corrupt food",
        "Go Back"};

    while (1)
    {
        clear();

        int start_y = (max_y / 2) - (NUM_FOOD_MENU / 2);
        int start_x = (max_x / 2) - 15;

        // Draw border and title
        draw_border(start_y - 1, start_x, NUM_FOOD_MENU + 2, 30);
        show_title(start_y - 3, start_x + 8, "=== FOOD ===");

        for (int i = 0; i < NUM_FOOD_MENU; i++)
        {
            int y = start_y + i;
            if (i == choice)
            {
                attron(A_REVERSE);
            }

            if (i < 4)
            {
                mvprintw(y, start_x + 2, "%-16s", food_options[i]);
                int count;
                switch (i)
                {
                case 0:
                    count = player->stuff.food_ordinary;
                    break;
                case 1:
                    count = player->stuff.food_excellent;
                    break;
                case 2:
                    count = player->stuff.food_magic;
                    break;
                case 3:
                    count = player->stuff.food_corrupt;
                    break;
                }
                mvprintw(y, start_x + 20, "%d", count);
            }
            else
            {
                mvprintw(y, start_x + 2, "%s", food_options[i]);
            }

            if (i == choice)
            {
                attroff(A_REVERSE);
            }
        }

        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice = (choice - 1 + NUM_FOOD_MENU) % NUM_FOOD_MENU;
            break;

        case KEY_DOWN:
            choice = (choice + 1) % NUM_FOOD_MENU;
            break;

        case ENTER:
            if (choice == 0)
            {
                if (player->stuff.food_ordinary > 0)
                {
                    player->stuff.food_ordinary--;
                    player->health += 5;
                    if (player->health > 100)
                    {
                        player->health = 100;
                    }

                    attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "Health was increased by 5!");
                    mvprintw(start_y + NUM_FOOD_MENU + 3, start_x - 1, "Current health status is (%d / 100)", player->health);
                    attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    refresh();
                    sleep(2);
                }
                else
                {
                    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "You don't have enough food!");
                    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    refresh();
                    sleep(2);
                }
            }
            else if (choice == 1)
            {
                if (player->stuff.food_excellent > 0)
                {
                    player->stuff.food_excellent--;
                    player->health += 20;
                    if (player->health > 100)
                    {
                        player->health = 100;
                    }

                    attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "Health was increased by 20!");
                    mvprintw(start_y + NUM_FOOD_MENU + 3, start_x - 1, "Current health status is (%d / 100).", player->health);
                    attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    refresh();
                    sleep(2);
                }
                else
                {
                    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "You don't have enough food!");
                    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    refresh();
                    sleep(2);
                }
            }
            else if (choice == 2)
            {

                if (player->stuff.food_magic > 0)
                {
                    player->stuff.food_magic--;
                    player->health += 50;
                    if (player->health > 100)
                    {
                        player->health = 100;
                    }

                    attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "Health was increased by 50!");
                    mvprintw(start_y + NUM_FOOD_MENU + 3, start_x - 1, "Current health status is (%d / 100).", player->health);
                    attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    refresh();
                    sleep(2);
                }
                else
                {
                    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "You don't have enough food!");
                    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    refresh();
                    sleep(2);
                }
            }
            else if (choice == 3)
            {
                if (player->stuff.food_corrupt > 0)
                {
                    player->stuff.food_corrupt--;
                    player->health -= 10;
                    if (player->health < 0)
                    {
                        player->health = 0;
                    }

                    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "Health was decreased by 10!");
                    mvprintw(start_y + NUM_FOOD_MENU + 3, start_x - 1, "Current health status is (%d / 100).", player->health);
                    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    refresh();
                    sleep(2);
                }
                else
                {
                    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "You don't have enough food!");
                    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    refresh();
                    sleep(2);
                }
            }

            else if (choice == 4)
            {
                return;
            }
            break;

        default:
            break;
        }
    }
}

void show_spells(Player *player)
{
    int choice = 0;
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    curs_set(0); // Hide cursor

    const char *spell_options[] = {
        "Health spell",
        "Speed spell",
        "Damage spell",
        "Go Back"};

    while (1)
    {
        clear();

        int start_y = (max_y / 2) - (NUM_SPELL_MENU / 2);
        int start_x = (max_x / 2) - 15;

        // Draw border and title
        draw_border(start_y - 1, start_x, NUM_SPELL_MENU + 2, 30);
        show_title(start_y - 3, start_x + 8, "=== SPELL ===");

        for (int i = 0; i < NUM_SPELL_MENU; i++)
        {
            int y = start_y + i;
            if (i == choice)
            {
                attron(A_REVERSE);
            }

            if (i < 3)
            {
                mvprintw(y, start_x + 2, "%-16s", spell_options[i]);
                int count;
                switch (i)
                {
                case 0:
                    count = player->stuff.spell_health;
                    break;
                case 1:
                    count = player->stuff.spell_speed;
                    break;
                case 2:
                    count = player->stuff.spell_damage;
                    break;
                }
                mvprintw(y, start_x + 20, "%d", count);
            }
            else
            {
                mvprintw(y, start_x + 2, "%s", spell_options[i]);
            }

            if (i == choice)
            {
                attroff(A_REVERSE);
            }
        }

        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice = (choice - 1 + NUM_SPELL_MENU) % NUM_SPELL_MENU;
            break;

        case KEY_DOWN:
            choice = (choice + 1) % NUM_SPELL_MENU;
            break;

        case ENTER:
            if (choice == 0)
            {
                if (player->stuff.spell_health > 0)
                {
                    player->stuff.spell_health--;
                    player->health = 100;

                    attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    mvprintw(start_y + NUM_SPELL_MENU + 2, start_x - 1, "Health was recovered completely!");
                    attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    refresh();
                    sleep(2);
                }
                else
                {
                    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    mvprintw(start_y + NUM_SPELL_MENU + 2, start_x - 1, "You don't have enough spell!");
                    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    refresh();
                    sleep(2);
                }
            }
            else if (choice == 1)
            {
                if (player->stuff.spell_speed > 0)
                {
                    player->stuff.spell_speed--;

                    // attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    // mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "Health was increased by 20!");
                    // mvprintw(start_y + NUM_FOOD_MENU + 3, start_x - 1, "Current health status is (%d / 100).", player->health);
                    // attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    // refresh();
                    // sleep(2);
                }
                else
                {
                    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    mvprintw(start_y + NUM_SPELL_MENU + 2, start_x - 1, "You don't have enough spell!");
                    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    refresh();
                    sleep(2);
                }
            }
            else if (choice == 2)
            {

                if (player->stuff.spell_damage > 0)
                {
                    player->stuff.spell_damage--;

                    // attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    // mvprintw(start_y + NUM_FOOD_MENU + 2, start_x - 1, "Health was restored completely!");
                    // mvprintw(start_y + NUM_FOOD_MENU + 3, start_x - 1, "Current health status is (%d / 100).", player->health);
                    // attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                    // refresh();
                    // sleep(2);
                }
                else
                {
                    attron(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    mvprintw(start_y + NUM_SPELL_MENU + 2, start_x - 1, "You don't have enough food!");
                    attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE));
                    refresh();
                    sleep(2);
                }
            }

            else if (choice == 3)
            {
                return;
            }
            break;

        default:
            break;
        }
    }
}

void show_weapons(Player *player)
{
    int choice = 0;
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    curs_set(0);

    int start_y = (max_y / 2) - 3;
    int start_x = (max_x / 2) - 15;

    char *weapon_options[10];
    int option_count = 0;

    if (player->stuff.weapon_mace)
        weapon_options[option_count++] = "Mace";
    if (player->stuff.weapon_dagger)
        weapon_options[option_count++] = "Dagger";
    if (player->stuff.weapon_wand)
        weapon_options[option_count++] = "Wand";
    if (player->stuff.weapon_arrow)
        weapon_options[option_count++] = "Arrow";
    if (player->stuff.weapon_sword)
        weapon_options[option_count++] = "Sword";

    weapon_options[option_count++] = "Go back";

    while (1)
    {
        clear();

        draw_border(start_y - 1, start_x, option_count + 2, 30);
        show_title(start_y - 3, start_x + 8, "=== WEAPON ===");

        for (int i = 0; i < option_count; i++)
        {
            int y = start_y + i;
            if (i == choice)
                attron(A_REVERSE);

            mvprintw(y, start_x + 2, "%s", weapon_options[i]);

            if (i == choice)
                attroff(A_REVERSE);
        }
        refresh();

        int ch = getch();
        switch (ch)
        {
        case KEY_UP:
            choice = (choice - 1 + option_count) % option_count;
            break;

        case KEY_DOWN:
            choice = (choice + 1) % option_count;
            break;

        case ENTER:
            if (strcmp(weapon_options[choice], "Go back") == 0)
            {
                return;
            }
            else
            {
                attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                mvprintw(start_y + option_count + 2, start_x - 1, "You picked up %s.", weapon_options[choice]);
                attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE));
                refresh();
                sleep(2);
            }
            break;

        default:
            break;
        }
    }
}

void status_bar(Player *player)
{
    mvprintw(30, 0, "Current floor: %d", player->current_floor + 1);
    mvprintw(30, 25, "Health: %d", player->health);
    mvprintw(30, 45, "Gold: %d", player->gold);
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

    int inp = getch();
    player->message[0] = '\0'; // update the message

    // check for map overview
    if (inp == 'm' || inp == 'M')
    {
        strcpy(player->message, "Showing the whole map. (press M key again to cancel)");
        show_message(player->message);

        draw_all_map(rooms, rooms_number, floors[player->current_floor]->map);
        getch();
        player->message[0] = '\0';
    }

    // check for fast mode
    else if (inp == 'f' || inp == 'F')
    {
        strcpy(player->message, "Fast mode activated. Choose a direction. (press F key again to cancel)");
        show_message(player->message);

        fast_move(floors, rooms, rooms_number, player);
        player->message[0] = '\0';
    }

    // check for showing stuff
    else if (inp == 's' || inp == 'S')
    {
        strcpy(player->message, "Which item do you want to view? (Food: F | Spell: S | Weapon: W | Cancel: c)");
        show_message(player->message);

        int ch = getch();
        if (ch == 'f' || ch == 'F')
        {
            show_foods(player);
        }
        else if (ch == 's' || ch == 'S')
        {
            show_spells(player);
        }
        else if (ch == 'w' || ch == 'W')
        {
            show_weapons(player);
        }

        player->message[0] = '\0';
    }

    // handle the inparacter moving
    else
    {
        move_player(inp, floors, rooms, rooms_number, player);

        // reduce health by 1 after moving 10 blocks
        while (player->passed_blockes > 5)
        {
            player->passed_blockes -= 5;
            player->health--;
        }
    }
}

int check_status(Player *player, Floor **floors)
{
    if (player->health <= 0)
    {
        clear();

        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        curs_set(0); // Hide cursor

        int start_y = (max_y / 2) - 1;
        int start_x = (max_x / 2) - 22;

        // Draw border and title
        draw_border(start_y - 1, start_x - 2, 3, 45);
        attron(COLOR_PAIR(COLOR_ALERT_MESSAGE) | A_BLINK);
        mvprintw(start_y - 3, start_x + 8, "=== !!!YOU LOST!!! ===");
        attroff(COLOR_PAIR(COLOR_ALERT_MESSAGE) | A_BLINK);

        attron(COLOR_PAIR(COLOR_GOLD_ORDINARY) | A_BOLD);
        mvprintw(start_y, start_x, "Collected Golds: % d", player->gold);
        attroff(COLOR_PAIR(COLOR_GOLD_ORDINARY) | A_BOLD);

        attron(COLOR_PAIR(COLOR_GOLD_BLACK) | A_BOLD);
        mvprintw(start_y, start_x + 30, "Score: %d", player->gold * 175);
        attroff(COLOR_PAIR(COLOR_GOLD_BLACK) | A_BOLD);

        attron(A_REVERSE);
        mvprintw(start_y + 3, start_x + 8, "Return to Pregame Menu");
        attroff(A_REVERSE);

        int ch = getch();
        while (ch != ENTER)
        {
            ch = getch();
        }

        return LOSS;
    }

    for (int i = 0; i < floors[player->current_floor]->rooms_number; i++)
    {
        if (floors[player->current_floor]->rooms[i]->type == ROOM_TREASURE &&
            player->position.y > floors[player->current_floor]->rooms[i]->start.y &&
            player->position.y < floors[player->current_floor]->rooms[i]->start.y + floors[player->current_floor]->rooms[i]->height - 1 &&
            player->position.x > floors[player->current_floor]->rooms[i]->start.x &&
            player->position.x < floors[player->current_floor]->rooms[i]->start.x + floors[player->current_floor]->rooms[i]->width - 1)
        {
            clear();
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);
            curs_set(0); // Hide cursor

            int start_y = (max_y / 2) - 1;
            int start_x = (max_x / 2) - 22;

            // Draw border and title
            draw_border(start_y - 1, start_x - 2, 3, 45);
            attron(COLOR_PAIR(COLOR_SUCCESS_MESSAGE) | A_BLINK);
            mvprintw(start_y - 3, start_x + 9, "=== !!!YOU WON!!! ===");
            attroff(COLOR_PAIR(COLOR_SUCCESS_MESSAGE) | A_BLINK);

            attron(COLOR_PAIR(COLOR_GOLD_ORDINARY) | A_BOLD);
            mvprintw(start_y, start_x, "Collected Golds: % d", player->gold);
            attroff(COLOR_PAIR(COLOR_GOLD_ORDINARY) | A_BOLD);

            attron(COLOR_PAIR(COLOR_GOLD_BLACK) | A_BOLD);
            mvprintw(start_y, start_x + 30, "Score: %d", player->gold * 175);
            attroff(COLOR_PAIR(COLOR_GOLD_BLACK) | A_BOLD);

            attron(A_REVERSE);
            mvprintw(start_y + 3, start_x + 8, "Return to Pregame Menu");
            attroff(A_REVERSE);

            int ch = getch();
            while (ch != ENTER)
            {
                ch = getch();
            }

            return WIN;
        }
    }

    return NOTHING;
}
