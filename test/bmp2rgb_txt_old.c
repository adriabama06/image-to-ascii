/*
this write file: rgb.bin (realy the extension is what you like, dosen't matter)
and after use test_rgb_bin2txt.c for load and do the last conversion
*/

#include <stdio.h>
#include <stdlib.h>

struct bitmap_header{
    unsigned short signature_B;
    unsigned long FileSize;
    unsigned long reserved;
    unsigned long DataOffset;

    unsigned long Width;
    unsigned long Height;
    unsigned short Planes;
    unsigned short Bits_Per_Pixel;
    unsigned long Compression;
    unsigned long ImageSize;
    unsigned long XpixelsPerM;
    unsigned long YpixelsPerM;
    unsigned long Colors_Used;
    unsigned long Important_Colors;
};

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Write input file\n");
        return -1;
    }

    FILE* input_image = fopen("image_files\\renai_circulation_360p.bmp", "rb");

/*

    char info[54] = { 0 }; // char is 8 bit int in C

    fread(info, 1, 54, input_image); // where is 1 i can write sizeof(char) because equals to 1 or sizeof(info[0]) is the same as sizeof(char)

    int offset = *(int*) (info + 17);
    int width = *(int*) (info + 18);
    int height = *(int*) (info + 22);
    int bitcount = *(int*) (info + 28);
    int size = (width * height) * 3;
*/

    unsigned short signature;
    unsigned long FileSize;
    unsigned long reserved;
    unsigned long DataOffset;

    unsigned long Size;
    unsigned long Width;
    unsigned long Height;
    unsigned short Planes;
    unsigned short Bits_Per_Pixel;
    unsigned long Compression;
    unsigned long ImageSize;
    unsigned long XpixelsPerM;
    unsigned long YpixelsPerM;
    unsigned long Colors_Used;
    unsigned long Important_Colors;

    fread(&signature, 1, 2, input_image);
    fread(&FileSize, 1, 4, input_image);
    fread(&reserved, 1, 4, input_image);
    fread(&DataOffset, 1, 4, input_image);
    fread(&Size, 1, 4, input_image);
    fread(&Width, 1, 4, input_image);
    fread(&Height, 1, 4, input_image);

    int padding = Width - ((Width/4)*4);


    int bitcount = 24;
    int size = (Width * Height * 3) + (padding * Height);

    printf("%d offset\n", 0);

    
    if(bitcount != 24)
    {
        printf("Only 24 bitcount / 8 bit suported, please use bgr24");
        return 1;
    }

    //printf("Basic image data of '%s': %dx%d resolution @ %d bitcount (%d per pixel) - %d size\n", argv[1], width, height, bitcount, bitcount / 3, size);

    unsigned char* data = (unsigned char*) malloc(size);

    fseek(input_image, DataOffset, SEEK_SET);
    long len = fread(data, 1, size, input_image);

    printf("%ld len , %d size\n", len, size);


    FILE* result = fopen("output.txt", "w");

    int x = 0;
    int w = 0;

    for ( int i = 0; i < size; i++ )
    {

        w++;

        if ( w <= Width ){

            unsigned int b = data[i++];
            unsigned int g = data[i++];
            unsigned int r = data[i];
            
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
        else {
            fwrite("\n", sizeof(char), 1, result);
            i += padding-1;
            w = 0;
        }
    }
    
    /*for ( int i = 0; i < size; i++ )
    {
        unsigned int b = data[i++];
        unsigned int g = data[i++];
        unsigned int r = data[i];

        unsigned int avg = (r + g + b) / 3;

        if(w > Width)

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
        if (w >= Width + padding){
            fwrite("\n", sizeof(char), 1, result);
            w = -1;
        }
        w++;
    }*/

    /*for(int row = Height - 1; row >= 0; row--) // the rows is reverse or something ¿? mind break
    {
        // reverse chunk colum
        for(int col = 0; col < Width+padding; col++)
        {
            if(col > Width)
            {
                continue;
            }
            long pos = ((row * Width) + col) * 3;
            
            /*
            bmp work with BGR in this case only i know the order to do BGR 2 RGB, easy:
            
            B G R
            0 1 2
            ----- <- conversion
            R G B
            2 1 0

            but in this case cause is struct i can put how i like and read easy
            *//*

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
    }*/

    fclose(result);

    fclose(input_image);

    return 0;
}