#include "include/quick.h"

#include "include/bitmap.h"
#include "include/image.h"
#include "include/string-util.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void convert(const char* input, const char* output, char* color_palete)
{
    FILE* bmp_fd = fopen(input, "rb");
    
    BITMAP bmp;

    bitmap_decode(bmp_fd, &bmp);

    fclose(bmp_fd);

    STRING ascii = image2ascii(bmp, color_palete != NULL ? color_palete : DEFAULT_CHAR_PALETTE);

    FILE* result_fd = fopen(output, "w");

    fwrite(ascii.data, sizeof(char), ascii.length, result_fd);

    fclose(result_fd);

    free(bmp.pixels);
    free(ascii.data);

    return;
}

void* convert_multiple(void* __data)
{
    CONVERT_MULTIPLE_ARGS* data = (CONVERT_MULTIPLE_ARGS*) __data;

    for (uint32_t i = data->from; i < data->to; i++)
    {
        /* code */
    }
    

    return NULL;
}