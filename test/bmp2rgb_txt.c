/*
this write file: rgb.bin (realy the extension is what you like, dosen't matter)
and after use test_rgb_bin2txt.c for load and do the last conversion
*/

// http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
// for know the bmp header

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

typedef struct BMP_HEADER_STRUCT {
    uint32_t filesize;
    uint32_t reserved;
    uint32_t dataoffset;

    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t imagesize;
    uint32_t y_pixels_per_m;
    uint32_t x_pixels_per_m;
    uint32_t colors_used;
    uint32_t important_colors;

    uint8_t signature[2];
} BMP_HEADER;

typedef struct rgb_struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb;


typedef struct image_struct
{
    BMP_HEADER header;
    rgb* pixels;
} image;

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

    uint8_t* raw_pixel_data = (uint8_t*) malloc(header.imagesize);

    fread(raw_pixel_data, 1, header.imagesize, input_image);

    fclose(input_image);

    image* img = (image*) malloc(sizeof(image));

    img->header = header;

    img->pixels = (rgb*) malloc((header.width * header.height) * sizeof(rgb));

    uint32_t padding = header.width - ((header.width / 4) * 4);

    uint32_t width_count = 0;

    uint32_t normal_count = 0;

    for (uint32_t i = 0; i < header.imagesize;)
    {
        width_count++;

        if(width_count <= header.width) // this is like the second loop in the first loop
        {
            rgb pixel;

            pixel.b = raw_pixel_data[i++];
            pixel.g = raw_pixel_data[i++];
            pixel.r = raw_pixel_data[i++];

            img->pixels[normal_count++] = pixel;
        }
        else
        {
            i += padding;
            width_count = 0;
        }
    }

    FILE* result = fopen("output.txt", "w");

    for(int32_t row = header.height - 1; row >= 0; row--)
    {
        for(uint32_t col = 0; col < header.width; col++)
        {
            uint32_t pos = (row * header.width) + col;

            rgb pixel = img->pixels[pos];

            uint8_t avg = (pixel.r + pixel.g + pixel.b) / 3;
            
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

    return 0;
}
