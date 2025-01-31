#include "music.h"
#include "global_defines.h"

void play_music(int music)
{
    if (music == 1)
    {
        system("mpg123 --loop -1 -q music/TheLastOfUs.mp3 >/dev/null 2>&1 &");
    }
}

void stop_music()
{
    system("killall mpg123 >/dev/null 2>&1");
}