#include "include/bmp.h"

#include "include/image_struct.h"

#include <stdio.h>

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Write input file\n");
        return -1;
    }

    image* img = bmp_read(argv[1]);

    unsigned int size = img->width * img->height;

    for (unsigned int i = 0; i < size; i++)
    {
        rgb pixel = img->pixels[i];
        printf("rgb(%d, %d, %d)\n", pixel.r, pixel.g, pixel.b);
    }

    printf("Basic image data of '%s': %dx%d resolution - %d size\n", argv[1], img->width, img->height, (img->width * 3) * img->height);

    return 0;
}