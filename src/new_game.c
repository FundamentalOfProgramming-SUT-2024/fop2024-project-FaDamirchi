#include "new_game.h"
#include "global_defines.h"
#include "player.h"
#include "map.h"

void new_game(int level, int color, int music)
{
    Game *newGame = (Game *)malloc(sizeof(Game));

    // generating random number of floors based on the level
    switch (level)
    {
    case 1: // easy
        newGame->floors_number = 2;
        break;
    case 2: // medium
        newGame->floors_number = 3 + rand() % 2;
        break;
    case 3: // hard
        newGame->floors_number = 4 + rand() % 2;
        break;

    default:
        break;
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

        newGame->floors[i]->rooms = map_setup(newGame->floors[i]->rooms_number, newGame->floors[i]->map);
    }

    newGame->player = player_setup(newGame->floors[0], newGame->floors[0]->rooms, newGame->floors[0]->rooms_number);

    while (1)
    {
        clear();
        draw_map(newGame->floors[0]->rooms, newGame->floors[0]->rooms_number, newGame->floors[0]->map);
        show_next_step(newGame->floors[0]->rooms, newGame->player, newGame->floors[0]->rooms_number, newGame->floors[0]->map);
        player_update(newGame->floors[0]->rooms, newGame->floors[0]->rooms_number, newGame->player, color);
        refresh();
    }
}