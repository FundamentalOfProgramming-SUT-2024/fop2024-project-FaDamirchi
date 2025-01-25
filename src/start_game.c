#include "start_game.h"
#include "map.h"
#include <stdlib.h>
#include <ncurses.h>

void start_game()
{
    clear();
    map_setup();
    getch();
}