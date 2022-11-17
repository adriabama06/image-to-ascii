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

int endsWith(char*, char*);

char* get_filename(char*);

char* get_extension(char*);

void sort_by_aplhabet(STRING_ARRAY);