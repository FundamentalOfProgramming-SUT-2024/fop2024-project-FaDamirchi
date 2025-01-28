#include "new_game.h"
#include "global_defines.h"
#include "player.h"
#include "map.h"

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
        show_next_step(rooms, player, rooms_number);
        player_update(rooms, rooms_number, player);
        refresh();
    }
    
}