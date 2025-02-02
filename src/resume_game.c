#include "resume_game.h"
#include "global_defines.h"
#include "manage_users.h"
#include "new_game.h"
#include "map.h"
#include "player.h"
#include "monsters.h"

bool recover_information(Game *game, char *username)
{
    FILE *fp = fopen(SAVED_GAMES_FILE, "r");

    char line[256];
    int value;
    bool found = false;

    // searching for the username
    while (fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, "USERNAME:", 9) == 0)
        {
            char fileUsername[100];
            sscanf(line, "USERNAME: %s", fileUsername);
            if (strcmp(fileUsername, username) == 0)
            {
                found = true;
                break;
            }
            else
            {
                // if the user was not found, skip the file to the END_GAME
                while (fgets(line, sizeof(line), fp))
                {
                    if (strstr(line, "END_GAME"))
                        break;
                }
            }
        }
    }

    if (!found)
    {
        return false;
    }

    
    game->player = (Player *)malloc(sizeof(Player));

    // recovering player information
    while (fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, "Player_Position:", 16) == 0)
        {
            int posY, posX;
            sscanf(line, "Player_Position: %d %d", &posX, &posY);
            game->player->position.x = posX;
            game->player->position.y = posY;
        }
        else if (strncmp(line, "Player_Current_Floor:", 21) == 0)
        {
            sscanf(line, "Player_Current_Floor: %d", &value);
            game->player->current_floor = value;
        }
        else if (strncmp(line, "Player_Passed_Blockes:", 23) == 0)
        {
            sscanf(line, "Player_Passed_Blockes: %d", &value);
            game->player->passed_blockes = value;
        }
        else if (strncmp(line, "Player_Gold:", 12) == 0)
        {
            sscanf(line, "Player_Gold: %d", &value);
            game->player->gold = value;
        }
        else if (strncmp(line, "Player_Health:", 14) == 0)
        {
            sscanf(line, "Player_Health: %d", &value);
            game->player->health = value;
        }
        // Stuff information
        else if (strncmp(line, "Stuff_Food_Ordinary:", 20) == 0)
        {
            sscanf(line, "Stuff_Food_Ordinary: %d", &value);
            game->player->stuff.food_ordinary = value;
        }
        else if (strncmp(line, "Stuff_Food_Excellent:", 21) == 0)
        {
            sscanf(line, "Stuff_Food_Excellent: %d", &value);
            game->player->stuff.food_excellent = value;
        }
        else if (strncmp(line, "Stuff_Food_Magic:", 17) == 0)
        {
            sscanf(line, "Stuff_Food_Magic: %d", &value);
            game->player->stuff.food_magic = value;
        }
        else if (strncmp(line, "Stuff_Food_Corrupt:", 19) == 0)
        {
            sscanf(line, "Stuff_Food_Corrupt: %d", &value);
            game->player->stuff.food_corrupt = value;
        }
        else if (strncmp(line, "Stuff_Spell_Health:", 19) == 0)
        {
            sscanf(line, "Stuff_Spell_Health: %d", &value);
            game->player->stuff.spell_health = value;
        }
        else if (strncmp(line, "Stuff_Spell_Speed:", 18) == 0)
        {
            sscanf(line, "Stuff_Spell_Speed: %d", &value);
            game->player->stuff.spell_speed = value;
        }
        else if (strncmp(line, "Stuff_Spell_Damage:", 19) == 0)
        {
            sscanf(line, "Stuff_Spell_Damage: %d", &value);
            game->player->stuff.spell_damage = value;
        }
        else if (strncmp(line, "Stuff_Weapon_Mace:", 18) == 0)
        {
            sscanf(line, "Stuff_Weapon_Mace: %d", &value);
            game->player->stuff.weapon_mace = value;
        }
        else if (strncmp(line, "Stuff_Weapon_Dagger:", 20) == 0)
        {
            sscanf(line, "Stuff_Weapon_Dagger: %d", &value);
            game->player->stuff.weapon_dagger = value;
        }
        else if (strncmp(line, "Stuff_Weapon_Wand:", 18) == 0)
        {
            sscanf(line, "Stuff_Weapon_Wand: %d", &value);
            game->player->stuff.weapon_wand = value;
        }
        else if (strncmp(line, "Stuff_Weapon_Arrow:", 19) == 0)
        {
            sscanf(line, "Stuff_Weapon_Arrow: %d", &value);
            game->player->stuff.weapon_arrow = value;
        }
        else if (strncmp(line, "Stuff_Weapon_Sword:", 19) == 0)
        {
            sscanf(line, "Stuff_Weapon_Sword: %d", &value);
            game->player->stuff.weapon_sword = value;
        }
        else if (strncmp(line, "Floors_Number:", 14) == 0)
        {
            // recovering Floors_number
            int floors;
            sscanf(line, "Floors_Number: %d", &floors);
            game->floors_number = floors;
            game->floors = (Floor **)malloc(sizeof(Floor *) * floors);
            break;
        }
    }

    game->floors = (Floor **)malloc(sizeof(Floor *) * game->floors_number);

    // recovering floors
    for (int i = 0; i < game->floors_number; i++)
    {
        // finding floor[i] in the file
        while (fgets(line, sizeof(line), fp))
        {
            int floor_index;
            if (sscanf(line, "Floor %d:", &floor_index) == 1)
            {
                if (floor_index == i)
                    break;
            }
        }

        game->floors[i] = (Floor *)malloc(sizeof(Floor) * game->floors_number);

        // recovering hallways information
        game->floors[i]->map = (bool ***)malloc(sizeof(bool **) * MAP_HEIGHT);
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            game->floors[i]->map[y] = (bool **)malloc(sizeof(bool *) * MAP_WIDTH);
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                game->floors[i]->map[y][x] = (bool *)malloc(sizeof(bool) * 2);

                // recovering is_hallway
                if (fgets(line, sizeof(line), fp))
                {
                    int yy, xx, layer, map_val;
                    sscanf(line, "Map[%d][%d].[%d] = %d", &yy, &xx, &layer, &map_val);
                    game->floors[i]->map[y][x][layer] = (map_val != 0);
                }

                // recovering is_seen
                if (fgets(line, sizeof(line), fp))
                {
                    int yy, xx, layer, map_val;
                    sscanf(line, "Map[%d][%d].[%d] = %d", &yy, &xx, &layer, &map_val);
                    game->floors[i]->map[y][x][layer] = (map_val != 0);
                }
            }
        }

        // recovering rooms number
        if (fgets(line, sizeof(line), fp))
        {
            int rooms;
            sscanf(line, "Rooms_Number: %d", &rooms);
            game->floors[i]->rooms_number = rooms;
            game->floors[i]->rooms = (Room **)malloc(sizeof(Room *) * rooms);
        }

        // recovering rooms
        for (int j = 0; j < game->floors[i]->rooms_number; j++)
        {
            // finding room[j]
            while (fgets(line, sizeof(line), fp))
            {
                int room_index;
                if (sscanf(line, "  Room %d:", &room_index) == 1)
                {
                    if (room_index == j)
                        break;
                }
            }
            game->floors[i]->rooms[j] = (Room *)malloc(sizeof(Room));

            if (fgets(line, sizeof(line), fp))
                sscanf(line, "    Start: %d %d", &game->floors[i]->rooms[j]->start.x, &game->floors[i]->rooms[j]->start.y);
            if (fgets(line, sizeof(line), fp))
                sscanf(line, "    Width: %d", &game->floors[i]->rooms[j]->width);
            if (fgets(line, sizeof(line), fp))
                sscanf(line, "    Height: %d", &game->floors[i]->rooms[j]->height);
            if (fgets(line, sizeof(line), fp))
                sscanf(line, "    Grid: %d", &game->floors[i]->rooms[j]->grid);
            if (fgets(line, sizeof(line), fp))
                sscanf(line, "    Type: %d", &game->floors[i]->rooms[j]->type);

            int temp;
            if (fgets(line, sizeof(line), fp))
                sscanf(line, "    IsSeen: %d", &temp);
            game->floors[i]->rooms[j]->isSeen = temp;

            // recovering doors
            if (fgets(line, sizeof(line), fp))
            {
                int doors_number;
                sscanf(line, "    Doors_Number: %d", &doors_number);
                game->floors[i]->rooms[j]->doors_number = doors_number;
                for (int d = 0; d < doors_number; d++)
                {
                    if (fgets(line, sizeof(line), fp))
                    {
                        int idx;
                        sscanf(line, "      Door %d: %d %d %d %d",
                               &idx,
                               &game->floors[i]->rooms[j]->doors[d].position.x,
                               &game->floors[i]->rooms[j]->doors[d].position.y,
                               &temp,
                               &game->floors[i]->rooms[j]->doors[d].type);

                        game->floors[i]->rooms[j]->doors[d].isConnected = temp;
                    }
                }
            }
            // recovering windows
            if (fgets(line, sizeof(line), fp))
            {
                int windows_number;
                sscanf(line, "    Windows_Number: %d", &windows_number);
                game->floors[i]->rooms[j]->windows_number = windows_number;
                for (int w = 0; w < windows_number; w++)
                {
                    if (fgets(line, sizeof(line), fp))
                    {
                        int idx;
                        sscanf(line, "      Window %d: %d %d %d",
                               &idx,
                               &game->floors[i]->rooms[j]->windows[w].position.x,
                               &game->floors[i]->rooms[j]->windows[w].position.y,
                               &game->floors[i]->rooms[j]->windows[w].side);
                    }
                }
            }
            // recovering stairs
            if (fgets(line, sizeof(line), fp))
            {
                sscanf(line, "    Stair: %d %d %d %d %d",
                       &temp,
                       &game->floors[i]->rooms[j]->stairs.position.x,
                       &game->floors[i]->rooms[j]->stairs.position.y,
                       &game->floors[i]->rooms[j]->stairs.previous_floor,
                       &game->floors[i]->rooms[j]->stairs.next_floor);
                game->floors[i]->rooms[j]->stairs.has_stairs = temp;
            }

            // recovering reserved positions
            if (fgets(line, sizeof(line), fp))
            {
                int reserved_number;
                sscanf(line, "    Reserved_Number: %d", &reserved_number);
                game->floors[i]->rooms[j]->reserved_number = reserved_number;
                if (reserved_number > 0)
                {
                    game->floors[i]->rooms[j]->reserved_poitions = (Position *)malloc(sizeof(Position) * reserved_number);
                    for (int r = 0; r < reserved_number; r++)
                    {
                        if (fgets(line, sizeof(line), fp))
                        {
                            int idx;
                            sscanf(line, "      Reserved %d: %d %d", &idx, &game->floors[i]->rooms[j]->reserved_poitions[r].x, &game->floors[i]->rooms[j]->reserved_poitions[r].y);
                        }
                    }
                }
            }
            // recovering golds
            if (fgets(line, sizeof(line), fp))
            {
                int golds_number;
                sscanf(line, "    Golds_Number: %d", &golds_number);
                game->floors[i]->rooms[j]->golds_number = golds_number;
                if (golds_number > 0)
                {
                    game->floors[i]->rooms[j]->golds = (Gold *)malloc(sizeof(Gold) * golds_number);
                    for (int g = 0; g < golds_number; g++)
                    {
                        if (fgets(line, sizeof(line), fp))
                        {
                            int idx;
                            sscanf(line, "      Gold %d: %d %d %d", &idx, &game->floors[i]->rooms[j]->golds[g].position.x, &game->floors[i]->rooms[j]->golds[g].position.y, &game->floors[i]->rooms[j]->golds[g].type);
                        }
                    }
                }
            }
            // recovering foods
            if (fgets(line, sizeof(line), fp))
            {
                int foods_number;
                sscanf(line, "    Foods_Number: %d", &foods_number);
                game->floors[i]->rooms[j]->foods_number = foods_number;
                if (foods_number > 0)
                {
                    game->floors[i]->rooms[j]->foods = (Food *)malloc(sizeof(Food) * foods_number);
                    for (int f = 0; f < foods_number; f++)
                    {
                        if (fgets(line, sizeof(line), fp))
                        {
                            int idx;
                            sscanf(line, "      Food %d: %d %d %d", &idx, &game->floors[i]->rooms[j]->foods[f].position.x, &game->floors[i]->rooms[j]->foods[f].position.y, &game->floors[i]->rooms[j]->foods[f].type);
                        }
                    }
                }
            }
            // recovering spells
            if (fgets(line, sizeof(line), fp))
            {
                int spells_number;
                sscanf(line, "    Spells_Number: %d", &spells_number);
                game->floors[i]->rooms[j]->spells_number = spells_number;
                if (spells_number > 0)
                {
                    game->floors[i]->rooms[j]->spells = (Spell *)malloc(sizeof(Spell) * spells_number);
                    for (int s = 0; s < spells_number; s++)
                    {
                        if (fgets(line, sizeof(line), fp))
                        {
                            int idx;
                            sscanf(line, "      Spell %d: %d %d %d", &idx, &game->floors[i]->rooms[j]->spells[s].position.x, &game->floors[i]->rooms[j]->spells[s].position.y, &game->floors[i]->rooms[j]->spells[s].type);
                        }
                    }
                }
            }
            // recovering weapons
            if (fgets(line, sizeof(line), fp))
            {
                int weapons_number;
                sscanf(line, "    Weapons_Number: %d", &weapons_number);
                game->floors[i]->rooms[j]->weapons_number = weapons_number;
                if (weapons_number > 0)
                {
                    game->floors[i]->rooms[j]->weapons = (Weapon *)malloc(sizeof(Weapon) * weapons_number);
                    for (int wpn = 0; wpn < weapons_number; wpn++)
                    {
                        if (fgets(line, sizeof(line), fp))
                        {
                            int idx;
                            sscanf(line, "      Weapon %d: %d %d %d", &idx, &game->floors[i]->rooms[j]->weapons[wpn].position.x, &game->floors[i]->rooms[j]->weapons[wpn].position.y, &game->floors[i]->rooms[j]->weapons[wpn].type);
                        }
                    }
                }
            }
            // recovering traps
            if (fgets(line, sizeof(line), fp))
            {
                int traps_number;
                sscanf(line, "    Traps_Number: %d", &traps_number);
                game->floors[i]->rooms[j]->traps_number = traps_number;
                if (traps_number > 0)
                {
                    game->floors[i]->rooms[j]->traps_position = (Position *)malloc(sizeof(Position) * traps_number);
                    for (int t = 0; t < traps_number; t++)
                    {
                        if (fgets(line, sizeof(line), fp))
                        {
                            int idx;
                            sscanf(line, "      Trap %d: %d %d", &idx, &game->floors[i]->rooms[j]->traps_position[t].x, &game->floors[i]->rooms[j]->traps_position[t].y);
                        }
                    }
                }
            }
            // recovering monsters
            if (fgets(line, sizeof(line), fp))
            {
                int monsters_number;
                sscanf(line, "    Monsters_Number: %d", &monsters_number);
                game->floors[i]->rooms[j]->monsters_number = monsters_number;
                if (monsters_number > 0)
                {
                    game->floors[i]->rooms[j]->monsters =(Monster **) malloc(sizeof(Monster *) * monsters_number);
                    for (int m = 0; m < monsters_number; m++)
                    {
                        if (fgets(line, sizeof(line), fp))
                        {
                            game->floors[i]->rooms[j]->monsters[m] = (Monster *)malloc(sizeof(Monster));
                            int idx;
                            sscanf(line, "      Monster %d: %d %d %d %d %d %d",
                                   &idx,
                                   &game->floors[i]->rooms[j]->monsters[m]->monster_type,
                                   &game->floors[i]->rooms[j]->monsters[m]->moving_type,
                                   &game->floors[i]->rooms[j]->monsters[m]->damage,
                                   &game->floors[i]->rooms[j]->monsters[m]->health,
                                   &game->floors[i]->rooms[j]->monsters[m]->position.x,
                                   &game->floors[i]->rooms[j]->monsters[m]->position.y);
                        }
                    }
                }
            }
        }
    }

    // if the END_GAME was reached, stop reading the file
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, "END_GAME"))
            break;
    }

    fclose(fp);
    return true;
}

void resume_game(char *username, int color)
{
    Game *game = (Game *)malloc(sizeof(Game));

    if (!recover_information(game, username))
    {
        clear();
        show_alert_message(15, 48, "YOU DON'T HAVE ANY UNFINISHED GAMES!", 2);
        return;
    }

    while (1)
    {
        clear();
        status_bar(game->player);
        show_message(game->player->message);

        draw_map(game->floors[game->player->current_floor]->rooms,
                 game->floors[game->player->current_floor]->rooms_number,
                 game->floors[game->player->current_floor]->map,
                 game->player->current_floor);

        show_next_step(game->floors[game->player->current_floor]->rooms,
                       game->player,
                       game->floors[game->player->current_floor]->rooms_number,
                       game->floors[game->player->current_floor]->map);

        if (!player_update(game->floors,
                           game->floors[game->player->current_floor]->rooms,
                           game->floors[game->player->current_floor]->rooms_number,
                           game->player,
                           color))
        {
            save_game(game, username);
            break;
        }

        if (check_status(game->player, game->floors) != NOTHING)
        {
            update_score(username, game->player->gold * 175, game->player->gold, 1, 0);
            break;
        }

        refresh();
    }
}