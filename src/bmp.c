#include "include/bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bmp_data* bmp_read(const char* file)
{
    FILE* input_image = fopen(file, "rb");

    char info[54] = { 0 };

    fread(info, 1, 54, input_image);

    int width = *(int*) (info + 18);
    int height = *(int*) (info + 22);
    int bitcount = *(int*) (info + 28);
    int size = (width * height) * 3;

    if(bitcount != 24)
    {
        perror("Error: color depth can only be 24 (8bit per color)");
        return NULL;
    }

    bmp_data* bd = (bmp_data*) malloc(sizeof(bmp_data));

    bd->width = width;
    bd->height = height;
    bd->bitcount = bitcount;
    bd->size = size;

    bd->data = (unsigned char*) malloc(size);

    fread(bd->data, 1, size, input_image);

    fclose(input_image); // bye i don't need you

    //free(data); // clear memory, data is not necessary because is now in img as rgb pixel

    return bd;
}