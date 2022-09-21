#pragma once

// if you dont like #pragma once other method is using #ifndef and #define, but #pragma is ok

#include "include/bmp.h"

// #ifndef _IMAGE_STRUCT_H_
// #define _IMAGE_STRUCT_H_

typedef struct RGB_STRUCT
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB;


typedef struct IMAGE_STRUCT
{
    BMP_HEADER header;
    RGB* pixels;
} IMAGE;

IMAGE* bmp_data_to_image(BMP_DATA*);

IMAGE* image_invert(IMAGE*);

void image_to_char_file(IMAGE*, const char*);

char* image_to_char(IMAGE*);

// #endif