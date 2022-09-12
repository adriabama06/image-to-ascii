/*
file.bmp
First 54 bytes is for data of the image like resolution, color depth, etc...
byte 18 is for width in signed int
byte 22 is for height in signed int
byte 28 is for bitcount (color depth * color channel) (in my case i got 24 because is 8 bit * R G B like : (8*3 = 24))
for get the size for malloc do: ((width * bitcount + 31) / 32) * 4 * height; or using my calc: (width * 3) * height
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printColor(unsigned char* data, int pos, int color_order)
{
    switch (color_order)
    {
    case 0:
        printf("rgb(%d, %d, %d)\n", data[pos+2], data[pos+1], data[pos]);
        break;
    
    case 1:
        printf("gbr(%d, %d, %d)\n", data[pos+1], data[pos], data[pos+2]);
        break;
    
    case 2:
        printf("bgr(%d, %d, %d)\n", data[pos], data[pos+1], data[pos+2]);
        break;
    
    default:
        printf("Bad color order selected, rgb/gbr/bgr");
        exit(-2);
        break;
    }
}

int main(int argc, const char *argv[])
{
    if(argc <= 1)
    {
        printf("Write input file\n");
        return -1;
    }

    int input_color_order = 0; // 0 rgb, 1 gbr, 2 bgr

    if(argc > 2)
    {
        if(strcmp(argv[2], "gbr"))
        {
            input_color_order = 1;
        }
        if(strcmp(argv[2], "bgr"))
        {
            input_color_order = 2;
        }
    }

    FILE* file = fopen(argv[1], "rb");

    char info[54] = { 0 }; // char is 8 bit int in C

    fread(info, 1, 54, file); // where is 1 i can write sizeof(char) because equals to 1 or sizeof(info[0]) is the same as sizeof(char)

    int width = *(int*) (info + 18);
    int height = *(int*) (info + 22);
    int bitcount = *(int*) (info + 28);
    int size = (width * 3) * height;

    unsigned char* data = (unsigned char*) malloc(size);

    fread(data, 1, size, file);

    for(int row = height - 1; row >= 0; row--) // the rows is reverse or something ¿? mind break
    {
        printf("Start Row :\n");
        for(int col = 0; col < width; col++)
        {
            int pos = ((row * width) + col) * 3;
            printColor(data, pos, input_color_order);
        }
        printf(": End Row\n");
    }

    printf("%d x %d @ %d - - %d\n", width, height, bitcount, size);

    return 0;
}