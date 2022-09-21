#include "include/bmp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BMP_DATA* bmp_read_data(const char* file)
{
    FILE* input_image = fopen(file, "rb");

    if(input_image == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }

    BMP_DATA* bmp_data = (BMP_DATA*) malloc(sizeof(BMP_DATA));

    fseek(input_image, 2, SEEK_SET);

    fread(&bmp_data->header, 1, 52, input_image);

    fseek(input_image, 0, SEEK_SET);

    fread(&bmp_data->header.signature, 1, 2, input_image);

    fseek(input_image, bmp_data->header.dataoffset, SEEK_SET);

    if(bmp_data->header.bits_per_pixel != 24)
    {
        printf("Only 24 bitcount / 8 bit suported, please use bgr24\n");
        return NULL;
    }

    bmp_data->data = (uint8_t*) malloc(bmp_data->header.imagesize);

    fread(bmp_data->data, 1, bmp_data->header.imagesize, input_image);

    fclose(input_image);

    return bmp_data;
}