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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Write input file\n");
        return -1;
    }

    image* img = (image*) malloc(sizeof(image));


    FILE* file_to_read = fopen(argv[1], "rb");

    
    fread(&img->width, sizeof(unsigned int), 1, file_to_read);
    fread(&img->height, sizeof(unsigned int), 1, file_to_read);


    unsigned long pixels_len;
    fread(&pixels_len, sizeof(unsigned long), 1, file_to_read);


    img->pixels = (rgb*) malloc(pixels_len); 
    fread(img->pixels, pixels_len, 1, file_to_read);

    
    fclose(file_to_read);


    unsigned long size = img->width * img->height;


    unsigned int do_break_line = 0;

    for (unsigned long i = 0; i < size; i++)
    {
        rgb pixel = img->pixels[i];
        unsigned int avg = (pixel.r + pixel.g + pixel.b) / 3;
        
        if(avg < 85)
        {
            printf(" ");
        } 
        else if(avg > 85 && avg < 170)
        {
            printf("·");
        }
        else
        {
            printf("#");
        }
        
        if(do_break_line >= img->width)
        {
            printf("\n");
            do_break_line = 0;
        } else {
            do_break_line++;
        }
    }
    
    printf("\n");

    printf("Basic image data of '%s': %dx%d resolution - %d size\n", argv[1], img->width, img->height, (img->width * 3) * img->height);

    return 0;
}