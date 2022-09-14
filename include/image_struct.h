#pragma once

// if you dont like #pragma once other method is using #ifndef and #define, but #pragma is ok

// #ifndef _IMAGE_STRUCT_H_
// #define _IMAGE_STRUCT_H_

typedef struct rgb_struct
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
} rgb;


typedef struct image_struct
{
    unsigned int width;
    unsigned int height;
    rgb* pixels;
} image;

// #endif