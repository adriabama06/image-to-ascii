#pragma once

#include <stdint.h>

typedef struct STRING_S
{
    char* data;
    uint32_t length;
} STRING;

STRING string_from(const char*);

typedef struct STRING_ARRAY_S
{
    STRING* strings;
    uint32_t length;
} STRING_ARRAY;

void free_string_array(STRING_ARRAY);

int endsWith(char*, char*);

void sort_by_aplhabet(STRING_ARRAY);