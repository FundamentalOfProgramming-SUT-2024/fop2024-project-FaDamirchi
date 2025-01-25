// This file is written for ease of access to practical definitions

#ifndef GLOBAL_DEFINES
#define GLOBAL_DEFINES

// includes
#include <stdbool.h>

// objects
typedef struct
{
    int x;
    int y;
} Position;

// characters
#define ENTER 10
#define IS_YES(c) ((c) == 'y' || (c) == 'Y')
#define IS_NO (c) ((c) == 'n' || (c) == 'N')

#endif