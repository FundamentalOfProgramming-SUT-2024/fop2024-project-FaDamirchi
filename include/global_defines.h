// This file is written for ease of access to practical definitions

#ifndef GLOBAL_DEFINES
#define GLOBAL_DEFINES

// includes
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "ui_utils.h"

// objects
typedef struct Position
{
    int x;
    int y;
} Position;

// characters
#define ENTER 10

#endif