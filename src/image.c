#include "include/image.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


IMAGE* bmp_data_to_image(BMP_DATA* bmp_data)
{
    IMAGE* img = (IMAGE*) malloc(sizeof(IMAGE));

    img->header = bmp_data->header;

    img->pixels = (RGB*) malloc((img->header.width * img->header.height) * sizeof(RGB));

    uint32_t padding = img->header.width - ((img->header.width / 4) * 4);

    uint32_t width_count = 0;

    uint32_t normal_count = 0;

    for (uint32_t i = 0; i < img->header.imagesize;)
    {
        width_count++;

        if(width_count <= img->header.width) // this is like the second loop in the first loop
        {
            RGB pixel;

            pixel.b = bmp_data->data[i++];
            pixel.g = bmp_data->data[i++];
            pixel.r = bmp_data->data[i++];

            img->pixels[normal_count++] = pixel;
        }
        else
        {
            i += padding;
            width_count = 0;
        }
    }

    return img;
}

IMAGE* image_invert(IMAGE* img)
{
    IMAGE* new_img = (IMAGE*) malloc(sizeof(IMAGE));

    new_img->header = img->header;
    
    new_img->pixels = (RGB*) malloc((img->header.width * img->header.height) * sizeof(RGB));



    uint32_t normal_count = 0;

    for(int32_t row = img->header.height - 1; row >= 0; row--)
    {
        for(uint32_t col = 0; col < img->header.width; col++)
        {
            uint32_t pos = (row * img->header.width) + col;

            RGB pixel = img->pixels[pos];
            
            new_img->pixels[normal_count++] = pixel;
        }
    }

    return new_img;
}

void image_to_char_file(IMAGE* img, const char* output)
{
    FILE* result = fopen(output, "w");

    char* img_char = image_to_char(img);

    for (long i = 0; img_char[i] != '\0'; i++)
    {
        fwrite(&img_char[i], sizeof(char), 1, result);
    }
    
    fclose(result);

    return;
}

char* image_to_char(IMAGE* img)
{
    uint32_t size = img->header.width * img->header.height;

    char* result = (char*) malloc(size + img->header.height);

    uint32_t width_count = 0;

    uint32_t result_count = 0;

    for (uint32_t i = 0; i <= img->header.width * img->header.height; result_count++)
    {
        width_count++;
        
        if(width_count <= img->header.width)
        {
            RGB pixel = img->pixels[i++];

            uint8_t avg = (pixel.r + pixel.g + pixel.b) / 3;

            if(avg < 85)
            {
                result[result_count] = ' ';
            } 
            else if(avg > 85 && avg < 170)
            {
                result[result_count] = '/';
            }
            else
            {
                result[result_count] = '#';
            }
        }
        else
        {
            result[result_count] = '\n';
            width_count = 0;
        }
    }

    result[size + img->header.height - 1] = '\0';

    return result;
}