#pragma once

#include <stdio.h>
#include <stdint.h>

// http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
typedef struct BITMAP_HEADER_FILE_S
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

    uint8_t signature[2]; // <-- this in theory need to go at the start, but for the padding this cause problems, see "test/padding.c"
} BITMAP_HEADER_FILE;

typedef struct RGB_S {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;

typedef struct BITMAP_S {
    BITMAP_HEADER_FILE header;
    RGB* pixels;
} BITMAP;

int bitmap_decode(FILE*, BITMAP*);