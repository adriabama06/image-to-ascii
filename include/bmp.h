#pragma once

#include <stdint.h>

typedef struct BMP_HEADER_STRUCT
{
    uint32_t filesize;
    uint32_t reserved;
    uint32_t dataoffset;

    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t imagesize;
    uint32_t y_pixels_per_m;
    uint32_t x_pixels_per_m;
    uint32_t colors_used;
    uint32_t important_colors;

    uint8_t signature[2];
} BMP_HEADER;

typedef struct BMP_DATA_STRUCT
{
    BMP_HEADER header;
    uint8_t* data;
} BMP_DATA;

BMP_DATA* bmp_read_data(const char*);
