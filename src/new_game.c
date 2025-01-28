#include "new_game.h"
#include "player.h"
#include "map.h"
#include <stdlib.h>
#include <ncurses.h>

Room **rooms;
Player *player;
int rooms_number;

void new_game()
{
    rooms = map_setup(&rooms_number);
    player = player_setup(rooms, rooms_number);

    while (1)
    {
        clear();
        draw_map(rooms, rooms_number);
        show_next(rooms, player, rooms_number);
        player_update(rooms, rooms_number, player);
        refresh();
    }
    
}