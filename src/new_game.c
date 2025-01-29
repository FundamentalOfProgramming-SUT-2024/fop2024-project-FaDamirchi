#include "new_game.h"
#include "global_defines.h"
#include "player.h"
#include "map.h"

void new_game()
{
    srand(time(NULL));

    Game *newGame = (Game *)malloc(sizeof(Game));

    newGame->floors_number = 1 + rand() % 5;
    newGame->floors = (Floor **)malloc(sizeof(Floor *) * newGame->floors_number);

    for (int i = 0; i < newGame->floors_number; i++)
    {
        newGame->floors[i] = (Floor *)malloc(sizeof(Floor));
        newGame->floors[i]->rooms_number = 6 + rand() % 5;

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

    newGame->player = player_setup(newGame->floors[0]->rooms, newGame->floors[0]->rooms_number);

    while (1)
    {
        clear();
        draw_map(newGame->floors[0]->rooms, newGame->floors[0]->rooms_number, newGame->floors[0]->map);
        show_next_step(newGame->floors[0]->rooms, newGame->player, newGame->floors[0]->rooms_number, newGame->floors[0]->map);
        player_update(newGame->floors[0]->rooms, newGame->floors[0]->rooms_number, newGame->player);
        refresh();
    }
}