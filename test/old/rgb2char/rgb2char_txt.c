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


    unsigned int do_break_line = 0U;

    FILE* file_to_write = fopen("output.txt", "w");

    for (unsigned long long i = 0; i < size; i++)
    {
        rgb pixel = img->pixels[i];
        unsigned int avg = (pixel.r + pixel.g + pixel.b) / 3U;
        
        if(avg < 85U)
        {
            fprintf(file_to_write, " ");
        } 
        else if(avg > 85U && avg < 170U)
        {
            fprintf(file_to_write, "·");
        }
        else
        {
            fprintf(file_to_write, "#");
        }
        
        if(do_break_line + 1U == img->width)
        {
            fprintf(file_to_write, "\n");
            do_break_line = 0U;
        } else {
            do_break_line++;
        }
    }

    fclose(file_to_write);
    
    printf("Basic image data of '%s': %dx%d resolution - %d size - %d size + rgb\n", argv[1], img->width, img->height, size, (img->width * 3) * img->height);

    return 0;
}