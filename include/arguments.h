#pragma once

#include "string-util.h"

#include <stdint.h>

typedef struct ARGUMENTS_S
{
    STRING input;
    STRING output;

    uint32_t play;
    double fps;
    STRING color_palete;
    uint32_t clear_console;

    uint32_t threads;

    uint32_t verbose;
} ARGUMENTS;

ARGUMENTS parseArguments(int argc, const char** argv);