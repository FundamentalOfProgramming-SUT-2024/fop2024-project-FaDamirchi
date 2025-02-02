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

        room->monsters[i]->passed_blocks = 0;
    }
}

bool monster_can_move(Room **rooms, int rooms_number, int next_y, int next_x, Player *player)
{
    for (int i = 0; i < rooms_number; i++)
    {
        if (next_y > rooms[i]->start.y && next_y < rooms[i]->start.y + rooms[i]->height - 1 &&
            next_x > rooms[i]->start.x && next_x < rooms[i]->start.x + rooms[i]->width - 1)
        {
            return true;
        }

        if ((next_y >= rooms[i]->start.y && next_y <= rooms[i]->start.y + rooms[i]->height - 1 && next_x == rooms[i]->start.x) ||
            (next_y >= rooms[i]->start.y && next_y <= rooms[i]->start.y + rooms[i]->height - 1 && next_x == rooms[i]->start.x + rooms[i]->width - 1) ||
            (next_x >= rooms[i]->start.x && next_x <= rooms[i]->start.x + rooms[i]->width - 1 && next_y == rooms[i]->start.y) ||
            (next_x >= rooms[i]->start.x && next_x <= rooms[i]->start.x + rooms[i]->width - 1 && next_y == rooms[i]->start.y + rooms[i]->height - 1))
        {
            return false;
        }

        if (next_y == player->position.y && next_x == player->position.x)
        {
            return false;
        }
    }

    return false;
}

void move_monster(Room **rooms, int rooms_number, Player *player, Monster *monster)
{
    if (monster->monster_type != SNAKE && monster->passed_blocks > 5)
    {
        return;
    }

    int next_y, next_x;

    // choose direction towards the player
    if (monster->position.y < player->position.y)
    {
        next_y = monster->position.y + 1;
        next_x = monster->position.x;
    }
    else if (monster->position.y > player->position.y)
    {
        next_y = monster->position.y - 1;
        next_x = monster->position.x;
    }
    else if (monster->position.x < player->position.x)
    {
        next_x = monster->position.x + 1;
        next_y = monster->position.y;
    }
    else if (monster->position.x > player->position.x)
    {
        next_x = monster->position.x - 1;
        next_y = monster->position.y;
    }
    else
    {
        return; // Already at player's position
    }

    if (monster_can_move(rooms, rooms_number, next_y, next_x, player))
    {
        monster->position.y = next_y;
        monster->position.x = next_x;
        monster->passed_blocks++;
    }
}

bool monster_update(Room **rooms, int rooms_number, Player *player)
{
    Room *current_room = NULL;
    // Find the current room based on player's position
    for (int i = 0; i < rooms_number; i++)
    {
        if (player->position.y > rooms[i]->start.y && player->position.y < rooms[i]->start.y + rooms[i]->height - 1 &&
            player->position.x > rooms[i]->start.x && player->position.x < rooms[i]->start.x + rooms[i]->width - 1)
        {
            current_room = rooms[i];
            break;
        }
    }

    if (!current_room)
        return true;

    for (int i = 0; i < current_room->monsters_number; i++)
    {
        Monster *monster = current_room->monsters[i];
        int delta_y[] = {-1, 0, 1, 0};
        int delta_x[] = {0, 1, 0, -1};

        for (int j = 0; j < 4; j++)
        {
            int adj_y = monster->position.y + delta_y[j];
            int adj_x = monster->position.x + delta_x[j];
            if (adj_y == player->position.y && adj_x == player->position.x)
            {
                // Combat initiated
                strcpy(player->message, "Press ENTER to attack the monster!");
                show_message(player->message);
                refresh();

                int ch = getch();
                if (ch == '\n')
                {
                    if (player->current_weapon == WEAPON_MACE)
                    {
                        if (player->spell_usage > 0 && player->current_spell == SPELL_DAMAGE)
                        {
                            monster->health -= 10;
                            player->spell_usage--;
                        }
                        else
                        {
                            monster->health -= 5;
                        }
                    }
                    else if (player->current_weapon == WEAPON_DAGGER)
                    {
                        if (player->stuff.weapon_dagger > 0)
                        {

                            if (player->spell_usage > 0 && player->current_spell == SPELL_DAMAGE)
                            {
                                monster->health -= 24;
                                player->spell_usage--;
                                player->stuff.weapon_dagger--;
                            }
                            else
                            {
                                monster->health -= 12;
                                player->stuff.weapon_dagger--;
                            }
                        }
                        else
                        {
                            strcpy(player->message, "You Don't have enough Dagger!");
                        }
                    }
                    else if (player->current_weapon == WEAPON_WAND)
                    {

                        if (player->stuff.weapon_wand > 0)
                        {

                            if (player->spell_usage > 0 && player->current_spell == SPELL_DAMAGE)
                            {
                                monster->health -= 30;
                                player->spell_usage--;
                                player->stuff.weapon_wand--;
                            }
                            else
                            {
                                monster->health -= 15;
                                player->stuff.weapon_wand--;
                            }
                        }
                        else
                        {
                            strcpy(player->message, "You Don't have enough Magic Wand!");
                        }
                    }
                    else if (player->current_weapon == WEAPON_ARROW)
                    {
                        if (player->stuff.weapon_arrow > 0)
                        {

                            if (player->spell_usage > 0 && player->current_spell == SPELL_DAMAGE)
                            {
                                monster->health -= 5;
                                player->spell_usage--;
                                player->stuff.weapon_arrow--;
                            }
                            else
                            {
                                monster->health -= 10;
                                player->stuff.weapon_arrow--;
                            }
                        }
                        else
                        {
                            strcpy(player->message, "You Don't have enough Normal Arrow!");
                        }
                    }
                    else if (player->current_weapon == WEAPON_SWORD)
                    {
                        if (player->spell_usage > 0 && player->current_spell == SPELL_DAMAGE)
                        {
                            monster->health -= 20;
                            player->spell_usage--;
                        }
                        else
                        {
                            monster->health -= 10;
                        }
                    }

                    if (monster->monster_type == DEAMON)
                    {
                        strcpy(player->message, "You hit the Deamon!");
                    }
                    else if (monster->monster_type == FIRE)
                    {
                        strcpy(player->message, "You hit the Fire Breathing Monster!");
                    }
                    else if (monster->monster_type == GIANT)
                    {
                        strcpy(player->message, "You hit the Giant!");
                    }
                    else if (monster->monster_type == SNAKE)
                    {
                        strcpy(player->message, "You hit the Snake!");
                    }
                    else if (monster->monster_type == UNDEED)
                    {
                        strcpy(player->message, "You hit the Undeed!");
                    }

                    if (monster->health <= 0)
                    {
                        // Remove monster
                        monster->position.y = -1;
                        monster->position.x = -1;

                        i--;
                        if (monster->monster_type == DEAMON)
                        {
                            strcpy(player->message, "You defeated the Deamon!");
                        }
                        else if (monster->monster_type == FIRE)
                        {
                            strcpy(player->message, "You defeated the Fire Breathing Monster!");
                        }
                        else if (monster->monster_type == GIANT)
                        {
                            strcpy(player->message, "You defeated the Giant!");
                        }
                        else if (monster->monster_type == SNAKE)
                        {
                            strcpy(player->message, "You defeated the Snake!");
                        }
                        else if (monster->monster_type == UNDEED)
                        {
                            strcpy(player->message, "You defeated the Undeed!");
                        }
                        free(monster);
                    }
                    else
                    {
                        // monster attacks
                        player->health -= monster->damage;
                        if (monster->monster_type == DEAMON)
                        {
                            strcpy(player->message, "The Deamon hit you!");
                        }
                        else if (monster->monster_type == FIRE)
                        {
                            strcpy(player->message, "The Fire Breathing Monster hit you!");
                        }
                        else if (monster->monster_type == GIANT)
                        {
                            strcpy(player->message, "The Giant hit you!");
                        }
                        else if (monster->monster_type == SNAKE)
                        {
                            strcpy(player->message, "The Snake hit you!");
                        }
                        else if (monster->monster_type == UNDEED)
                        {
                            strcpy(player->message, "The Undeed hit you!");
                        }
                    }
                }
                else
                {
                    // monster attacks
                    player->health -= monster->damage;
                    strcpy(player->message, "The monster attacks you!");
                }
                show_message(player->message);
                refresh();

                if (player->health <= 0)
                    return false;
                break;
            }
        }
    }

    // move remaining monsters
    for (int i = 0; i < current_room->monsters_number; i++)
    {
        move_monster(rooms, rooms_number, player, current_room->monsters[i]);
    }

    return true;
}