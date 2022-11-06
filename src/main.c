#include <stdio.h>
#include <stdlib.h>

#include "include/bitmap.h"
#include "include/image.h"
#include "include/threads.h"

int main(int argc, char** argv)
{
    FILE* bmp_fp = fopen(argv[1], "rb");

    BITMAP bmp;

    int error = bitmap_decode(bmp_fp, &bmp);

    fclose(bmp_fp);

    printf("%c%c == BM ?\n", bmp.header.signature[0], bmp.header.signature[1]);
    printf("%dx%d\n", bmp.header.height, bmp.header.width);


    printf("RGB(%d, %d, %d)\n", bmp.pixels[0].r, bmp.pixels[0].g, bmp.pixels[0].b);

    CHAR_ARRAY ascii = image2ascii(bmp, argv[3] != NULL ? argv[3] : DEFAULT_CHAR_PALETTE);

    printf("%d\n", ascii.length);
    
    FILE* result_fd = fopen(argv[2], "w");

    fwrite(ascii.data, sizeof(char), ascii.length, result_fd);

    /*
    BM == BM ?
    360x640
    RGB(228, 224, 225)
    */
    
    // clear memory dynamically created
    free(bmp.pixels);

    return 0;
}