/*
this write file: rgb.bin (realy the extension is what you like, dosen't matter)
and after use test_rgb_bin2txt.c for load and do the last conversion
*/

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



int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Write input file\n");
        return -1;
    }

    FILE* input_image = fopen(argv[1], "rb");

    char info[54] = { 0 }; // char is 8 bit int in C

    fread(info, 1, 54, input_image); // where is 1 i can write sizeof(char) because equals to 1 or sizeof(info[0]) is the same as sizeof(char)

    int width = *(int*) (info + 18);
    int height = *(int*) (info + 22);
    int bitcount = *(int*) (info + 28);
    int size = (width * height) * 3;

    if(bitcount != 24)
    {
        printf("Only 24 bitcount / 8 bit suported, please use bgr24");
        return 1;
    }

    printf("Basic image data of '%s': %dx%d resolution @ %d bitcount (%d per pixel) - %d size\n", argv[1], width, height, bitcount, bitcount / 3, size);

    unsigned char* data = (unsigned char*) malloc(size);

    fread(data, 1, size, input_image);

    FILE* result = fopen("output.txt", "w");

    for(int row = height - 1; row >= 0; row--) // the rows is reverse or something ¿? mind break
    {
        // reverse chunk colum
        for(int col = 0; col < width; col++)
        {
            long pos = ((row * width) + col) * 3;
            
            /*
            bmp work with BGR in this case only i know the order to do BGR 2 RGB, easy:
            
            B G R
            0 1 2
            ----- <- conversion
            R G B
            2 1 0

            but in this case cause is struct i can put how i like and read easy
            */

            unsigned int b = data[pos];
            unsigned int g = data[pos + 1];
            unsigned int r = data[pos + 2];

            unsigned int avg = (r + g + b) / 3;


            if(avg < 85)
            {
                fwrite(" ", sizeof(char), 1, result);
            } 
            else if(avg > 85 && avg < 170)
            {
                fwrite("/", sizeof(char), 1, result);
            }
            else
            {
                fwrite("#", sizeof(char), 1, result);
            }
        }
        fwrite("\n", sizeof(char), 1, result);
    }

    fclose(result);

    fclose(input_image);

    return 0;
}