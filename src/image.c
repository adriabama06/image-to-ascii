#include "include/image.h"

#include "include/bitmap.h"

#include <stdlib.h>
#include <string.h> 

CHAR_ARRAY image2ascii(BITMAP bmp, char* char_palette)
{
    uint32_t color_palette_length = strlen(char_palette);

    uint32_t size = bmp.header.width * bmp.header.height;

    CHAR_ARRAY ascii;

    ascii.length = 0;
    // size + bmp.header.height -> one extra vertical line for \n char
    ascii.data = (char*) malloc((size + bmp.header.height) * sizeof(char));


    uint32_t width_count = 0;

    for (uint32_t i = 0; i <= size; ascii.length++)
    {
        width_count++;

        if (width_count <= bmp.header.width)
        {
            RGB pixel = bmp.pixels[i++];

            uint8_t avg = (pixel.r + pixel.g + pixel.b) / 3;

            float __color_select = ((float) avg / 255.0f);

            uint8_t color_select = __color_select * color_palette_length;

            if(color_select >= color_palette_length) {
	            color_select = color_palette_length - 1;
            }

            ascii.data[ascii.length] = char_palette[color_select];
        }
        else
        {
            ascii.data[ascii.length] = '\n';
            width_count = 0;
        }
    }

    ascii.data[ascii.length-- - 1] = '\0';

    return ascii;
}
