#pragma once

typedef struct bmp_data_struct
{
    int width;
    int height;
    int bitcount;
    int size;

    unsigned char* data;
} bmp_data;


bmp_data* bmp_read(const char*);