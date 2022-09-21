#include "include/bmp.h"

#include "include/image.h"

#include <stdio.h>

int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("Write input file\n");
        return -1;
    }

    BMP_DATA* bmp_data = bmp_read_data(argv[1]);

    IMAGE* raw_img = bmp_data_to_image(bmp_data);

    IMAGE* img = image_invert(raw_img);

    image_to_char_file(img, "output.txt");

    printf("Basic image data of '%s': %dx%d resolution - %d size\n", argv[1], img->header.width, img->header.height, (img->header.width * 3) * img->header.height);

    return 0;
}