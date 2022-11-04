#pragma once

#include "include/bitmap.h"

#define DEFAULT_CHAR_PALETTE " .,-~:=#$@"

typedef struct CHAR_ARRAY_S
{
    char* data;
    uint32_t length;
} CHAR_ARRAY;

CHAR_ARRAY image2ascii(BITMAP, char*);