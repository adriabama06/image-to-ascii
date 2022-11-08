#pragma once

#include "include/bitmap.h"

#include "include/string-util.h"

#define DEFAULT_CHAR_PALETTE " .,-~:=$#@"

STRING image2ascii(BITMAP, char*);