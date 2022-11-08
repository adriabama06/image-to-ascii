#include <stdio.h>
#include <stdlib.h>

#include "include/bitmap.h"
#include "include/image.h"
#include "include/fs.h"
#include "include/threads.h"

/*int nomain(int argc, char** argv)
{
    FILE* bmp_fp = fopen(argv[1], "rb");

    BITMAP bmp;

    int error = bitmap_decode(bmp_fp, &bmp);

    fclose(bmp_fp);

    printf("%c%c == BM ?\n", bmp.header.signature[0], bmp.header.signature[1]);
    printf("%dx%d\n", bmp.header.height, bmp.header.width);


    printf("RGB(%d, %d, %d)\n", bmp.pixels[0].r, bmp.pixels[0].g, bmp.pixels[0].b);

    STRING ascii = image2ascii(bmp, argv[3] != NULL ? argv[3] : DEFAULT_CHAR_PALETTE);

    printf("%d\n", ascii.length);
    
    FILE* result_fd = fopen(argv[2], "w");

    fwrite(ascii.data, sizeof(char), ascii.length, result_fd);

    /*
    BM == BM ?
    360x640
    RGB(228, 224, 225)
    * /
    
    // clear memory dynamically created
    free(bmp.pixels);

    return 0;
}*/

int main(int argc, const char** argv)
{
    const char* scandir = argv[1];
    const char* extension = argv[2];

    if(!existDir((char*) scandir))
    {
        printf("Dir \"%s\" does not exist\n", scandir);
        return 1;
    }

    STRING_ARRAY files = search_files_by_suffix(scandir, (char*) extension);

    printf("%d:\n", files.length);

    for (uint32_t i = 0; i < files.length; i++)
    {
        printf("  %d -> %s (%d)\n", i, files.strings[i].data, files.strings[i].length);
    
        free(files.strings[i].data);
    }

    free(files.strings);

    return 0;
}