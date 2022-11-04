// #pragma pack(1) // prevent padding at all structs

#include <stdio.h>
#include <stdint.h>

typedef struct
__attribute__((__packed__)) // prevent padding, try comment and un comment this line for see changes in the output
{
    uint8_t signature[2]; // 2 bytes


    uint32_t filesize; // 4 bytes
    uint32_t reserved; // 4 bytes
    uint32_t dataoffset; // 4 bytes
    // <-- 14 bytes


    uint32_t size; // 4 bytes
    uint32_t width; // 4 bytes
    uint32_t height; // 4 bytes
    uint16_t planes; // 2 bytes
    uint16_t bits_per_pixel; // 2 bytes
    uint32_t compression; // 4 bytes
    uint32_t imagesize; // 4 bytes
    uint32_t y_pixels_per_m; // 4 bytes
    uint32_t x_pixels_per_m; // 4 bytes
    uint32_t colors_used; // 4 bytes
    uint32_t important_colors; // 4 bytes
    // <-- 40 bytes

    // 14 + 40 = 54 ? but sizeof(BITMAP_HEADER_FILE) == 56 <-- if padding is enabled add 2 byte at start for aligment
} BITMAP_HEADER_FILE;

int main()
{
    BITMAP_HEADER_FILE mystruct;

    printf("sizeof(mystruct) = %d\n", sizeof(mystruct));

    return 0;
}