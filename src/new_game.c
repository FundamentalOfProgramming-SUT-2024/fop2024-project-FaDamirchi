#include "new_game.h"
#include "global_defines.h"
#include "player.h"
#include "map.h"

void new_game(int level, int color)
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
        show_status(newGame->player);
        show_message(newGame->player->message);

        draw_map(newGame->floors[newGame->player->current_floor]->rooms,
                 newGame->floors[newGame->player->current_floor]->rooms_number,
                 newGame->floors[newGame->player->current_floor]->map,
                 newGame->player->current_floor);

        show_next_step(newGame->floors[newGame->player->current_floor]->rooms,
                       newGame->player,
                       newGame->floors[newGame->player->current_floor]->rooms_number,
                       newGame->floors[newGame->player->current_floor]->map);

        player_update(newGame->floors,
                      newGame->floors[newGame->player->current_floor]->rooms,
                      newGame->floors[newGame->player->current_floor]->rooms_number,
                      newGame->player,
                      color);

        refresh();
    }
}