#include <stdlib.h>

#include "include/bitmap.h"

RGB* parse_raw_pixels(uint8_t* raw_pixels, BITMAP_HEADER_FILE header)
{
    RGB* pixels = (RGB*) malloc((header.width * header.height) * sizeof(RGB));

    uint32_t padding = header.width - ((header.width / 4) * 4);

    uint32_t width_count = 0;
    uint32_t normal_count = 0;

    for (uint32_t i = 0; i < header.imagesize;)
    {
        width_count++;

        if(width_count <= header.width) // while is not the end of width, do this
        {
            RGB pixel;

            pixel.b = raw_pixels[i++];
            pixel.g = raw_pixels[i++];
            pixel.r = raw_pixels[i++];
            
            pixels[normal_count++] = pixel;
        }
        else // in other case move i to skip padding and reset the width count
        {
            i += padding;
            width_count = 0;
        }
    }

    return pixels;
}

RGB* flip_horizontally(RGB* pixels, BITMAP_HEADER_FILE header)
{
    RGB* flip_pixels = (RGB*) malloc((header.width * header.height) * sizeof(RGB));

    uint32_t normal_count = 0;

    for(int32_t row = header.height - 1; row >= 0; row--)
    {
        for(uint32_t col = 0; col < header.width; col++)
        {
            uint32_t pos = (row * header.width) + col;

            RGB pixel = pixels[pos];
            
            flip_pixels[normal_count++] = pixel;
        }
    }

    return flip_pixels;
}

// if return value is > 0 has errors 
int bitmap_decode(FILE* bmp_file_fp, BITMAP* bmp)
{
    /*
    For best performance i don't disable padding, see "test/padding.c"
    */

    fseek(bmp_file_fp, 0, SEEK_SET); // go to the start

    fread(&bmp->header.signature, 1, 2, bmp_file_fp); // copy only the signature

    // you already at bite 2 in the file fseek(bmp_file_fd, 2, SEEK_SET); // skip signature

    fread(&bmp->header, 1, 52, bmp_file_fp); // copy header

    if(bmp->header.signature[0] != 'B' || bmp->header.signature[1] != 'M')
    {
        return 1;
    }

    if(bmp->header.bits_per_pixel != 24)
    {
        return 2;
    }

    fseek(bmp_file_fp, bmp->header.dataoffset, SEEK_SET);

    // copy to memory rest of the file
    uint8_t* raw_pixels = (uint8_t*) malloc(bmp->header.imagesize * sizeof(uint8_t));
    fread(raw_pixels, 1, bmp->header.imagesize, bmp_file_fp);
 
    // parse pixels
    /*
    3 pixels ->
    data = [b, g, r,   b, g ,r,   b, g, r]

    as pixels RGB struct
    pixel1.b = data[0]
    pixel1.g = data[1]
    pixel1.r = data[2]

    pixel2.b = data[0]
    pixel2.g = data[1]
    pixel2.r = data[2]

    pixel3.b = data[0]
    pixel3.g = data[1]
    pixel3.r = data[2]
    */
    RGB* tmp_pixels = parse_raw_pixels(raw_pixels, bmp->header);

    // then flip the image
    bmp->pixels = flip_horizontally(tmp_pixels, bmp->header);

    // clear memory
    free(raw_pixels);
    free(tmp_pixels);

    return 0;
}