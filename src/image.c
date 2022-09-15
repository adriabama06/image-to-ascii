#include "include/image.h"

#include <stdlib.h>

image* bmp_data2image(bmp_data* bmp)
{
    image* img = (image*) malloc(sizeof(image));

    img->width = bmp->width;
    img->height = bmp->height;

    img->pixels = (rgb*) malloc((img->width * img->height) * sizeof(rgb));

    int normal_count = 0;
    for(int row = img->height - 1; row >= 0; row--) // the rows is reverse or something ¿? mind break
    {
        for(int col = 0; col < img->width; col++)
        {
            int pos = ((row * img->width) + col) * 3;
            
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
           pixel.b = bmp->data[pos];
           pixel.g = bmp->data[pos + 1];
           pixel.r = bmp->data[pos + 2];

           img->pixels[normal_count++] = pixel;

           // can i do normal_count and after do normal_count += 1, how you like, but how is now is ok
        }
    }

    return img;
}

image* get_image(const char* file)
{
    bmp_data* bmp_d = bmp_read(file);

    image* img = bmp_data2image(bmp_d);

    free(bmp_d);

    return img;
}