#include "include/bmp.h"

#include "include/image_struct.h"

#include <stdio.h>
#include <stdlib.h>

image* bmp_read(const char* file_path)
{
    FILE* input_image = fopen(file_path, "rb");

    char info[54] = { 0 };

    fread(info, 1, 54, input_image);

    int width = *(int*) (info + 18);
    int height = *(int*) (info + 22);
    int bitcount = *(int*) (info + 28);
    int size = (width * height) * 3;

    if(bitcount != 24)
    {
        perror("Error: color depth can only be 24 (8bit per color)");
        exit(0);
    }

    unsigned char* data = (unsigned char*) malloc(size);

    fread(data, 1, size, input_image);

    image* img = (image*) malloc(sizeof(image));

    img->width = width;
    img->height = height;

    img->pixels = (rgb*) malloc((img->width * img->height) * sizeof(rgb));

    int normal_count = 0;
    for(int row = height - 1; row >= 0; row--) // the rows is reverse or something ¿? mind break
    {
        for(int col = 0; col < width; col++)
        {
            int pos = ((row * width) + col) * 3;
            
            /*
            bmp work with BGR, i know the order to do BGR 2 RGB, easy:
            
            B G R
            0 1 2
            ----- <- conversion
            R G B
            2 1 0

            but in this case cause is struct i can put how i like and read easy
            */

           rgb pixel;
           pixel.b = data[pos];
           pixel.g = data[pos + 1];
           pixel.r = data[pos + 2];

           img->pixels[normal_count++] = pixel;

           // can i do normal_count and after do normal_count += 1, how you like, but how is now is ok
        }
    }

    fclose(input_image); // bye i don't need you

    free(data); // clear memory, data is not necessary because is now in img as rgb pixel

    return img;
}