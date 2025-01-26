#include "new_game.h"
#include "map.h"
#include "player.h"
#include <stdlib.h>
#include <ncurses.h>

Room **rooms;
Player *player;
int rooms_number;

void start_game()
{
    rooms = map_setup(&rooms_number);
    player = player_setup(rooms, rooms_number);

    while (1)
    {
        clear();
        draw_room(rooms, rooms_number);
        player_update(player);
        refresh();
    }
    
}