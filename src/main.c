#include <stdio.h>
#include <stdlib.h>

#include "include/bitmap.h"
#include "include/image.h"
#include "include/fs.h"
#include "include/threads.h"
#include "include/player.h"
#include "include/time.h"

int old_main(int argc, char** argv)
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
    */
    
    // clear memory dynamically created
    free(bmp.pixels);

    return 0;
}

int main(int argc, const char** argv)
{
    PLAYER_ARGS args;

    args.base_path = string_from("../txtframes/");

    args.files = search_files_by_suffix("../txtframes/", ".txt");

    sort_by_aplhabet(args.files);

    args.framerate_ns = 1000000 / 30;

    args.frames.strings = NULL;
    args.frames.length = args.files.length;

    args.dynamically_convert = 1;

    args.color_palete = NULL;

    player(args);

    return 0;
}

int main_sleep(int argc, const char** argv)
{
    int sec_to_sleep = atoi(argv[1]);

    SYSTEM_TIME t;

    t.tv_usec = 0;
    t.tv_sec = sec_to_sleep;

    nanosleep(&t, &t);

    return 0;
}