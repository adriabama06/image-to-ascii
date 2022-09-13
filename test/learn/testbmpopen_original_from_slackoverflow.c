#include <stdio.h>
#include <stdlib.h>

int main()
{
    int width, height, padding, bitcount, size;
    unsigned char *data = 0;
    unsigned char info[54] = { 0 };
    FILE *file = fopen("basic_test.bmp", "rb");
    if(!file) {
        return 1;
    }

    fread(info, 1, 54, file); // why 1 is because 1 = sizeof(unsigned char)
    width = *(int*)(info + 18);
    height = *(int*)(info + 22);
    bitcount = *(int*)(info + 28);
    size = ((width * bitcount + 31) / 32) * 4 * height;
    padding = width % 4;

    if(bitcount != 24) {//this code works for 24-bit bitmap only
        printf("Error");
        if(file) fclose(file);
        if(data) free(data);
        return 2;
    }

    data = (unsigned char*) malloc(size);
    fread(data, 1, size, file);

    FILE* result = fopen("test.txt", "w");

    for(int row = height - 1; row >= 0; row--)
    {
        for(int col = 0; col < width; col++)
        {
            int p = (row * width + col) * 3 + row * padding;
            fprintf(result, "%02X%02X%02X ", data[p + 0], data[p + 1], data[p + 2]);
        }
        fprintf(result, "\n");
    }
    printf("Ok");

    if(file) fclose(file);
    if(data) free(data);
    return 0;
}
