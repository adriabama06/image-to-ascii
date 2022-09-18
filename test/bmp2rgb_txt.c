/*
this write file: rgb.bin (realy the extension is what you like, dosen't matter)
and after use test_rgb_bin2txt.c for load and do the last conversion
*/

// http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
// for know the bmp header

#include <stdio.h>
#include <stdlib.h>

typedef struct BMP_HEADER_STRUCT {
    unsigned long filesize;
    unsigned long reserved;
    unsigned long dataoffset;

    unsigned long size;
    unsigned long width;
    unsigned long height;
    unsigned short planes;
    unsigned short bits_per_pixel;
    unsigned long compression;
    unsigned long imagesize;
    unsigned long y_pixels_per_m;
    unsigned long x_pixels_per_m;
    unsigned long colors_used;
    unsigned long important_colors;

    unsigned char signature[2];
} BMP_HEADER;

int main(int argc, const char *argv[])
{
    FILE* input_image = fopen("image_files\\renai_circulation_random_res.bmp", "rb");

    if(input_image == NULL)
    {
        printf("Error opening file\n");
        return 2;
    }

    // sizeof(BMP_HEADER); -> 56 <- only for know why i don't use sizeof for load header in fread

    BMP_HEADER header;
    
    fseek(input_image, 2, SEEK_SET);

    fread(&header, 1, 52, input_image);

    fseek(input_image, 0, SEEK_SET);

    fread(&header.signature, 1, 2, input_image);

    fseek(input_image, header.dataoffset, SEEK_SET);

    if(header.bits_per_pixel != 24)
    {
        printf("Only 24 bitcount / 8 bit suported, please use bgr24\n");
        return 1;
    }

    unsigned char* pixel_data = (unsigned char*) malloc(header.imagesize);

    fread(pixel_data, 1, header.imagesize, input_image);

    fclose(input_image);

    FILE* result = fopen("output.txt", "w");

    unsigned long padding = header.width - ((header.width / 4) * 4);

    unsigned long width_count = 0;

    for (unsigned long i = 0; i < header.imagesize;)
    {
        width_count++;

        if(width_count <= header.width)
        {
            unsigned int b = pixel_data[i++];
            unsigned int g = pixel_data[i++];
            unsigned int r = pixel_data[i++];

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
        else
        {
            fwrite("\n", sizeof(char), 1, result);
            i += padding; // cause after we do i++ how is defined in the for loop at 3rd argument
            width_count = 0;
        }
    }
    

    fclose(result);

    return 0;
}