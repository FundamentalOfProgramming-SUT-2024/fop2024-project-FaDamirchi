#include "new_game.h"
#include "global_defines.h"
#include "player.h"
#include "map.h"
#include "manage_users.h"

void save_game(Game *game, char *username)
{
    FILE *fp = fopen(SAVED_GAMES_FILE, "a");

    // saving username
    fprintf(fp, "USERNAME: %s\n", username);

    // saving player information
    if (game->player)
    {
        fprintf(fp, "Player_Position: %d %d\n", game->player->position.x, game->player->position.y);
        fprintf(fp, "Player_Current_Floor: %d\n", game->player->current_floor);
        fprintf(fp, "Player_Passed_Blockes: %d\n", game->player->passed_blockes);
        fprintf(fp, "Player_Gold: %d\n", game->player->gold);
        fprintf(fp, "Player_Health: %d\n", game->player->health);

        // saving collected stuff
        fprintf(fp, "Stuff_Food_Ordinary: %d\n", game->player->stuff.food_ordinary);
        fprintf(fp, "Stuff_Food_Excellent: %d\n", game->player->stuff.food_excellent);
        fprintf(fp, "Stuff_Food_Magic: %d\n", game->player->stuff.food_magic);
        fprintf(fp, "Stuff_Food_Corrupt: %d\n", game->player->stuff.food_corrupt);

        fprintf(fp, "Stuff_Spell_Health: %d\n", game->player->stuff.spell_health);
        fprintf(fp, "Stuff_Spell_Speed: %d\n", game->player->stuff.spell_speed);
        fprintf(fp, "Stuff_Spell_Damage: %d\n", game->player->stuff.spell_damage);

        fprintf(fp, "Stuff_Weapon_Mace: %d\n", game->player->stuff.weapon_mace);
        fprintf(fp, "Stuff_Weapon_Dagger: %d\n", game->player->stuff.weapon_dagger);
        fprintf(fp, "Stuff_Weapon_Wand: %d\n", game->player->stuff.weapon_wand);
        fprintf(fp, "Stuff_Weapon_Arrow: %d\n", game->player->stuff.weapon_arrow);
        fprintf(fp, "Stuff_Weapon_Sword: %d\n", game->player->stuff.weapon_sword);
    }

    // saving floors information
    fprintf(fp, "Floors_Number: %d\n", game->floors_number);

    for (int i = 0; i < game->floors_number; i++)
    {
        Floor *floor = game->floors[i];
        fprintf(fp, "Floor %d:\n", i);

        // saving hallways information
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            for (int x = 0; x < MAP_WIDTH; x++)
            {
                fprintf(fp, "Map[%d][%d].[0] = %d\n", y, x, floor->map[y][x][0]);
                fprintf(fp, "Map[%d][%d].[1] = %d\n", y, x, floor->map[y][x][1]);
            }
        }

        // saving rooms information
        fprintf(fp, "Rooms_Number: %d\n", floor->rooms_number);
        for (int j = 0; j < floor->rooms_number; j++)
        {
            Room *room = floor->rooms[j];
            fprintf(fp, "  Room %d:\n", j);
            fprintf(fp, "    Start: %d %d\n", room->start.x, room->start.y);
            fprintf(fp, "    Width: %d\n", room->width);
            fprintf(fp, "    Height: %d\n", room->height);
            fprintf(fp, "    Grid: %d\n", room->grid);
            fprintf(fp, "    Type: %d\n", room->type);
            fprintf(fp, "    IsSeen: %d\n", room->isSeen);

            // saving doors
            fprintf(fp, "    Doors_Number: %d\n", room->doors_number);
            for (int d = 0; d < room->doors_number; d++)
            {
                Door door = room->doors[d];
                fprintf(fp, "      Door %d: %d %d %d %d\n",
                        d,
                        door.position.x,
                        door.position.y,
                        door.isConnected,
                        door.type);
            }

            // saving windows
            fprintf(fp, "    Windows_Number: %d\n", room->windows_number);
            for (int w = 0; w < room->windows_number; w++)
            {
                Window window = room->windows[w];
                fprintf(fp, "      Window %d: %d %d %d\n",
                        w,
                        window.position.x,
                        window.position.y,
                        window.side);
            }

            // saving stairs
            fprintf(fp, "    Stair: %d %d %d %d %d\n",
                    room->stairs.has_stairs,
                    room->stairs.position.x,
                    room->stairs.position.y,
                    room->stairs.previous_floor,
                    room->stairs.next_floor);

            // saving reserved positions
            fprintf(fp, "    Reserved_Number: %d\n", room->reserved_number);
            for (int r = 0; r < room->reserved_number; r++)
            {
                Position pos = room->reserved_poitions[r];
                fprintf(fp, "      Reserved %d: %d %d\n", r, pos.x, pos.y);
            }

            // saving golds
            fprintf(fp, "    Golds_Number: %d\n", room->golds_number);
            for (int g = 0; g < room->golds_number; g++)
            {
                Gold gold = room->golds[g];
                fprintf(fp, "      Gold %d: %d %d %d\n",
                        g, gold.position.x, gold.position.y, gold.type);
            }

            // saving foods
            fprintf(fp, "    Foods_Number: %d\n", room->foods_number);
            for (int f = 0; f < room->foods_number; f++)
            {
                Food food = room->foods[f];
                fprintf(fp, "      Food %d: %d %d %d\n",
                        f, food.position.x, food.position.y, food.type);
            }

            // saving spells
            fprintf(fp, "    Spells_Number: %d\n", room->spells_number);
            for (int s = 0; s < room->spells_number; s++)
            {
                Spell spell = room->spells[s];
                fprintf(fp, "      Spell %d: %d %d %d\n",
                        s, spell.position.x, spell.position.y, spell.type);
            }

            // saving weapons
            fprintf(fp, "    Weapons_Number: %d\n", room->weapons_number);
            for (int wpn = 0; wpn < room->weapons_number; wpn++)
            {
                Weapon weapon = room->weapons[wpn];
                fprintf(fp, "      Weapon %d: %d %d %d\n",
                        wpn, weapon.position.x, weapon.position.y, weapon.type);
            }

            // saving traps
            fprintf(fp, "    Traps_Number: %d\n", room->traps_number);
            for (int t = 0; t < room->traps_number; t++)
            {
                Position pos = room->traps_position[t];
                fprintf(fp, "      Trap %d: %d %d\n", t, pos.x, pos.y);
            }

            // saving monsters
            fprintf(fp, "    Monsters_Number: %d\n", room->monsters_number);
            for (int m = 0; m < room->monsters_number; m++)
            {
                Monster *monster = room->monsters[m];
                fprintf(fp, "      Monster %d: %d %d %d %d %d %d\n",
                        m,
                        monster->monster_type,
                        monster->moving_type,
                        monster->damage,
                        monster->health,
                        monster->position.x,
                        monster->position.y);
            }
        }
    }

    fprintf(fp, "END_GAME\n\n");
    fclose(fp);
}

void new_game(char * username, int level, int color)
{
    srand(time(NULL));

    Game *newGame = (Game *)malloc(sizeof(Game));

    // generating random number of floors based on the level
    if (level == 3)
    {
        newGame->floors_number = 5;
    }
    else if (level == 2)
    {
        newGame->floors_number = 4 + rand() % 2;
    }
    else if (level == 1)
    {
        newGame->floors_number = 4;
    }

    newGame->floors = (Floor **)malloc(sizeof(Floor *) * newGame->floors_number);

    // generating random map for each floor
    for (int i = 0; i < newGame->floors_number; i++)
    {
        newGame->floors[i] = (Floor *)malloc(sizeof(Floor));

        // generating random number of rooms based on the level
        switch (level)
        {
        case 1: // easy
            newGame->floors[i]->rooms_number = 6 + rand() % 2;
            break;
        case 2: // medium
            newGame->floors[i]->rooms_number = 7 + rand() % 2;
            break;
        case 3: // hard
            newGame->floors[i]->rooms_number = 9 + rand() % 2;
            break;

        default:
            break;
        }

        // initializing the map array to hold the hallways for each floor
        newGame->floors[i]->map = (bool ***)malloc(40 * sizeof(bool **));
        for (int j = 0; j < 40; j++)
        {
            newGame->floors[i]->map[j] = (bool **)malloc(130 * sizeof(bool *));
            for (int k = 0; k < 130; k++)
            {
                newGame->floors[i]->map[j][k] = (bool *)malloc(2 * sizeof(bool));
            }
        }

        // initializing every floor according to its place
        if (i == 0) // first floor only has a GOING stairs
        {
            newGame->floors[i]->rooms = map_setup(newGame->floors[i]->rooms_number,
                                                  newGame->floors[i]->map,
                                                  NULL,
                                                  false,
                                                  i);
        }
        else if (i == newGame->floors_number - 1) // last floor only a COMING stairs
        {
            for (int j = 0; j < newGame->floors[i - 1]->rooms_number; j++)
            {
                if (newGame->floors[i - 1]->rooms[j]->stairs.has_stairs &&
                    newGame->floors[i - 1]->rooms[j]->stairs.previous_floor == i - 1)
                {
                    newGame->floors[i]->rooms = map_setup(newGame->floors[i]->rooms_number,
                                                          newGame->floors[i]->map,
                                                          newGame->floors[i - 1]->rooms[j],
                                                          true,
                                                          i);
                }
            }
        }
        else // other floors have both stairs
        {
            for (int j = 0; j < newGame->floors[i - 1]->rooms_number; j++)
            {
                if (newGame->floors[i - 1]->rooms[j]->stairs.has_stairs &&
                    newGame->floors[i - 1]->rooms[j]->stairs.previous_floor == i - 1)
                {
                    newGame->floors[i]->rooms = map_setup(newGame->floors[i]->rooms_number,
                                                          newGame->floors[i]->map,
                                                          newGame->floors[i - 1]->rooms[j],
                                                          false,
                                                          i);
                }
            }
        }
    }

    complete_map(newGame->floors, newGame->floors_number, level);

    newGame->player = player_setup(newGame->floors[0]->rooms,
                                   newGame->floors[0]->rooms_number);

    while (1)
    {
        clear();
        status_bar(newGame->player);
        show_message(newGame->player->message);

        draw_map(newGame->floors[newGame->player->current_floor]->rooms,
                 newGame->floors[newGame->player->current_floor]->rooms_number,
                 newGame->floors[newGame->player->current_floor]->map,
                 newGame->player->current_floor);

        show_next_step(newGame->floors[newGame->player->current_floor]->rooms,
                       newGame->player,
                       newGame->floors[newGame->player->current_floor]->rooms_number,
                       newGame->floors[newGame->player->current_floor]->map);

        if(!player_update(newGame->floors,
                      newGame->floors[newGame->player->current_floor]->rooms,
                      newGame->floors[newGame->player->current_floor]->rooms_number,
                      newGame->player,
                      color))
        {
            save_game(newGame, username);
            break;
        }

        if (check_status(newGame->player, newGame->floors) != NOTHING)
        {
            break;
        }

        refresh();
    }
}